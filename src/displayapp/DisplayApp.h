#pragma once
#include <FreeRTOS.h>
#include <task.h>
#include <drivers/St7789.h>
#include <drivers/SpiMaster.h>
#include <bits/unique_ptr.h>
#include <queue.h>
#include "components/gfx/Gfx.h"
#include "components/battery/BatteryController.h"
#include "components/ble/BleController.h"
#include "components/datetime/DateTimeController.h"
#include "components/ble/NotificationManager.h"
#include "components/firmwarevalidator/FirmwareValidator.h"
#include "drivers/Cst816s.h"
#include "drivers/Acnt101.h"
#include "LittleVgl.h"
#include <date/date.h>
#include "displayapp/screens/Clock.h"
#include "displayapp/screens/Modal.h"
#include <drivers/Watchdog.h>
#include "TouchEvents.h"
#include "Apps.h"


namespace Watch {
  namespace System {
    class SystemTask;
  };
  namespace Applications {
    class DisplayApp {
      public:
        enum class States {Idle, Running};
        enum class Messages : uint8_t {GoToSleep, GoToRunning,TouchEvent, UpdateBleConnection,Charging,ButtonPushed, BleFirmwareUpdateStarted,Impact,Fall,CheckIn,Clock,Lowbattery};
        enum class TouchModes { Gestures, Polling };
         enum class FullRefreshDirections { None, Up, Down, Left, Right, LeftAnim, RightAnim };

        DisplayApp(Drivers::St7789 &lcd, Components::LittleVgl &lvgl, Drivers::Cst816S &,
                   Controllers::Battery &batteryController, Controllers::Ble &bleController,
                   Controllers::DateTime &dateTimeController, Drivers::WatchdogView &watchdog,
                   System::SystemTask &systemTask,                 
                   Watch::Drivers::Acnt101& tempSensor);
        void Start();
        void PushMessage(Messages msg);
        void StartApp(Apps app);
        void SwichApp(uint8_t app);
        void SetTouchMode(TouchModes mode);
        void SetFullRefresh(FullRefreshDirections direction);

      private:
        TaskHandle_t taskHandle;
        static void Process(void* instance);
        void InitHw();
        Watch::Drivers::St7789& lcd;
        Watch::Components::LittleVgl& lvgl;
        void Refresh();
       
        States state = States::Running;
        void RunningState();
        QueueHandle_t msgQueue;

        static constexpr uint8_t queueSize = 10;
        static constexpr uint8_t itemSize = 1;

        Watch::Controllers::Battery &batteryController;
        Watch::Controllers::Ble &bleController;
        Watch::Controllers::DateTime& dateTimeController;
        Watch::Drivers::WatchdogView& watchdog;
        Watch::Drivers::Cst816S& touchPanel;
        Watch::System::SystemTask& systemTask;
        Watch::Drivers::Acnt101& tempSensor;

        
        TouchEvents OnTouchEvent();

        bool isClock = true;
        uint8_t appIndex=0;       
        Apps nextApp = Apps::None;
        bool onClockApp = true; 
        bool checkupdate = false;
        bool checkFall = false;
        bool checkImpact = false ;
        bool checkCheckin =false;  
        //std::unique_ptr<Screens::Modal> modal;

        Watch::Controllers::FirmwareValidator validator;
        TouchModes touchMode = TouchModes::Polling;
        std::unique_ptr<Screens::Screen> currentScreen;
    };
  }
}

