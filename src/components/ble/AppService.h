#pragma once
#include <cstdint>
#include <array>

#include <host/ble_gap.h>
#include <Version.h>
#define AppServiceId               {0x50,0xdb,0x15,0x2A,0x41,0x8d,0x46,0x90,0x95,0x89,0xab,0x7b,0xe9,0xe2,0x26,0x84};
#define AppServiceCharacteristicId {0x50,0xdb,0x15,0x24,0x41,0x8d,0x46,0x90,0x95,0x89,0xab,0x7b,0xe9,0xe2,0x26,0x84};

namespace Watch {
  namespace Application {
    class Warning;
  }
}

namespace Watch {
  namespace Controllers {
    class Battery;
    class AppService {
      public:
        AppService(Controllers::Battery& batteryController);
        void Init();

      int OnDeviceInfoRequested(uint16_t conn_handle, uint16_t attr_handle,
                                    struct ble_gatt_access_ctxt *ctxt);
      private:
        Controllers::Battery& batteryController;
        static constexpr ble_uuid128_t AppServiceUuid {
                .u {.type = BLE_UUID_TYPE_128},
                .value = {0x84,0x26,0xe2,0xe9,0x7b,0xab,0x89,0x95,0x90,0x46,0x8d,0x41,0x2A,0x15,0xdb,0x50}

        };

        static constexpr ble_uuid128_t AppServiceCharacteristicUuid {
                .u {.type = BLE_UUID_TYPE_128},
                .value = {0x84,0x26,0xe2,0xe9,0x7b,0xab,0x89,0x95,0x90,0x46,0x8d,0x41,0x24,0x15,0xdb,0x50}
        };

       
        struct ble_gatt_chr_def characteristicDefinition[2];
        struct ble_gatt_svc_def serviceDefinition[2];

        uint16_t dataCharacteristicHandle;
        uint16_t controlCharacteristicHandle;

    };
  }
}


