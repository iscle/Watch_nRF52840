#include <libraries/log/nrf_log.h>
#include <libraries/gpiote/app_gpiote.h>
#include <drivers/Cst816s.h>
#include "displayapp/LittleVgl.h"
#include <hal/nrf_rtc.h>
#include "components/ble/NotificationManager.h"
#include <host/ble_gatt.h>
#include <host/ble_hs_adv.h>
#include "SystemTask.h"
#include <nimble/hci_common.h>
#include <host/ble_gap.h>
#include <host/util/util.h>
#include <drivers/InternalFlash.h>
#include "main.h"
#include "components/ble/NimbleController.h"
#include "SEGGER_RTT.h" 

using namespace Watch::System;

void IdleTimerCallback(TimerHandle_t xTimer) {
  auto sysTask = static_cast<SystemTask *>(pvTimerGetTimerID(xTimer));
  sysTask->OnIdle();
}

void IdleTimerAccCallback(TimerHandle_t xTimer) {
  auto sysTask = static_cast<SystemTask *>(pvTimerGetTimerID(xTimer));
  sysTask->CheckACC();
}
void IdleTimerCommonCallback(TimerHandle_t xTimer) {
  auto sysTask = static_cast<SystemTask *>(pvTimerGetTimerID(xTimer));
  sysTask->CheckCommon();
}

void IdleTimerTrackingCallback(TimerHandle_t xTimer) {
  auto sysTask = static_cast<SystemTask *>(pvTimerGetTimerID(xTimer));
  sysTask->CheckTracking();
}

void IdleTimerHeartbeatCallback(TimerHandle_t xTimer) {
  auto sysTask = static_cast<SystemTask *>(pvTimerGetTimerID(xTimer));
  sysTask->CheckHeartbeat();
}

SystemTask::SystemTask(Drivers::SpiMaster &spi, Drivers::St7789 &lcd,
                       Watch::Drivers::SpiNorFlash& spiNorFlash,
                       Drivers::TwiMaster& twiMaster,Drivers::Cst816S &touchPanel,
                        Drivers::Kx126& motionSensor,
                       //Drivers::Kx022& motionSensor,
                       //Drivers::Gh301& heartRateSensor,
                       Components::LittleVgl &lvgl,
                       Controllers::Battery &batteryController, Controllers::Ble &bleController,
                       Controllers::DateTime &dateTimeController,
                       Watch::Controllers::NotificationManager& notificationManager,
                       Watch::Drivers::Acnt101& tempSensor) :
                       spi{spi}, lcd{lcd}, spiNorFlash{spiNorFlash},
                       twiMaster{twiMaster}, touchPanel{touchPanel},
                       lvgl{lvgl}, batteryController{batteryController},                       
                       bleController{bleController}, dateTimeController{dateTimeController},
                       watchdog{}, watchdogView{watchdog}, notificationManager{notificationManager},tempSensor{tempSensor},
                       motionSensor{motionSensor},
                       nimbleController(*this, bleController,dateTimeController, notificationManager, batteryController, spiNorFlash)                   
                       {
   systemTasksMsgQueue = xQueueCreate(10, 1);
}
void SystemTask::Start() {
  if (pdPASS != xTaskCreate(SystemTask::Process, "MAIN", 350, this, 0, &taskHandle))
    APP_ERROR_HANDLER(NRF_ERROR_NO_MEM);
}

void SystemTask::Process(void *instance) {
  auto *app = static_cast<SystemTask *>(instance);
  app->Work();
}

void SystemTask::Work() {
  watchdog.Setup(5);
  watchdog.Start();
  APP_GPIOTE_INIT(2);

  spi.Init();
  spiNorFlash.Init();
  spiNorFlash.Wakeup();
  nimbleController.Init();
  nimbleController.StartAdvertising();
  lcd.Init();

  twiMaster.Init();
  touchPanel.Init();
  batteryController.Init();
 
  heartRateSensor.Enable();
  tempSensor.Init(); 
  motionSensor.Init();

  displayApp = std::make_unique<Watch::Applications::DisplayApp>(lcd, lvgl, touchPanel, batteryController, bleController,
                                                          dateTimeController, watchdogView, *this,tempSensor);
  displayApp->Start();

  displayApp->PushMessage(Watch::Applications::DisplayApp::Messages::UpdateBatteryLevel);

  nrf_gpio_cfg_sense_input(pinButton, (nrf_gpio_pin_pull_t)GPIO_PIN_CNF_PULL_Pullup, (nrf_gpio_pin_sense_t)GPIO_PIN_CNF_SENSE_Low); 
  nrfx_gpiote_in_config_t pinConfig;
  pinConfig.skip_gpio_setup = true;
  pinConfig.hi_accuracy = false;
  pinConfig.is_watcher = false;
  pinConfig.sense = (nrf_gpiote_polarity_t)NRF_GPIOTE_POLARITY_HITOLO;
  pinConfig.pull = (nrf_gpio_pin_pull_t)GPIO_PIN_CNF_PULL_Pulldown;
  nrfx_gpiote_in_init(pinButton, &pinConfig, nrfx_gpiote_evt_handler);

  nrf_gpio_cfg_sense_input(pinTouchIrq, (nrf_gpio_pin_pull_t)GPIO_PIN_CNF_PULL_Pullup, (nrf_gpio_pin_sense_t)GPIO_PIN_CNF_SENSE_Low);
  pinConfig.pull = (nrf_gpio_pin_pull_t)GPIO_PIN_CNF_PULL_Pullup;
  nrfx_gpiote_in_init(pinTouchIrq, &pinConfig, nrfx_gpiote_evt_handler); 
/*
  nrf_gpio_cfg_sense_input(pinPowerPresentIrq, (nrf_gpio_pin_pull_t) NRF_GPIO_PIN_NOPULL, (nrf_gpio_pin_sense_t) GPIO_PIN_CNF_SENSE_Low);
  pinConfig.sense = NRF_GPIOTE_POLARITY_TOGGLE;
  pinConfig.pull = NRF_GPIO_PIN_NOPULL;
  pinConfig.is_watcher = false;
  pinConfig.hi_accuracy = false;
  pinConfig.skip_gpio_setup = true;
  nrfx_gpiote_in_init(pinPowerPresentIrq, &pinConfig, nrfx_gpiote_evt_handler);
 */
     
  idleTimer = xTimerCreate ("idleTimer", pdMS_TO_TICKS(25000), pdFALSE, this, IdleTimerCallback);
  idleTimerAcc = xTimerCreate ("idleTimerAcc", pdMS_TO_TICKS(50), pdTRUE, this, IdleTimerAccCallback);
  idleTimerCommon = xTimerCreate ("idleTimerCommon", pdMS_TO_TICKS(200), pdTRUE, this, IdleTimerCommonCallback);
  idleTimerTracking = xTimerCreate ("idleTimerAcc", pdMS_TO_TICKS(60000), pdTRUE, this, IdleTimerTrackingCallback);
  idleTimerHeartbeat = xTimerCreate ("idleTimerHeartbeat", pdMS_TO_TICKS(60000), pdTRUE, this, IdleTimerHeartbeatCallback);
  xTimerStart(idleTimer, 0);
  xTimerStart(idleTimerAcc, 0);
  xTimerStart(idleTimerCommon, 0);  
  
  // Suppress endless loop diagnostic
  #pragma clang diagnostic push
  #pragma ide diagnostic ignored "EndlessLoop"
  while(true) {
  
    uint8_t msg;
    if (xQueueReceive(systemTasksMsgQueue, &msg, 100)) {    
      Messages message = static_cast<Messages >(msg); 
      batteryController.Update();  
      switch(message) {
        case Messages::GoToRunning:       
          //spi.Wakeup();
          nimbleController.StartAdvertising();
          xTimerStart(idleTimer, 0);
          //touchPanel.Wakeup();
          lcd.Wakeup();                
          displayApp->PushMessage(Watch::Applications::DisplayApp::Messages::GoToRunning);
          displayApp->PushMessage(Watch::Applications::DisplayApp::Messages::UpdateBatteryLevel);
          isSleeping = false;
          isWakingUp = false;      
          break;
        case Messages::GoToSleep:
          xTimerStop(idleTimer, 0);
          isGoingToSleep = true;
          displayApp->PushMessage(Watch::Applications::DisplayApp::Messages::Clock);
          displayApp->PushMessage(Watch::Applications::DisplayApp::Messages::GoToSleep);
          heartRateSensor.Disable(); 
          break;
        case Messages::BleConnected:
          ReloadIdleTimer();
          nimbleController.StartDiscovery();
          if(isSleeping && !isWakingUp) GoToRunning(); 
          displayApp->PushMessage(Watch::Applications::DisplayApp::Messages::UpdateBleConnection);         
          break;
        case Messages::BleFirmwareUpdateStarted:
          batteryController.setGoToSleep(false);
          if(isSleeping && !isWakingUp) GoToRunning();
          displayApp->PushMessage(Watch::Applications::DisplayApp::Messages::BleFirmwareUpdateStarted);
          break;
        case Messages::BleFirmwareUpdateFinished:
          batteryController.setGoToSleep(true);
          xTimerStart(idleTimer, 0);
          if(bleController.State() == Watch::Controllers::Ble::FirmwareUpdateStates::Validated)
          NVIC_SystemReset();
          break;
        case Messages::OnTouchEvent:
          ReloadIdleTimer();
          if(batteryController.getDisturnOff()) break;
          batteryController.setGoToSleep(true);
          break;
        case Messages::OnButtonEvent:
          batteryController.setGoToSleep(true);
          GoToRunning();
          if(batteryController.IsCharging())    
              displayApp->PushMessage(Watch::Applications::DisplayApp::Messages::Charging); 
          else  displayApp->PushMessage(Watch::Applications::DisplayApp::Messages::Clock);
          ReloadIdleTimer();
          break;

        case Messages::TouchWakeUp: {
          auto touchInfo = touchPanel.GetTouchInfo();
          if (touchInfo.isTouch && (touchInfo.gesture == Watch::Drivers::Cst816S::Gestures::DoubleTap)) {                                                                                              
            GoToRunning();
          if(batteryController.IsCharging())    
                displayApp->PushMessage(Watch::Applications::DisplayApp::Messages::Charging); 
           else displayApp->PushMessage(Watch::Applications::DisplayApp::Messages::Clock);
          }
        } break;

        case Messages::AlwaysDisplay:
         batteryController.setGoToSleep(false);
          xTimerStart(idleTimer, 0);
          break;
        case Messages::OnDisplayTaskSleeping:         
          //lcd.DisplayOff(); 
          displayApp->PushMessage(Watch::Applications::DisplayApp::Messages::Clock);      
          lcd.Sleep();         
          //touchPanel.Sleep();
          //spi.Sleep();
          //twiMaster.Sleep();         
          isSleeping = true;
          isGoingToSleep = false;
          break;
        case Messages::OnChargingEvent:
        batteryController.setIsVibrate();
          break;
        default: break;
      }
    }

    if(batteryController.Istracking()){  
      if (batteryController.getIsAlert()!=preAlert) { 
        xTimerStart(idleTimerTracking, 0);
        checktime=0;
        checknum=0;
      }
      preAlert= batteryController.getIsAlert();
    }

    if(batteryController.Isheartbeat()&& checkheartbeat) { xTimerStart(idleTimerHeartbeat, 0); checkheartbeat = false;}

    if(batteryController.getGoToSleep())  doNotGoToSleep = false;  else doNotGoToSleep = true;  

    CheckLowbattery();  

    uint32_t systick_counter = nrf_rtc_counter_get(portNRF_RTC_REG);
    dateTimeController.UpdateTime(systick_counter);
    if(nrf_gpio_pin_read(pinButton))  watchdog.Kick();
  }
  #pragma clang diagnostic pop
}

void SystemTask::OnButtonPushed() {     
  if(isGoingToSleep) return;
  if(!isSleeping) {
    PushMessage(Messages::OnButtonEvent);
    displayApp->PushMessage(Watch::Applications::DisplayApp::Messages::ButtonPushed);
  }
  else {
    if(!isWakingUp) {
       PushMessage(Messages::OnButtonEvent);
      //GoToRunning();  
    }
  }
}

void SystemTask::GoToRunning() {
  if(isGoingToSleep || (!isSleeping) ||isWakingUp) return;
  isWakingUp = true;
  PushMessage(Messages::GoToRunning);
}

void SystemTask::OnTouchEvent() {
  if (isGoingToSleep)return;
  if (!isSleeping) {
    PushMessage(Messages::OnTouchEvent);
    displayApp->PushMessage(Watch::Applications::DisplayApp::Messages::TouchEvent);
  } else if (!isWakingUp) {
    PushMessage(Messages::TouchWakeUp);
  }
}

void SystemTask::PushMessage(SystemTask::Messages msg) {
  if(msg == Messages::GoToSleep) {
    isGoingToSleep = true;
  }
  BaseType_t xHigherPriorityTaskWoken;
  xHigherPriorityTaskWoken = pdFALSE;
  xQueueSendFromISR(systemTasksMsgQueue, &msg, &xHigherPriorityTaskWoken);
  if (xHigherPriorityTaskWoken) {
  }
}

void SystemTask::OnIdle() {
  if(doNotGoToSleep) return;
  nrf_gpio_pin_clear(2); 
  PushMessage(Messages::GoToSleep);
}

void SystemTask::ReloadIdleTimer() const {
  if(isSleeping || isGoingToSleep) return;
  xTimerReset(idleTimer, 0);
}

void SystemTask::ReadTempSensor() {
  if(tempSensor.getIsCount()==0)
  {
   tempSensor.timer_temp_start();
   tempSensor.setIsCount(true);
  }  
  else 
   tempData++;
}

 void SystemTask::ResetSensor() {
  tempSensor.setIsCount(false);
  tempSensor.ReadData(tempData);
  tempData=0;
}

void SystemTask::CheckFallImpact(){
if(bleController.IsConnected()) {
    //Test//
 /* if((batteryController.getfallyy()!=0x02)||(batteryController.getimpactyy()!=0x02)){
    batteryController.setAccData(motionSensor.Process());
    auto xyz =motionSensor.ProcessTest();
    batteryController.setxyz(xyz.x,xyz.y,xyz.z);
    batteryController.setXmax(std::max(abs(xyz.x),abs(batteryController.getxmax())));
    batteryController.setYmax(std::max(abs(xyz.y),abs(batteryController.getymax())));
    batteryController.setZmax(std::max(abs(xyz.z),abs(batteryController.getzmax())));
  }
  */

    if(batteryController.getfallyy()!=0x02) {
        if(accValue>batteryController.getfallHighpeak()) isFallDiscoveryTimerRunning =true;
        if(isFallDiscoveryTimerRunning) FallDiscoveryTimer++;

        if(((FallDiscoveryTimer==batteryController.getfalltime()*20)&&(accValue<batteryController.getfallLowpeak()))||(batteryController.getfallyy()==0x07)){
          if(isSleeping && !isWakingUp) GoToRunning();
          displayApp->PushMessage(Watch::Applications::DisplayApp::Messages::Fall);
          batteryController.setfallyy(0x01);
          isFallDiscoveryTimerRunning =false;
          FallDiscoveryTimer=0;
          return;
        }
    }
 
  if((batteryController.getimpactyy()!=0x02) && (!isFallDiscoveryTimerRunning)) {
      if(accValue>batteryController.getimpactzz()) isImpactDiscoveryTimerRunning =true;
      if(isImpactDiscoveryTimerRunning || (batteryController.getimpactyy()==0x05)){
        if(isSleeping && !isWakingUp) GoToRunning();
        displayApp->PushMessage(Watch::Applications::DisplayApp::Messages::Impact);
        batteryController.setimpactyy(0x01);
        isImpactDiscoveryTimerRunning= false;
      }
    } 
  }
}


void SystemTask::CheckACC() { 
  accValue=motionSensor.Process();
  batteryController.setAccData(accValue);
  nimbleController.ble_acc_checkevent();
  CheckFallImpact();
}


void SystemTask::CheckCommon(){
  
    nimbleController.ble_checkevent();
    CheckCheckIn();
    //CheckFallImpact();

	  if(!checkcharging && batteryController.IsCharging()){ 
       if(isSleeping && !isWakingUp) GoToRunning();
        displayApp->PushMessage(Watch::Applications::DisplayApp::Messages::Charging);  
    } else if(checkcharging && !batteryController.IsCharging() ){   
       if(isSleeping && !isWakingUp) GoToRunning();
        displayApp->PushMessage(Watch::Applications::DisplayApp::Messages::Charging);
    } 
    checkcharging=batteryController.IsCharging();
}


void SystemTask::CheckTracking(){
      if((checknum==batteryController.getnumtracking()) || !batteryController.Istracking()|| (batteryController.getIsAlert()==0x02)){
        xTimerStop(idleTimerTracking, 0);
        checktime=0;
        checknum=0;
        return;
     }
      checktime++;
      if(checktime==batteryController.gettimetracking()){
      batteryController.setButtonDataNoVibrate(0x07);
      checktime=0;
      checknum++;
    };
}

void SystemTask::CheckHeartbeat(){
  if(!batteryController.Isheartbeat()) { xTimerStop(idleTimerHeartbeat, 0); checkheartbeat = true; checktimeheart=0;return;}
    checktimeheart++;
   if(checktimeheart==batteryController.gettimeheartbeat()){
      batteryController.setButtonDataNoVibrate(0x10);
      xTimerStop(idleTimerHeartbeat, 0);
      checktimeheart=0;
      checkheartbeat = true;
      batteryController.setIsheartbeat(false);
   };     
}

void SystemTask::CheckLowbattery(){
    if((batteryController.PercentRemaining()<25)&& !batteryController.IsCharging() && !checklowbattery) { 
        batteryController.setButtonData(0x05);
       if(isSleeping && !isWakingUp) GoToRunning();
        displayApp->PushMessage(Watch::Applications::DisplayApp::Messages::Lowbattery);
        checklowbattery = true;
    } 
    if((batteryController.PercentRemaining()>30)&& batteryController.IsCharging()) checklowbattery = false;
}

void SystemTask::CheckCheckIn(){
    uint8_t hour = dateTimeController.Hours();
    uint8_t minute = dateTimeController.Minutes();
    uint8_t second = dateTimeController.Seconds();
    batteryController.setCurrentHour(hour);
    batteryController.setCurrentMinute(minute);
    batteryController.setCurrentSecond(second);

    if((batteryController.isTimerStart1() && (batteryController.getCheckinTime1()== hour) && (minute==0) && (second<2)) ||(batteryController.isTimerStart2() && (batteryController.getCheckinTime2()== hour) && (minute==0) && (second<2))) {             
          if(isSleeping && !isWakingUp) GoToRunning();
          displayApp->PushMessage(Watch::Applications::DisplayApp::Messages::CheckIn); 
          batteryController.setGoToSleep(false);
          if (batteryController.isTimerStart1()) batteryController.setisTimer1Display(false) ;
          if (batteryController.isTimerStart2()) batteryController.setisTimer2Display(false) ;   
     }
}

void SystemTask::UpdateTimeOut(uint32_t timeout){
    xTimerChangePeriod(idleTimer, pdMS_TO_TICKS(timeout), 0);
}
