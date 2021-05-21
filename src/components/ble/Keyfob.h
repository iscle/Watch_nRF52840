#pragma once
#include <cstdint>
#include <array>

#include <host/ble_gap.h>
#include <Version.h>
#include "host/ble_hs.h"
#include "host/ble_uuid.h"


namespace Watch {
  namespace Application {
    class Warning;
  }
}

namespace Watch {
  namespace Controllers {
    class Battery;
    class Keyfob {
      public:
        Keyfob(Controllers::Battery& batteryController);
        void Init();
        int  ble_checkevent();

      int OnDeviceInfoRequested(uint16_t conn_handle, uint16_t attr_handle,
                                    struct ble_gatt_access_ctxt *ctxt);

       int OnDeviceInfoRequested1(uint16_t conn_handle, uint16_t attr_handle,
                                    struct ble_gatt_access_ctxt *ctxt);                              
      private:
        Controllers::Battery& batteryController;
  
        static constexpr ble_uuid128_t  deviceInfoUuid {
                .u { .type = BLE_UUID_TYPE_128 },
                .value = {0x84,0x26,0xe2,0xe9,0x7b,0xab,0x89,0x95,0x90,0x46,0x8d,0x41,0x2A,0x15,0xdb,0x50}
        };

        static constexpr ble_uuid128_t  dataCharacteristicUuid {
                .u { .type = BLE_UUID_TYPE_128 },
                .value = {0x84,0x26,0xe2,0xe9,0x7b,0xab,0x89,0x95,0x90,0x46,0x8d,0x41,0x24,0x15,0xdb,0x50}
        };

        static constexpr ble_uuid128_t  controlCharacteristicUuid {
                .u { .type = BLE_UUID_TYPE_128 },
                .value = {0x84,0x26,0xe2,0xe9,0x7b,0xab,0x89,0x95,0x90,0x46,0x8d,0x41,0x27,0x15,0xdb,0x50}
        };      
        struct ble_gatt_chr_def characteristicDefinition[3];
        struct ble_gatt_svc_def serviceDefinition[2];

        uint16_t dataCharacteristicHandle;
        uint16_t controlCharacteristicHandle;

        typedef struct __attribute__((packed)){            
          uint8_t  batteryStatus;
          uint8_t  packetCode;
        } dataCharacteristicStr;

       typedef struct __attribute__((packed)) { 
          uint8_t  zz;
          uint8_t  yy;
          uint8_t  nn;
        } controlCharacteristicStr;

         dataCharacteristicStr currentdataCharacteristic;
         controlCharacteristicStr result;
         controlCharacteristicStr fallCharacteristic;
         controlCharacteristicStr checkinCharacteristic;
         controlCharacteristicStr impactCharacteristic;
         
         uint16_t buttonHandle;
         uint16_t chr_val_handle;

    };
  }
}