#include "Fall.h"

#include <date/date.h>
#include <lvgl/lvgl.h>
#include <cstdio>
#include "BatteryIcon.h"
#include "BleIcon.h"
#include "Symbols.h"
#include "components/battery/BatteryController.h"
#include "components/ble/BleController.h"
#include "../DisplayApp.h"
#include "displayapp/icons/sending/sending.c"
#include "creatsymbol.h"

using namespace Watch::Applications::Screens;

extern lv_font_t San_Francisco_22;

extern lv_style_t* LabelBigStyle;
extern lv_style_t* LabelSanStyle;

LV_IMG_DECLARE(sending);
static void event_handler(lv_obj_t * obj, lv_event_t event) {
  Fall* screen = static_cast<Fall *>(obj->user_data);
  screen->OnObjectEvent(obj, event);
}


Fall::Fall(DisplayApp* app,
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

  //lv_label_set_style(labeleft, LV_LABEL_STYLE_MAIN, &style);
*/
creatSymbol();
  //batteryIcon = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_text(batteryIcon, Symbols::batteryFull);
  lv_obj_align(batteryIcon, lv_scr_act(), LV_ALIGN_IN_TOP_RIGHT, -5, 2);

  //batteryPlug = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_text(batteryPlug, Symbols::plug);
  lv_obj_align(batteryPlug, batteryIcon, LV_ALIGN_OUT_LEFT_MID, -5, 0);

  //bleIcon = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_text(bleIcon, Symbols::bluetooth);
  lv_obj_align(bleIcon, batteryPlug, LV_ALIGN_OUT_LEFT_MID, -5, 0);

  //label_time = lv_label_create(lv_scr_act(), nullptr);
   lv_label_set_text(label_time, "00:00");  
  lv_label_set_style(label_time, LV_LABEL_STYLE_MAIN, LabelBigStyle);
  lv_obj_align(label_time, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, 0, 0);

    buttonHelp = lv_btn_create(lv_scr_act(), nullptr);
    buttonHelp->user_data = this;
    lv_obj_align(buttonHelp, NULL, LV_ALIGN_CENTER, -23, -8);
    lv_obj_set_event_cb(buttonHelp,event_handler);  ///*Assign a callback to the button*/


    labelFall = lv_label_create(lv_scr_act(), nullptr);
    lv_label_set_text(labelFall, "Fall");                   /*Set the labels text*/
    lv_obj_align(labelFall, lv_scr_act(), LV_ALIGN_IN_BOTTOM_MID, 0, -110);

    labelButtonHelp = lv_label_create(lv_scr_act(), nullptr);
    lv_label_set_text(labelButtonHelp, "DETECTED");                   /*Set the labels text*/
     lv_obj_align(labelButtonHelp,nullptr, LV_ALIGN_IN_BOTTOM_MID, 0, -90);
    labelSending = lv_label_create(lv_scr_act(), nullptr);
    lv_label_set_text(labelSending, "Sending Alert");                   /*Set the labels text*/
     lv_obj_align(labelSending,nullptr, LV_ALIGN_IN_BOTTOM_MID, 0, -70);
 
    buttonOK = lv_btn_create(lv_scr_act(), nullptr);
    buttonOK->user_data = this;
    lv_obj_align(buttonOK, nullptr, LV_ALIGN_IN_TOP_RIGHT, 35, 40);
    lv_obj_set_event_cb(buttonOK, event_handler);
    labelButtonOK = lv_label_create(buttonOK, nullptr);
    lv_label_set_text(labelButtonOK, "X");                     /*Set the labels text*/

    /////////////////style Button////////////////////////
    static lv_style_t style_btn_rel;                        /*A variable to store the released style*/
    lv_style_copy(&style_btn_rel, &lv_style_btn_rel);         /*Initialize from a built-in style*/
    style_btn_rel.body.border.color = LV_COLOR_GREEN;
    style_btn_rel.body.border.width = 8;
    style_btn_rel.body.main_color =LV_COLOR_WHITE;
    style_btn_rel.body.grad_color = LV_COLOR_WHITE;
    //style_btn_rel.body.shadow.width = 0;
    //style_btn_rel.body.shadow.type = LV_SHADOW_BOTTOM;
    style_btn_rel.body.radius = LV_RADIUS_CIRCLE;
    //style_btn_rel.text.color = lv_color_hex3(0xDEF);

    static lv_style_t style_btn_rel_help;                        /*A variable to store the released style*/
    lv_style_copy(&style_btn_rel_help, &lv_style_btn_rel);         /*Initialize from a built-in style*/
    style_btn_rel_help.body.border.color = LV_COLOR_RED;
    style_btn_rel_help.body.border.width = 8;
    style_btn_rel_help.body.main_color =LV_COLOR_WHITE;
    style_btn_rel_help.body.grad_color = LV_COLOR_WHITE;
    //style_btn_rel_help.body.shadow.width = 0;
    //style_btn_rel_help.body.shadow.type = LV_SHADOW_BOTTOM;
    style_btn_rel_help.body.radius = LV_RADIUS_CIRCLE;
    //style_btn_rel_help.text.color = lv_color_hex3(0xDEF);

    static lv_style_t style_btn_pr;                         /*A variable to store the pressed style*/
    lv_style_copy(&style_btn_pr, &style_btn_rel);           /*Initialize from the released style*/
    //style_btn_pr.body.border.color = lv_color_hex3(0x46B);
    style_btn_pr.body.main_color = LV_COLOR_WHITE;
    style_btn_pr.body.grad_color = LV_COLOR_WHITE;
    style_btn_pr.body.shadow.width = 0;
    style_btn_pr.text.color = lv_color_hex3(0xBCD);
   
    lv_btn_set_style(buttonOK, LV_BTN_STYLE_REL, &style_btn_rel);    /*Set the button's released style*/
    lv_obj_set_size(buttonOK, 60, 60); //set the button size
    lv_btn_set_style(buttonOK, LV_BTN_STYLE_PR, &style_btn_pr);      /*Set the button's pressed style*/
    lv_btn_set_style(buttonHelp, LV_BTN_STYLE_REL, &style_btn_rel_help);    /*Set the button's released style*/
    lv_btn_set_style(buttonHelp, LV_BTN_STYLE_PR, &style_btn_pr);      /*Set the button's pressed style*/
    lv_obj_set_size(buttonHelp, 150, 150); //set the button size

    labelRelStyle = const_cast<lv_style_t *>(lv_label_get_style(buttonOK, LV_BTN_STYLE_REL));  
    labelRelStyle->text.font = &San_Francisco_22;
    labelRelStyle->text.color=LV_COLOR_GREEN;
    lv_btn_set_style(buttonOK, LV_BTN_STYLE_REL, labelRelStyle);

    labelRelStyle = const_cast<lv_style_t *>(lv_label_get_style(buttonHelp, LV_BTN_STYLE_REL));  
    labelRelStyle->text.font = &San_Francisco_22;
    labelRelStyle->text.color=LV_COLOR_RED;
    lv_label_set_style(labelFall, LV_LABEL_STYLE_MAIN,labelRelStyle);
    lv_label_set_style(labelButtonHelp, LV_LABEL_STYLE_MAIN,labelRelStyle);

    static lv_style_t  templabelStyle;
    lv_style_copy(& templabelStyle, &lv_style_plain);
    templabelStyle.text.font = &San_Francisco_22;
    templabelStyle.text.color=LV_COLOR_ORANGE;
    lv_label_set_style( labelSending,LV_LABEL_STYLE_MAIN,&templabelStyle);


  lv_obj_t * imgsending = lv_img_create(lv_scr_act(), nullptr);
  lv_img_set_src(imgsending, &sending);
  lv_obj_align(imgsending,nullptr,LV_ALIGN_IN_BOTTOM_MID, 0, -25);
 
}

Fall::~Fall() {
  lv_obj_clean(lv_scr_act());
}

bool Fall::Refresh() {
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


void Fall::OnObjectEvent(lv_obj_t *obj, lv_event_t event) {

  if(event == LV_EVENT_CLICKED){
    if(obj == buttonOK ) {
        //batteryController.setButtonData(0x02); 
        //batteryController.setIsTouch(true);   
      checkButton=1;
    } else if(obj == buttonHelp ) {
        batteryController.setButtonData(0x04); 
        batteryController.setIsTouch(true); 
        batteryController.setIsVibrate();
    checkButton=2;
    }
  }
}

bool Fall::OnButtonPushed() {
  running = false;
  return false;
}

