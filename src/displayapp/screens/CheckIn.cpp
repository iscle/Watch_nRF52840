#include "CheckIn.h"

#include <date/date.h>
#include <lvgl/lvgl.h>
#include <cstdio>
#include "BatteryIcon.h"
#include "Symbols.h"
#include "components/battery/BatteryController.h"
#include "components/ble/BleController.h"
#include "components/ble/NotificationManager.h"
#include "../DisplayApp.h"
#include "displayapp/icons/clock/Checkin.c"


using namespace Watch::Applications::Screens;
extern lv_style_t* LabelBigStyle;
extern lv_style_t* LabelSanStyle;
LV_IMG_DECLARE(Checkin);

static void event_handler(lv_obj_t * obj, lv_event_t event) {
  CheckIn* screen = static_cast<CheckIn *>(obj->user_data);
  screen->OnObjectEvent(obj, event);
}

CheckIn::CheckIn(DisplayApp* app,
        Controllers::DateTime& dateTimeController,
        Controllers::Battery& batteryController,
        Controllers::Ble& bleController) : Screen(app), currentDateTime{{}},
                                           dateTimeController{dateTimeController}, batteryController{batteryController},
                                           bleController{bleController} {
/*
  labeleft = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_text(labeleft, "<");
  lv_obj_align(labeleft, lv_scr_act(),LV_ALIGN_IN_LEFT_MID, 0, 0);

  labelright = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_text(labelright, ">");
  lv_obj_align(labelright, lv_scr_act(),LV_ALIGN_IN_RIGHT_MID, 0, 0);

  labelpoint = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_text(labelpoint, ". . .");
  lv_obj_align(labelpoint, lv_scr_act(),LV_ALIGN_IN_BOTTOM_MID, 0, 0);
*/

  batteryIcon = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_text(batteryIcon, Symbols::batteryFull);
  lv_obj_align(batteryIcon, lv_scr_act(), LV_ALIGN_IN_TOP_RIGHT, -5, 2);

  batteryPlug = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_text(batteryPlug, Symbols::plug);
  lv_obj_align(batteryPlug, batteryIcon, LV_ALIGN_OUT_LEFT_MID, -5, 0);

  bleIcon = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_text(bleIcon, Symbols::bluetoothFull);
  lv_obj_align(bleIcon, batteryPlug, LV_ALIGN_OUT_LEFT_MID, -5, 0);

 label_time = lv_label_create(lv_scr_act(), nullptr);
 lv_label_set_text(label_time, "00:00");                   /*Set the labels text*/
 lv_label_set_style(label_time, LV_LABEL_STYLE_MAIN, LabelBigStyle);
 lv_obj_align(label_time, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, 0, 0);

  buttonCheckin =  batteryController.lv_icon_create(lv_scr_act(), &Checkin);  
  buttonCheckin->user_data = this;
  lv_obj_set_event_cb( buttonCheckin, event_handler);
  lv_obj_align( buttonCheckin, NULL, LV_ALIGN_CENTER, 0,20);

}

CheckIn::~CheckIn() {
  lv_obj_clean(lv_scr_act());
}

bool CheckIn::Refresh() {
  batteryPercentRemaining = batteryController.PercentRemaining();
  if (batteryPercentRemaining.IsUpdated()) {
    auto batteryPercent = batteryPercentRemaining.Get();
    lv_label_set_text(batteryIcon, BatteryIcon::GetBatteryIcon(batteryPercent));
    auto isCharging = batteryController.IsCharging() || batteryController.IsPowerPresent();
    lv_label_set_text(batteryPlug, BatteryIcon::GetPlugIcon(isCharging));
  }

  bleState = bleController.IsConnected();
  if (bleState.IsUpdated()) {
    if(bleState.Get() == true) {
      lv_label_set_text(bleIcon, Symbols::bluetoothFull);
    } else {
      lv_label_set_text(bleIcon, "");
    }
  }

  lv_obj_align(batteryIcon, lv_scr_act(), LV_ALIGN_IN_TOP_RIGHT, -5, 5);
  lv_obj_align(batteryPlug, batteryIcon, LV_ALIGN_OUT_LEFT_MID, -5, 0);
  lv_obj_align(bleIcon, batteryPlug, LV_ALIGN_OUT_LEFT_MID, -5, 0);
  lv_obj_align( buttonCheckin, NULL, LV_ALIGN_CENTER, 0,20);
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

    if ((hour != currentHour) || (minute != currentMinute)) {
      char timeStr[5];
      sprintf(timeStr, "%02d:%02d", static_cast<int>(hour), static_cast<int>(minute));
      lv_label_set_text(label_time, timeStr);
      lv_obj_align(label_time, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, 0, 0);
      currentMinute = minute;
      currentHour = hour;
    }

  }

   return running;
}


void CheckIn::OnObjectEvent(lv_obj_t *obj, lv_event_t event) {
  if(event == LV_EVENT_CLICKED){
  
    if(obj ==  buttonCheckin ) {
        batteryController.setButtonData(0x09); 
        batteryController.setIsTouch(true); 
      lv_obj_align( buttonCheckin, NULL, LV_ALIGN_CENTER, 0,30);
  
  }
}
}
bool CheckIn::OnButtonPushed() {
  running = false;
  return true;
}

























