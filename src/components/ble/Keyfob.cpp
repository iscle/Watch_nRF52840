#include "Keyfob.h"
#include "components/battery/BatteryController.h"
#include <hal/nrf_gpio.h>
using namespace Watch::Controllers;
using namespace Watch::Application;

constexpr ble_uuid128_t Keyfob::dataCharacteristicUuid;
constexpr ble_uuid128_t Keyfob::controlCharacteristicUuid;
constexpr ble_uuid128_t Keyfob::deviceInfoUuid;



int KeyfobInformationCallback(uint16_t conn_handle, uint16_t attr_handle, struct ble_gatt_access_ctxt *ctxt, void *arg) {
  auto keyfob = static_cast<Keyfob*>(arg);
  return keyfob->OnDeviceInfoRequested(conn_handle, attr_handle, ctxt);
}

int KeyfobInformationCallback1(uint16_t conn_handle, uint16_t attr_handle, struct ble_gatt_access_ctxt *ctxt, void *arg) {
  auto keyfob = static_cast<Keyfob*>(arg);
  return keyfob->OnDeviceInfoRequested1(conn_handle, attr_handle, ctxt);
}

void Keyfob::Init() {
  int res = 0;
  res = ble_gatts_count_cfg(serviceDefinition);
  ASSERT(res == 0);

  res = ble_gatts_add_svcs(serviceDefinition);
  ASSERT(res == 0);
}


int Keyfob::OnDeviceInfoRequested(uint16_t conn_handle, uint16_t attr_handle, struct ble_gatt_access_ctxt *ctxt) { 
if (ctxt->op == BLE_GATT_ACCESS_OP_WRITE_CHR) {  
        os_mbuf_copydata(ctxt->om, 0, sizeof(dataCharacteristicStr), &currentdataCharacteristic);        
} else if (ctxt->op == BLE_GATT_ACCESS_OP_READ_CHR) {  
        uint8_t batteryValue = batteryController.PercentRemaining();
        if(batteryValue>25) currentdataCharacteristic.batteryStatus=0x01; else currentdataCharacteristic.batteryStatus =0x00;
        currentdataCharacteristic.packetCode = batteryController.getButtonData();
        int res = os_mbuf_append(ctxt->om, &currentdataCharacteristic,  sizeof(dataCharacteristicStr));   
        return (res == 0) ? 0 : BLE_ATT_ERR_INSUFFICIENT_RES;
}
return 0;
}

int Keyfob::ble_checkevent()
{       if(batteryController.getIsTouch()){ 
        ble_gatts_find_chr((ble_uuid_t *) &deviceInfoUuid, (ble_uuid_t *) &dataCharacteristicUuid, nullptr, &chr_val_handle);     
        ble_gatts_chr_updated(chr_val_handle);
        batteryController.setIsTouch(false);}        
        return (0);
}



int Keyfob::OnDeviceInfoRequested1(uint16_t conn_handle, uint16_t attr_handle, struct ble_gatt_access_ctxt *ctxt) {
if (ctxt->op == BLE_GATT_ACCESS_OP_WRITE_CHR) {
        os_mbuf_copydata(ctxt->om, 0, sizeof(controlCharacteristicStr), &result);
                  switch(result.nn){
                        case 2:
                                batteryController.fallCharacteristic(result.zz, result.yy);                          
                        break;
                        case 5:
                                batteryController.checkinCharacteristic(result.zz, result.yy);
                        break;
                        case 6:
                                batteryController.impactCharacteristic(result.zz, result.yy);
                        break;                    
                        case 9:
                                NVIC_SystemReset();
                        break;
                        default :
                                batteryController.trackCharacteristic(result.zz, result.yy,result.nn);
                        break;
                       
                  }
                
} else if (ctxt->op == BLE_GATT_ACCESS_OP_READ_CHR) {                 
        int res = os_mbuf_append(ctxt->om, &result, sizeof(controlCharacteristicStr));  
        return (res == 0) ? 0 : BLE_ATT_ERR_INSUFFICIENT_RES; 
        }  
        
         return 0;
}



Keyfob::Keyfob(Controllers::Battery& batteryController) :
        batteryController{batteryController},
        characteristicDefinition{
                {
                        .uuid = (ble_uuid_t *) &dataCharacteristicUuid,
                        .access_cb = KeyfobInformationCallback,
                        .arg = this,
                        .flags = BLE_GATT_CHR_F_NOTIFY                
                        
                },
                {
                        .uuid = (ble_uuid_t *) &controlCharacteristicUuid,
                        .access_cb = KeyfobInformationCallback1,
                        .arg = this,
                        .flags = BLE_GATT_CHR_F_WRITE | BLE_GATT_CHR_F_READ                      
                },
                {
                        0
                }
        },
        serviceDefinition{
                {
                        /* Device Information Service */
                        .type = BLE_GATT_SVC_TYPE_PRIMARY,
                        .uuid = (ble_uuid_t *) &deviceInfoUuid,
                        .characteristics = characteristicDefinition
                },
                {
                        0
                },
        }
         {

}

