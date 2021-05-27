#include <nrfx_log.h>
#include <nrf_delay.h>
#include "Bma421.h"
#include "TwiMaster.h"
#include <drivers/Bma421_C/bma423.h>

using namespace Watch::Drivers;

int8_t user_i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t length, void *intf_ptr) {
  auto bma421 = static_cast<Bma421*>(intf_ptr);
  bma421->Read(reg_addr, reg_data, length);
  return 0;
}

int8_t user_i2c_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t length, void *intf_ptr) {
  auto bma421 = static_cast<Bma421*>(intf_ptr);
  bma421->Write(reg_addr, reg_data, length);
  return 0;
}

void user_delay(uint32_t period_us, void *intf_ptr) {
  nrf_delay_us(period_us);
}

Bma421::Bma421(TwiMaster& twiMaster, uint8_t twiAddress) : twiMaster{twiMaster}, twiAddress{twiAddress} {
  bma.intf = BMA4_I2C_INTF;
  bma.bus_read = user_i2c_read;
  bma.bus_write = user_i2c_write;
  bma.variant = BMA42X_VARIANT;
  bma.intf_ptr = this;
  bma.delay_us = user_delay;
  bma.read_write_len = 8;

  accel_conf.odr = BMA4_OUTPUT_DATA_RATE_100HZ;
  accel_conf.range = BMA4_ACCEL_RANGE_2G;
  accel_conf.bandwidth = BMA4_ACCEL_NORMAL_AVG4;
  accel_conf.perf_mode = BMA4_CIC_AVG_MODE;
}

void Bma421::Init() {
  Reset();
  nrf_delay_us(2000);

  auto ret = bma423_init(&bma);
  ASSERT(ret == BMA4_OK);

  ret = bma423_write_config_file(&bma);
  ASSERT(ret == BMA4_OK);

  ret = bma4_set_accel_enable(1, &bma);
  ASSERT(ret == BMA4_OK);

  ret = bma4_set_accel_config(&accel_conf, &bma);
  ASSERT(ret == BMA4_OK);


  //ret =  bma423_feature_enable(BMA423_STEP_CNTR | BMA423_STEP_ACT | BMA423_WRIST_WEAR | BMA423_SINGLE_TAP | BMA423_DOUBLE_TAP, 1, &bma);
  ret = bma423_feature_enable(0xff, 1, &bma);
  ASSERT(ret == BMA4_OK);

  //ret = bma423_map_interrupt(BMA4_INTR1_MAP,  BMA423_SINGLE_TAP_INT | BMA423_STEP_CNTR_INT | BMA423_ACTIVITY_INT | BMA423_WRIST_WEAR_INT | BMA423_DOUBLE_TAP_INT | BMA423_ANY_MOT_INT | BMA423_NO_MOT_INT| BMA423_ERROR_INT, 1,&bma);
  ret = bma423_map_interrupt(BMA4_INTR1_MAP,  0xff, 1,&bma);
  ASSERT(ret == BMA4_OK);

  ret = bma423_step_counter_set_watermark(1, &bma);// 1*20 Steps
  ASSERT(ret == BMA4_OK);

  bma423_step_detector_enable(1, &bma);

  struct bma4_int_pin_config int_pin_config;
  int_pin_config.edge_ctrl = BMA4_LEVEL_TRIGGER;
  int_pin_config.lvl = BMA4_ACTIVE_LOW;
  int_pin_config.od = BMA4_PUSH_PULL;
  int_pin_config.output_en = BMA4_OUTPUT_ENABLE;
  int_pin_config.input_en = BMA4_INPUT_DISABLE;
  bma4_set_int_pin_config(&int_pin_config, BMA4_INTR1_MAP, &bma);
}

void Bma421::Reset() {
  uint8_t data = 0xb6;
  twiMaster.Write(deviceAddress, 0x7E, &data, 1);
}

void Bma421::Read(uint8_t registerAddress, uint8_t *buffer, size_t size) {
  twiMaster.Read(deviceAddress, registerAddress, buffer, size);
}

void Bma421::Write(uint8_t registerAddress, const uint8_t *data, size_t size) {
  twiMaster.Write(deviceAddress, registerAddress, data, size);
}

Bma421::Values Bma421::Process() {
  struct bma4_accel data;
  bma4_read_accel_xyz(&data, &bma);

  //NRF_LOG_INFO("X/Y/Z : %d/%d/%d", data.x, data.y, data.z);


  uint32_t steps = 0;
  bma423_step_counter_output(&steps, &bma);
  //NRF_LOG_INFO("Steps : %d", steps);


  int32_t temperature;
  bma4_get_temperature(&temperature, BMA4_DEG, &bma);
  temperature = temperature / 1000;
  //NRF_LOG_INFO("Temperature : %d", temperature);

  uint16_t intStatus = 0;
  bma423_read_int_status(&intStatus, &bma);
  //NRF_LOG_INFO("Interrupt status : %d", intStatus);

  uint8_t activity = 0;
  bma423_activity_output(&activity, &bma);
  //NRF_LOG_INFO("Activity : %d", activity);
  //NRF_LOG_INFO("");

  return {steps, data.x, data.y, data.z};
}

