#include "Cst816s.h"
#include <FreeRTOS.h>
#include <legacy/nrf_drv_gpiote.h>
#include <nrfx_log.h>
#include <task.h>

using namespace Watch::Drivers;

Cst816S::Cst816S(TwiMaster &twiMaster, uint8_t twiAddress) : twiMaster{twiMaster}, twiAddress{twiAddress} {

}

void Cst816S::Init() {
  nrf_gpio_cfg_output(pinReset);
  nrf_gpio_pin_set(pinReset);
  vTaskDelay(50);
  nrf_gpio_pin_clear(pinReset);
  vTaskDelay(5);
  nrf_gpio_pin_set(pinReset);
  vTaskDelay(50);

  // Wake the touchpanel up
  uint8_t dummy;
  twiMaster.Read(twiAddress, 0x15, &dummy, 1);
  vTaskDelay(5);
  twiMaster.Read(twiAddress, 0xa7, &dummy, 1);
  vTaskDelay(5);
  
  /*
  [2] EnConLR - Continuous operation can slide around
  [1] EnConUD - Slide up and down to enable continuous operation
  [0] EnDClick - Enable Double-click action
  */
  static constexpr uint8_t motionMask = 0b00000001;
  twiMaster.Write(twiAddress, 0xEC, &motionMask, 1);
  //static constexpr uint8_t irqCtl = 0b01000000;
  //twiMaster.Write(twiAddress, 0xFA, &irqCtl, 1);
 //  static constexpr uint8_t LongPressTime = 5;
 //twiMaster.Write(twiAddress, 0xFC, &LongPressTime, 1);

}


Cst816S::TouchInfos Cst816S::GetTouchInfo() {
  Cst816S::TouchInfos info;

  auto ret = twiMaster.Read(twiAddress, 0, touchData, sizeof(touchData));
  if(ret != TwiMaster::ErrorCodes::NoError) return {};

  auto nbTouchPoints = touchData[2] & 0x0f;

  uint8_t pointId = (touchData[touchIdIndex ]) >> 4;
  if(nbTouchPoints == 0 && pointId == lastTouchId) return info;

  info.isTouch = true;

  auto xHigh = touchData[touchXHighIndex ] & 0x0f;
  auto xLow = touchData[touchXLowIndex ];
  uint16_t x = (xHigh << 8) | xLow;

  auto yHigh = touchData[touchYHighIndex ] & 0x0f;
  auto yLow = touchData[touchYLowIndex ];
  uint16_t y = (yHigh << 8) | yLow;

  auto action = touchData[touchEventIndex] >> 6; /* 0 = Down, 1 = Up, 2 = contact*/

  info.x = 240-y;
  info.y = 240-x;
  info.action = action;
  info.gesture = static_cast<Gestures>(touchData[gestureIndex]);

  return info;
}

void Cst816S::Sleep() {
  nrf_gpio_pin_clear(pinReset);
  vTaskDelay(5);
  nrf_gpio_pin_set(pinReset);
  vTaskDelay(50);
  static constexpr uint8_t sleepValue = 0x03;
  twiMaster.Write(twiAddress, 0xA5, &sleepValue, 1);
 // NRF_LOG_INFO("[TOUCHPANEL] Sleep");
}

void Cst816S::Wakeup() {
  Init();
 // NRF_LOG_INFO("[TOUCHPANEL] Wakeup");
}