#pragma once

#include <cstdint>

namespace Watch {
  namespace Controllers {
    class MotionController {
      public:
        void Update(uint16_t x, uint16_t y, uint16_t z, uint32_t nbSteps);

        uint16_t X() const { return x; }
        uint16_t Y() const { return y; }
        uint16_t Z() const { return z; }
        uint32_t NbSteps() { return nbSteps; }
      private:
        uint32_t nbSteps;
        uint16_t x;
        uint16_t y;
        uint16_t z;
    };
  }
}
