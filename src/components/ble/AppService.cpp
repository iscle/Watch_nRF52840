#include "AppService.h"
#include "components/battery/BatteryController.h"

using namespace Watch::Controllers;
using namespace Watch::Application;

constexpr  ble_uuid128_t  AppService::AppServiceUuid;
constexpr  ble_uuid128_t  AppService::AppServiceCharacteristicUuid;


int AppServiceInformationCallback(uint16_t conn_handle, uint16_t attr_handle, struct ble_gatt_access_ctxt *ctxt, void *arg) {
  auto appService = static_cast<AppService*>(arg);
  return appService->OnDeviceInfoRequested(conn_handle, attr_handle, ctxt);
}

void AppService::Init() {
  int res = 0;
  res = ble_gatts_count_cfg(serviceDefinition);
  ASSERT(res == 0);

  res = ble_gatts_add_svcs(serviceDefinition);
  ASSERT(res == 0);
}


int AppService::OnDeviceInfoRequested(uint16_t conn_handle, uint16_t attr_handle, struct ble_gatt_access_ctxt *ctxt) {
  int res;
     
return (res == 0) ? 0 : BLE_ATT_ERR_INSUFFICIENT_RES;
}

AppService::AppService(Controllers::Battery& batteryController) :
        batteryController{batteryController},
        characteristicDefinition{
                {
                        .uuid = (ble_uuid_t *) &AppServiceCharacteristicUuid,
                        .access_cb = AppServiceInformationCallback,
                        .arg = this,
                        .flags = BLE_GATT_CHR_F_NOTIFY
                         
                        
                },
                {
                  0                
                },
        },
        serviceDefinition{
                {
                        /* Device Information Service */
                        .type = BLE_GATT_SVC_TYPE_PRIMARY,
                        .uuid = (ble_uuid_t *) &AppServiceUuid,
                        .characteristics = characteristicDefinition
                },
                {
                        0
                },
        }
         {

}

