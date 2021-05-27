#pragma once

#include <cstdint>
#include "VchR02/module_heart_vc_int.h"
namespace Watch {
  namespace Drivers {
    class VchR02 {
      public:

      void HrInit();
      void Enable();
      void Disable();
      uint8_t ReadHr();
      uint8_t ReadAls();
      uint8_t ReadSpO2();
      void SpO2Init();
      void TempInt();

      private:
 

    };
  }
}
