#include "Acnt101.h"
#include <hal/nrf_gpio.h>
#include "app_timer.h"
#include "nrf_drv_clock.h"
#include "main.h"
#include "boards.h"
#include "nrf_drv_ppi.h"
#include "nrf_drv_timer.h"
#include "nrf_drv_gpiote.h"
#include "SEGGER_RTT.h" 


APP_TIMER_DEF(tempTimer);

using namespace Watch::Drivers;
extern "C" {
#define  pinTempOut      NRF_GPIO_PIN_MAP(1,2) 
#define  pinTempIn      NRF_GPIO_PIN_MAP(1,3) 
}
static void lfclk_request(void){
    nrf_drv_clock_init();
    nrf_drv_clock_lfclk_request(NULL);
}

void Acnt101::setIsCount( bool data) {
is_lock_counting = data ;
}

static void create_timers(){
    app_timer_create(&tempTimer, APP_TIMER_MODE_SINGLE_SHOT, Time_IRQHandler);
}

void Acnt101::Init() { 
    nrf_gpio_cfg_output(pinTempOut);      
    nrf_gpio_cfg_sense_input(pinTempIn, (nrf_gpio_pin_pull_t)GPIO_PIN_CNF_PULL_Pullup, (nrf_gpio_pin_sense_t)GPIO_PIN_CNF_SENSE_High);
    nrfx_gpiote_in_config_t pinConfig;
    pinConfig.skip_gpio_setup = true;
    pinConfig.hi_accuracy = false;
    pinConfig.is_watcher = false;
    pinConfig.sense = (nrf_gpiote_polarity_t)NRF_GPIOTE_POLARITY_HITOLO;
    pinConfig.pull = (nrf_gpio_pin_pull_t)GPIO_PIN_CNF_PULL_Pullup;
    nrfx_gpiote_in_init(pinTempIn, &pinConfig, nrfx_gpiote_temp_evt_handler); 
    
    lfclk_request();        
    app_timer_init();       
    create_timers(); 
    nrf_gpio_pin_clear(pinTempOut); 
}

void Acnt101::timer_temp_start() {    
    app_timer_start(tempTimer, APP_TIMER_TICKS(60), NULL); 
}

void Acnt101::start() {    
     nrf_gpio_pin_clear(pinTempOut);
}

void Acnt101::stop() {    
     nrf_gpio_pin_set(pinTempOut);
}

void Acnt101::ReadData(uint32_t data)
{
     count++;
    sumtemp+=(data+110);
    if(count>10) {; 
    dataTemp=sumtemp/20.0f*0.0625f - 50.0625f;
    count =0; sumtemp=0;     
    } 
    
}