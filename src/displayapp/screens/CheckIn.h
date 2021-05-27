#pragma once

#include <lvgl/src/lv_core/lv_obj.h>
#include <chrono>
#include <cstdint>
#include <memory>
#include "Screen.h"
#include "components/datetime/DateTimeController.h"


namespace Watch {
  namespace Controllers {
    class Battery;
    class HeartRateController;
    class Ble;
  }

  namespace Applications {
    namespace Screens {

      template <class T>
      class DirtyValueC {
        public:
          explicit DirtyValueC(T v) { value = v; }
          explicit DirtyValueC(T& v) { value = v; }
          bool IsUpdated() const { return isUpdated; }
          T& Get() { this->isUpdated = false; return value; }

          DirtyValueC& operator=(const T& other) {
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
      
      class CheckIn : public Screen {
        public:
          CheckIn(DisplayApp* app,
                  Controllers::DateTime& dateTimeController,
                  Controllers::Battery& batteryController,
                  Controllers::Ble& bleController);
          ~CheckIn() override;

          bool Refresh() override;
          bool OnButtonPushed() override;

          void OnObjectEvent(lv_obj_t *pObj, lv_event_t i);
        private:        

       
          uint8_t currentHour = 0;
          uint8_t currentMinute = 0;  
          DirtyValueC<float> batteryPercentRemaining  {0};
          DirtyValueC<bool> bleState {false};
          DirtyValueC<std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>> currentDateTime;

          lv_obj_t* label_time;
          //lv_obj_t* label_date;
         // lv_obj_t* backgroundLabel;
          lv_obj_t* batteryIcon;
          lv_obj_t* bleIcon;
          lv_obj_t* batteryPlug;
          //lv_obj_t* labeleft;
          //lv_obj_t* laberight;
          lv_obj_t* buttonCheckin;
          //lv_obj_t*labelbuttonTest;          
          //lv_obj_t* labelright;  
          // lv_obj_t* labelpoint;        
          ///lv_style_t* labelRelStyle;
          //lv_style_t style;

          Controllers::DateTime& dateTimeController;
          Controllers::Battery& batteryController;
          Controllers::Ble& bleController;
          bool running = true;
          uint16_t checkButton=0;

      };
    }
  }
}
