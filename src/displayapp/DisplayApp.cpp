#include <string>

#include "DisplayApp.h"
#include <FreeRTOS.h>
#include <task.h>
#include <libraries/log/nrf_log.h>
#include <nrf_font.h>
#include <queue.h>
#include "components/datetime/DateTimeController.h"
#include <drivers/Cst816s.h>
#include "displayapp/screens/SystemInfo.h"
#include "components/ble/NotificationManager.h"
#include "displayapp/screens/FirmwareUpdate.h"
#include "displayapp/screens/FirmwareValidation.h"
#include "systemtask/SystemTask.h"
#include "displayapp/screens/HeartRate.h"
#include "displayapp/screens/Test.h"
#include "displayapp/screens/SensorDisplay.h"
#include "displayapp/screens/Pair.h"
#include "displayapp/screens/Battery.h"
#include "displayapp/screens/CheckIn.h"
#include "displayapp/screens/Impact.h"
#include "displayapp/screens/Fall.h"


using namespace Watch::Applications;

DisplayApp::DisplayApp(Drivers::St7789 &lcd, Components::LittleVgl &lvgl, Drivers::Cst816S &touchPanel,
                       Controllers::Battery &batteryController, Controllers::Ble &bleController,
                       Controllers::DateTime &dateTimeController, Drivers::WatchdogView &watchdog,
                       System::SystemTask &systemTask,
                       Watch::Drivers::Acnt101& tempSensor) :
        lcd{lcd},
        lvgl{lvgl},
        batteryController{batteryController},
        bleController{bleController},
        dateTimeController{dateTimeController},
        watchdog{watchdog},
        touchPanel{touchPanel},        
        systemTask{systemTask},
        tempSensor{tempSensor} {
          if(bleController.IsConnected()) SwichApp(0); else  {SwichApp(7); batteryController.setIsVibrate();}
          msgQueue = xQueueCreate(queueSize, itemSize);
          onClockApp = true;         
        }

void DisplayApp::Start() {
  if (pdPASS != xTaskCreate(DisplayApp::Process, "displayapp", 800, this, 0, &taskHandle))
    APP_ERROR_HANDLER(NRF_ERROR_NO_MEM);
}

void DisplayApp::Process(void *instance) {
    auto *app = static_cast<DisplayApp *>(instance);
    app->InitHw();
    xTaskNotifyGive(xTaskGetCurrentTaskHandle());
    while (1) {
      app->Refresh();
  }
}

void DisplayApp::InitHw() {
}

void DisplayApp::Refresh() {
  TickType_t queueTimeout;
  switch (state) {
    case States::Idle:    
      queueTimeout = portMAX_DELAY;
      break;
    case States::Running:
      RunningState();
      queueTimeout = 150;
      break;
    default:
      queueTimeout = portMAX_DELAY;
      break;
  }

  Messages msg;
  if (xQueueReceive(msgQueue, &msg, queueTimeout)) {
    switch (msg) {
      case Messages::GoToSleep:          
        //lcd.DisplayOff();
        systemTask.PushMessage(System::SystemTask::Messages::OnDisplayTaskSleeping);
        state = States::Idle;
        break;
      case Messages::GoToRunning:         
        //lcd.DisplayOn();           
        state = States::Running;
        break;
      case Messages::UpdateBleConnection: 
        checkupdate = false;
        checkFall = false;
        checkImpact =false;
        checkCheckin =false;    
        batteryController.setIsVibrate();
        validator.Validate();     
        if(bleController.IsConnected()) { SwichApp(1);   appIndex =1; }          
        else SwichApp(7);           
        break;
      case Messages::TouchEvent: {
        if (state != States::Running) break;
        auto gesture = OnTouchEvent();
        if(!currentScreen->OnTouchEvent(gesture)) {
          switch(gesture) {
          /* case TouchEvents::SwipeDown:             
             SwichApp(6);              
              break;
            case TouchEvents::SwipeUp:
              SwichApp(appIndex);
                break; 
          */  
            case TouchEvents::SwipeLeft:
             if (!bleController.IsConnected() || checkupdate || checkCheckin|| checkFall || checkImpact) break;
              if(appIndex>0) {       
                appIndex--;
                SwichApp(appIndex);               
            } else  {appIndex =4;   SwichApp(appIndex);}      
              break;
           case TouchEvents::SwipeRight:
             if (!bleController.IsConnected() || checkupdate || checkCheckin|| checkFall || checkImpact) break;
            if(appIndex<4) {     
                appIndex++;
                SwichApp(appIndex);               
              } else {appIndex =0;   SwichApp(appIndex);} 
              break;
            default:
              break;
          }
        }
      }
          break;
      case Messages::ButtonPushed:
          checkupdate = false;
          checkFall = false;
          checkImpact =false;
          checkCheckin =false;
          batteryController.setDisturnOff(false);
          nrf_gpio_pin_clear(2);               
          appIndex=0;
          if(bleController.IsConnected()) SwichApp(0); else  SwichApp(7);
          systemTask.PushMessage(System::SystemTask::Messages::GoToSleep); 
          break;

      case Messages::BleFirmwareUpdateStarted:
          checkupdate= true;
          batteryController.setDisturnOff(true);
          currentScreen.reset(nullptr);
          batteryController.setIsVibrate(); 
          currentScreen.reset(new Screens::FirmwareUpdate(this, bleController));          
          break;

      case Messages::Impact:
          //batteryController.setDisturnOff(true);
          checkImpact= true;
          batteryController.setButtonData(0x12); 
          batteryController.setIsAlert(0x12); 
          systemTask.PushMessage(System::SystemTask::Messages::AlwaysDisplay);    
          SwichApp(5);      
          break;

      case Messages::Fall: 
          checkFall = true;
          //batteryController.setDisturnOff(true);
          batteryController.setButtonData(0x08);
          batteryController.setIsAlert(0x08); 
          systemTask.PushMessage(System::SystemTask::Messages::AlwaysDisplay);     
          SwichApp(6);      
          break;

      case Messages::CheckIn:  
          checkCheckin = true;
          batteryController.setDisturnOff(true);
          systemTask.PushMessage(System::SystemTask::Messages::AlwaysDisplay);
          SwichApp(10);      
          break;

      case Messages::Clock: 
          batteryController.setDisturnOff(false);
          if(bleController.IsConnected()) SwichApp(0); else  SwichApp(7);       
          break;

      case Messages::Lowbattery: 
          batteryController.setDisturnOff(false);
          SwichApp(9);      
          break;
      case Messages::Charging:
          batteryController.setDisturnOff(false);     
          SwichApp(8);
          break;
      default:
          break;
    }
  }

  if(state != States::Idle && touchMode == TouchModes::Polling) {
    auto info = touchPanel.GetTouchInfo();
    if(info.action == 2) {// 2 = contact
      if(!currentScreen->OnTouchEvent(info.x, info.y)) {
        lvgl.SetNewTapEvent(info.x, info.y);
      }
    }
  }
}

void DisplayApp::RunningState() { 
  if(!currentScreen->Refresh()) {  } 
  lv_task_handler();
}

void DisplayApp::PushMessage(DisplayApp::Messages msg) {
  BaseType_t xHigherPriorityTaskWoken;
  xHigherPriorityTaskWoken = pdFALSE;
  xQueueSendFromISR(msgQueue, &msg, &xHigherPriorityTaskWoken);
  if (xHigherPriorityTaskWoken) {
  }
}

TouchEvents DisplayApp::OnTouchEvent() {
  auto info = touchPanel.GetTouchInfo();
  if(info.isTouch) {
    batteryController.setTouch(info.x, info.y);
    switch(info.gesture) {
      case Watch::Drivers::Cst816S::Gestures::SingleTap:
        if(touchMode == TouchModes::Gestures){
          lvgl.SetNewTapEvent(info.x, info.y);          
        }
        return TouchEvents::Tap;
      case Watch::Drivers::Cst816S::Gestures::LongPress:
        return TouchEvents::LongTap;
      case Watch::Drivers::Cst816S::Gestures::DoubleTap:
        return TouchEvents::DoubleTap;
      case Watch::Drivers::Cst816S::Gestures::SlideRight:
        return TouchEvents::SwipeRight;
      case Watch::Drivers::Cst816S::Gestures::SlideLeft:
        return TouchEvents::SwipeLeft;
     /* case Watch::Drivers::Cst816S::Gestures::SlideDown:
        return TouchEvents::SwipeDown;
      case Watch::Drivers::Cst816S::Gestures::SlideUp:
        return TouchEvents::SwipeUp;
        */
      case Watch::Drivers::Cst816S::Gestures::None:
      default:
        return TouchEvents::None;
    }
  }
  return TouchEvents::None;
}

void DisplayApp::StartApp(Apps app) {
   nextApp = app;
}

void DisplayApp::SetTouchMode(DisplayApp::TouchModes mode) {
  touchMode = mode;
}


void DisplayApp::SwichApp(uint8_t app ){    
    //currentScreen.reset(nullptr); 
    //currentScreen.reset(nullptr);
    currentScreen.reset(nullptr);
    onClockApp = true;
    switch (app)
    {
      case 0: 
        checkupdate = false;
        checkFall = false;
        checkImpact = false;
        checkCheckin =false;
        batteryController.setDisturnOff(false); 
        appIndex=0;  
        systemTask.UpdateTimeOut(25000);
      currentScreen.reset(new Screens::Clock(this, dateTimeController, batteryController, bleController, tempSensor,Screens::Clock::Modes::Clock));
        break;
      case 1:
       systemTask.UpdateTimeOut(25000);
        currentScreen.reset(new Screens::Clock(this, dateTimeController, batteryController, bleController, tempSensor, Screens::Clock::Modes::Test));
        break;
      case 2:
        //systemTask.PushMessage(System::SystemTask::Messages::AlwaysDisplay);
        systemTask.UpdateTimeOut(70000);
        currentScreen.reset(new Screens::Clock(this, dateTimeController, batteryController, bleController, tempSensor,Screens::Clock::Modes::Sensor));
        break;
      case 3:
       systemTask.UpdateTimeOut(45000);
        //systemTask.PushMessage(System::SystemTask::Messages::AlwaysDisplay);
        currentScreen.reset(new Screens::Clock(this, dateTimeController, batteryController, bleController, tempSensor,Screens::Clock::Modes::Temp));
        break;
      case 4:
       systemTask.UpdateTimeOut(45000);
        //systemTask.PushMessage(System::SystemTask::Messages::AlwaysDisplay);
        currentScreen.reset(new Screens::Clock(this, dateTimeController, batteryController, bleController, tempSensor,Screens::Clock::Modes::Oxi));
        break;
      case 5:
       systemTask.UpdateTimeOut(50000);
        currentScreen.reset(new Screens::Clock(this, dateTimeController, batteryController, bleController, tempSensor, Screens::Clock::Modes::Impact));
        break;
      case 6:
       systemTask.UpdateTimeOut(50000);
        currentScreen.reset(new Screens::Clock(this, dateTimeController, batteryController, bleController, tempSensor, Screens::Clock::Modes::Fall));
        break;
      //case 6:
    // currentScreen.reset(new Screens::FirmwareValidation(this, validator));
       // break; 
      case 7:
        currentScreen.reset(new Screens::Clock(this, dateTimeController, batteryController, bleController, tempSensor, Screens::Clock::Modes::PairDis));
        appIndex=0;
        break;
      case 8:
        currentScreen.reset(new Screens::Clock(this, dateTimeController, batteryController, bleController, tempSensor, Screens::Clock::Modes::Charging));
        break;
      case 9:
        currentScreen.reset(new Screens::Clock(this, dateTimeController, batteryController, bleController, tempSensor, Screens::Clock::Modes::LowBattery));
        break;
      case 10:
        currentScreen.reset(new Screens::Clock(this, dateTimeController, batteryController, bleController, tempSensor, Screens::Clock::Modes::CheckIn));
        break;
      default:
        break;
    }

}
