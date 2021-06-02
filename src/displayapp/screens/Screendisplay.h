#pragma once

#include <lvgl/src/lv_core/lv_obj.h>
#include <chrono>
#include <cstdint>
#include <memory>
#include "nrf_delay.h"
#include "Screen.h"
#include "components/datetime/DateTimeController.h"
#include "drivers/Acnt101.h"
#include <drivers/Gh301.h>

namespace Watch {
  namespace Controllers {
    class Battery;
    class Ble;
  }

  namespace Applications {
    namespace Screens {

      template <class T>
      class DirtyValueS {
        public:
          explicit DirtyValueS(T v) { value = v; }
          explicit DirtyValueS(T& v) { value = v; }
          bool IsUpdated() const { return isUpdated; }
          T& Get() { this->isUpdated = false; return value; }

          DirtyValueS& operator=(const T& other) {
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
      class Screendisplay : public Screen {
        public:
         enum class Modes {Clock, Test, Sensor, CheckIn, Impact,Fall,Firmware};
          Screendisplay(DisplayApp* app,
                  Controllers::DateTime& dateTimeController,
                  Controllers::Battery& batteryController,
                  Controllers::Ble& bleController,
                  Watch::Drivers::Acnt101& tempSensor,
                  Modes mode
                 // Controllers::NotificationManager& notificatioManager
                  );
          ~Screendisplay() override;

          bool Refresh() override;
          bool OnButtonPushed() override;

          void OnObjectEvent(lv_obj_t *pObj, lv_event_t i);
        private:

         // bool OnTouchEvent(TouchEvents event);
          static const char* MonthToString(Watch::Controllers::DateTime::Months month);
          static const char* DayOfWeekToString(Watch::Controllers::DateTime::Days dayOfWeek);
          static char const *DaysString[];
          static char const *MonthsString[];

          uint16_t currentYear = 1970;
          Watch::Controllers::DateTime::Months currentMonth = Watch::Controllers::DateTime::Months::Unknown;
          Watch::Controllers::DateTime::Days currentDayOfWeek = Watch::Controllers::DateTime::Days::Unknown;
          uint8_t currentDay = 0;
          uint8_t currentHour = 0;
          uint8_t currentMinute = 0;        

          DirtyValueS<float> batteryPercentRemaining  {0};
          DirtyValueS<bool> bleState {false};
          DirtyValueS<std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>> currentDateTime;
          DirtyValueS<bool> notificationState {false};

          lv_obj_t* label_time;
          lv_obj_t* label_date;
          //lv_obj_t* backgroundLabel;
          lv_obj_t* batteryIcon;
          lv_obj_t* bleIcon;
          lv_obj_t* batteryPlug;
          //lv_obj_t* labeleft;
          //lv_obj_t* laberight;
          lv_obj_t* buttonHelp;
          lv_obj_t*labelButtonHelp;          
          lv_obj_t* labelButtonOK;
          lv_obj_t* buttonOK;
           lv_obj_t* buttonTest;
          //lv_obj_t* labelright;  
          // lv_obj_t* labelpoint;        
          lv_style_t* labelRelStyle;
          lv_style_t style;
          //lv_style_t newstyle;
          //lv_obj_t * arc;
           lv_obj_t* heartbeatValue;
         // lv_obj_t* heartbeatBpm;
         // lv_obj_t* stepIcon;
          lv_obj_t* tempCValue;
          //lv_obj_t* tempFValue;
          lv_obj_t* battery;
          lv_obj_t* buttonCheckin;
          lv_obj_t* img;
          // lv_obj_t* arc;


          Controllers::DateTime& dateTimeController;
          Controllers::Battery& batteryController;
          Controllers::Ble& bleController;
          Watch::Drivers::Gh301 heartRateSensor;
          Watch::Drivers::Acnt101& tempSensor;

          Modes mode = Modes::Clock;
          bool running = true;         
           uint32_t flagstick = 0;
           uint32_t max =70;


      };
    }
  }
}
