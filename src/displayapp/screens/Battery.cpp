#include "Battery.h"

#include <date/date.h>
#include <lvgl/lvgl.h>
#include <cstdio>
#include "BatteryIcon.h"
#include "BleIcon.h"
#include "NotificationIcon.h"
#include "Symbols.h"
#include "components/battery/BatteryController.h"
#include "components/ble/BleController.h"
#include "../DisplayApp.h"

using namespace Watch::Applications::Screens;
extern lv_font_t San_Francisco_22;
extern lv_font_t San_Francisco_18;
extern lv_font_t San_Francisco_Bold_18;
extern lv_font_t San_Francisco_Bold_30;

extern lv_style_t* LabelBigStyle;
extern lv_style_t* LabelSanStyle;

LV_IMG_DECLARE(lowbattery);
Battery::Battery(DisplayApp* app,
        Controllers::DateTime& dateTimeController,
        Controllers::Battery& batteryController,
        Controllers::Ble& bleController) : Screen(app), currentDateTime{{}},
                                           dateTimeController{dateTimeController}, batteryController{batteryController},
                                           bleController{bleController} {
  displayedChar[0] = 0;
  displayedChar[1] = 0;
  displayedChar[2] = 0;
  displayedChar[3] = 0;
  displayedChar[4] = 0;

  batteryIcon = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_text(batteryIcon, Symbols::batteryFull);
  lv_obj_align(batteryIcon, lv_scr_act(), LV_ALIGN_IN_TOP_RIGHT, -5, 2);

  batteryPlug = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_text(batteryPlug, Symbols::plug);
  lv_obj_align(batteryPlug, batteryIcon, LV_ALIGN_OUT_LEFT_MID, -5, 0);

  bleIcon = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_text(bleIcon, Symbols::bluetooth);
  lv_obj_align(bleIcon, batteryPlug, LV_ALIGN_OUT_LEFT_MID, -5, 0);

  label_time = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_style(label_time, LV_LABEL_STYLE_MAIN, LabelBigStyle);
  lv_obj_align(label_time, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, 0, 0);

  labelLowBattery = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_text( labelLowBattery, "LOW BATTERY");
  static lv_style_t labelStyle;
  lv_style_copy(& labelStyle, &lv_style_plain);
  labelStyle.text.font = &San_Francisco_22;
  labelStyle.text.color=LV_COLOR_RED;
  lv_label_set_style(labelLowBattery,LV_LABEL_STYLE_MAIN,&labelStyle);
  lv_obj_align(labelLowBattery, lv_scr_act(), LV_ALIGN_IN_BOTTOM_MID, 0, -40);

  backgroundLabel = lv_label_create(lv_scr_act(), nullptr);
  backgroundLabel->user_data = this;
  lv_obj_set_click(backgroundLabel, true);
  lv_label_set_long_mode(backgroundLabel, LV_LABEL_LONG_CROP);
  lv_obj_set_size(backgroundLabel, 240, 240);
  lv_obj_set_pos(backgroundLabel, 0, 0);
  lv_label_set_text(backgroundLabel, "");


  lv_obj_t * imgbattery = lv_img_create(lv_scr_act(), nullptr);
  lv_img_set_src(imgbattery, &lowbattery);
  lv_obj_align(imgbattery, nullptr, LV_ALIGN_CENTER, 0, 0);


    static lv_style_t style_line;
    lv_style_copy(&style_line, &lv_style_plain);
    style_line.line.color = LV_COLOR_WHITE;
    style_line.line.width = 3;
    style_line.line.rounded = 0;

    timeoutLine = lv_line_create(lv_scr_act(), nullptr);
    lv_line_set_style(timeoutLine, LV_LINE_STYLE_MAIN, &style_line);
    lv_line_set_points(timeoutLine, timeoutLinePoints, 2);
    timeoutTickCountStart = xTaskGetTickCount();
    timeoutTickCountEnd = timeoutTickCountStart + (5*1024);

   
}

Battery::~Battery() {
  lv_obj_clean(lv_scr_act());
}

bool Battery::Refresh() {
  batteryPercentRemaining = batteryController.PercentRemaining();
  batteryController.setButtonData(0x05);
  batteryController.setIsTouch(true);
  
  if (batteryPercentRemaining.IsUpdated()) {
    auto batteryPercent = batteryPercentRemaining.Get();
    lv_label_set_text(batteryIcon, BatteryIcon::GetBatteryIcon(batteryPercent));
    auto isCharging = batteryController.IsCharging() || batteryController.IsPowerPresent();
    lv_label_set_text(batteryPlug, BatteryIcon::GetPlugIcon(isCharging));
  }

  bleState = bleController.IsConnected();
  if (bleState.IsUpdated()) {
    if(bleState.Get() == true) {
      lv_label_set_text(bleIcon, BleIcon::GetIcon(true));
    } else {
      lv_label_set_text(bleIcon, BleIcon::GetIcon(false));
    }
  }
  lv_obj_align(batteryIcon, lv_scr_act(), LV_ALIGN_IN_TOP_RIGHT, -5, 5);
  lv_obj_align(batteryPlug, batteryIcon, LV_ALIGN_OUT_LEFT_MID, -5, 0);
  lv_obj_align(bleIcon, batteryPlug, LV_ALIGN_OUT_LEFT_MID, -5, 0);

  currentDateTime = dateTimeController.CurrentDateTime();

  if(currentDateTime.IsUpdated()) {
    auto newDateTime = currentDateTime.Get();

    auto dp = date::floor<date::days>(newDateTime);
    auto time = date::make_time(newDateTime-dp);
 

    auto hour = time.hours().count();
    auto minute = time.minutes().count();

    char minutesChar[3];
    sprintf(minutesChar, "%02d", static_cast<int>(minute));

    char hoursChar[3];
    sprintf(hoursChar, "%02d", static_cast<int>(hour));

    char timeStr[6];
    sprintf(timeStr, "%c%c:%c%c", hoursChar[0],hoursChar[1],minutesChar[0], minutesChar[1]);

    if(hoursChar[0] != displayedChar[0] || hoursChar[1] != displayedChar[1] || minutesChar[0] != displayedChar[2] || minutesChar[1] != displayedChar[3]) {
      displayedChar[0] = hoursChar[0];
      displayedChar[1] = hoursChar[1];
      displayedChar[2] = minutesChar[0];
      displayedChar[3] = minutesChar[1];

      lv_label_set_text(label_time, timeStr);  
       }  
  }
    auto tick = xTaskGetTickCount();
    int32_t pos = 240 - ((tick - timeoutTickCountStart) / ((timeoutTickCountEnd - timeoutTickCountStart) / 240));
    if (pos < 0)
      running = false;

    timeoutLinePoints[1].x = pos;
    lv_line_set_points(timeoutLine, timeoutLinePoints, 2);

    if (!running) {
      // Start clock app when exiting this one
      app->StartApp(Apps::Clock);
    }  
  return running;
}


bool Battery::OnButtonPushed() {
  running = false;
  return true;
}


