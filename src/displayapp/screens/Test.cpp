#include "Test.h"
#include <date/date.h>
#include <lvgl/lvgl.h>
#include <hal/nrf_gpio.h>
#include <cstdio>
#include "BatteryIcon.h"
#include "BleIcon.h"
#include "Symbols.h"
#include "components/battery/BatteryController.h"
#include "components/ble/BleController.h"
#include "../DisplayApp.h"
#include "displayapp/icons/clock/TestButton.c"
#include "displayapp/icons/clock/helpButton.c"
#include "displayapp/icons/clock/Okbutton.c"
#include "displayapp/icons/battery/battery_05.c"
#include "displayapp/icons/battery/battery_05_c.c"
#include "displayapp/icons/battery/battery_20.c"
#include "displayapp/icons/battery/battery_20_c.c"
#include "displayapp/icons/battery/battery_50.c"
#include "displayapp/icons/battery/battery_50_c.c"
#include "displayapp/icons/battery/battery_100.c"
#include "displayapp/icons/battery/battery_100_c.c"
#include "displayapp/icons/bluetooth/bluetooth.c"
#include "displayapp/icons/bluetooth/bluetoothdis.c"





using namespace Watch::Applications::Screens;
extern lv_font_t San_Francisco_22;
extern lv_style_t* LabelBigStyle;
extern lv_style_t* LabelSanStyle;
LV_IMG_DECLARE(TestButton);
LV_IMG_DECLARE(battery_05);
//LV_IMG_DECLARE(battery_05_c);
LV_IMG_DECLARE(battery_20);
//LV_IMG_DECLARE(battery_20_c);
LV_IMG_DECLARE(battery_50);
//LV_IMG_DECLARE(battery_50_c);
LV_IMG_DECLARE(battery_100);
//LV_IMG_DECLARE(battery_100_c);
LV_IMG_DECLARE(bluetooth);
LV_IMG_DECLARE(bluetoothdis);



static void event_handler(lv_obj_t * obj, lv_event_t event) {
  Test* screen = static_cast<Test *>(obj->user_data);
  screen->OnObjectEvent(obj, event);
}


Test::Test(DisplayApp* app,
        Controllers::DateTime& dateTimeController,
        Controllers::Battery& batteryController,
        Controllers::Ble& bleController) : Screen(app), currentDateTime{{}},
                                           dateTimeController{dateTimeController}, batteryController{batteryController},
                                           bleController{bleController} {

  batteryIcon = lv_img_create(lv_scr_act(), nullptr);
  lv_img_set_src(batteryIcon, &battery_100);
  lv_obj_align(batteryIcon, NULL, LV_ALIGN_IN_TOP_RIGHT, -5, 2);

  batteryPlug = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_text(batteryPlug, Symbols::plug);
  lv_obj_align(batteryPlug, batteryIcon, LV_ALIGN_OUT_LEFT_MID, -5, 0);

  bleIcon =  lv_img_create(lv_scr_act(), nullptr);
  lv_img_set_src(bleIcon, &bluetooth);
  lv_obj_align(bleIcon, batteryPlug, LV_ALIGN_OUT_LEFT_MID, -5, 0);

  label_time = lv_label_create(lv_scr_act(), nullptr);
   lv_label_set_text(label_time, "00:00");  
  lv_label_set_style(label_time, LV_LABEL_STYLE_MAIN, LabelBigStyle);
  lv_obj_align(label_time, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, 0, 0);

  //buttonTest = lv_icon_create(lv_scr_act(), &TestButton);  
  buttonTest->user_data = this;
  lv_obj_set_event_cb( buttonTest, event_handler);
  lv_obj_align( buttonTest, NULL, LV_ALIGN_CENTER, 0,20);
}

Test::~Test() {
  lv_obj_clean(lv_scr_act());
}


bool Test::Refresh() {

    batteryPercentRemaining = batteryController.PercentRemaining();
  if (batteryPercentRemaining.IsUpdated()) {
    auto batteryPercent = batteryPercentRemaining.Get();
    if(batteryPercent<25) lv_img_set_src(batteryIcon, &battery_05);
    else if(batteryPercent<50) lv_img_set_src(batteryIcon, &battery_20);
     else if(batteryPercent<75) lv_img_set_src(batteryIcon, &battery_50);
     else  lv_img_set_src(batteryIcon, &battery_100);
    
    auto isCharging = batteryController.IsCharging() || batteryController.IsPowerPresent();
    if( isCharging ) lv_label_set_text(batteryPlug, Symbols::plug);
    else lv_label_set_text(batteryPlug, "");
  }

  bleState = bleController.IsConnected();
  if (bleState.IsUpdated()) {
    if(bleState.Get() == true) {
       lv_img_set_src(bleIcon, &bluetooth);
    } else {
       lv_img_set_src(bleIcon, &bluetoothdis);
    }
  }

  lv_obj_align(batteryIcon, lv_scr_act(), LV_ALIGN_IN_TOP_RIGHT, -5, 5);
  lv_obj_align(batteryPlug, batteryIcon, LV_ALIGN_OUT_LEFT_MID, -5, 0);
  lv_obj_align(bleIcon, batteryPlug, LV_ALIGN_OUT_LEFT_MID, -5, 0);



  lv_obj_align( buttonTest, NULL, LV_ALIGN_CENTER, 0,20);

  currentDateTime = dateTimeController.CurrentDateTime();

  if(currentDateTime.IsUpdated()) {
    auto newDateTime = currentDateTime.Get();

    auto dp = date::floor<date::days>(newDateTime);
    auto time = date::make_time(newDateTime-dp);
    auto hour = time.hours().count();
    auto minute = time.minutes().count();
    if ((hour != currentHour) || (minute != currentMinute)) {
      char timeStr[5];
      sprintf(timeStr, "%02d:%02d", static_cast<int>(hour), static_cast<int>(minute));
      lv_label_set_text(label_time, timeStr);
      currentMinute = minute;
      currentHour = hour;
    }
  }

  return running;
}



void Test::OnObjectEvent(lv_obj_t *obj, lv_event_t event) {
     
  if(event == LV_EVENT_CLICKED){
  
    if(obj ==  buttonTest ) {
        checkButton=1;
        batteryController.setButtonData(0x03); 
        batteryController.setIsTouch(true); 
        //batteryController.setIsVibrate();
        lv_obj_align( buttonTest, NULL, LV_ALIGN_CENTER, 0,25);
     }
}
}

bool Test::OnButtonPushed() {
  running = false;
  return true;
}

