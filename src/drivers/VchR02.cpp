#include "VchR02.h"
#include <cmath>

using namespace Watch::Drivers;

extern "C" {
float __hardfp_sqrt(float f) {return sqrt(f);} 
//float __hardfp_expf(float x) {return expf(x);}
//float __hardfp_log10f(float x) {return log10f(x);}
//float __hardfp_roundf(float x) { return roundf(x);}
//float __hardfp_fabsl(float x) {return fabs(x);}
float __hardfp_ceil(float x) {return ceil(x);}
float __hardfp_floor(float x) {return floor(x);}
float __hardfp_fmod(float x,float y) {return fmod(x,y);}
float __hardfp_cos(float x){return cos(x);}
float __hardfp_sin(float x){return sin(x);}

}


void VchR02::HrInit() {
  nrf_gpio_cfg_output(17);
  nrf_gpio_pin_set(17); 
  HeartInt();
}

void VchR02::SpO2Init() {
  nrf_gpio_cfg_output(17);
  nrf_gpio_pin_set(17); 
  SpO2Int();
}
void VchR02::TempInt() {
  nrf_gpio_cfg_output(17);
  nrf_gpio_pin_set(17); 
  TempInt();
}
void VchR02::Enable(){
HeartSpO2Int();
}

void VchR02::Disable() {
  Stopprocess();
}

uint8_t VchR02::ReadHr() { 
  process();  
  return HeartRateValue;
}

uint8_t VchR02::ReadSpO2() { 
  process();  
  return real_spo;
}
