#pragma once

#include <lvgl/src/lv_core/lv_obj.h>
#include <chrono>
#include <cstdint>
#include <memory>
#include "Screen.h"
#include "components/datetime/DateTimeController.h"
#include "drivers/Acnt101.h"
#include <drivers/Gh301.h>


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
      class DirtyVal {
        public:
          explicit DirtyVal(T v) { value = v; }
          explicit DirtyVal(T& v) { value = v; }
          bool IsUpdated() const { return isUpdated; }
          T& Get() { this->isUpdated = false; return value; }

          DirtyVal& operator=(const T& other) {
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
      class SensorDisplay : public Screen {
        public:
          SensorDisplay(DisplayApp* app,
                  Controllers::DateTime& dateTimeController,
                  Controllers::Battery& batteryController,
                  Controllers::Ble& bleController,
                  Watch::Drivers::Acnt101& tempSensor);
          ~SensorDisplay() override;

          bool Refresh() override;
          bool OnButtonPushed() override;

        private:
        
          uint8_t currentDay = 0;
          uint8_t currentHour = 0;
          uint8_t currentMinute = 0;

          float batteryPercentRemaining ;
          DirtyVal<bool> bleState {false};
          DirtyVal<std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>> currentDateTime;

          lv_obj_t* label_time;
         // lv_obj_t* label_date;
         // lv_obj_t* backgroundLabel;
          lv_obj_t* batteryIcon;
         // lv_obj_t* tempIcon;
         // lv_obj_t* oxiIcon;
          lv_obj_t* bleIcon;
          lv_obj_t* batteryPlug;
         // lv_obj_t* heartbeatIcon;
          lv_obj_t* heartbeatValue;
         // lv_obj_t* heartbeatBpm;
         // lv_obj_t* stepIcon;
          lv_obj_t* tempCValue;
          //lv_obj_t* tempFValue;
          lv_obj_t* battery;
         // lv_obj_t* labeltempC;
         // lv_obj_t* labeltempF;
         // lv_obj_t* labeloxi;
          //lv_obj_t* labeleft;
         // lv_obj_t* laberight;
          //lv_obj_t* buttonheartbeat;
         // lv_obj_t*labelButtonHelp;          
         // lv_obj_t* labelButtontemp;
         // lv_obj_t* labelButtonoxi;
          lv_obj_t* buttontemp;
          lv_obj_t* buttonoxi;
          //lv_obj_t* labelright;  
          //lv_obj_t* labelpoint;        
          lv_style_t* labelRelStyle;
           lv_style_t* labelStyleoxi;
          
     
          Controllers::DateTime& dateTimeController;
          Controllers::Battery& batteryController;
          Watch::Drivers::Gh301 heartRateSensor;
          Controllers::Ble& bleController;
          Watch::Drivers::Acnt101& tempSensor;

          bool running = true;
          uint16_t checkButton=0;
          uint32_t flagstick = 0;
           uint32_t max =80;
      };
    }
  }
}
