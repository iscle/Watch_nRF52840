#pragma once
#define min // workaround: nimble's min/max macros conflict with libstdc++
#define max
#include <host/ble_gap.h>
#undef max
#undef min
#include "components/battery/BatteryController.h"
namespace Watch {
  namespace System {
    class SystemTask;
    class Battery;
  }
  namespace Controllers {
    class HeartRateService {
      public:
        HeartRateService(Watch::System::SystemTask &system,Controllers::Battery& batteryController);
        void Init();
        int OnHeartRateRequested(uint16_t connectionHandle, uint16_t attributeHandle, ble_gatt_access_ctxt *context);
        void OnNewHeartRateValue();

    private:
        Watch::System::SystemTask &system;
        Controllers::Battery& batteryController;
        static constexpr uint16_t heartRateServiceId {0x180D};
        static constexpr uint16_t heartRateMeasurementId {0x2A37};

        static constexpr ble_uuid16_t heartRateServiceUuid {
                .u {.type = BLE_UUID_TYPE_16},
                .value = heartRateServiceId
        };

        static constexpr ble_uuid16_t heartRateMeasurementUuid {
                .u {.type = BLE_UUID_TYPE_16},
                .value = heartRateMeasurementId
        };

        struct ble_gatt_chr_def characteristicDefinition[3];
        struct ble_gatt_svc_def serviceDefinition[2];
        uint8_t i=0;
        uint16_t heartRateMeasurementHandle;

    };
  }
}
