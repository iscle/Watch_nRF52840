#pragma once

#include <memory>
#include "Screen.h"
#include "ScreenList.h"

namespace Watch {
  namespace Controllers {
    class DateTime;
    class Battery;
    class Ble;
  }

  namespace Drivers {
    class WatchdogView;
  }

  namespace Applications {
    class DisplayApp;

    namespace Screens {
      class SystemInfo : public Screen {
        public:
          explicit SystemInfo(DisplayApp* app,
                              Watch::Controllers::DateTime& dateTimeController,
                              Watch::Controllers::Battery& batteryController,
                              Watch::Controllers::Ble& bleController,
                              Watch::Drivers::WatchdogView& watchdog);
          ~SystemInfo() override;
          bool Refresh() override;
          bool OnButtonPushed() override;
          bool OnTouchEvent(TouchEvents event) override;
        private:
          bool running = true;

          Watch::Controllers::DateTime& dateTimeController;
          Watch::Controllers::Battery& batteryController;
          Watch::Controllers::Ble& bleController;
          Watch::Drivers::WatchdogView& watchdog;

          char t1[200];
          char t2[200];
          char t3[200];

          ScreenList<3> screens;
          std::unique_ptr<Screen> CreateScreen1();
          std::unique_ptr<Screen> CreateScreen2();
          std::unique_ptr<Screen> CreateScreen3();
      };
    }
  }
}