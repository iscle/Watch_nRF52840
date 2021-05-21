 /* Copyright (c) 2009 Nordic Semiconductor. All Rights Reserved.
 *
 * The information contained herein is property of Nordic Semiconductor ASA.
 * Terms and conditions of usage are described in detail in NORDIC
 * SEMICONDUCTOR STANDARD SOFTWARE LICENSE AGREEMENT.
 *
 * Licensees are granted free, non-transferable use of the information. NO
 * WARRANTY of ANY KIND is provided. This heading must NOT be removed from
 * the file.
 *
 */

#ifndef GH30X_TWI_MASTER_H
#define GH30X_TWI_MASTER_H

/*lint ++flb "Enter library region" */

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @file
* @brief Software controlled TWI Master driver.
*
*
* @defgroup lib_driver_twi_master Software controlled TWI Master driver
* @{
* @ingroup nrf_twi
* @brief Software controlled TWI Master driver (deprecated).
*
* @warning This module is deprecated.
*
* Supported features:
* - Repeated start
* - No multi-master
* - Only 7-bit addressing
* - Supports clock stretching (with optional SMBus style slave timeout)
* - Tries to handle slaves stuck in the middle of transfer
*/

/**
 * @brief Function for initializing TWI bus IO pins and checks if the bus is operational.
 *
 * Both pins are configured as Standard-0, No-drive-1 (open drain).
 *
 * @return
 * @retval true TWI bus is clear for transfers.
 * @retval false TWI bus is stuck.
 */
bool gh30x_twi_master_init(void);

/**
 * @brief Function for transferring data over TWI bus.
 *
 * If TWI master detects even one NACK from the slave or timeout occurs, STOP condition is issued
 * and the function returns false.
 * Bit 0 (@ref TWI_READ_BIT) in the address parameter controls transfer direction;
 * - If 1, master reads data_length number of bytes from the slave
 * - If 0, master writes data_length number of bytes to the slave.
 *
 * @note Make sure at least data_length number of bytes is allocated in data if TWI_READ_BIT is set.
 * @note @ref TWI_ISSUE_STOP
 *
 * @param address Data transfer direction (LSB) / Slave address (7 MSBs).
 * @param data Pointer to data.
 * @param data_length Number of bytes to transfer.
 * @param issue_stop_condition If @ref TWI_ISSUE_STOP, STOP condition is issued before exiting function. If @ref TWI_DONT_ISSUE_STOP, STOP condition is not issued before exiting function. If transfer failed for any reason, STOP condition will be issued in any case.
 * @return
 * @retval true Data transfer succeeded without errors.
 * @retval false Data transfer failed.
 */
bool gh30x_twi_master_transfer(uint8_t address, uint8_t *data, uint8_t data_length, bool issue_stop_condition);


/**
 *@}
 **/

/*lint --flb "Leave library region" */

#ifdef __cplusplus
}
#endif

#endif //TWI_MASTER_H
