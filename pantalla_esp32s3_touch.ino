#include <lvgl.h>
#include "Arduino_GFX_Library.h"
#include "lv_conf.h"
#include "HWCDC.h"
#include "TouchDrvGT911.hpp"
#include <Wire.h>
#include <SPI.h>
#include "ui.h"
#include "screens.h"

// ================= PCF8574 =================
#define PCF_ADDR 0x27
uint8_t pcf_state = 0xFF;

void pcf_write(uint8_t data) {
  Wire.beginTransmission(PCF_ADDR);
  Wire.write(data);
  Wire.endTransmission();
}

void pcf_digitalWrite(uint8_t pin, bool value) {
  if (value)
    pcf_state |= (1 << pin);
  else
    pcf_state &= ~(1 << pin);

  pcf_write(pcf_state);
}

// ================= TOUCH =================
TouchDrvGT911 GT911;
int16_t x[5], y[5];
uint8_t gt911_i2c_addr = 0;

// ================= SERIAL =================
HWCDC USBSerial;

// ================= LVGL =================
#define EXAMPLE_LVGL_TICK_PERIOD_MS 2

uint32_t screenWidth;
uint32_t screenHeight;
static lv_disp_draw_buf_t draw_buf;

// ================= BUS =================
Arduino_DataBus *bus = new Arduino_SWSPI(
  GFX_NOT_DEFINED, 42,
  2, 1, GFX_NOT_DEFINED);

// ================= PANEL =================
Arduino_ESP32RGBPanel *rgbpanel = new Arduino_ESP32RGBPanel(
  40, 39, 38, 41,
  46, 3, 8, 18, 17,
  14, 13, 12, 11, 10, 9,
  5, 45, 48, 47, 21,
  1, 10, 8, 50,
  1, 10, 8, 20);

// ================= DISPLAY =================
Arduino_RGB_Display *gfx = new Arduino_RGB_Display(
  480, 480, rgbpanel, 2, true,
  bus, GFX_NOT_DEFINED,
  st7701_type1_init_operations,
  sizeof(st7701_type1_init_operations));

// ================= FLUSH =================
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
  uint32_t w = area->x2 - area->x1 + 1;
  uint32_t h = area->y2 - area->y1 + 1;

  gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
  lv_disp_flush_ready(disp);
}

// ================= TICK =================
void lv_tick_task(void *arg) {}

// ================= TOUCH =================
void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data) {
  uint8_t touched = GT911.getPoint(x, y, GT911.getSupportTouchPoint());

  if (touched > 0) {
    data->state = LV_INDEV_STATE_PR;
    data->point.x = screenWidth - x[0];
    data->point.y = screenHeight - y[0];
  } else {
    data->state = LV_INDEV_STATE_REL;
  }
}

// ================= I2C SCAN =================
void i2c_scan() {
  for (uint8_t address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    if (Wire.endTransmission() == 0)
      if (address == GT911_SLAVE_ADDRESS_L || address == GT911_SLAVE_ADDRESS_H) {
        gt911_i2c_addr = address;
      }
  }
}

// ================= TOUCH INIT =================
bool init_gt911() {
  Wire.begin(15, 7);
  delay(100);

  i2c_scan();

  if (gt911_i2c_addr == 0) return false;

  GT911.setPins(-1, -1);
  return GT911.begin(Wire, gt911_i2c_addr, 15, 7);
}

// ================= BOTONES UI =================
void btn_off_event(lv_event_t *e) {
  pcf_digitalWrite(0, false);  //  encender
  USBSerial.println("LED ON");
}

void btn_on_event(lv_event_t *e) {
  pcf_digitalWrite(0, true);  //  apagar
  USBSerial.println("LED OFF");
}

// ================= SETUP =================
void setup() {

  USBSerial.begin(115200);

  // 🔥 I2C
  Wire.begin(15, 7);

  // 🔥 INICIALIZAR PCF8574
  pcf_write(pcf_state);

  // 🔥 CONFIG PANEL
  Wire.beginTransmission(0x24);
  Wire.write(0x02);
  Wire.write(0xff);
  Wire.endTransmission();

  Wire.beginTransmission(0x24);
  Wire.write(0x03);
  Wire.write(0x3a);
  Wire.endTransmission();

  // 🔥 BACKLIGHT
  Wire.beginTransmission(0x24);
  Wire.write(0x01);
  Wire.write(0x01);
  Wire.endTransmission();

  // ================= DISPLAY =================
  gfx->begin();
  delay(100);

  screenWidth = gfx->width();
  screenHeight = gfx->height();

  // ================= LVGL =================
  lv_init();

  lv_color_t *buf1 = (lv_color_t *)heap_caps_malloc(
    screenWidth * screenHeight / 4 * sizeof(lv_color_t), MALLOC_CAP_DMA);

  lv_color_t *buf2 = (lv_color_t *)heap_caps_malloc(
    screenWidth * screenHeight / 4 * sizeof(lv_color_t), MALLOC_CAP_DMA);

  lv_disp_draw_buf_init(&draw_buf, buf1, buf2, screenWidth * screenHeight / 4);

  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  disp_drv.sw_rotate = 1;
  lv_disp_drv_register(&disp_drv);

  // ================= TOUCH =================
  if (init_gt911()) {
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register(&indev_drv);
  } else {
    USBSerial.println("Touch no detectado (no es crítico)");
  }

  // ================= TICK =================
  const esp_timer_create_args_t tick_args = {
    .callback = &lv_tick_task,
    .name = "lvgl_tick"
  };

  esp_timer_handle_t tick_timer;
  esp_timer_create(&tick_args, &tick_timer);
  esp_timer_start_periodic(tick_timer, EXAMPLE_LVGL_TICK_PERIOD_MS * 1000);

  // ================= UI =================
  ui_init();

  lv_obj_add_event_cb(objects.au_temp, btn_on_event, LV_EVENT_CLICKED, NULL);
  lv_obj_add_event_cb(objects.dis_temp, btn_off_event, LV_EVENT_CLICKED, NULL);

  USBSerial.println("Sistema iniciado correctamente");
}

// ================= LOOP =================
void loop() {

  // LVGL
  lv_timer_handler();
  lv_tick_inc(5);
  ui_tick();

  delay(0);
}