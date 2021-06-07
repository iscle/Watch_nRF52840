#pragma once

#include <FreeRTOS.h>
#include <timers.h>
#include <nrfx_gpiote.h>

void nrfx_gpiote_evt_handler(nrfx_gpiote_pin_t pin, nrf_gpiote_polarity_t action);
void nrfx_gpiote_temp_evt_handler(nrfx_gpiote_pin_t pin, nrf_gpiote_polarity_t action);
void Time_IRQHandler(void * p_context);
//void DebounceTimerCallback(TimerHandle_t xTimer);