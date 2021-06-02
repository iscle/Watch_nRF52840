#include "BatteryController.h"
#include <hal/nrf_gpio.h>
#include <libraries/log/nrf_log.h>
#include <algorithm>
#include <lvgl/src/lv_core/lv_obj.h>
#include <math.h>
using namespace Watch::Controllers;
Battery *Battery::instance = nullptr;

Battery::Battery() {
  instance = this;
}

void Battery::Init() {
  nrf_gpio_cfg_input(chargingPin, (nrf_gpio_pin_pull_t)GPIO_PIN_CNF_PULL_Pullup);
  //nrf_gpio_cfg_input(powerPresentPin, (nrf_gpio_pin_pull_t)GPIO_PIN_CNF_PULL_Pullup);
  MotorControllerInit();
}

void Battery::Update() {  
  if ( isReading ) return;
  // Non blocking read
  samples = 0;
  isReading = true;
  SaadcInit();	

	nrfx_saadc_sample();
  
}

void Battery::adcCallbackStatic(nrfx_saadc_evt_t const *event) {
  instance->SaadcEventHandler(event);
}

void Battery::SaadcInit() {
  nrfx_saadc_config_t adcConfig = NRFX_SAADC_DEFAULT_CONFIG;
  APP_ERROR_CHECK(nrfx_saadc_init(&adcConfig, adcCallbackStatic));

  nrf_saadc_channel_config_t adcChannelConfig = {
          .resistor_p = NRF_SAADC_RESISTOR_DISABLED,
          .resistor_n = NRF_SAADC_RESISTOR_DISABLED,
          .gain       = NRF_SAADC_GAIN1_5,
          .reference  = NRF_SAADC_REFERENCE_INTERNAL,
          .acq_time   = NRF_SAADC_ACQTIME_3US,
          .mode       = NRF_SAADC_MODE_SINGLE_ENDED,
          .burst      = NRF_SAADC_BURST_ENABLED,
          .pin_p      = batteryVoltageAdcInput,
          .pin_n      = NRF_SAADC_INPUT_DISABLED
  };
  APP_ERROR_CHECK(nrfx_saadc_channel_init(0, &adcChannelConfig));
  APP_ERROR_CHECK(nrfx_saadc_buffer_convert(&saadc_value, 1));

}

void Battery::SaadcEventHandler(nrfx_saadc_evt_t const * p_event) {

    const float battery_max = 4.2; // maximum voltage of battery ( max charging voltage is 4.21 )
    const float battery_min = 3.7; // minimum voltage of battery before shutdown ( depends on the battery )

    if (p_event->type == NRFX_SAADC_EVT_DONE) {
      
      APP_ERROR_CHECK(nrfx_saadc_buffer_convert(&saadc_value, 1));

      voltage = (static_cast<float>(p_event->data.done.p_buffer[0]) * 2.04f) / (1024 / 3.0f);
      voltage = roundf(voltage * 100.0f) / 100.0f;

      percentRemaining = static_cast<int>(((voltage - battery_min) / (battery_max - battery_min)) * 100.0f);

      percentRemaining = std::max(percentRemaining, 0.0f);
      percentRemaining = std::min(percentRemaining, 100.0f);

      percentRemainingBuffer.insert(percentRemaining);
      samples++;
      if ( samples > percentRemainingSamples ) {
        nrfx_saadc_uninit();
        isReading = false;
      } else {
        nrfx_saadc_sample();
      }
    }
  }


void Battery::setButtonData( uint8_t data) {
      buttonData = data;
      isTouch = true;
      MotorControllerSetDuration(200);
}

void Battery::setButtonDataNoVibrate( uint8_t data) {
      buttonData = data;
      isTouch = true;
}

void Battery::setIsTouch( bool data) {  isTouch = data;}  
void Battery::setIsVibrate(void){ MotorControllerSetDuration(200);} 
void Battery::StopVibrate(void) {MotorControllerStop();}
bool Battery::IsCharging(){ return !nrf_gpio_pin_read(chargingPin);}

void Battery::impactCharacteristic(uint8_t zz, uint8_t yy){
  impactyy=yy;
  if(yy==0x03) impactzz=zz;
}

void Battery::checkinCharacteristic(uint8_t zz, uint8_t yy){
  switch (yy){
  case 0x01:
     CheckinTime1 =zz;
    break;
  case 0x02:
    CheckinTime2 =zz;
   break;
  case 0x03:
    isTimer1Start=true;
    isTimer1Display= true;
   break;
  case 0x04:
    isTimer2Start=true;
    isTimer2Display= true;
  break;
  case 0x05:
    isTimer1Start=false;
   break;
  case 0x06:
    isTimer2Start=false;
  break;
  case 0x07:
    isTimer1Done=true;
   break;
  case 0x08:
    isTimer2Done=true;
  break;
  
  default:
    break;
  }
}

void Battery::fallCharacteristic(uint8_t zz, uint8_t yy){
  fallyy=yy;
  switch (yy){
  case 0x03:
    fallHighpeak = zz;
    break;
  case 0x04:
    falltime = zz;
    break;
  case 0x05:
    fallLowpeak = zz; 
    break; 
  default:
    break;
  }
}

void Battery::trackCharacteristic(uint8_t zz, uint8_t yy,uint8_t nn){
  switch (nn){
  case 0x00:
    istracking=true;
    numtracking=zz;
    timetracking=yy;
    break;
  case 0x01:
    istracking=false;
   break;
  case 0x03:
    isheartbeat =true;
    timeheartbeat= yy;
    break;
  case 0x04:
    isheartbeat =false;    
    break;
  }
}

void Battery::setimpactyy(uint8_t data) {impactyy=data;}
void Battery::setfallyy(uint8_t data) {fallyy = data;}
void Battery::setisTimer1Done( bool data) {isTimer1Done=data;}
void Battery::setisTimer2Done( bool data) {isTimer2Done=data;}
void Battery::setCurrentHour(uint8_t data) { currentHour =data ;};
void Battery::setCurrentMinute(uint8_t data) { currentMinute = data;};
void Battery::setCurrentSecond(uint8_t data) { currentSecond= data;};
void Battery::setisTimer1Display(bool data) {isTimer1Display=data;};
void Battery::setisTimer2Display(bool data) {isTimer2Display=data;};
void Battery::setGoToSleep(bool data) {GoToSleep=data;};
void Battery::setAccData( float data) {AccData = data;}
void Battery::setTouch( uint8_t x, uint8_t y) {
  touchx=x;
  touchy=y;
}
void Battery::setIsAlert(uint8_t data){isAlert=data;}
void Battery::setIsheartbeat(bool data){isheartbeat=data;}
void Battery::setIstracking(bool data){istracking=data;}
void Battery::setIslowbattery(bool data){islowbattery=data;}
void Battery::setcheckVibrate(bool data){checkVibrate=data;}
void Battery::setisButtonPushed(bool data){isButtonPushed=data;}
void Battery::setDisturnOff(bool data){isDisturnOff=data;};

void Battery::setxyz( int8_t _x,int8_t _y,int8_t _z) {
x=_x;
y=_y;
z=_z;
}

void Battery::setXmax(int8_t x){xmax=x;};
void Battery::setYmax(int8_t y){ymax=y;};
void Battery::setZmax(int8_t z){zmax=z;};



