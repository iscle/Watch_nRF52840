#include "Datasensor.h"
#include "components/battery/BatteryController.h"
#include <hal/nrf_gpio.h>
using namespace Watch::Controllers;
using namespace Watch::Application;

constexpr ble_uuid128_t DataSensor::dataCharacteristicUuid;
constexpr ble_uuid128_t DataSensor::controlCharacteristicUuid;
constexpr ble_uuid128_t DataSensor::dataSensorUuid;


int DataSensorInformationCallback(uint16_t conn_handle, uint16_t attr_handle, struct ble_gatt_access_ctxt *ctxt, void *arg) {
  auto dataSensor = static_cast<DataSensor*>(arg);
  return dataSensor->OnDeviceInfoRequested(conn_handle, attr_handle, ctxt);
}

int DataSensorInformationCallback1(uint16_t conn_handle, uint16_t attr_handle, struct ble_gatt_access_ctxt *ctxt, void *arg) {
  auto dataSensor = static_cast<DataSensor*>(arg);
  return dataSensor->OnDeviceInfoRequested1(conn_handle, attr_handle, ctxt);
}

void DataSensor::Init() {
  int res = 0;
  res = ble_gatts_count_cfg(serviceDefinition);
  ASSERT(res == 0);

  res = ble_gatts_add_svcs(serviceDefinition);
  ASSERT(res == 0);
}


int DataSensor::OnDeviceInfoRequested(uint16_t conn_handle, uint16_t attr_handle, struct ble_gatt_access_ctxt *ctxt) { 
if (ctxt->op == BLE_GATT_ACCESS_OP_WRITE_CHR) {  
        os_mbuf_copydata(ctxt->om, 0, sizeof(currentdataCharacteristic), &currentdataCharacteristic);        
} else if (ctxt->op == BLE_GATT_ACCESS_OP_READ_CHR) {  
        currentdataCharacteristic=rand() % 256;
        int res = os_mbuf_append(ctxt->om, &currentdataCharacteristic,  sizeof(currentdataCharacteristic));   
        return (res == 0) ? 0 : BLE_ATT_ERR_INSUFFICIENT_RES;
}
return 0;
}

int DataSensor::ble_checkevent(){     
        ble_gatts_find_chr((ble_uuid_t *) &dataSensorUuid, (ble_uuid_t *) &dataCharacteristicUuid, nullptr, &chr_val_handle);  
        ble_gatts_find_chr((ble_uuid_t *) &dataSensorUuid, (ble_uuid_t *) &controlCharacteristicUuid, nullptr, &chr_val_handle1);    
        ble_gatts_chr_updated(chr_val_handle);
        ble_gatts_chr_updated(chr_val_handle1);  
        return (0);
}


int DataSensor::OnDeviceInfoRequested1(uint16_t conn_handle, uint16_t attr_handle, struct ble_gatt_access_ctxt *ctxt) {
if (ctxt->op == BLE_GATT_ACCESS_OP_WRITE_CHR) {  
        os_mbuf_copydata(ctxt->om, 0, sizeof(result), &result);        
} else if (ctxt->op == BLE_GATT_ACCESS_OP_READ_CHR) { 
       result=rand() % 256;                
        int res = os_mbuf_append(ctxt->om, &result, sizeof(result));  
        return (res == 0) ? 0 : BLE_ATT_ERR_INSUFFICIENT_RES; 
        }  
     return 0;
}

DataSensor::DataSensor(Controllers::Battery& batteryController) :
        batteryController{batteryController},
        characteristicDefinition{
                {
                        .uuid = (ble_uuid_t *) &dataCharacteristicUuid,
                        .access_cb = DataSensorInformationCallback,
                        .arg = this,
                        .flags = BLE_GATT_CHR_F_NOTIFY               
                        
                },
                {
                        .uuid = (ble_uuid_t *) &controlCharacteristicUuid,
                        .access_cb = DataSensorInformationCallback1,
                        .arg = this,
                         .flags = BLE_GATT_CHR_F_NOTIFY                   
                },
                {
                  0
                }
        },
        serviceDefinition{
                {
                        /* Device Information Service */
                        .type = BLE_GATT_SVC_TYPE_PRIMARY,
                        .uuid = (ble_uuid_t *) &dataSensorUuid,
                        .characteristics = characteristicDefinition
                },
                {
                        0
                },
        }
         {

}

