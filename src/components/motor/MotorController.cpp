#include "MotorController.h"
#include <hal/nrf_gpio.h>
#include "app_timer.h"
#include "nrf_drv_clock.h"

APP_TIMER_DEF(vibTimer);

#define pinMotor  24
static void lfclk_request(void) {
    nrf_drv_clock_init();
    nrf_drv_clock_lfclk_request(NULL);
}

void vibrateTimer(void * p_context){
    nrf_gpio_pin_clear(pinMotor);
}

static void create_timers(){
    app_timer_create(&vibTimer, APP_TIMER_MODE_SINGLE_SHOT, vibrateTimer);
}

void MotorControllerInit() {
    nrf_gpio_cfg_output(pinMotor); 
    nrf_gpio_pin_clear(pinMotor);
    lfclk_request();        
    app_timer_init();       
    create_timers();
}

void MotorControllerSetDuration(uint32_t motorDuration) {    
    nrf_gpio_pin_set(pinMotor);
    app_timer_start(vibTimer, APP_TIMER_TICKS(motorDuration), NULL); 
}

void MotorControllerStop(){
    nrf_gpio_pin_clear(pinMotor);
}