#pragma once
#include <lvgl/src/lv_core/lv_obj.h>

extern lv_obj_t* label_time;
extern lv_obj_t* label_date;
extern lv_obj_t* batteryIcon;
extern lv_obj_t* bleIcon;
extern lv_obj_t* batteryPlug;
#ifdef __cplusplus
  extern "C" {
#endif
void creatSymbol(void);

#ifdef __cplusplus
  }
#endif