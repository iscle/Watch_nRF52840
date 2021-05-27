#include "Acnt101Adc.h"
#include <hal/nrf_gpio.h>
#include <libraries/log/nrf_log.h>
#include <algorithm>
#include "SEGGER_RTT.h" 

using namespace Watch::Drivers;
#define  pinTempOut      NRF_GPIO_PIN_MAP(1,3) 
void Acnt101Adc::Init() {
   nrf_gpio_cfg_output(pinTempOut); // set the temp pin as an output 
 nrf_gpio_pin_clear(pinTempOut);
  nrfx_saadc_config_t adcConfig = NRFX_SAADC_DEFAULT_CONFIG;
  nrfx_saadc_init(&adcConfig, SaadcEvenTemptHandler);
  nrf_saadc_channel_config_t adcChannelConfig = {
        .resistor_p = NRF_SAADC_RESISTOR_DISABLED,
          .resistor_n = NRF_SAADC_RESISTOR_DISABLED,
          .gain       = NRF_SAADC_GAIN1_6,
          .reference  = NRF_SAADC_REFERENCE_INTERNAL,
          .acq_time   = NRF_SAADC_ACQTIME_3US,
          .mode       = NRF_SAADC_MODE_SINGLE_ENDED,
          .burst      = NRF_SAADC_BURST_DISABLED,
          .pin_p      = tempVoltageAdcInput,
          .pin_n      = NRF_SAADC_INPUT_DISABLED  };
  nrfx_saadc_channel_init(0, &adcChannelConfig);
};

void Acnt101Adc::Update() {
  nrf_saadc_value_t value = 0;
  nrfx_saadc_sample_convert(0, &value); 
  voltage=value;
  SEGGER_RTT_printf(0, "temp=%d\n",(int)voltage);
}

void Acnt101Adc::SaadcEvenTemptHandler(nrfx_saadc_evt_t const * event) {

}
