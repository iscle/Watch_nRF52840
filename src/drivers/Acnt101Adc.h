#pragma once
#include <cstdint>
#include <drivers/include/nrfx_saadc.h>
#include "nrf_drv_pwm.h"
#include <array>
#include <numeric>
#include <lvgl/lvgl.h>



namespace Watch {
  namespace Drivers {
    //static constexpr uint8_t pinTempOut = 35;
    //static constexpr uint8_t pinTempIn = 34;

    class Acnt101Adc {
      public:
        void Init();
        void Update();

      private:
      static constexpr nrf_saadc_input_t tempVoltageAdcInput = NRF_SAADC_INPUT_AIN7;
      static void SaadcEvenTemptHandler(nrfx_saadc_evt_t const * p_event);

float voltage =0.0;

    };
  }
}