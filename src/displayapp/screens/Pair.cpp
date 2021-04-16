#include "Pair.h"
#include <displayapp/DisplayApp.h>
#include "Symbols.h"
#include "components/battery/BatteryController.h"
#include "components/ble/BleController.h"
LV_IMG_DECLARE(battery_05);
LV_IMG_DECLARE(battery_20);
LV_IMG_DECLARE(battery_50);
LV_IMG_DECLARE(battery_100);
LV_IMG_DECLARE(bluetooth);
LV_IMG_DECLARE(bluetoothdis);
LV_IMG_DECLARE(pairdis);
extern lv_style_t* LabelSanStyle;

using namespace Watch::Applications::Screens;
LV_IMG_DECLARE(pair);
LV_IMG_DECLARE(pairdis);
Pair::Pair(DisplayApp *app,
      Controllers::Battery& batteryController,
      Controllers::Ble& bleController,
      Modes mode ) : Screen(app), 
                 batteryController{batteryController},
                 bleController{bleController},
                 mode{mode} {

  batteryPlug = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(batteryPlug, "");
  lv_obj_align(batteryPlug, batteryIcon, LV_ALIGN_OUT_LEFT_MID, -5, 0);

  bleIcon =  lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(bleIcon, &bluetooth);
  lv_obj_align(bleIcon, batteryPlug, LV_ALIGN_OUT_LEFT_MID, -5, 0);

  logo = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_style(logo, LV_LABEL_STYLE_MAIN, LabelSanStyle);
  lv_label_set_text(logo, "OEM Name"); 
  lv_obj_align(logo, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, 0, 0); 

  batteryIcon = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(batteryIcon, &battery_100);
  lv_obj_align(batteryIcon, NULL, LV_ALIGN_IN_TOP_RIGHT, -5, 2);        


  imgpair = lv_img_create(lv_scr_act(), NULL);  
  lv_img_set_src(imgpair, &pairdis);
  lv_obj_align(imgpair, NULL, LV_ALIGN_CENTER, 0, 0);   


  
}

Pair::~Pair() {
  lv_obj_clean(lv_scr_act());
}

bool Pair::Refresh() {

    auto batteryPercent = batteryController.PercentRemaining();
    if(batteryPercent<25) lv_img_set_src(batteryIcon, &battery_05);
    else if(batteryPercent<50) lv_img_set_src(batteryIcon, &battery_20);
    else if(batteryPercent<75) lv_img_set_src(batteryIcon, &battery_50);
    else lv_img_set_src(batteryIcon, &battery_100);
    
    auto isCharging = batteryController.IsCharging()||batteryController.IsPowerPresent();
    if(isCharging){
      lv_label_set_text(batteryPlug, Symbols::plug);
      if(batteryPercent>98) lv_label_set_text(batteryPlug, Symbols::pause);
      if(batteryPercent<10) lv_label_set_text(batteryPlug, Symbols::warning);
    } else lv_label_set_text(batteryPlug, ""); 

    if (bleController.IsConnected()) { lv_img_set_src(bleIcon, &bluetooth);} 
    else { lv_img_set_src(bleIcon, &bluetoothdis); }  
  
    lv_obj_align(batteryIcon, lv_scr_act(), LV_ALIGN_IN_TOP_RIGHT, -5, 5);
    lv_obj_align(batteryPlug, batteryIcon, LV_ALIGN_OUT_LEFT_MID, -5, 0);
    lv_obj_align(bleIcon, batteryPlug, LV_ALIGN_OUT_LEFT_MID, -5, 0);



  

  return running;
}




bool Pair::OnButtonPushed() {
  running = false;
  return true;
}


