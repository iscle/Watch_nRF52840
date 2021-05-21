#include "SensorDisplay.h"

#include <date/date.h>
#include <lvgl/lvgl.h>
#include <cstdio>
#include "BatteryIcon.h"
#include "Symbols.h"
#include "components/battery/BatteryController.h"
#include "components/ble/BleController.h"
#include "../DisplayApp.h"
#include "displayapp/icons/clock/sensor.c"


using namespace Watch::Applications::Screens;
extern lv_font_t San_Francisco_22;
extern lv_font_t San_Francisco_30;

extern lv_style_t* LabelBigStyle;
extern lv_style_t* LabelSanStyle;
extern lv_style_t* LabelSmallStyle;
LV_IMG_DECLARE(sensor);
//LV_IMG_DECLARE(oxi);


SensorDisplay::SensorDisplay(DisplayApp* app,
        Controllers::DateTime& dateTimeController,
        Controllers::Battery& batteryController,
        Controllers::Ble& bleController,
        Watch::Drivers::Acnt101& tempSensor) : Screen(app), currentDateTime{{}},
                                           dateTimeController{dateTimeController}, batteryController{batteryController},
                                           bleController{bleController}, tempSensor{tempSensor} {

  lv_obj_t * img = lv_img_create(lv_scr_act(), NULL);  
  lv_img_set_src(img, &sensor);
  lv_obj_align(img, NULL, LV_ALIGN_CENTER, 0, 0);
  batteryPlug = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_text(batteryPlug, Symbols::plug);
  lv_obj_align(batteryPlug, lv_scr_act(), LV_ALIGN_IN_TOP_RIGHT, -5, 2);

  bleIcon = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_text(bleIcon, Symbols::bluetoothFull);
  lv_obj_align(bleIcon, batteryPlug, LV_ALIGN_OUT_LEFT_MID, -5, 0);

  label_time = lv_label_create(lv_scr_act(), nullptr);
   lv_label_set_text(label_time, "00:00");  
  lv_label_set_style(label_time, LV_LABEL_STYLE_MAIN, LabelBigStyle);
  lv_obj_align(label_time, nullptr,  LV_ALIGN_CENTER, 0, -60);
  

  heartbeatValue = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_text(heartbeatValue, "--");
  static lv_style_t  labelStyle;
  static lv_style_t labelStyltemp;
  lv_style_copy(& labelStyle, &lv_style_plain);
  labelStyle.text.font = &San_Francisco_30;
  labelStyle.text.color=LV_COLOR_WHITE;
  lv_label_set_style(heartbeatValue,LV_LABEL_STYLE_MAIN,&labelStyle);
  lv_obj_align(heartbeatValue, lv_scr_act(), LV_ALIGN_IN_BOTTOM_MID, -15, -45);

  tempCValue = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_text(tempCValue, "--");
  lv_style_copy(& labelStyltemp, &lv_style_plain);
  labelStyltemp.text.font = &San_Francisco_30;
  labelStyltemp.text.color=LV_COLOR_WHITE;
  lv_label_set_style( tempCValue,LV_LABEL_STYLE_MAIN,&labelStyltemp);
  lv_obj_align( tempCValue,lv_scr_act(), LV_ALIGN_IN_RIGHT_MID, -50, 0);

  battery = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_text(battery, "--");
  lv_label_set_style(battery,LV_LABEL_STYLE_MAIN,&labelStyltemp);
  lv_obj_align( battery,lv_scr_act(), LV_ALIGN_CENTER, -65, 0);

}

SensorDisplay::~SensorDisplay() {
  lv_obj_clean(lv_scr_act());
  heartRateSensor.Disable();
}
 
bool SensorDisplay::Refresh() {
  
 char timeStr[5];
  batteryPercentRemaining = batteryController.PercentRemaining();
 sprintf(timeStr, "%04d", uint16_t(batteryPercentRemaining));
lv_label_set_text(battery, timeStr);

auto isCharging = batteryController.IsCharging() || batteryController.IsPowerPresent();
lv_label_set_text(batteryPlug, BatteryIcon::GetPlugIcon(isCharging));   
 
  bleState = bleController.IsConnected();
  if (bleState.IsUpdated()) {
    if(bleState.Get() == true) {
      lv_label_set_text(bleIcon, Symbols::bluetoothFull);
    } else {
      lv_label_set_text(bleIcon, "");
    }
  }
  lv_obj_align(batteryPlug, lv_scr_act(), LV_ALIGN_IN_TOP_RIGHT, -5, 5);
  lv_obj_align(bleIcon, batteryPlug, LV_ALIGN_OUT_LEFT_MID, -5, 0);


  currentDateTime = dateTimeController.CurrentDateTime();

  if(currentDateTime.IsUpdated()) {
    auto newDateTime = currentDateTime.Get();

    auto dp = date::floor<date::days>(newDateTime);
    auto time = date::make_time(newDateTime-dp); 
    auto hour = time.hours().count();
    auto minute = time.minutes().count();

    if ((hour != currentHour) || (minute != currentMinute)) {
      sprintf(timeStr, "%02d:%02d", static_cast<int>(hour), static_cast<int>(minute));
      lv_label_set_text(label_time, timeStr);
      currentMinute = minute;
      currentHour = hour;
    }
  }
  


if(flagstick==max){
  flagstick =0;
  max =40;
  char hr[4];
  if(heartRateSensor.ReadHrs()==0)  lv_label_set_text(heartbeatValue, "--");
  else {sprintf(hr, "%03d", heartRateSensor.ReadHrs()); lv_label_set_text(heartbeatValue, hr);  } 
  

  if(tempSensor.getIsCount()){
    float rawTemp= tempSensor.Update();
    if(rawTemp<70.0) 
    {
      uint8_t tempInt1 = rawTemp;                  // Get the integer (678).
      uint8_t tempInt2 = (rawTemp - tempInt1) * 10;  // Turn into integer (123).
      char strTemp[5];
      sprintf (strTemp, "%d.%01d\n", tempInt1, tempInt2);    
      lv_label_set_text(tempCValue,strTemp); 
      //float rawTempF = 1.8*rawTemp + 32;
      //tempInt1 = rawTempF;
      //tempInt2 = (rawTempF - tempInt1) * 10;
     // sprintf (strTemp, "%d.%01d\n", tempInt1, tempInt2); 
     // lv_label_set_text(tempFValue,strTemp);
    }
  }
   
} else flagstick++;

  return running;
}


bool SensorDisplay::OnButtonPushed() {
  running = false;
  return true;
}

