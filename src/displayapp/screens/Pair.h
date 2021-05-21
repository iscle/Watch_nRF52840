#pragma once

#include <lvgl/lvgl.h>
#include <cstdint>
#include <memory>
#include "Screen.h"
#include "components/ble/NotificationManager.h"
#include "displayapp/icons/bluetooth/pair.c"
#include "displayapp/icons/bluetooth/pairdis.c"

namespace Watch {

  namespace Controllers {
    class Battery;
    class Ble;
  }

  namespace Applications {
    namespace Screens {
      class Pair : public Screen {
        public:
         enum class Modes {PairDis};
           Pair(DisplayApp* app,
          Controllers::Battery& batteryController,
          Controllers::Ble& bleController,
          Modes mode);
          ~Pair() override;

          bool Refresh() override;
          bool OnButtonPushed() override;         

        private:

         Controllers::Battery& batteryController;
          Controllers::Ble& bleController;
           Modes mode = Modes::PairDis;


          lv_obj_t* imgpair; 
          lv_obj_t* logo;
          lv_obj_t* batteryIcon;
          lv_obj_t* bleIcon;
          lv_obj_t* batteryPlug;

          bool running = true;
                  

      };
    }
  }
}
