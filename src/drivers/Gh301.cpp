#include "Gh301.h"
#include <cmath>
#include "drivers/Gh301/gh30x.h"

using namespace Watch::Drivers;

extern "C" {
float __hardfp_sqrtf(float f) {return sqrtf(f);} 
float __hardfp_expf(float x) {return expf(x);}
float __hardfp_log10f(float x) {return log10f(x);}
float __hardfp_roundf(float x) { return roundf(x);}
float __hardfp_fabsl(float x) {return fabs(x);}
}

void Gh301::Init() {
   GH30x_module_init();
}


void Gh301::Enable(){
 gh30x_restart();
}

void Gh301::Disable() {
  user_gh30x_heart_stop();
}

uint8_t Gh301::ReadHrs() {   
  return heartrate;
}
