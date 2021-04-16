#pragma once

#include <cstdint>
#include <chrono>
#include <components/gfx/Gfx.h>
#include "Screen.h"
#include <bits/unique_ptr.h>
#include <libs/lvgl/src/lv_core/lv_style.h>
#include <libs/lvgl/src/lv_core/lv_obj.h>
#include <components/battery/BatteryController.h>
#include <components/ble/BleController.h>
#include <components/heartrate/HeartRateController.h>
#include <drivers/Gh301.h>


namespace Watch {
  namespace Applications {
    namespace Screens {

      class HeartRate : public Screen{
        public:
          HeartRate(DisplayApp* app );
          ~HeartRate() override;

          bool Refresh() override;
          bool OnButtonPushed() override;

        private:
          Watch::Drivers::Gh301 heartRateSensor;
          lv_obj_t* label_hr;
          lv_obj_t* label_bpm;
          lv_obj_t* label_status;
          lv_style_t labelBigStyle;
          lv_style_t* labelStyle;

          bool running = true;

      };
    }
  }
}