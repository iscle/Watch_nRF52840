#pragma once

#include <cstdint>
#include "Screen.h"
#include <bits/unique_ptr.h>
#include "Modal.h"
#include <lvgl/src/lv_core/lv_style.h>
#include <displayapp/Apps.h>

namespace Watch {
  namespace Applications {
    namespace Screens {
      class Tile : public Screen {
        public:
          struct Applications {
            const char* icon;
            Watch::Applications::Apps application;
          };

          explicit Tile(DisplayApp* app, std::array<Applications, 6>& applications);
          ~Tile() override;

          bool Refresh() override;
          bool OnButtonPushed() override;

          void OnObjectEvent(lv_obj_t* obj, lv_event_t event, uint32_t buttonId);

        private:
          lv_obj_t * btnm1;
          bool running = true;
          lv_style_t* labelRelStyle;
          std::unique_ptr<Modal> modal;

          const char* btnm_map1[8];
          Watch::Applications::Apps apps[6];
      };
    }
  }
}
