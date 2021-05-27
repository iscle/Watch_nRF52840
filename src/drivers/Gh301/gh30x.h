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

#ifndef gh30x_H
#define gh30x_H

/*lint ++flb "Enter library region" */

#ifdef __cplusplus
 extern "C" {
#endif 

#include <stdbool.h>
#include <stdint.h>

#include "hbd_ctrl.h"
/************************************************************************
*   hardware gpio config
************************************************************************/
//#define GH30X_IIC_EN_PIN_NUMBER         (42U) // P1.10
//#define GH30X_INT_PIN_NUMBER            (19U) // P0.19
//#define GH30X_RSTN_PIN_NUMBER           (25U) // P0.25
//#define GS_INT1_PIN_NUMBER              (21U) // P0.21
//#define GH30X_HBD_ON_PIN_NUMBER         (2U)  // P0.2

//// spi pin define     
//#define IIC_GS_CS_NOT_USE_PIN_NUMBER    (3U)  // P0.3
//#define GH30X_IIC_ADDR_L0_PIN_NUMBER    (45U) // P1.13
//#define GH30X_IIC_ADDR_L1_PIN_NUMBER    (47U) // P1.15
//#define IIC_SCL_PIN_NUMBER              (29U) // P0.29
//#define IIC_SDA_PIN_NUMBER              (31U) // P0.31
//#define IIC_INTRENAL_PULLUP_ENABLE      (1)     

 
//#define GS_SPI_CS_PIN_NUMBER            (3U)  // P0.3 
//#define GH30X_SPI_CS_PIN_NUMBER         (31U) // P0.31
//#define SPI_MISO_PIN_NUMBER             (45U) // P1.13
//#define SPI_MOSI_PIN_NUMBER             (29U) // P0.29
//#define SPI_CLK_PIN_NUMBER              (47U) // P1.15
//#define SPI_MASTER_INSTANCE             2  // SPI instance index. 

//-----------------ʵ���õ���IO-------------------------
#define GH30X_CLOCK_PIN_NUMBER       (12U)   
#define GH30X_DATA_PIN_NUMBER        (13U) 
#define GH30X_RESET_PIN_NUMBER       (24U)
#define GH30X_INT_PIN_NUMBER         (23U)     
//-----------------ʵ���õ���IO-------------------------     

//#define GSENSOR_SOFT_FIFO_BUFFER_MAX_LEN (108)  //buffer��󳤶�
     
//extern  uint16_t gsensor_soft_fifo_buffer_index;
//extern  ST_GS_DATA_TYPE gsensor_soft_fifo_buffer[GSENSOR_SOFT_FIFO_BUFFER_MAX_LEN];
    

int GH30x_module_init(void);
uint8_t gh30x_module_init_check(void);

void gh30x_restart(void);
 
void user_gh30x_heart_stop(void);
uint32_t hal_gh30x_enable_handcheck_int(void);
void gh30x_handcheck_init(void);
bool get_handcheck(void);
void ble_module_gdcs_rx_parse(uint8_t *rx_data, uint16_t rx_length);
void ble_module_disconnected(void);

#ifdef __cplusplus
}
#endif

#endif /* __IO_I2C_GH30x_H */
 
/************************END OF FILE****/



