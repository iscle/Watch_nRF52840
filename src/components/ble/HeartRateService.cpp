#include "HeartRateService.h"
#include "systemtask/SystemTask.h"

using namespace Watch::Controllers;

constexpr ble_uuid16_t HeartRateService::heartRateServiceUuid;
constexpr ble_uuid16_t HeartRateService::heartRateMeasurementUuid;

namespace {
  int HeartRateServiceServiceCallback(uint16_t conn_handle, uint16_t attr_handle, struct ble_gatt_access_ctxt *ctxt, void *arg) {
    auto* heartRateService = static_cast<HeartRateService*>(arg);
    return heartRateService->OnHeartRateRequested(conn_handle, attr_handle, ctxt);
  }
}

// TODO Refactoring - remove dependency to SystemTask
HeartRateService::HeartRateService(Watch::System::SystemTask &system,Controllers::Battery& batteryController) :
        system{system},
        batteryController{batteryController},
        characteristicDefinition{
                {
                        .uuid = (ble_uuid_t *) &heartRateMeasurementUuid,
                        .access_cb = HeartRateServiceServiceCallback,
                        .arg = this,
                        .flags = BLE_GATT_CHR_F_READ | BLE_GATT_CHR_F_NOTIFY,
                        .val_handle = &heartRateMeasurementHandle
                },
                {
                        0
                }
        },
        serviceDefinition{
                {
                        /* Device Information Service */
                        .type = BLE_GATT_SVC_TYPE_PRIMARY,
                        .uuid = (ble_uuid_t *) &heartRateServiceUuid,
                        .characteristics = characteristicDefinition
                },
                {
                        0
                },
        }{
  // TODO refactor to prevent this loop dependency (service depends on controller and controller depends on service)
 // heartRateController.SetService(this);
}

void HeartRateService::Init() {
  int res = 0;
  res = ble_gatts_count_cfg(serviceDefinition);
  ASSERT(res == 0);

  res = ble_gatts_add_svcs(serviceDefinition);
  ASSERT(res == 0);
}

int HeartRateService::OnHeartRateRequested(uint16_t connectionHandle, uint16_t attributeHandle,
                                           ble_gatt_access_ctxt *context) {
  if(attributeHandle == heartRateMeasurementHandle) {
   // NRF_LOG_INFO("BATTERY : handle = %d", heartRateMeasurementHandle);
    //static uint8_t batteryValue = heartRateController.HeartRate();
    i= uint8_t(batteryController.getz()*10);
    uint8_t buffer[2] = {0, i}; // [0] = flags, [1] = hr value
    int res = os_mbuf_append(context->om, buffer, 2);
    return (res == 0) ? 0 : BLE_ATT_ERR_INSUFFICIENT_RES;
  }
  return 0;
}

void HeartRateService::OnNewHeartRateValue() {
 ble_gatts_find_chr((ble_uuid_t *) &heartRateServiceUuid, (ble_uuid_t *)&heartRateMeasurementUuid, nullptr, &heartRateMeasurementHandle);     
 ble_gatts_chr_updated(heartRateMeasurementHandle);
}
