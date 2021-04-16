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
     class HeartRateController;
    class DataSensor {
      public:
        DataSensor(Controllers::Battery& batteryController);
        void Init();
        int  ble_checkevent();

      int OnDeviceInfoRequested(uint16_t conn_handle, uint16_t attr_handle,
                                    struct ble_gatt_access_ctxt *ctxt);

       int OnDeviceInfoRequested1(uint16_t conn_handle, uint16_t attr_handle,
                                    struct ble_gatt_access_ctxt *ctxt);                              
      private:
        Controllers::Battery& batteryController;
  
        static constexpr ble_uuid128_t  dataSensorUuid {
                .u { .type = BLE_UUID_TYPE_128 },
                .value = {0xfb,0x34,0x9b,0x5f,0x80,0x00,0x00,0x80,0x00,0x10,0x00,0x00,0x0D,0x18,0x00,0x00}                
        };
  

        static constexpr ble_uuid128_t  dataCharacteristicUuid {
                .u { .type = BLE_UUID_TYPE_128 },
                .value = {0xfb,0x34,0x9b,0x5f,0x80,0x00,0x00,0x80,0x00,0x10,0x00,0x00,0x37,0x2A,0x00,0x00}
        };

        static constexpr ble_uuid128_t  controlCharacteristicUuid {
                .u { .type = BLE_UUID_TYPE_128 },
                .value = {0xfb,0x34,0x9b,0x5f,0x80,0x00,0x00,0x80,0x00,0x10,0x00,0x00,0x35,0x2A,0x00,0x00}
        };

       
        struct ble_gatt_chr_def characteristicDefinition[3];
        struct ble_gatt_svc_def serviceDefinition[2];

        uint16_t dataCharacteristicHandle;
        uint16_t controlCharacteristicHandle;

         uint8_t result;
         uint8_t currentdataCharacteristic;
         uint16_t buttonHandle;
         uint16_t chr_val_handle;
         uint16_t chr_val_handle1;

    };
  }
}