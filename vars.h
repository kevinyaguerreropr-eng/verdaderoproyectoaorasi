#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// enum declarations

// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_NONE
};

// Native global variables

extern int32_t get_var_dia_inicio();
extern void set_var_dia_inicio(int32_t value);
extern int32_t get_var_mes_inicio();
extern void set_var_mes_inicio(int32_t value);
extern int32_t get_var_anio_inicio();
extern void set_var_anio_inicio(int32_t value);
extern int32_t get_var_duracion_periodo();
extern void set_var_duracion_periodo(int32_t value);
extern int32_t get_var_duracion_ciclo();
extern void set_var_duracion_ciclo(int32_t value);

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/