#include "Screendisplay.h"

#include <date/date.h>
#include <lvgl/lvgl.h>
#include <cstdio>
#include "BatteryIcon.h"
#include "BleIcon.h"
#include "Symbols.h"
#include "components/battery/BatteryController.h"
#include "components/ble/BleController.h"
#include "../DisplayApp.h"
#include "displayapp/icons/clock/helpButton.c"
#include "displayapp/icons/clock/Okbutton.c"
#include "displayapp/icons/clock/TestButton.c"
#include "displayapp/icons/clock/Checkin.c"
#include "displayapp/icons/clock/sensor.c"

using namespace Watch::Applications::Screens;

extern lv_font_t San_Francisco_22;
extern lv_font_t San_Francisco_30;
extern lv_style_t* LabelBigStyle;
extern lv_style_t* LabelSanStyle;
LV_IMG_DECLARE(helpButton);  // your image src declaration
LV_IMG_DECLARE(Okbutton);
LV_IMG_DECLARE(TestButton);
LV_IMG_DECLARE(sensor);
LV_IMG_DECLARE(Checkin);


static void event_handler(lv_obj_t * obj, lv_event_t event) {
  Screendisplay* screen = static_cast<Screendisplay *>(obj->user_data);
  screen->OnObjectEvent(obj, event);
}



Screendisplay::Screendisplay(DisplayApp* app,
        Controllers::DateTime& dateTimeController,
        Controllers::Battery& batteryController,
        Controllers::Ble& bleController,
        Watch::Drivers::Acnt101& tempSensor,
         Modes mode
        ) : Screen(app), currentDateTime{{}},
                                           dateTimeController{dateTimeController}, batteryController{batteryController},
                                           bleController{bleController},tempSensor{tempSensor},
                                           mode{mode}
                                           {

  batteryIcon = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_text(batteryIcon, Symbols::batteryFull);
  lv_obj_align(batteryIcon, lv_scr_act(), LV_ALIGN_IN_TOP_RIGHT, -5, 2);

  batteryPlug = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_text(batteryPlug, Symbols::plug);
  lv_obj_align(batteryPlug, batteryIcon, LV_ALIGN_OUT_LEFT_MID, -5, 0);

  bleIcon = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_text(bleIcon, Symbols::bluetoothFull);
  lv_obj_align(bleIcon, batteryPlug, LV_ALIGN_OUT_LEFT_MID, -5, 0);
  
  label_time = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(label_time, "00:00");                   /*Set the labels text*/
  lv_label_set_style(label_time, LV_LABEL_STYLE_MAIN, LabelBigStyle);
  lv_obj_align(label_time, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, 0, 0);

  switch(mode) {
      case Modes::Clock: 
            label_date = lv_label_create(lv_scr_act(), nullptr);
            lv_label_set_style(label_date, LV_LABEL_STYLE_MAIN, LabelSanStyle);
            lv_obj_align(label_date, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, 0, 50);

            buttonHelp =  batteryController.lv_icon_create(lv_scr_act(), &helpButton);  
            buttonHelp->user_data = this;
            lv_obj_set_event_cb(buttonHelp, event_handler);
            lv_obj_align(buttonHelp, NULL, LV_ALIGN_CENTER, 0,35);

            buttonOK =  batteryController.lv_icon_create(lv_scr_act(), &Okbutton);  
            buttonOK->user_data = this;
            lv_obj_set_event_cb(buttonOK, event_handler);
            lv_obj_align(buttonOK, nullptr, LV_ALIGN_IN_TOP_RIGHT, 10, 30);
        break;
      case Modes::Test:
            buttonTest =  batteryController.lv_icon_create(lv_scr_act(), &TestButton);  
            buttonTest->user_data = this;
            lv_obj_set_event_cb( buttonTest, event_handler);
            lv_obj_align( buttonTest, NULL, LV_ALIGN_CENTER, 0,20);
        break;
      case Modes::Sensor:
          //heartRateSensor.Enable();
          img = lv_img_create(lv_scr_act(), NULL);  
          lv_img_set_src(img, &sensor);
          lv_obj_align(img, NULL, LV_ALIGN_CENTER, 0, 0);

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

      break;
      case Modes::CheckIn:
            buttonCheckin =  batteryController.lv_icon_create(lv_scr_act(), &Checkin);  
            buttonCheckin->user_data = this;
            lv_obj_set_event_cb( buttonCheckin, event_handler);
            lv_obj_align( buttonCheckin, NULL, LV_ALIGN_CENTER, 0,20);

      break;
      case Modes::Impact:



      break;
      case Modes::Fall:
      break;
      case Modes::Firmware:
      break;
  }
}

Screendisplay::~Screendisplay() {
  lv_obj_clean(lv_scr_act());
}

bool Screendisplay::Refresh() {

  currentDateTime = dateTimeController.CurrentDateTime();  
    auto newDateTime = currentDateTime.Get();
    auto dp = date::floor<date::days>(newDateTime);
    auto time = date::make_time(newDateTime-dp);
    auto yearMonthDay = date::year_month_day(dp);

    auto year = (int)yearMonthDay.year();
    auto month = static_cast<Watch::Controllers::DateTime::Months>((unsigned)yearMonthDay.month());
    auto day = (unsigned)yearMonthDay.day();
    auto dayOfWeek = static_cast<Watch::Controllers::DateTime::Days>(date::weekday(yearMonthDay).iso_encoding());

    auto hour = time.hours().count();
    auto minute = time.minutes().count();
    if ((hour != currentHour) || (minute != currentMinute)) {
      char timeStr[5];
      sprintf(timeStr, "%02d:%02d", static_cast<int>(hour), static_cast<int>(minute));
      lv_label_set_text(label_time, timeStr);
      lv_obj_align(label_time, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, 0, 0);
      currentMinute = minute;
      currentHour = hour;
    }

    if ((year != currentYear) || (month != currentMonth) || (dayOfWeek != currentDayOfWeek) || (day != currentDay)) {
      char dateStr[22];
      sprintf(dateStr, "%s,%s %d", DayOfWeekToString(dayOfWeek),MonthToString(month),day);
      lv_label_set_text(label_date, dateStr);
      lv_obj_align(label_date, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, 0, 50);
      currentYear = year;
      currentMonth = month;
      currentDayOfWeek = dayOfWeek;
      currentDay = day;
    }
  

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
      lv_label_set_text(bleIcon, BleIcon::GetIcon(true));
    } else {
      lv_label_set_text(bleIcon, BleIcon::GetIcon(false));
    }
  }
  lv_obj_align(batteryIcon, lv_scr_act(), LV_ALIGN_IN_TOP_RIGHT, -5, 5);
  lv_obj_align(batteryPlug, batteryIcon, LV_ALIGN_OUT_LEFT_MID, -5, 0);
  lv_obj_align(bleIcon, batteryPlug, LV_ALIGN_OUT_LEFT_MID, -5, 0);
  
  switch(mode) {
     case Modes::Clock:
      lv_obj_align(buttonHelp, NULL, LV_ALIGN_CENTER, 0,35);
      lv_obj_align(buttonOK, NULL, LV_ALIGN_IN_TOP_RIGHT, 10, 30); 
      break;

      case Modes::Test:
     lv_obj_align(buttonTest, NULL, LV_ALIGN_CENTER, 0,20);
      break;
      
      case Modes::CheckIn:
      lv_obj_align( buttonCheckin, NULL, LV_ALIGN_CENTER, 0,20);

      break;

      break;
      case Modes::Impact:


      break;
      case Modes::Fall:
      break;
      case Modes::Firmware:
      break;
    
  }
 
  
  return running;
}

const char *Screendisplay::MonthToString(Watch::Controllers::DateTime::Months month) {
  return Screendisplay::MonthsString[static_cast<uint8_t>(month)];
}

const char *Screendisplay::DayOfWeekToString(Watch::Controllers::DateTime::Days dayOfWeek) {
  return Screendisplay::DaysString[static_cast<uint8_t>(dayOfWeek)];
}

char const *Screendisplay::DaysString[] = {
        "",
        "MON",
        "TUE",
        "WED",
        "THUR",
        "FRI",
        "SAT",
        "SUN"
};

char const *Screendisplay::MonthsString[] = {
        "",
        "Jan",
        "Feb",
        "Mar",
        "Arp",
        "May",
        "Jun",
        "Jul",
        "Aug",
        "Sep",
        "Oct",
        "Nov",
        "Dec"
};

void Screendisplay::OnObjectEvent(lv_obj_t *obj, lv_event_t event) {
  if(event == LV_EVENT_CLICKED){
switch(mode){
case Modes::Clock:

    if(obj == buttonOK ) {
        batteryController.setButtonData(0x02); 
        batteryController.setIsTouch(true); 
        //batteryController.setIsVibrate();  
        lv_obj_align(buttonOK, nullptr, LV_ALIGN_IN_TOP_RIGHT, 10, 40);         
    } else if(obj == buttonHelp ) {
        batteryController.setButtonData(0x01); 
        batteryController.setIsTouch(true); 
        //batteryController.setIsVibrate();
         lv_obj_align(buttonHelp, NULL, LV_ALIGN_CENTER, 0,25);        
    }
    break;
      case Modes::Test:
        if(obj ==  buttonTest ) {       
        batteryController.setButtonData(0x03); 
        batteryController.setIsTouch(true); 
        //batteryController.setIsVibrate();
        lv_obj_align( buttonTest, NULL, LV_ALIGN_CENTER, 0,25);
     }
     
      break;
      case Modes::CheckIn:
      
      break;

      case Modes::Impact:
      break;
      case Modes::Fall:
      break;
      case Modes::Firmware:
      break;

}
}
}


bool Screendisplay::OnButtonPushed() {
  running = false;
   return true;
}

