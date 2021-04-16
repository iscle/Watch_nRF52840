#pragma once

#include <lvgl/src/lv_core/lv_obj.h>
#include <chrono>
#include <cstdint>
#include <memory>
#include "Screen.h"
#include "displayapp/icons/sending/sending.c"
#include "components/datetime/DateTimeController.h"

namespace Watch {
  namespace Controllers {
    class Battery;   
    class Ble;
  }

  namespace Applications {
    namespace Screens {

      template <class T>
      class DirtyValu {
        public:
          explicit DirtyValu(T v) { value = v; }
          explicit DirtyValu(T& v) { value = v; }
          bool IsUpdated() const { return isUpdated; }
          T& Get() { this->isUpdated = false; return value; }

          DirtyValu& operator=(const T& other) {
            if (this->value != other) {
              this->value = other;
              this->isUpdated = true;
            }
            return *this;
          }
        private:
          T value;
          bool isUpdated = true;
      };
      class Impact : public Screen {
        public:
          Impact(DisplayApp* app,
                  Controllers::DateTime& dateTimeController,
                  Controllers::Battery& batteryController,
                  Controllers::Ble& bleController);
          ~Impact() override;

          bool Refresh() override;
          bool OnButtonPushed() override;

          void OnObjectEvent(lv_obj_t *pObj, lv_event_t i);
        private:

          uint8_t currentDay = 0;
          uint8_t currentHour = 0;
          uint8_t currentMinute = 0;

          DirtyValu<float> batteryPercentRemaining  {0};
          DirtyValu<bool> bleState {false};
          DirtyValu<std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>> currentDateTime;
         

          lv_obj_t* label_time;
          //lv_obj_t* label_date;
          lv_obj_t* batteryIcon;
          lv_obj_t* bleIcon;
          lv_obj_t* batteryPlug;
          lv_obj_t* labelSending;
         // lv_obj_t* labeleft;
         // lv_obj_t* laberight;
          lv_obj_t* buttonHelp;
          lv_obj_t* labelButtonHelp;   
          lv_obj_t* labelButtonOK;         
          lv_obj_t* labelImpact;
          lv_obj_t* buttonOK;
         // lv_obj_t* labelright;  
         // lv_obj_t* labelpoint;        
          lv_style_t* labelRelStyle;
          lv_style_t style;

          Controllers::DateTime& dateTimeController;
          Controllers::Battery& batteryController;
          Controllers::Ble& bleController;
          bool running = true;
          uint16_t checkButton=0;

      };
    }
  }
}
