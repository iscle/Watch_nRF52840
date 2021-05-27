#pragma once

#include <cstdint>
#include "drivers/Gh301/hbd_ctrl.h"


namespace Watch {
  namespace Drivers {
    class Gh301 {
      public:

      void Init();
      void Enable();
      void Disable();
      uint8_t ReadHrs();
      uint8_t ReadAls();

      private:
 

    };
  }
}
