#include "vars.h"
#include "actions.h"
#include "screens.h"
#include "lvgl.h"
#include <time.h>
#include <stdio.h>

extern "C" {

// Variables nativas
int32_t anio_inicio = 2025;
int32_t mes_inicio = 0;
int32_t dia_inicio = 0;
int32_t duracion_periodo = 5;
int32_t duracion_ciclo = 28;

// Get y Set
int32_t get_var_anio_inicio() { return anio_inicio; }
void set_var_anio_inicio(int32_t value) { anio_inicio = value; }

int32_t get_var_mes_inicio() { return mes_inicio; }
void set_var_mes_inicio(int32_t value) { mes_inicio = value; }

int32_t get_var_dia_inicio() { return dia_inicio; }
void set_var_dia_inicio(int32_t value) { dia_inicio = value; }

int32_t get_var_duracion_periodo() { return duracion_periodo; }
void set_var_duracion_periodo(int32_t value) { duracion_periodo = value; }

int32_t get_var_duracion_ciclo() { return duracion_ciclo; }
void set_var_duracion_ciclo(int32_t value) { duracion_ciclo = value; }

void action_calcular_ciclo(lv_event_t *e) {
    struct tm t = {0};
    t.tm_year = anio_inicio - 1900;
    t.tm_mon  = mes_inicio - 1;
    t.tm_mday = dia_inicio;
    t.tm_hour = 12;

    time_t t0 = mktime(&t);

    static char texto_fin[40];
    time_t t_fin = t0 + (duracion_periodo * 86400);
    struct tm *tf = localtime(&t_fin);
    snprintf(texto_fin, sizeof(texto_fin),
             "Fin estimado: %02d/%02d/%04d",
             tf->tm_mday,
             tf->tm_mon + 1,
             tf->tm_year + 1900);
    lv_label_set_text(objects.lbl_fin, texto_fin);

    static char texto_prox[40];
    time_t t_prox = t0 + (duracion_ciclo * 86400);
    struct tm *tp = localtime(&t_prox);
    snprintf(texto_prox, sizeof(texto_prox),
             "Proximo ciclo: %02d/%02d/%04d",
             tp->tm_mday,
             tp->tm_mon + 1,
             tp->tm_year + 1900);
    lv_label_set_text(objects.lbl_proximo, texto_prox);

    static lv_calendar_date_t resaltados[10];
    for (int i = 0; i < duracion_periodo; i++) {
        time_t td = t0 + (i * 86400);
        struct tm *d = localtime(&td);
        resaltados[i].year  = d->tm_year + 1900;
        resaltados[i].month = d->tm_mon + 1;
        resaltados[i].day   = d->tm_mday;
    }
    lv_calendar_set_highlighted_dates(
        objects.cal_inicio,
        resaltados,
        duracion_periodo
    );
}

} // extern "C"