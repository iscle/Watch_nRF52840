#pragma once

#include <cstdint>

#define min // workaround: nimble's min/max macros conflict with libstdc++
#define max
#include <host/ble_gap.h>
#undef max
#undef min
#include "AlertNotificationClient.h"
#include "AlertNotificationService.h"
#include "BatteryInformationService.h"
#include "CurrentTimeClient.h"
#include "CurrentTimeService.h"
#include "DeviceInformationService.h"
#include "DfuService.h"
#include "ImmediateAlertService.h"
#include "MusicService.h"
#include "ServiceDiscovery.h"
#include "Keyfob.h"
#include "Datasensor.h"

namespace Watch {
  namespace Drivers {
    class SpiNorFlash;
  }

  namespace System {
    class SystemTask;
  }

  namespace Controllers {
    class Ble;
    class DateTime;
    class NotificationManager;

    class NimbleController {

      public:
        NimbleController(Watch::System::SystemTask& systemTask, Watch::Controllers::Ble& bleController,
                DateTime& dateTimeController, Watch::Controllers::NotificationManager& notificationManager,
                Controllers::Battery& batteryController, Watch::Drivers::SpiNorFlash& spiNorFlash);
        void Init();
        void StartAdvertising();
        int OnGAPEvent(ble_gap_event *event);

        int OnDiscoveryEvent(uint16_t i, const ble_gatt_error *pError, const ble_gatt_svc *pSvc);
        int OnCTSCharacteristicDiscoveryEvent(uint16_t connectionHandle, const ble_gatt_error *error,
                                              const ble_gatt_chr *characteristic);
        int OnANSCharacteristicDiscoveryEvent(uint16_t connectionHandle, const ble_gatt_error *error,
                                              const ble_gatt_chr *characteristic);
        int OnCurrentTimeReadResult(uint16_t connectionHandle, const ble_gatt_error *error, ble_gatt_attr *attribute);
        int OnANSDescriptorDiscoveryEventCallback(uint16_t connectionHandle, const ble_gatt_error *error,
                                                  uint16_t characteristicValueHandle, const ble_gatt_dsc *descriptor);

        void StartDiscovery();
        void ble_checkevent();

        //Watch::Controllers::MusicService& music() {return musicService;};

        uint16_t connHandle();

      private:
        //static constexpr const char* deviceName = "SA-AlertWatch";
        Watch::System::SystemTask& systemTask;
        Watch::Controllers::Ble& bleController;
        DateTime& dateTimeController;
        Watch::Controllers::NotificationManager& notificationManager;
        Watch::Drivers::SpiNorFlash& spiNorFlash;
        Watch::Controllers::DfuService dfuService;

       // DeviceInformationService deviceInformationService;
        CurrentTimeClient currentTimeClient;
       // AlertNotificationService anService;
        //AlertNotificationClient alertNotificationClient;
        //CurrentTimeService currentTimeService;
        //MusicService musicService;
       // BatteryInformationService batteryInformationService;  
        Keyfob keyfob;
        //DataSensor dataSensor;        
        //ImmediateAlertService immediateAlertService;
        
        

        uint8_t addrType; // 1 = Random, 0 = PUBLIC
        uint16_t connectionHandle = 0;
        char deviceName[10];

        ble_uuid128_t dfuServiceUuid {
                .u { .type = BLE_UUID_TYPE_128},
               .value = {0x84,0x26,0xe2,0xe9,0x7b,0xab,0x89,0x95,0x90,0x46,0x8d,0x41,0x2A,0x15,0xdb,0x50}
               
        };
        ServiceDiscovery serviceDiscovery;
    };
  }
}




