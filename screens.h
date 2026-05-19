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
    SCREEN_ID_ALIVIO_GUIADO = 2,
    SCREEN_ID_BOTON_CONTROL = 3,
    SCREEN_ID_CAL_INICIO12 = 4,
    SCREEN_ID_BOTONES = 5,
    SCREEN_ID_INFORMACION_DATOS = 6,
    SCREEN_ID_GUIA_RESPIRACION = 7,
    SCREEN_ID_MOVIMIENTO = 8,
    SCREEN_ID_HABITOS = 9,
    _SCREEN_ID_LAST = 9
};

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *alivio_guiado;
    lv_obj_t *boton_control;
    lv_obj_t *cal_inicio12;
    lv_obj_t *botones;
    lv_obj_t *informacion_datos;
    lv_obj_t *guia_respiracion;
    lv_obj_t *movimiento;
    lv_obj_t *habitos;
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
    lv_obj_t *au_temp;
    lv_obj_t *dis_temp;
    lv_obj_t *obj15;
    lv_obj_t *obj16;
    lv_obj_t *obj17;
    lv_obj_t *cal_inicio;
    lv_obj_t *lbl_estado;
    lv_obj_t *lbl_fin;
    lv_obj_t *lbl_proximo;
    lv_obj_t *obj18;
    lv_obj_t *obj19;
    lv_obj_t *obj20;
    lv_obj_t *obj21;
    lv_obj_t *obj22;
    lv_obj_t *obj23;
    lv_obj_t *obj24;
    lv_obj_t *obj25;
    lv_obj_t *obj26;
    lv_obj_t *obj27;
    lv_obj_t *obj28;
    lv_obj_t *obj29;
    lv_obj_t *obj30;
    lv_obj_t *obj31;
    lv_obj_t *obj32;
    lv_obj_t *obj33;
    lv_obj_t *obj34;
    lv_obj_t *obj35;
    lv_obj_t *obj36;
    lv_obj_t *obj37;
    lv_obj_t *obj38;
    lv_obj_t *obj39;
    lv_obj_t *obj40;
    lv_obj_t *obj41;
    lv_obj_t *obj42;
    lv_obj_t *obj43;
    lv_obj_t *obj44;
    lv_obj_t *obj45;
    lv_obj_t *obj46;
    lv_obj_t *obj47;
    lv_obj_t *obj48;
    lv_obj_t *obj49;
    lv_obj_t *obj50;
    lv_obj_t *obj51;
    lv_obj_t *obj52;
    lv_obj_t *obj53;
    lv_obj_t *obj54;
    lv_obj_t *obj55;
    lv_obj_t *obj56;
    lv_obj_t *obj57;
    lv_obj_t *obj58;
    lv_obj_t *obj59;
    lv_obj_t *obj60;
    lv_obj_t *obj61;
    lv_obj_t *obj62;
    lv_obj_t *obj63;
    lv_obj_t *obj64;
    lv_obj_t *obj65;
    lv_obj_t *obj66;
    lv_obj_t *obj67;
} objects_t;

extern objects_t objects;

void create_screen_main();
void tick_screen_main();

void create_screen_alivio_guiado();
void tick_screen_alivio_guiado();

void create_screen_boton_control();
void tick_screen_boton_control();

void create_screen_cal_inicio12();
void tick_screen_cal_inicio12();

void create_screen_botones();
void tick_screen_botones();

void create_screen_informacion_datos();
void tick_screen_informacion_datos();

void create_screen_guia_respiracion();
void tick_screen_guia_respiracion();

void create_screen_movimiento();
void tick_screen_movimiento();

void create_screen_habitos();
void tick_screen_habitos();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/