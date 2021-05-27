#pragma once

#include <lvgl/src/lv_core/lv_obj.h>
#include <chrono>
#include <cstdint>
#include <memory>
#include "Screen.h"
#include "components/datetime/DateTimeController.h"
#include "displayapp/icons/battery/lowbattery.c"

namespace Watch {
  namespace Controllers {
    class Battery;
    class HeartRateController;
    class Ble;
    class NotificationManager;
  }

  namespace Applications {
    namespace Screens {

      template <class T>
      class DirtyVa {
        public:
          explicit DirtyVa(T v) { value = v; }
          explicit DirtyVa(T& v) { value = v; }
          bool IsUpdated() const { return isUpdated; }
          T& Get() { this->isUpdated = false; return value; }

          DirtyVa& operator=(const T& other) {
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
      class Battery : public Screen {
        public:
          Battery(DisplayApp* app,
                  Controllers::DateTime& dateTimeController,
                  Controllers::Battery& batteryController,
                  Controllers::Ble& bleController);
          ~Battery() override;

          bool Refresh() override;
          bool OnButtonPushed() override;
         
        private:
        
       
          char displayedChar[5];


          DirtyVa<float> batteryPercentRemaining  {0};
          DirtyVa<bool> bleState {false};
          DirtyVa<std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>> currentDateTime;
          DirtyVa<uint32_t> stepCount  {0};
          DirtyVa<uint8_t> heartbeat  {0};
          DirtyVa<bool> notificationState {false};

          lv_obj_t* label_time;
          lv_obj_t* label_date;
          lv_obj_t* backgroundLabel;
          lv_obj_t* batteryIcon;
          lv_obj_t* bleIcon;
          lv_obj_t* batteryPlug;
          lv_obj_t* labelLowBattery;
          lv_obj_t* notificationIcon;
          lv_obj_t* heartbeatValue;
          lv_obj_t*labelButtonHelp;          
          lv_obj_t* labelButtonOK;         
          lv_obj_t* labelright;  
          lv_obj_t* labelpoint;        
          lv_style_t* labelRelStyle;
          lv_style_t style;

          Controllers::DateTime& dateTimeController;
          Controllers::Battery& batteryController;
          Controllers::Ble& bleController;
          bool running = true;
          uint16_t checkButton=0;
          lv_point_t timeoutLinePoints[2]  { {0, 237}, {239, 237} };
          lv_obj_t* timeoutLine;
          lv_obj_t* button; 
          uint32_t timeoutTickCountStart;
          uint32_t timeoutTickCountEnd;

      };
    }
  }
}
