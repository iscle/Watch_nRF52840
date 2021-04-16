#include <libs/lvgl/lvgl.h>
#include "Warning.h"
#include "../DisplayApp.h"
#include "../../Version.h"

using namespace Watch::Applications::Screens;
LV_IMG_DECLARE(alarm);

namespace {
  static void ButtonEventHandler(lv_obj_t * obj, lv_event_t event)
  {
    Warning* screen = static_cast< Warning *>(obj->user_data);
    screen->OnButtonEvent(obj, event);
  }
}

 Warning:: Warning(Watch::Applications::DisplayApp *app,Watch::Controllers::Battery& batteryController)
                                       : Screen{app},batteryController{batteryController} {
    lv_obj_t * imgalarm = lv_img_create(lv_scr_act(), NULL);
    lv_img_set_src(imgalarm, &alarm);
    lv_obj_align(imgalarm, NULL, LV_ALIGN_CENTER, 0, -40);

    
    lv_style_init();
    buttonHelp = lv_btn_create(lv_scr_act(), nullptr);
    buttonHelp->user_data = this;
    lv_obj_align(buttonHelp, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 0, 0);
    lv_obj_set_event_cb(buttonHelp, ButtonEventHandler);  ///*Assign a callback to the button*/
    labelButtonHelp = lv_label_create(buttonHelp, nullptr);
    lv_label_set_text(labelButtonHelp, "Help");                     /*Set the labels text*/

    buttonOK = lv_btn_create(lv_scr_act(), nullptr);
    buttonOK->user_data = this;
    lv_obj_align(buttonOK, nullptr, LV_ALIGN_IN_BOTTOM_RIGHT, 0, 0);
    lv_obj_set_event_cb(buttonOK, ButtonEventHandler);
    labelButtonOK = lv_label_create(buttonOK, nullptr);
    lv_label_set_text(labelButtonOK, "OK");                     /*Set the labels text*/

    /////////////////style Button////////////////////////
    static lv_style_t style_btn_rel;                        /*A variable to store the released style*/
    lv_style_copy(&style_btn_rel, &lv_style_btn_rel);         /*Initialize from a built-in style*/
    style_btn_rel.body.border.color = LV_COLOR_ORANGE;
    style_btn_rel.body.border.width = 0;
    style_btn_rel.body.main_color =LV_COLOR_GREEN;
    style_btn_rel.body.grad_color = LV_COLOR_GREEN;
    style_btn_rel.body.shadow.width = 0;
    style_btn_rel.body.shadow.type = LV_SHADOW_BOTTOM;
    style_btn_rel.body.radius = LV_RADIUS_CIRCLE;
    style_btn_rel.text.color = lv_color_hex3(0xDEF);

    static lv_style_t style_btn_rel_help;                        /*A variable to store the released style*/
    lv_style_copy(&style_btn_rel_help, &lv_style_btn_rel);         /*Initialize from a built-in style*/
    style_btn_rel_help.body.border.color = LV_COLOR_ORANGE;
    style_btn_rel_help.body.border.width = 0;
    style_btn_rel_help.body.main_color =LV_COLOR_RED;
    style_btn_rel_help.body.grad_color = LV_COLOR_RED;
    style_btn_rel_help.body.shadow.width = 0;
    style_btn_rel_help.body.shadow.type = LV_SHADOW_BOTTOM;
    style_btn_rel_help.body.radius = LV_RADIUS_CIRCLE;
    style_btn_rel_help.text.color = lv_color_hex3(0xDEF);

    static lv_style_t style_btn_pr;                         /*A variable to store the pressed style*/
    lv_style_copy(&style_btn_pr, &style_btn_rel);           /*Initialize from the released style*/
    style_btn_pr.body.border.color = lv_color_hex3(0x46B);
    style_btn_pr.body.main_color = lv_color_hex3(0x8BD);
    style_btn_pr.body.grad_color = lv_color_hex3(0x24A);
    style_btn_pr.body.shadow.width = 0;
    style_btn_pr.text.color = lv_color_hex3(0xBCD);

    lv_btn_set_style(buttonOK, LV_BTN_STYLE_REL, &style_btn_rel);    /*Set the button's released style*/
    lv_btn_set_style(buttonOK, LV_BTN_STYLE_PR, &style_btn_pr);      /*Set the button's pressed style*/
    lv_btn_set_style(buttonHelp, LV_BTN_STYLE_REL, &style_btn_rel_help);    /*Set the button's released style*/
    lv_btn_set_style(buttonHelp, LV_BTN_STYLE_PR, &style_btn_pr);      /*Set the button's pressed style*/
    ////////////////Lable////////////////////
    lv_obj_t * labelOK = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_long_mode(labelOK,LV_LABEL_LONG_EXPAND);     /*Break the long lines*/
    lv_label_set_recolor(labelOK, true);                      /*Enable re-coloring by commands in the text*/
    lv_obj_align(labelOK, NULL,  LV_ALIGN_IN_BOTTOM_RIGHT, -20, -25);
    lv_label_set_text(labelOK, "OK");

    lv_obj_t * labelHelp = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_long_mode(labelHelp,LV_LABEL_LONG_EXPAND);     /*Break the long lines*/
    lv_label_set_recolor(labelHelp, true);                      /*Enable re-coloring by commands in the text*/
    lv_obj_align(labelHelp, NULL,  LV_ALIGN_IN_BOTTOM_LEFT, 20, -25);
    lv_label_set_text(labelHelp, "HELP");
}



Warning::~ Warning() {
  lv_obj_clean(lv_scr_act());
}

bool  Warning::Refresh() {
  return running;
}

bool Warning::OnButtonPushed() {
  running = false;
  return true;
}


void Warning::OnButtonEvent(lv_obj_t *object, lv_event_t event) {  
  if(object == buttonOK && event == LV_EVENT_PRESSED) {
    batteryController.setButtonData(0x02);    
    //running  = false;
  } else if(object == buttonHelp && event == LV_EVENT_PRESSED) {
    batteryController.setButtonData(0x01);    
  }
  batteryController.setIsTouch(true);
}