#include "creatsymbol.h"
#include <lvgl/lvgl.h>

lv_obj_t* label_time;
lv_obj_t* label_date;
lv_obj_t* batteryIcon;
lv_obj_t* bleIcon;
lv_obj_t* batteryPlug;

void creatSymbol(){
  batteryIcon = lv_label_create(lv_scr_act(),NULL);
  batteryPlug = lv_label_create(lv_scr_act(), NULL);
  bleIcon = lv_label_create(lv_scr_act(), NULL);
  label_time = lv_label_create(lv_scr_act(), NULL);
}