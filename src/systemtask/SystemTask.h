#pragma once

#include <memory>

#include <FreeRTOS.h>
#include <task.h>
#include <drivers/SpiMaster.h>
#include <drivers/St7789.h>
#include "components/battery/BatteryController.h"
#include "displayapp/DisplayApp.h"
#include <drivers/Watchdog.h>
#include <drivers/SpiNorFlash.h>
#include "SystemMonitor.h"
#include "components/ble/NimbleController.h"
#include "timers.h"
#include <drivers/Kx022.h>
#include <drivers/Kx126.h>
#include <drivers/Acnt101.h>
#include <drivers/Acnt101Adc.h>
#include <drivers/Gh301.h>
#include <drivers/VchR02.h>
#include <components/heartrate/HeartRateController.h>
#include <heartratetask/HeartRateTask.h>
#include <components/motion/MotionControllerTask.h>
#include <motionTask/MotionTask.h>

namespace Watch {
  namespace System {
    class SystemTask {
      public:
        enum class Messages {GoToSleep, GoToRunning, BleConnected,
            BleFirmwareUpdateStarted, BleFirmwareUpdateFinished, OnTouchEvent, OnButtonEvent, OnDisplayTaskSleeping, AlwaysDisplay,UpdateTimeOut};
  
       SystemTask(Drivers::SpiMaster &spi, Drivers::St7789 &lcd,
                   Watch::Drivers::SpiNorFlash& spiNorFlash,
                   Drivers::TwiMaster& twiMaster, Drivers::Cst816S &touchPanel,
                  //Drivers::Kx022& motionSensor,
                    Drivers::Kx126& motionSensor,
                  // Drivers::Gh301& heartRateSensor,
                   Components::LittleVgl &lvgl,
                   Controllers::Battery &batteryController, Controllers::Ble &bleController,
                   Controllers::DateTime &dateTimeController,
                   Watch::Controllers::NotificationManager& manager,
                   Watch::Drivers::Acnt101& tempSensor);

        void Start();
        void PushMessage(Messages msg);

        void OnButtonPushed();
        void OnTouchEvent();
        void OnIdle();
        void ReadTempSensor();
        void ResetSensor();
        void CheckACC();
        void CheckCommon();
        void CheckTracking();
        void CheckHeartbeat();
        void UpdateTimeOut(uint32_t timeout);

        Watch::Controllers::NimbleController& nimble() {return nimbleController;};

      private:
        TaskHandle_t taskHandle;

          Watch::Drivers::SpiMaster& spi;
          Watch::Drivers::St7789& lcd;
          Watch::Drivers::SpiNorFlash& spiNorFlash;
          Watch::Drivers::TwiMaster& twiMaster;
          Watch::Drivers::Cst816S& touchPanel;
          Watch::Components::LittleVgl& lvgl;
          Watch::Controllers::Battery& batteryController;
          std::unique_ptr<Watch::Applications::DisplayApp> displayApp;

          Watch::Controllers::Ble& bleController;
          Watch::Controllers::DateTime& dateTimeController;
          QueueHandle_t systemTasksMsgQueue;
          std::atomic<bool> isSleeping{false};
          std::atomic<bool> isGoingToSleep{false};
          std::atomic<bool> isWakingUp{false};
          Watch::Drivers::Watchdog watchdog;
          Watch::Drivers::WatchdogView watchdogView;
          Watch::Controllers::NotificationManager& notificationManager;
          Watch::Drivers::Acnt101& tempSensor;
          //Watch::Drivers::Acnt101Adc tempSensorAdc;
          //Watch::Drivers::Kx022& motionSensor;
          Watch::Drivers::Kx126& motionSensor;
          Watch::Controllers::NimbleController nimbleController;   
          Watch::Drivers::VchR02 heartRateSensor;    

        static constexpr uint8_t pinSpiSck = 16;
        static constexpr uint8_t pinSpiMosi = 14;
        static constexpr uint8_t pinSpiMiso = 15;
        static constexpr uint8_t pinSpiFlashCsn = 23;
        static constexpr uint8_t pinLcdCsn = 22;
        static constexpr uint8_t pinLcdDataCommand = 11;
        static constexpr uint8_t pinSpiAccCsn = 8;
        static constexpr uint8_t pinButton = 27;
        static constexpr uint8_t pinTouchIrq = 25;  


        static void Process(void* instance);
        void Work();
        void ReloadIdleTimer() const;
        void CheckLowbattery();
        void CheckCheckIn();
        void GoToRunning();
        
        bool isTouchDiscoveryTimerRunning = false;
        uint8_t TouchDiscoveryTimer = 2;
         bool isHandDiscoveryTimerRunning = false;
        uint8_t HandDiscoveryTimer = 0;
        bool isImpactDiscoveryTimerRunning = false;

        uint8_t ble_notifyTimer =2;
        TimerHandle_t idleTimer;
        TimerHandle_t idleTimerAcc;
        TimerHandle_t idleTimerCommon;
        TimerHandle_t idleTimerTracking;
        TimerHandle_t idleTimerHeartbeat;
        bool doNotGoToSleep = false;
        bool sendLowbattery= true;
        uint32_t tempData = 0;
        uint8_t Touch=0;
        bool checkcharging = true;
        bool checklowbattery = false;
      
        bool checkbright= false;
        uint8_t BrightDiscoveryTimer = 0;
        uint8_t prehour=0;
        uint8_t checktime=0;
        uint8_t checknum =0;
        uint8_t preAlert =0;
        bool checkheartbeat = true;
        uint8_t checktimeheart=0;
        uint8_t checknumheart =0;
       //float accValue=0;
        //bool runACC = true;
     
/*
#if configUSE_TRACE_FACILITY == 1
        SystemMonitor<FreeRtosMonitor> monitor;
#else
        SystemMonitor<DummyMonitor> monitor;
#endif
*/
    };
  }
}
