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
  
  idleTimer = xTimerCreate ("idleTimer", pdMS_TO_TICKS(25000), pdFALSE, this, IdleTimerCallback);
  idleTimerAcc = xTimerCreate ("idleTimerAcc", pdMS_TO_TICKS(100), pdTRUE, this, IdleTimerAccCallback);
  idleTimerTracking = xTimerCreate ("idleTimerAcc", pdMS_TO_TICKS(60000), pdTRUE, this, IdleTimerTrackingCallback);
  idleTimerHeartbeat = xTimerCreate ("idleTimerHeartbeat", pdMS_TO_TICKS(60000), pdTRUE, this, IdleTimerHeartbeatCallback);
  xTimerStart(idleTimer, 0);
  xTimerStart(idleTimerAcc, 0);
  
  
  // Suppress endless loop diagnostic
  #pragma clang diagnostic push
  #pragma ide diagnostic ignored "EndlessLoop"
  while(true) {
    uint8_t msg;
     batteryController.Update();
    if (xQueueReceive(systemTasksMsgQueue, &msg, isSleeping ? 2500 : 1000)){         
      Messages message = static_cast<Messages >(msg); 
      switch(message) {
        case Messages::GoToRunning:        
          //spi.Wakeup();
          //twiMaster.Wakeup();
          nimbleController.StartAdvertising();
          xTimerStart(idleTimer, 0);
          //spiNorFlash.Wakeup();
          //touchPanel.Wakeup();
          lcd.Wakeup();  
          motionSensor.Init();                
          displayApp->PushMessage(Watch::Applications::DisplayApp::Messages::GoToRunning);
          isSleeping = false;
          isWakingUp = false;         
         
          break;
        case Messages::GoToSleep:
          isGoingToSleep = true;
          checkcharging = false;
          xTimerStop(idleTimer, 0);
          displayApp->PushMessage(Watch::Applications::DisplayApp::Messages::Clock);
          displayApp->PushMessage(Watch::Applications::DisplayApp::Messages::GoToSleep);
          heartRateSensor.Disable(); 
          break;
        case Messages::BleConnected:
          ReloadIdleTimer();
          nimbleController.StartDiscovery(); 
          if(isSleeping) GoToRunning();  
          displayApp->PushMessage(Watch::Applications::DisplayApp::Messages::UpdateBleConnection); 
               
          break;
        case Messages::BleFirmwareUpdateStarted:
          batteryController.setGoToSleep(false);
          if(isSleeping) GoToRunning();
          displayApp->PushMessage(Watch::Applications::DisplayApp::Messages::BleFirmwareUpdateStarted);
          break;
        case Messages::BleFirmwareUpdateFinished:
          batteryController.setGoToSleep(true);
          xTimerStart(idleTimer, 0);
          if(bleController.State() == Watch::Controllers::Ble::FirmwareUpdateStates::Validated)
          NVIC_SystemReset();
          break;
        case Messages::OnTouchEvent:
          if(batteryController.getDisturnOff()) break;
          batteryController.setGoToSleep(true);
          if(isSleeping) {            
          auto info = touchPanel.GetTouchInfo();
          if(info.isTouch &&(info.gesture==Watch::Drivers::Cst816S::Gestures::SingleTap)) Touch++;
            if(Touch==2) {GoToRunning(); Touch=0;          
              displayApp->PushMessage(Watch::Applications::DisplayApp::Messages::Clock);
              }
            isTouchDiscoveryTimerRunning = true;          
          }
          ReloadIdleTimer();
          break;
        case Messages::OnButtonEvent:
         batteryController.setGoToSleep(true);
          ReloadIdleTimer();
          break;
        case Messages::AlwaysDisplay:
         batteryController.setGoToSleep(false);
          xTimerStart(idleTimer, 0);
          break;
        case Messages::OnDisplayTaskSleeping:         
          //spiNorFlash.Sleep();          
          //lcd.Sleep();         
          //touchPanel.Sleep();
          //spi.Sleep();
          //twiMaster.Sleep();
          displayApp->PushMessage(Watch::Applications::DisplayApp::Messages::Clock);
          isSleeping = true;
          isGoingToSleep = false;
          break;
        default: break;
      }
    }

    if(isTouchDiscoveryTimerRunning && (Touch==1)) {
      if(TouchDiscoveryTimer == 0) {
        isTouchDiscoveryTimerRunning = false;
        TouchDiscoveryTimer=3;
       Touch=0;
      } else {
        TouchDiscoveryTimer--;
      }
    }    

    if(!checkcharging && batteryController.CheckCharging())
    { if(isSleeping) GoToRunning();
      displayApp->PushMessage(Watch::Applications::DisplayApp::Messages::Charging);
    }
    checkcharging=batteryController.CheckCharging();


    if(batteryController.Istracking()){  
      if (batteryController.getIsAlert()!=preAlert) { 
        xTimerStart(idleTimerTracking, 0);
        checktime=0;
        checknum=0;
      }
      preAlert= batteryController.getIsAlert();
    }

    CheckCheckIn();

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
      GoToRunning();     
    }
  }
}

void SystemTask::GoToRunning() {
 // if(isGoingToSleep || (!isSleeping) ||isWakingUp) return;
  isWakingUp = true;
  PushMessage(Messages::GoToRunning);
}

void SystemTask::OnTouchEvent() {
  PushMessage(Messages::OnTouchEvent);
  displayApp->PushMessage(Watch::Applications::DisplayApp::Messages::TouchEvent);
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
  displayApp->PushMessage(Watch::Applications::DisplayApp::Messages::Clock);
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

void SystemTask::CheckACC() { 
if(bleController.IsConnected()) {
  nimbleController.ble_checkevent();
  if(motionSensor.Process()>batteryController.getfallHighpeak()) {isHandDiscoveryTimerRunning =true;}
  if(motionSensor.Process()>batteryController.getimpactzz()) {isImpactDiscoveryTimerRunning =true;}
  if(isHandDiscoveryTimerRunning) HandDiscoveryTimer++;

  if(HandDiscoveryTimer>batteryController.getfalltime()*12) {
    isHandDiscoveryTimerRunning =false;
    HandDiscoveryTimer=0;
}

    if(batteryController.getfallyy()!=0x02) {
      if(((HandDiscoveryTimer==batteryController.getfalltime()*10)&&(motionSensor.Process()<batteryController.getfallLowpeak()))||(batteryController.getfallyy()==0x07)){
        if(isSleeping) GoToRunning();
        displayApp->PushMessage(Watch::Applications::DisplayApp::Messages::Fall);
         batteryController.setfallyy(0x01);
         isHandDiscoveryTimerRunning =false;
         isImpactDiscoveryTimerRunning= false;
         HandDiscoveryTimer=0;
         return;
      }
    }
 
  if((batteryController.getimpactyy()!=0x02) ) {
      if((isImpactDiscoveryTimerRunning && !isHandDiscoveryTimerRunning)|| (batteryController.getimpactyy()==0x05)){
        if(isSleeping) GoToRunning();
        displayApp->PushMessage(Watch::Applications::DisplayApp::Messages::Impact);
        batteryController.setimpactyy(0x01);
        isImpactDiscoveryTimerRunning= false;
        return;
      }
    } 
}
    if(isSleeping){
      if(motionSensor.Process()>1.3) checkbright=true;
      if(checkbright) BrightDiscoveryTimer++;
      if((BrightDiscoveryTimer==10) && (motionSensor.Process()<1.2)) { GoToRunning();BrightDiscoveryTimer=0;checkbright=false;}
    }

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
    if((batteryController.PercentRemaining()<28)&& !checkcharging && !checklowbattery) { 
        batteryController.setButtonData(0x05);
        displayApp->PushMessage(Watch::Applications::DisplayApp::Messages::Lowbattery);
        checklowbattery = true;
    } 
    if((batteryController.PercentRemaining()>35)&& checkcharging) checklowbattery = false;
}


void SystemTask::CheckCheckIn(){
    uint8_t hour = dateTimeController.Hours();
    uint8_t minute = dateTimeController.Minutes();
    uint8_t second = dateTimeController.Seconds();
    batteryController.setCurrentHour(hour);
    batteryController.setCurrentMinute(minute);
    batteryController.setCurrentSecond(second);

    if((batteryController.isTimerStart1() && (batteryController.getCheckinTime1()== hour) && (minute==0) && (second<2)) ||(batteryController.isTimerStart2() && (batteryController.getCheckinTime2()== hour) && (minute==0) && (second<2))) {             
          if(isSleeping) GoToRunning();
          displayApp->PushMessage(Watch::Applications::DisplayApp::Messages::CheckIn); 
          batteryController.setGoToSleep(false);
          if (batteryController.isTimerStart1()) batteryController.setisTimer1Display(false) ;
          if (batteryController.isTimerStart2()) batteryController.setisTimer2Display(false) ;   
     }
}

void SystemTask::UpdateTimeOut(uint32_t timeout){
    xTimerChangePeriod(idleTimer, pdMS_TO_TICKS(timeout), 0);
}