#pragma once

#include <cstdint>
#include "Screen.h"
#include <bits/unique_ptr.h>
#include <libs/lvgl/src/lv_core/lv_style.h>
#include <libs/lvgl/src/lv_core/lv_obj.h>
#include "displayapp/icons/screen/alarm.c"
#include "components/battery/BatteryController.h"

namespace Watch {
  namespace Controllers {
    class FirmwareValidator;
  }

  namespace Applications {
    namespace Screens {

      class Warning : public Screen{
        public:
           Warning(DisplayApp* app,Controllers::Battery& batteryController);
          ~ Warning() override;

          bool Refresh() override;
          bool OnButtonPushed() override;
          void OnButtonEvent(lv_obj_t *object, lv_event_t event);

        private:
        Watch::Controllers::Battery& batteryController;
          lv_obj_t* labelVersionInfo;
          lv_obj_t* labelVersionValue;
          char version[9];
          lv_obj_t* labelIsValidated;
          lv_obj_t* buttonHelp;
          lv_obj_t* labelButtonHelp;
          lv_obj_t* buttonOK;
          lv_obj_t* labelButtonOK;
          bool running = true;
      };
    }
  }
}
