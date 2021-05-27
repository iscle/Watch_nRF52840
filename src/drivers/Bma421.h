#pragma once

#include <drivers/Bma421_C/bma4_defs.h>
#include "drivers/Bma421_C/bma250.h"
#include "drivers/Bma421_C/bma423.h"

#define KX022_DEFAULT_SLAVE_ADDRESS (0x1E << 1)
#define KX022_WAI_VAL         (0x14)
 
#define KX022_XOUT_L          (0x06)
#define KX022_XOUT_H          (0x07)
#define KX022_YOUT_L          (0x08)
#define KX022_YOUT_H          (0x09)
#define KX022_ZOUT_L          (0x0A)
#define KX022_ZOUT_H          (0x0B)
#define KX022_WHO_AM_I        (0x0F)
#define KX022_CNTL1           (0x18)
#define KX022_CNTL3           (0x1A)
#define KX022_ODCNTL          (0x1B)
#define KX022_TILT_TIMER      (0x22)

namespace Watch {
  namespace Drivers {
    class TwiMaster;
    class Bma421 {
      public:
        struct Values {
          uint32_t steps;
          int16_t x;
          int16_t y;
          int16_t z;
        };
        Bma421(TwiMaster& twiMaster, uint8_t twiAddress);
        Bma421(const Bma421&) = delete;
        Bma421& operator=(const Bma421&) = delete;
        Bma421(Bma421&&) = delete;
        Bma421& operator=(Bma421&&) = delete;
        void Reset();
        void Init();
        Values Process();
        void Read(uint8_t registerAddress, uint8_t *buffer, size_t size);
        void Write(uint8_t registerAddress, const uint8_t *data, size_t size);

      private:
        TwiMaster& twiMaster;
        uint8_t twiAddress;
        struct bma4_dev bma;
        struct bma2x2_t bma2x2;
        struct bma4_accel_config accel_conf;
        static constexpr uint8_t deviceAddress = 0x18;
    };
  }
}