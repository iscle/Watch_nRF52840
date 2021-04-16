#include <libs/lvgl/lvgl.h>
#include "HeartRate.h"
#include "../DisplayApp.h"

using namespace Watch::Applications::Screens;
extern lv_font_t San_Francisco_50;
extern lv_font_t San_Francisco_18;

HeartRate::HeartRate(Watch::Applications::DisplayApp *app) : Screen(app) {
  label_bpm = lv_label_create(lv_scr_act(), NULL);

  labelStyle = const_cast<lv_style_t *>(lv_label_get_style(label_bpm, LV_LABEL_STYLE_MAIN));
  labelStyle->text.font = &San_Francisco_18;

  lv_style_copy(&labelBigStyle, labelStyle);
  labelBigStyle.text.font = &San_Francisco_50;

  lv_label_set_style(label_bpm, LV_LABEL_STYLE_MAIN, labelStyle);

  label_hr = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_style(label_hr, LV_LABEL_STYLE_MAIN, &labelBigStyle);
  lv_obj_align(label_hr, lv_scr_act(), LV_ALIGN_CENTER, -70, 0);
  lv_label_set_text(label_hr, "000");

  lv_label_set_text(label_bpm, "Heart rate BPM");
  lv_obj_align(label_bpm, label_hr, LV_ALIGN_OUT_TOP_MID, 0, -20);


  label_status = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_style(label_status, LV_LABEL_STYLE_MAIN, labelStyle);
  lv_obj_align(label_status, label_hr, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);

}

HeartRate::~HeartRate() {
  lv_obj_clean(lv_scr_act());
}

bool HeartRate::Refresh() {
  char hr[4];
      sprintf(hr, "%03d", heartRateSensor.ReadHrs());
      lv_label_set_text(label_hr, hr);
  
  lv_obj_align(label_status, label_hr, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);

  return running;
}

bool HeartRate::OnButtonPushed() {
  running = false;
  return true;
}
