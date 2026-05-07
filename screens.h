#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Screens

enum ScreensEnum {
    _SCREEN_ID_FIRST = 1,
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_BOTONES = 2,
    SCREEN_ID_BOTON_TEMP = 3,
    SCREEN_ID_BOTON_CALENDARIO = 4,
    SCREEN_ID_BOTON_CONTROL = 5,
    SCREEN_ID_ALIVIO_GUIADO = 6,
    SCREEN_ID_INFORMACION_DATOS = 7,
    _SCREEN_ID_LAST = 7
};

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *botones;
    lv_obj_t *boton_temp;
    lv_obj_t *boton_calendario;
    lv_obj_t *boton_control;
    lv_obj_t *alivio_guiado;
    lv_obj_t *informacion_datos;
    lv_obj_t *obj0;
    lv_obj_t *obj1;
    lv_obj_t *obj2;
    lv_obj_t *obj3;
    lv_obj_t *obj4;
    lv_obj_t *obj5;
    lv_obj_t *obj6;
    lv_obj_t *obj7;
    lv_obj_t *obj8;
    lv_obj_t *obj9;
    lv_obj_t *obj10;
    lv_obj_t *obj11;
    lv_obj_t *obj12;
    lv_obj_t *obj13;
    lv_obj_t *obj14;
    lv_obj_t *obj15;
    lv_obj_t *obj16;
    lv_obj_t *obj17;
    lv_obj_t *obj18;
    lv_obj_t *obj19;
    lv_obj_t *obj20;
    lv_obj_t *obj21;
    lv_obj_t *obj22;
    lv_obj_t *obj23;
    lv_obj_t *obj24;
    lv_obj_t *obj25;
    lv_obj_t *au_temp;
    lv_obj_t *dis_temp;
    lv_obj_t *obj26;
} objects_t;

extern objects_t objects;

void create_screen_main();
void tick_screen_main();

void create_screen_botones();
void tick_screen_botones();

void create_screen_boton_temp();
void tick_screen_boton_temp();

void create_screen_boton_calendario();
void tick_screen_boton_calendario();

void create_screen_boton_control();
void tick_screen_boton_control();

void create_screen_alivio_guiado();
void tick_screen_alivio_guiado();

void create_screen_informacion_datos();
void tick_screen_informacion_datos();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/