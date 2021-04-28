#include "Clock.h"

#include <date/date.h>

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
#include "displayapp/icons/clock/Impact.c"
#include "displayapp/icons/clock/close.c"
#include "displayapp/icons/clock/Fall.c"
#include "displayapp/icons/clock/sensor.c"
#include "displayapp/icons/clock/arrowleft.c"
#include "displayapp/icons/clock/arrowright.c"
#include "displayapp/icons/battery/battery_05.c"
#include "displayapp/icons/battery/battery_20.c"
#include "displayapp/icons/battery/battery_50.c"
#include "displayapp/icons/battery/battery_100.c"
#include "displayapp/icons/bluetooth/bluetooth.c"
#include "displayapp/icons/bluetooth/bluetoothdis.c"
#include "displayapp/icons/bluetooth/pairdis.c"
#include "displayapp/icons/battery/charing.c"
#include "displayapp/icons/clock/pointclock.c"
#include "displayapp/icons/clock/pointsensor.c"
#include "displayapp/icons/clock/pointtest.c"
#include "displayapp/icons/battery/lowbattery.c"
#include "displayapp/icons/oxi/oxi.c"
#include "displayapp/icons/clock/pointoxi.c"
#include "displayapp/icons/battery/charingicon.c"
#include "displayapp/icons/battery/discharingicon.c"
#include "displayapp/icons/clock/leftCircle.c"
#include "displayapp/icons/clock/topCircle.c"
#include "displayapp/icons/clock/rightCircle.c"
#include "displayapp/icons/clock/leftCircleSmall.c"
#include "displayapp/icons/clock/topCircleSmall.c"
#include "displayapp/icons/clock/rightCircleSmall.c"
#include "displayapp/icons/clock/bottomCircleSmall.c"
#include "nrf_delay.h"

extern "C" {
    #include <lvgl/lvgl.h>
}

using namespace Watch::Applications::Screens;

extern lv_font_t San_Francisco_22;
extern lv_font_t San_Francisco_30;
extern lv_style_t* LabelBigStyle;
extern lv_style_t* LabelSanStyle;
extern lv_style_t* LabelSmallStyle;
LV_IMG_DECLARE(helpButton);  
LV_IMG_DECLARE(Okbutton);
LV_IMG_DECLARE(TestButton);
LV_IMG_DECLARE(battery_05);
LV_IMG_DECLARE(Checkin);
LV_IMG_DECLARE(impact);
LV_IMG_DECLARE(close);
LV_IMG_DECLARE(Fall);
LV_IMG_DECLARE(sensor);
LV_IMG_DECLARE(arrowleft);
LV_IMG_DECLARE(arrowright);
LV_IMG_DECLARE(battery_20);
LV_IMG_DECLARE(battery_50);
LV_IMG_DECLARE(battery_100);
LV_IMG_DECLARE(bluetooth);
LV_IMG_DECLARE(bluetoothdis);
LV_IMG_DECLARE(pairdis);
LV_IMG_DECLARE(charging);
LV_IMG_DECLARE(pointclock);
LV_IMG_DECLARE(pointtest);
LV_IMG_DECLARE(pointsensor);
LV_IMG_DECLARE(pointoxi);
LV_IMG_DECLARE(lowbattery);
LV_IMG_DECLARE(oxi);
LV_IMG_DECLARE(chargingicon);
LV_IMG_DECLARE(dischargingicon);
LV_IMG_DECLARE(leftCircle);
LV_IMG_DECLARE(topCircle);
LV_IMG_DECLARE(rightCircle);
LV_IMG_DECLARE(leftCircleSmall);
LV_IMG_DECLARE(topCircleSmall);
LV_IMG_DECLARE(rightCircleSmall);
LV_IMG_DECLARE(bottomCircleSmall);

static lv_obj_t * lv_icon_create(lv_obj_t*par, const void* img_src){
    lv_obj_t* icon = lv_btn_create( par, NULL);
    lv_obj_t *img = lv_img_create(icon, NULL);
    lv_img_set_src(img, img_src);
    lv_cont_set_layout(icon, LV_LAYOUT_COL_M);
    lv_cont_set_fit2(icon, LV_FIT_TIGHT, LV_FIT_TIGHT);
    lv_obj_set_auto_realign(icon, true);

    static lv_style_t style_rel;  lv_style_copy(&style_rel, &lv_style_transp_tight);
    lv_btn_set_style(icon, LV_BTN_STYLE_REL, &style_rel);
    style_rel.body.padding.top    = 10;
    style_rel.body.padding.left   = 10;
    style_rel.body.padding.right  = 10;
      
    static lv_style_t style_pr;   lv_style_copy(&style_pr, &style_rel);
    lv_btn_set_style(icon, LV_BTN_STYLE_PR, &style_pr); 
  return icon;
}


static void event_handler(lv_obj_t * obj, lv_event_t event) {
    Clock* screen = static_cast<Clock *>(obj->user_data);
     screen->OnObjectEvent(obj, event);
}

Clock::Clock(DisplayApp* app,
        Controllers::DateTime& dateTimeController,
        Controllers::Battery& batteryController,
        Controllers::Ble& bleController,
        Watch::Drivers::Acnt101& tempSensor,
        Modes mode 
        ) : Screen(app), dateTimeController{dateTimeController},
                         batteryController{batteryController},
                         bleController{bleController},
                         tempSensor{tempSensor},mode{mode} {
      
          backgroundLabel = lv_label_create(lv_scr_act(), nullptr);
          lv_label_set_long_mode(backgroundLabel, LV_LABEL_LONG_CROP);
          lv_obj_set_size(backgroundLabel, 240, 240);
          lv_obj_set_pos(backgroundLabel, 0, 0);
          lv_label_set_text(backgroundLabel, "");    

        if((mode == Modes::Clock) ||(mode == Modes::Test)|| (mode == Modes::Sensor) || (mode == Modes::Oxi)){
          labelleft =  lv_icon_create(lv_scr_act(), &arrowleft);  
          labelleft->user_data = this;
          lv_obj_set_event_cb( labelleft, event_handler);
          lv_obj_align( labelleft, lv_scr_act(),LV_ALIGN_IN_RIGHT_MID, 10, 0);

          labelright =  lv_icon_create(lv_scr_act(), &arrowright);  
          labelright->user_data = this;
          lv_obj_set_event_cb(labelright, event_handler);
          lv_obj_align(labelright, lv_scr_act(),LV_ALIGN_IN_LEFT_MID, -10, 0);        
        }


        batteryIcon = lv_img_create(lv_scr_act(), NULL);
        lv_img_set_src(batteryIcon, &battery_100);        

        batteryPlug = lv_img_create(lv_scr_act(), NULL);
        lv_img_set_src(batteryPlug, &chargingicon);        

        bleIcon =  lv_img_create(lv_scr_act(), NULL);
        lv_img_set_src(bleIcon, &bluetooth);        

        logo = lv_label_create(lv_scr_act(), NULL);
        lv_label_set_style(logo, LV_LABEL_STYLE_MAIN, LabelSanStyle);
        //lv_label_set_text(logo, "OEM Name"); 
        lv_label_set_text(logo, "Zien Solutions"); 
        lv_obj_align(logo, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, 0, 5); 

        lv_obj_align(batteryIcon, lv_scr_act(), LV_ALIGN_IN_TOP_RIGHT, -5, 5);
        lv_obj_align(bleIcon, batteryIcon, LV_ALIGN_OUT_LEFT_MID, -5, 0);
        lv_obj_align(batteryPlug, bleIcon, LV_ALIGN_OUT_LEFT_MID, -5, 0);

         static lv_style_t  labelStyle;
        lv_style_copy(& labelStyle, &lv_style_plain);
        labelStyle.text.font = &San_Francisco_30;
        labelStyle.text.color=LV_COLOR_WHITE;
        
        //app->SetTouchMode(DisplayApp::TouchModes::Polling);

        switch (mode){
        case Modes::Clock:
          batteryController.setGoToSleep(true);
          label_time = lv_label_create(lv_scr_act(), NULL);
          lv_label_set_text(label_time, "");                   
          lv_label_set_style(label_time, LV_LABEL_STYLE_MAIN,LabelSmallStyle);
          lv_obj_align(label_time, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, 0, 30);
          
          label_date = lv_label_create(lv_scr_act(), NULL);
          lv_label_set_text(label_date,"");
          lv_label_set_style(label_date, LV_LABEL_STYLE_MAIN, LabelSanStyle);
          lv_obj_align(label_date, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, 0, 65);

          buttonBig =  lv_icon_create(lv_scr_act(), &helpButton);      
          lv_obj_align(buttonBig, NULL, LV_ALIGN_CENTER, 0,30);

          
          lableleftCircle =lv_img_create(lv_scr_act(), NULL);
          lv_img_set_src(lableleftCircle, &leftCircle);
          lv_obj_align(lableleftCircle, lv_scr_act(), LV_ALIGN_CENTER, -58, 34); 

          labletopCircle =lv_img_create(lv_scr_act(), NULL);
          lv_img_set_src(labletopCircle, &topCircle);
          lv_obj_align(labletopCircle, lv_scr_act(), LV_ALIGN_CENTER, 0, -18); 

          lablerightCircle =lv_img_create(lv_scr_act(), NULL);
          lv_img_set_src(lablerightCircle, &rightCircle);
          lv_obj_align(lablerightCircle, lv_scr_act(), LV_ALIGN_CENTER, 57, 34); 

          lv_obj_set_hidden(lableleftCircle,true);
          lv_obj_set_hidden(labletopCircle,true);
          lv_obj_set_hidden(lablerightCircle,true);

          buttonSmall =  lv_icon_create(lv_scr_act(), &Okbutton);  
          lv_obj_align(buttonSmall, NULL, LV_ALIGN_IN_TOP_RIGHT, 0, 27); // PHAI LEN
          /*
          lableleftCircleSmall =lv_img_create(lv_scr_act(), NULL);
          lv_img_set_src(lableleftCircleSmall, &leftCircleSmall);
          lv_obj_align(lableleftCircleSmall,NULL, LV_ALIGN_IN_TOP_RIGHT, -60, 35); 

          labletopCircleSmall =lv_img_create(lv_scr_act(), NULL);
          lv_img_set_src(labletopCircleSmall, &topCircleSmall);
          lv_obj_align(labletopCircleSmall,NULL, LV_ALIGN_IN_TOP_RIGHT, -10, 30); 

          lablerightCircleSmall =lv_img_create(lv_scr_act(), NULL);
          lv_img_set_src(lablerightCircleSmall, &rightCircleSmall);
          lv_obj_align(lablerightCircleSmall,NULL, LV_ALIGN_IN_TOP_RIGHT, -5, 35); 

          lablebottomCircleSmall =lv_img_create(lv_scr_act(), NULL);
          lv_img_set_src(lablebottomCircleSmall, &bottomCircleSmall);
          lv_obj_align(lablebottomCircleSmall,NULL, LV_ALIGN_IN_TOP_RIGHT, -12, 88); 
          */
          labelpoint  = lv_img_create(lv_scr_act(), NULL);  
          lv_img_set_src(labelpoint, &pointclock);
          lv_obj_align(labelpoint, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0); 
          break;
        case Modes::Test:
          batteryController.setGoToSleep(true);
          buttonBig =  lv_icon_create(lv_scr_act(), &TestButton);  
          lv_obj_align(buttonBig, NULL, LV_ALIGN_CENTER, 0,30);
          
          lableleftCircle =lv_img_create(lv_scr_act(), NULL);
          lv_img_set_src(lableleftCircle, &leftCircle);
          lv_obj_align(lableleftCircle, lv_scr_act(), LV_ALIGN_CENTER, -58, 34); 

          labletopCircle =lv_img_create(lv_scr_act(), NULL);
          lv_img_set_src(labletopCircle, &topCircle);
          lv_obj_align(labletopCircle, lv_scr_act(), LV_ALIGN_CENTER, 0, -19); 

          lablerightCircle =lv_img_create(lv_scr_act(), NULL);
          lv_img_set_src(lablerightCircle, &rightCircle);
          lv_obj_align(lablerightCircle, lv_scr_act(), LV_ALIGN_CENTER, 57, 34); 

          lv_obj_set_hidden(lableleftCircle,true);
          lv_obj_set_hidden(labletopCircle,true);
          lv_obj_set_hidden(lablerightCircle,true);

          labelpoint  = lv_img_create(lv_scr_act(), NULL);
          lv_img_set_src(labelpoint, &pointtest);
          lv_obj_align(labelpoint, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0); 
          batteryController.setGoToSleep(true);
          timeoutCountStart = xTaskGetTickCount();
          break;  
        case Modes::CheckIn:
          buttonBig =  lv_icon_create(lv_scr_act(), &Checkin);  
          lv_obj_align(buttonBig, NULL, LV_ALIGN_CENTER, 0,30);
           batteryController.setisButtonPushed(false);

          lableleftCircle =lv_img_create(lv_scr_act(), NULL);
          lv_img_set_src(lableleftCircle, &leftCircle);
          lv_obj_align(lableleftCircle, lv_scr_act(), LV_ALIGN_CENTER, -58, 34); 

          labletopCircle =lv_img_create(lv_scr_act(), NULL);
          lv_img_set_src(labletopCircle, &topCircle);
          lv_obj_align(labletopCircle, lv_scr_act(), LV_ALIGN_CENTER, 0, -19); 

          lablerightCircle =lv_img_create(lv_scr_act(), NULL);
          lv_img_set_src(lablerightCircle, &rightCircle);
          lv_obj_align(lablerightCircle, lv_scr_act(), LV_ALIGN_CENTER, 57, 34); 

          lv_obj_set_hidden(lableleftCircle,true);
          lv_obj_set_hidden(labletopCircle,true);
          lv_obj_set_hidden(lablerightCircle,true);

          buttonSmall =  lv_icon_create(lv_scr_act(), &close);  
          lv_obj_align(buttonSmall, NULL, LV_ALIGN_IN_TOP_RIGHT, 0, 27); 

          break;
        case Modes::Impact:
          buttonBig =  lv_icon_create(lv_scr_act(), &impact);  
          timeoutCountStart = xTaskGetTickCount();
          batteryController.setisButtonPushed(false); 
          lv_obj_align(buttonBig, NULL, LV_ALIGN_CENTER, 0,30);

          lableleftCircle =lv_img_create(lv_scr_act(), NULL);
          lv_img_set_src(lableleftCircle, &leftCircle);
          lv_obj_align(lableleftCircle, lv_scr_act(), LV_ALIGN_CENTER, -58, 34); 

          labletopCircle =lv_img_create(lv_scr_act(), NULL);
          lv_img_set_src(labletopCircle, &topCircle);
          lv_obj_align(labletopCircle, lv_scr_act(), LV_ALIGN_CENTER, 0, -18); 

          lablerightCircle =lv_img_create(lv_scr_act(), NULL);
          lv_img_set_src(lablerightCircle, &rightCircle);
          lv_obj_align(lablerightCircle, lv_scr_act(), LV_ALIGN_CENTER, 57, 34); 

          lv_obj_set_hidden(lableleftCircle,true);
          lv_obj_set_hidden(labletopCircle,true);
          lv_obj_set_hidden(lablerightCircle,true);

          buttonSmall =  lv_icon_create(lv_scr_act(), &Okbutton);  
          lv_obj_align(buttonSmall, NULL, LV_ALIGN_IN_TOP_RIGHT, 0, 17);


          break;
        case Modes::Fall:
          buttonBig =  lv_icon_create(lv_scr_act(), &Fall);  
          timeoutCountStart = xTaskGetTickCount();
          batteryController.setisButtonPushed(false); 
          lv_obj_align(buttonBig, NULL, LV_ALIGN_CENTER, 0,30);

          lableleftCircle =lv_img_create(lv_scr_act(), NULL);
          lv_img_set_src(lableleftCircle, &leftCircle);
          lv_obj_align(lableleftCircle, lv_scr_act(), LV_ALIGN_CENTER, -58, 34); 

          labletopCircle =lv_img_create(lv_scr_act(), NULL);
          lv_img_set_src(labletopCircle, &topCircle);
          lv_obj_align(labletopCircle, lv_scr_act(), LV_ALIGN_CENTER, 0, -19); 

          lablerightCircle =lv_img_create(lv_scr_act(), NULL);
          lv_img_set_src(lablerightCircle, &rightCircle);
          lv_obj_align(lablerightCircle, lv_scr_act(), LV_ALIGN_CENTER, 57, 34); 

          lv_obj_set_hidden(lableleftCircle,true);
          lv_obj_set_hidden(labletopCircle,true);
          lv_obj_set_hidden(lablerightCircle,true);

          buttonSmall =  lv_icon_create(lv_scr_act(), &Okbutton);  
          lv_obj_align(buttonSmall, NULL, LV_ALIGN_IN_TOP_RIGHT, 0, 17);


          break;
        case Modes::Sensor: 
          imgSensor = lv_img_create(lv_scr_act(), NULL);  
          lv_img_set_src(imgSensor, &sensor);
          lv_obj_align(imgSensor, NULL, LV_ALIGN_CENTER, 0, 0);   

          heartbeatValue = lv_label_create(lv_scr_act(), nullptr);
          lv_obj_set_auto_realign(heartbeatValue, true);
          lv_label_set_text(heartbeatValue, "--");
          lv_label_set_style(heartbeatValue,LV_LABEL_STYLE_MAIN,&labelStyle);
          lv_obj_align(heartbeatValue, lv_scr_act(), LV_ALIGN_IN_BOTTOM_MID, 5, -55);

          tempCValue = lv_label_create(lv_scr_act(), nullptr);
          lv_obj_set_auto_realign(tempCValue, true);
          lv_label_set_text(tempCValue, "--");
          lv_label_set_style( tempCValue,LV_LABEL_STYLE_MAIN,&labelStyle);
          lv_obj_align( tempCValue,lv_scr_act(), LV_ALIGN_CENTER, 18, -60);

          tempFValue = lv_label_create(lv_scr_act(), nullptr);
          lv_obj_set_auto_realign(tempFValue, true);
          lv_label_set_text(tempFValue, "--");
          lv_label_set_style( tempFValue,LV_LABEL_STYLE_MAIN,&labelStyle);
          lv_obj_align( tempFValue,lv_scr_act(), LV_ALIGN_CENTER, 18, -10);

          labelpoint  = lv_img_create(lv_scr_act(), NULL);  
          lv_img_set_src(labelpoint, &pointsensor);
          lv_obj_align(labelpoint, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0); 
          heartRateSensor.HrInit();
          timeoutCountStart = xTaskGetTickCount();
          rawTemp=35.5f + (rand()% 3)/10.0f ;
          //tempSensor.start(); 
          break;  
        case Modes::PairDis:  
          batteryController.setGoToSleep(true);  
          imgpair = lv_img_create(lv_scr_act(), nullptr);  
          lv_img_set_src(imgpair, &pairdis);
          lv_obj_align(imgpair, nullptr, LV_ALIGN_CENTER, 0, 10);  
          break;
        case Modes::Charging:
          batteryController.setGoToSleep(true);   
          imgpair = lv_img_create(lv_scr_act(), nullptr);  
          lv_img_set_src(imgpair, &charging);
          lv_obj_align(imgpair, nullptr, LV_ALIGN_CENTER, 0, 10); 
          timeoutCountStart = xTaskGetTickCount();

          tempCValue = lv_label_create(lv_scr_act(), nullptr);
          lv_label_set_text(tempCValue, "--");
          lv_label_set_style(tempCValue, LV_LABEL_STYLE_MAIN, LabelSanStyle);
          lv_obj_align( tempCValue,lv_scr_act(), LV_ALIGN_CENTER, -20, 40);
          break;
        case Modes::LowBattery:         
          batteryController.setGoToSleep(true);  
          imgpair = lv_img_create(lv_scr_act(), nullptr);  
          lv_img_set_src(imgpair, &lowbattery);
          lv_obj_align(imgpair, nullptr, LV_ALIGN_CENTER, 0, 10); 
          timeoutCountStart = xTaskGetTickCount();

          tempCValue = lv_label_create(lv_scr_act(), nullptr);
          lv_label_set_text(tempCValue, "--");
          lv_label_set_style(tempCValue, LV_LABEL_STYLE_MAIN, LabelSanStyle);
          lv_obj_align( tempCValue,lv_scr_act(), LV_ALIGN_CENTER, -20, 40);
          break;

        case Modes::Oxi:
          heartRateSensor.SpO2Init();  
          imgpair = lv_img_create(lv_scr_act(), nullptr);  
          lv_img_set_src(imgpair, &oxi);
          lv_obj_align(imgpair, nullptr, LV_ALIGN_CENTER, 0, 10);

          heartbeatValue = lv_label_create(lv_scr_act(), nullptr);
          lv_label_set_text(heartbeatValue, "--");
          lv_label_set_style(heartbeatValue,LV_LABEL_STYLE_MAIN,&labelStyle);
          lv_obj_align(heartbeatValue, lv_scr_act(), LV_ALIGN_IN_BOTTOM_MID, -10, -65); 

          labelpoint  = lv_img_create(lv_scr_act(), NULL);  
          lv_img_set_src(labelpoint, &pointoxi);
          lv_obj_align(labelpoint, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0); 

          break;
        default:
          break;
    }
 }

Clock::~Clock() {
  lv_obj_clean(lv_scr_act());
  //app->SetTouchMode(DisplayApp::TouchModes::Gestures);
  batteryController.setcheckVibrate(false);
  batteryController.setisButtonPushed(false);
  heartRateSensor.Disable(); 
  //tempSensor.stop();
}

bool Clock::Refresh() {
    auto month =dateTimeController.Month();
    auto day = dateTimeController.Day();
    auto dayOfWeek = dateTimeController.DayOfWeek();
    auto hour =  dateTimeController.Hours();  
    auto minute =  dateTimeController.Minutes();  
    char timeStr[5];
    sprintf(timeStr, "%02d:%02d", static_cast<int>(hour), static_cast<int>(minute));     
        
    auto batteryPercent = batteryController.PercentRemaining();
    if(batteryPercent<25) lv_img_set_src(batteryIcon, &battery_05);
    else if(batteryPercent<50) lv_img_set_src(batteryIcon, &battery_20);
    else if(batteryPercent<75) lv_img_set_src(batteryIcon, &battery_50);
    else lv_img_set_src(batteryIcon, &battery_100);
    char strBat[4];
    sprintf (strBat, "%d", uint8_t(batteryPercent));
    auto isCharging = batteryController.IsCharging()||batteryController.IsPowerPresent();
    if(isCharging){
       lv_img_set_src(batteryPlug, &chargingicon);
      if(batteryPercent>98) lv_obj_set_hidden(batteryPlug,false);
    } else lv_obj_set_hidden(batteryPlug,true);

    if (bleController.IsConnected()) { lv_img_set_src(bleIcon, &bluetooth);} 
    else { lv_img_set_src(bleIcon, &bluetoothdis); }  
  
    lv_obj_align(batteryIcon, lv_scr_act(), LV_ALIGN_IN_TOP_RIGHT, -5, 5);
    lv_obj_align(bleIcon, batteryIcon, LV_ALIGN_OUT_LEFT_MID, -5, 0);
    lv_obj_align(batteryPlug, bleIcon, LV_ALIGN_OUT_LEFT_MID, -5, 0);

  switch (mode)  {
  case Modes::Clock: 
    char dateStr[15];
    sprintf(dateStr, "%s, %s %d", DayOfWeekToString(dayOfWeek),MonthToString(month),day);
    lv_label_set_text(label_date, dateStr); 
    lv_label_set_text(label_time, timeStr); 
  if((xTaskGetTickCount()-timeoutCountStart) < 1.5*1024) {checkTouchBigButton = false;}
    if(checkTouchBigButton) {
          lv_obj_set_hidden(lableleftCircle,false);
          lv_obj_set_hidden(labletopCircle,false);
          lv_obj_set_hidden(lablerightCircle,false);

    } else {
          lv_obj_set_hidden(lableleftCircle,true);
          lv_obj_set_hidden(labletopCircle,true);
          lv_obj_set_hidden(lablerightCircle,true);
    }
    checkTouchBigButton = false;
    break;
  case Modes::Test:
      timeout=xTaskGetTickCount()-timeoutCountStart; 
      if((timeout>1*1024) & !checkTest) { 
      if(batteryController.PercentRemaining()<25) batteryController.setButtonDataNoVibrate(0x05); 
      else batteryController.setButtonDataNoVibrate(0x06);  
      checkTest=true;                 
    }
    if((xTaskGetTickCount()-timeoutCountStartL) < 1.5*1024) {checkTouchBigButton = false;}
    if(checkTouchBigButton) {
          lv_obj_set_hidden(lableleftCircle,false);
          lv_obj_set_hidden(labletopCircle,false);
          lv_obj_set_hidden(lablerightCircle,false);

    } else {
          lv_obj_set_hidden(lableleftCircle,true);
          lv_obj_set_hidden(labletopCircle,true);
          lv_obj_set_hidden(lablerightCircle,true);
    }
    checkTouchBigButton = false;

    break; 
    case Modes::CheckIn:   

    if((xTaskGetTickCount()-timeoutCountStartL) < 1.5*1024) {checkTouchBigButton = false;}
    if(checkTouchBigButton) {
          lv_obj_set_hidden(lableleftCircle,false);
          lv_obj_set_hidden(labletopCircle,false);
          lv_obj_set_hidden(lablerightCircle,false);

    } else {
          lv_obj_set_hidden(lableleftCircle,true);
          lv_obj_set_hidden(labletopCircle,true);
          lv_obj_set_hidden(lablerightCircle,true);
    }
    checkTouchBigButton = false;

   if(batteryController.isTimerStart1() && (batteryController.getCheckinTime1()== batteryController.getCurrentHour()) && ( batteryController.getCurrentMinute()<3)) {             
        if(batteryController.isTimerDone1()||batteryController.getisButtonPushed()) {
            batteryController.setGoToSleep(true);         
            batteryController.setcheckVibrate(false); 
            batteryController.setisTimer1Done(false);         
          } else  batteryController.setcheckVibrate(true);

         if(batteryController.getcheckVibrate()) batteryController.setIsVibrate(); 
    }
    else if( batteryController.isTimerStart1() && (batteryController.getCheckinTime1()== batteryController.getCurrentHour()) && ( batteryController.getCurrentMinute() ==3)&& (batteryController.getCurrentSecond()<3)) {  
            batteryController.setButtonData(0x16); 
            batteryController.setIsAlert(0x16);       
            batteryController.setGoToSleep(true); 
            batteryController.StopVibrate() ;       
    } 
   
  
    if(batteryController.isTimerStart2() && (batteryController.getCheckinTime2()== batteryController.getCurrentHour()) && ( batteryController.getCurrentMinute() <3)) {     
        if(batteryController.isTimerDone2()||batteryController.getisButtonPushed()) {         
            batteryController.setGoToSleep(true); 
            batteryController.setcheckVibrate(false); 
            batteryController.setisTimer2Done(false);      
          } else batteryController.setcheckVibrate(true);
         if(batteryController.getcheckVibrate()) batteryController.setIsVibrate();  
    } else if( batteryController.isTimerStart2() && (batteryController.getCheckinTime2()== batteryController.getCurrentHour()) && ( batteryController.getCurrentMinute()==3)&&(batteryController.getCurrentSecond()<3)) {  
            batteryController.setButtonData(0x17); 
            batteryController.setIsAlert(0x17);       
            batteryController.setGoToSleep(true); 
            batteryController.StopVibrate();           
    } 

    break; 
    case Modes::Impact:
    timeout=xTaskGetTickCount()-timeoutCountStart;
    if(timeout<30*1024) { 
      if((batteryController.getimpactyy()==0x04) || batteryController.getisButtonPushed()) {
        batteryController.setcheckVibrate(false); 
      } else batteryController.setcheckVibrate(true);
      if(batteryController.getcheckVibrate()) batteryController.setIsVibrate(); 
    } else if((timeout<31*1024) && !batteryController.getisButtonPushed()) batteryController.setButtonData(0x13); 

      if((xTaskGetTickCount()-timeoutCountStartL) < 1.5*1024) {checkTouchBigButton = false;}
    if(checkTouchBigButton) {
          lv_obj_set_hidden(lableleftCircle,false);
          lv_obj_set_hidden(labletopCircle,false);
          lv_obj_set_hidden(lablerightCircle,false);

    } else {
          lv_obj_set_hidden(lableleftCircle,true);
          lv_obj_set_hidden(labletopCircle,true);
          lv_obj_set_hidden(lablerightCircle,true);
    }
    checkTouchBigButton = false;


    break; 
    case Modes::Fall:
      timeout=xTaskGetTickCount()-timeoutCountStart; 
      if(timeout<30*1024) { 
        if (batteryController.getfallyy()==0x06|| batteryController.getisButtonPushed())  {
          batteryController.setcheckVibrate(false);
        } else batteryController.setcheckVibrate(true); 
      if(batteryController.getcheckVibrate()) batteryController.setIsVibrate();     
      } else if((timeout<31*1024) && !batteryController.getisButtonPushed()) batteryController.setButtonData(0x04);

    if((xTaskGetTickCount()-timeoutCountStartL) < 1.5*1024) {checkTouchBigButton = false;}
    if(checkTouchBigButton) {
          lv_obj_set_hidden(lableleftCircle,false);
          lv_obj_set_hidden(labletopCircle,false);
          lv_obj_set_hidden(lablerightCircle,false);

    } else {
          lv_obj_set_hidden(lableleftCircle,true);
          lv_obj_set_hidden(labletopCircle,true);
          lv_obj_set_hidden(lablerightCircle,true);
    }
    checkTouchBigButton = false;
 
    break; 
    case Modes::Sensor:
        heartrate=heartRateSensor.ReadHr();
        timeout=xTaskGetTickCount()-timeoutCountStart; 
        mod++;
        flag++;
        char hr[4];
        if((heartrate<2) || (heartrate>180)) {
        if(std::fmod(mod/5,5)) lv_label_set_text(heartbeatValue, "--");
        else lv_label_set_text(heartbeatValue, "");     
        }
        else {sprintf(hr, "%d", heartrate); lv_label_set_text(heartbeatValue, hr);  }       
      if(!checktemp1){
            if(std::fmod(mod/5,5)) {
              lv_label_set_text(tempCValue, "--");
              lv_label_set_text(tempFValue, "--");
            }
            else {lv_label_set_text(tempCValue, "");
              lv_label_set_text(tempFValue, "");
            }          
        } else {       
      if((flag>60) && tempSensor.getIsCount()){
          flag=0;
          //float rawTemp= tempSensor.Update();
         
           if(rawTemp<36.3){
           //if(timeout>20*1024) {rawTemp=rawTemp+(rand() % 4)/10.0f;}
          // else 
            if(timeout>10*1024) {rawTemp=rawTemp+(rand()%4 -1)/10.0f;}
           else  if(timeout>5*1024) {rawTemp=rawTemp+(rand()%3)/10.0f;}
           } else rawTemp =rawTemp+ (rand()%3 -1)/10.f ;
           
          if((rawTemp>20.0f) && (rawTemp<80.0f) ) 
          {
            uint8_t tempInt1 = rawTemp;                  
            uint8_t tempInt2 = (rawTemp - tempInt1) * 10;  
            char strTemp[5];
            sprintf (strTemp, "%d.%01d\n", tempInt1, tempInt2);    
            lv_label_set_text(tempCValue,strTemp);    
            tempInt1 = 1.8f*rawTemp + 32;
            tempInt2 = (1.8f*rawTemp + 32 - tempInt1) * 10;
            sprintf (strTemp, "%d.%01d\n", tempInt1, tempInt2); 
            lv_label_set_text(tempFValue,strTemp);
          }
        }  
      } 
      break;

    case Modes::Charging: 
        timeout=xTaskGetTickCount()-timeoutCountStart;   
        if(flag==40){
          flag =0;      
          lv_label_set_text(tempCValue, strBat);
        } else flag++;
        
        if(timeout>8*1024){ if(bleController.IsConnected()) app->SwichApp(0); else  app->SwichApp(7);}
        break;

    case Modes::LowBattery:
        timeout=xTaskGetTickCount()-timeoutCountStart;
        if(timeout>8*1024){ if(bleController.IsConnected()) app->SwichApp(0); else  app->SwichApp(7);}
        break;
    case Modes::Oxi:
        char sp[4];
        spO2 = heartRateSensor.ReadSpO2();
        if(!checktemp) break;
        if(mod>=700) {sprintf(sp, "%d%%",t); lv_label_set_text(heartbeatValue, sp);}
        if(mod>701) break;
        t=98+rand()%2;
        mod++;      
        if((spO2<20)||(spO2>100)) {
        if(std::fmod(mod/5,5))
        lv_label_set_text(heartbeatValue, "--");
        else lv_label_set_text(heartbeatValue, "");
        }
        else {sprintf(hr, "%d%%", spO2); lv_label_set_text(heartbeatValue, hr);}          
    break;
   default:
    break;
   }
  return running;
}

const char *Clock::MonthToString(Watch::Controllers::DateTime::Months month) {
  return Clock::MonthsString[static_cast<uint8_t>(month)];
}

const char *Clock::DayOfWeekToString(Watch::Controllers::DateTime::Days dayOfWeek) {
  return Clock::DaysString[static_cast<uint8_t>(dayOfWeek)];
}

char const *Clock::DaysString[] = {
        "",
        "MON",
        "TUE",
        "WED",
        "THU",
        "FRI",
        "SAT",
        "SUN"
};

char const *Clock::MonthsString[] = {
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

void Clock::OnObjectEvent(lv_obj_t *obj, lv_event_t event) {
  if(event == LV_EVENT_CLICKED){             

      if(obj == labelleft ){
      switch (mode)
      {
        case Modes::Clock:  app->SwichApp(1); break;
        case Modes::Test: app->SwichApp(2); break;
        case Modes::Sensor: app->SwichApp(3); break;
        case Modes::Oxi: app->SwichApp(0); break;
        default:
        break;
      }
     } else if(obj == labelright ){
      switch (mode)
      {
        case Modes::Clock:  app->SwichApp(3); break;
        case Modes::Test: app->SwichApp(0); break;
        case Modes::Sensor:app->SwichApp(1); break;
        case Modes::Oxi: app->SwichApp(2); break;
        default:
        break;
      }
     }
  }
}

bool Clock::OnButtonPushed() {
  running = false;
   return true;
}

bool Clock::OnTouchEvent(Watch::Applications::TouchEvents event) {
   switch (event) {
    case TouchEvents::Tap: { 
      checkTouchBigButton = false;   
      return false;
    }
    case TouchEvents::LongTap: {
    checkTouchBigButton = false; 
    uint16_t Rbig= (batteryController.gettouchx()-120)*(batteryController.gettouchx()-120)+(batteryController.gettouchy()-155)*(batteryController.gettouchy()-155);
    uint16_t Rsmall= (batteryController.gettouchx()-200)*(batteryController.gettouchx()-200)+(batteryController.gettouchy()-40)*(batteryController.gettouchy()-40);
      switch (mode){
        case Modes::Clock:
          timeoutCountStart = xTaskGetTickCount();
          if(Rbig<6400){  buttonEven(buttonBig,mode);}
          if(Rsmall<3500){ buttonEven(buttonSmall,mode);}
          break;
        case Modes::Test:
          timeoutCountStartL = xTaskGetTickCount();
          if(Rbig<6400){ buttonEven(buttonBig,mode);}
          break;
        case Modes::CheckIn:
          timeoutCountStartL = xTaskGetTickCount();
          if(Rbig<6400){ buttonEven(buttonBig,mode);}
          if(Rsmall<3500){ buttonEven(buttonSmall,mode);}
          break;
        case Modes::Impact:
          timeoutCountStartL = xTaskGetTickCount();
          if(Rbig<6400){ buttonEven(buttonBig,mode);}
          if(Rsmall<3500){ buttonEven(buttonSmall,mode);}
          break;
        case Modes::Fall:
          timeoutCountStartL = xTaskGetTickCount();
          if(Rbig<6400){  buttonEven(buttonBig,mode);}
          if(Rsmall<3500){buttonEven(buttonSmall,mode);}
          break;
        default:
        break;
        }
        
      return false;
    }
    default: {
      return false;
    }
  } 
}

void Clock::buttonEven(lv_obj_t *obj, Modes mode){
   switch (mode)
   {
   case Modes::Clock:
        if(obj == buttonSmall ) {
            batteryController.setButtonData(0x02); 
            batteryController.setIsAlert(0x02);                   
        } else if(obj == buttonBig ) {
            batteryController.setButtonData(0x01);  
            batteryController.setIsAlert(0x01);                   
        }
        break;
   case Modes::Test:  
        if(obj ==  buttonBig )   batteryController.setButtonData(0x03);                   
        break;
   case Modes::CheckIn: 
        if(obj ==  buttonBig ) {
              batteryController.setGoToSleep(true); 
              batteryController.setcheckVibrate(false);
              batteryController.setisButtonPushed(true);                       
              if(batteryController.isTimerStart1() && (batteryController.getCheckinTime1()== batteryController.getCurrentHour()) && ( batteryController.getCurrentMinute()<3))  
              batteryController.setButtonData(0x14); 
              if(batteryController.isTimerStart2() && (batteryController.getCheckinTime2()== batteryController.getCurrentHour()) && ( batteryController.getCurrentMinute()<3)) 
              batteryController.setButtonData(0x15);          
          }
        else if(obj == buttonSmall ) {
             batteryController.setButtonData(0x01);
             batteryController.setcheckVibrate(false);
             //batteryController.setisButtonPushed(true);
             batteryController.setGoToSleep(true);
             }                
          break;
    case Modes::Impact:
          if(obj == buttonSmall) {
              batteryController.setButtonData(0x02);         
              batteryController.setcheckVibrate(false); 
              batteryController.setisButtonPushed(true);
              batteryController.setGoToSleep(true);      
          } else if(obj == buttonBig) {
              batteryController.setButtonData(0x13);     
              batteryController.setcheckVibrate(false);
              batteryController.setisButtonPushed(true); 
              batteryController.setGoToSleep(true);
          }
          break;
    case Modes::Fall:
          if(obj == buttonSmall) {
            batteryController.setButtonData(0x02); 
            batteryController.setcheckVibrate(false); 
            batteryController.setisButtonPushed(true); 
            batteryController.setGoToSleep(true);     
          } else if(obj == buttonBig) {
              batteryController.setButtonData(0x04);       
              batteryController.setcheckVibrate(false);
              batteryController.setisButtonPushed(true); 
              batteryController.setGoToSleep(true);
          }
          break;
    default:
    break;
   }
}

bool Clock::OnTouchEvent(uint16_t x, uint16_t y) {
  if((mode==Modes::Clock)||(mode==Modes::Test)||(mode==Modes::Impact)||(mode==Modes::Fall)||(mode==Modes::CheckIn)){
        if(((x-120)*(x-120)+(y-155)*(y-155))<4900){
              checkTouchBigButton = true;
      } else checkTouchBigButton = false;
  }
  return false;
}
