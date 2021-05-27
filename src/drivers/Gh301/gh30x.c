/* includes. */
#include "stdint.h"
#include "string.h"
#include "nrf_delay.h"
#include "nrf_gpio.h"
#include "nrf_drv_gpiote.h"
#include "app_scheduler.h"

#include "gh30x_twi_master.h"
#include "gh30x.h"
#include "hbd_ctrl.h"
#include "nrf_log.h"
#include "app_timer.h"

// application mode macro
#define __APP_MODE_ADT_HB_DET__ (2)
#define __APP_MODE_HRV_DET__ (3)
#define __APP_MODE_HSM_DET__ (4)
#define __APP_MODE_BPD_DET__ (5)
#define __APP_MODE_PFA_DET__ (6)

// application config macro
#define __APP_MODE_CONFIG__ (__APP_MODE_ADT_HB_DET__)
#define __ENABLE_WEARING__ (1)               // wearing algo enable flag
#define __USE_GOODIX_APP__ (0)               // if need use GOODIX app debug
#define __NEED_LOAD_NEW_COFIG__ (1)          // use reg_config_array val update gh30x.
#define __GH30X_IRQ_PLUSE_WIDTH_CONFIG__ (1) // gh30x default irq pluse width 20us, if need config irq pluse width, search this macro.
#define __HB_MODE_ENABLE_FIFO__ (1)

#define __GS_SENSITIVITY_CONFIG__ (HBD_GSENSOR_SENSITIVITY_2048_COUNTS_PER_G)
#define GH30X_CHECK_FIFO_INT_TIMER_TICK  APP_TIMER_TICKS(1080) // 1.08s
#define GH30X_CHECK_ADT_DETECT_TIMER_TICK APP_TIMER_TICKS(30000) // 1.08s
APP_TIMER_DEF(m_gh30x_int_check_timer_id);
APP_TIMER_DEF(m_gh30x_AdtDetect_check_timer_id);

static void gh30x_check_int_receive_handler(void *p_context);

#if (__USE_GOODIX_APP__)
#include "hbd_communicate.h"
#endif

HBD_INIT_CONFIG_DEFAULT_DEF(HbdInitStruct);

#if (__ENABLE_WEARING__)
GF32 wearing_config_array[3] = {0, 0, 0}; // ????app??????,???GOODIX??????
#endif

#if (__NEED_LOAD_NEW_COFIG__) // ??????APP ??,?????,???GOODIX??????
#if (__APP_MODE_CONFIG__ == __APP_MODE_ADT_HB_DET__)
static uint8_t reg_config_load_step = 1;
GU8 reg_config_array_step1[] =  {0x00, 0x47, 0x48, 0x33, 0x2e, 
    0x46, 0x6f, 0x9a, 0x59, 
    0x65, 0x7a, 0x73, 0xd7, 
    0x55, 0x47, 0x9a, 0x5e, 
    0x67, 0x6f, 0x5d, 0xd9, 
    0x73, 0x7a, 0xbe, 0x55, 
    0x78, 0x49, 0x55, 0xfc, 
    0x64, 0x4b, 0x9e, 0x27, 
    0x68, 0x6a, 0x46, 0xc9, 
    0x4e, 0x44, 0xb2, 0x27, 
    0x6f, 0x74, 0x57, 0xe7, 
    0x40, 0x66, 0x83, 0x03, 
    0x64, 0x6f, 0x7d, 0xef, 
    0x65, 0x79, 0x46, 0x90, 
    0x6e, 0x77, 0x65, 0x87, 
    0x48, 0x6f, 0x55, 0xbc, 
    0x6e, 0x48, 0x64, 0x6b, 
    0x66, 0x69, 0x72, 0x70, 
    0x4a, 0x55, 0x7b, 0x05, 
    0x6e, 0x56, 0x60, 0x01, 
    0x6e, 0x5b, 0x6c, 0x22, 
    0x78, 0x5f, 0x4a, 0x4a, 
    0x43, 0xef, 0x6c, 0x63, 
    0x69, 0xe5, 0x40, 0xb0, 
    0x72, 0xcf, 0x65, 0x47, 
    0x42, 0x77, 0x0a, 0x0b, 
    0x46, 0x75, 0x6f, 0x07, 
    0x65, 0x56, 0x49, 0x49, 
    0x55, 0x75, 0x6f, 0x6e, 
    0x67, 0xef, 0x67, 0x46, 
    0x73, 0xf2, 0x4b, 0x48, 
    0x78, 0x69, 0x6c, 0x67, 
    0x64, 0x6b, 0x6f, 0x6c, 
    0x69, 0xa6, 0x87, 0xb6, 
    0x4f, 0x90, 0x48, 0xd7, 
    0x6e, 0xa0, 0x96, 0x98, 
    0x41, 0xba, 0x79, 0xf3, 
    0x65, 0xb3, 0x43, 0xcf, 
    0x64, 0xa9, 0x47, 0x01, 
    0x6f, 0xa7, 0x64, 0x78, 
    0x49, 0x9f, 0x54, 0x43, 
    0x6f, 0xba, 0x66, 0x69, 
    0x67, 0x97, 0x72, 0x72, 
    0x4b, 0xbd, 0x7a, 0x40, 
    0x6f, 0xbe, 0x64, 0x46, 
    0x6f, 0xb3, 0x68, 0x65, 
    0x78, 0x97, 0x4f, 0x54,};

GU8 reg_config_array_step2[] = {
    0x00, 0x47, 0x48, 0x33, 0x2e, 
    0x46, 0x6f, 0x9a, 0x59, 
    0x65, 0x7a, 0x54, 0x03, 
    0x55, 0x47, 0x9a, 0x5e, 
    0x67, 0x6f, 0x7c, 0x19, 
    0x73, 0x7a, 0xbe, 0x55, 
    0x78, 0x49, 0x6e, 0x90, 
    0x64, 0x4b, 0x9e, 0x27, 
    0x68, 0x6a, 0x59, 0x7d, 
    0x4e, 0x44, 0xb2, 0x27, 
    0x6f, 0x74, 0x74, 0x2b, 
    0x40, 0x66, 0x83, 0x03, 
    0x64, 0x6f, 0x41, 0x37, 
    0x65, 0x79, 0x46, 0x90, 
    0x6e, 0x77, 0x65, 0x87, 
    0x48, 0x6f, 0x55, 0xbc, 
    0x6e, 0x48, 0x64, 0x6b, 
    0x66, 0x69, 0x72, 0x70, 
    0x4a, 0x55, 0x7d, 0x05, 
    0x6e, 0x56, 0x67, 0x01, 
    0x6e, 0x5b, 0x6d, 0x22, 
    0x78, 0x5f, 0x4a, 0x4a, 
    0x43, 0xef, 0x6c, 0x63, 
    0x69, 0xe5, 0x40, 0xb0, 
    0x72, 0xcf, 0x65, 0x5f, 
    0x42, 0x77, 0x0a, 0x65, 
    0x46, 0x75, 0x6f, 0x09, 
    0x65, 0x56, 0x49, 0x49, 
    0x55, 0x75, 0x6b, 0xe8, 
    0x67, 0xef, 0x67, 0x46, 
    0x73, 0xf2, 0x4b, 0x48, 
    0x78, 0x69, 0x6c, 0x67, 
    0x64, 0x6b, 0x6f, 0x6c, 
    0x69, 0xa6, 0x87, 0xb6, 
    0x4f, 0x90, 0x48, 0xd7, 
    0x6e, 0xa0, 0x96, 0x98, 
    0x41, 0xba, 0x79, 0xf3, 
    0x65, 0xb3, 0x43, 0xcf, 
    0x64, 0xa9, 0x47, 0x01, 
    0x6f, 0xa7, 0x64, 0x78, 
    0x49, 0x9f, 0x54, 0x43, 
    0x6f, 0xba, 0x66, 0x69, 
    0x67, 0x97, 0x72, 0x72, 
    0x4b, 0xbd, 0x7a, 0x40, 
    0x6f, 0xbe, 0x64, 0x46, 
    0x6f, 0xb3, 0x68, 0x65, 
    0x78, 0x97, 0x4f, 0x54, 
};
#elif (__APP_MODE_CONFIG__ == __APP_MODE_HRV_DET__)
GU8 reg_config_array[] =
    {
        0x00,
        0x3E,
        0x0A,
        0xD3,
        0x02,
        0x47,
        0xEB,
        0x6F,
        0x57,
        0x64,
        0x74,
        0x48,
        0xBF,
};
#elif (__APP_MODE_CONFIG__ == __APP_MODE_HSM_DET__)
GU8 reg_config_array[] =
    {
        0x00,
        0x3E,
        0x0A,
        0xD3,
        0x02,
        0x47,
        0xEB,
        0x6F,
        0x57,
        0x64,
        0x74,
        0x48,
        0xBF,
};
#elif (__APP_MODE_CONFIG__ == __APP_MODE_BPD_DET__)
GU8 reg_config_array[] =
    {
        0x00,
        0x3E,
        0x0A,
        0xD3,
        0x02,
        0x47,
        0xEB,
        0x6F,
        0x57,
        0x64,
        0x74,
        0x48,
        0xBF,
};
#elif (__APP_MODE_CONFIG__ == __APP_MODE_PFA_DET__)
GU8 reg_config_array[] =
    {
        0x00,
        0x3E,
        0x0A,
        0xD3,
        0x02,
        0x47,
        0xEB,
        0x6F,
        0x57,
        0x64,
        0x74,
        0x48,
        0xBF,
};
#endif
#endif

#if (__USE_GOODIX_APP__)
int8_t ble_comm_type = 0xFF;
EM_COMM_CMD_TYPE gh30x_status = COMM_CMD_INVALID;
#endif

#if (__ENABLE_WEARING__)
uint8_t last_wearing_state = 1;
#endif

#define GSENSOR_SOFT_FIFO_BUFFER_MAX_LEN (100)
static uint16_t gsensor_soft_fifo_buffer_index = 0;
static ST_GS_DATA_TYPE gsensor_soft_fifo_buffer[GSENSOR_SOFT_FIFO_BUFFER_MAX_LEN];

#define GH30X_CLOCK_PIN_NUMBER (12U)
#define GH30X_DATA_PIN_NUMBER (13U)
#define GH30X_RESET_PIN_NUMBER (24U)
#define GH30X_INT_PIN_NUMBER (23U)
#define GH30x_ADDR 0x28 // !< Device address in bits [7:1]   0x28
#define OUTPUT_HIGH 1
#define OUTPUT_LOW 0

#define TWI_READ_BIT (0x01)               //!< If this bit is set in the address field, transfer direction is from slave to master.
#define TWI_ISSUE_STOP ((bool)true)       //!< Parameter for @ref twi_master_transfer
#define TWI_DONT_ISSUE_STOP ((bool)false) //!< Parameter for @ref twi_master_transfer

bool g_i2c_init_done = 0;
uint8_t  heartrate;
uint8_t  flagI2C;
uint8_t  flagInt;

int8_t Gsensor_Buffer[252];
uint16_t gsensor_len;
int16_t xyz[3] = {0};
static bool is_hr_ready = false;
static bool is_hr_touch = false;
static bool is_handcheck = false;
bool get_hr_ready(void)
{
    return is_hr_ready;
}

bool get_hr_touch(void)
{
    return is_hr_touch;
}
bool get_handcheck(void)
{
    return is_handcheck;
}
uint8_t gh301_adt_working_flag = 0;
void HBD_AdtWearDetectStart_with_initcheck()
{
    if (HBD_AdtWearDetectStart() == HBD_RET_NO_INITED_ERROR) // start adt detect
    {
    	HBD_SimpleInit(&HbdInitStruct);
		
        #if (__NEED_LOAD_NEW_COFIG__)
        HBD_LoadNewConfig(reg_config_array_step1, 0);
        reg_config_load_step = 1;
        #endif

        if (HBD_AdtWearDetectStart() == HBD_RET_NO_INITED_ERROR) // start adt detect
		{
		     HBD_SimpleInit(&HbdInitStruct);

            #if (__NEED_LOAD_NEW_COFIG__)
            HBD_LoadNewConfig(reg_config_array_step1, 0);
            reg_config_load_step = 1;
            #endif
            if (HBD_AdtWearDetectStart() == HBD_RET_NO_INITED_ERROR) // start adt detect
            {
              
            }
            gh301_adt_working_flag = 1;
        }
    }
	else
	{
		gh301_adt_working_flag = 1;
	}
}
void HBD_HbDetectStart_with_initcheck()
{
    if (HBD_HbDetectStart() == HBD_RET_NO_INITED_ERROR) // start adt detect
    {
    	HBD_SimpleInit(&HbdInitStruct);
		
        #if (__NEED_LOAD_NEW_COFIG__)
        HBD_LoadNewConfig(reg_config_array_step1, 0);
        reg_config_load_step = 1;
        #endif

        if (HBD_HbDetectStart() == HBD_RET_NO_INITED_ERROR) // start adt detect
		{
		     HBD_SimpleInit(&HbdInitStruct);

            #if (__NEED_LOAD_NEW_COFIG__)
            HBD_LoadNewConfig(reg_config_array_step1, 0);
            reg_config_load_step = 1;
            #endif
            if (HBD_HbDetectStart() == HBD_RET_NO_INITED_ERROR) // start adt detect
            {
              
            }
            gh301_adt_working_flag = 0;
        }
    }
	else
	{
		gh301_adt_working_flag = 0;
	}
}
void gh30x_start(void)
{
    //  HBD_HbDetectStart();
    HBD_LoadNewConfig(reg_config_array_step1, 0);
    reg_config_load_step = 1;
    HBD_AdtWearDetectStart_with_initcheck();
	app_timer_stop(m_gh30x_AdtDetect_check_timer_id);
	 app_timer_start(m_gh30x_AdtDetect_check_timer_id, GH30X_CHECK_ADT_DETECT_TIMER_TICK, NULL);
    gh301_adt_working_flag = 1;
    //app_timer_start(m_gh30x_int_check_timer_id, GH30X_CHECK_FIFO_INT_TIMER_TICK, NULL);
}

void gh30x_restart(void)
{
    //	HBD_LoadNewConfig(reg_config_array_step1, 0);
    //   reg_config_load_step = 1;
    HBD_LoadNewConfig(reg_config_array_step1, 0);
    reg_config_load_step = 1;
    HBD_AdtWearDetectStart_with_initcheck();
	app_timer_stop(m_gh30x_AdtDetect_check_timer_id);
	 app_timer_start(m_gh30x_AdtDetect_check_timer_id, GH30X_CHECK_ADT_DETECT_TIMER_TICK, NULL);
    gh301_adt_working_flag = 1;
}
void user_gh30x_heart_stop(void)
{
    HBD_Stop();
    gh301_adt_working_flag = 0;
}
void set_hr(uint8_t hr){ heartrate=hr;}

void gh30x_nrf_io_set_output(uint8_t pin_number)
{
    nrf_gpio_cfg_output(pin_number);
}

void gh30x_nrf_io_output_HL(uint8_t pin_number, uint8_t pin_state)
{
    if (pin_state == 1)
    {
        nrf_gpio_pin_set(pin_number);
    }
    else
    {
        nrf_gpio_pin_clear(pin_number);
    }
}

void gsensor_drv_get_fifo_data(ST_GS_DATA_TYPE gsensor_buffer[], uint16_t *gsensor_buffer_index, uint16_t gsensor_max_len);

void process_gh301_fifo_int(void)
{
    uint8_t hb_value = 0;
    uint8_t wearing_state = 0;
    uint8_t wearing_quality = 0;
    uint8_t voice_broadcast = 0;
    uint16_t rr_value = 0;
    gsensor_drv_get_fifo_data(gsensor_soft_fifo_buffer, &gsensor_soft_fifo_buffer_index, GSENSOR_SOFT_FIFO_BUFFER_MAX_LEN);
    HBD_HbCalculateByFifoInt(gsensor_soft_fifo_buffer, gsensor_soft_fifo_buffer_index, __GS_SENSITIVITY_CONFIG__, &hb_value, &wearing_state, &wearing_quality, &voice_broadcast, &rr_value);
    app_timer_start(m_gh30x_int_check_timer_id, GH30X_CHECK_FIFO_INT_TIMER_TICK, NULL);
	if(hb_value==0)
	{
	     is_hr_ready = false;
	}
	else
	{
		 is_hr_ready = true;
	}
    set_hr(hb_value);
}

static void gh30x_check_int_receive_handler(void *p_context)
{
    app_timer_stop(m_gh30x_AdtDetect_check_timer_id);
    uint8_t uchChipIntStatus_check1;
    uint8_t uchChipIntStatus_check2;

    uchChipIntStatus_check1 = HBD_GetIntStatus();
    uchChipIntStatus_check2 = HBD_GetIntStatus();
    if ((uchChipIntStatus_check1 == INT_STATUS_FIFO_WATERMARK) && (uchChipIntStatus_check2 == INT_STATUS_INVALID))
    {
        process_gh301_fifo_int();
    }
    else
    {
        //gsensor_drv_enter_normal_mode();
        //gsensor_drv_clear_buffer(gsensor_soft_fifo_buffer, &gsensor_soft_fifo_buffer_index, GSENSOR_SOFT_FIFO_BUFFER_MAX_LEN)

       HBD_SimpleInit(&HbdInitStruct);
#if (__NEED_LOAD_NEW_COFIG__)
        HBD_LoadNewConfig(reg_config_array_step1, 0);
        reg_config_load_step = 1;
#endif
        HBD_AdtWearDetectStart_with_initcheck();

	 app_timer_start(m_gh30x_AdtDetect_check_timer_id, GH30X_CHECK_ADT_DETECT_TIMER_TICK, NULL);
        gh301_adt_working_flag = 1;
    }
}
static void gh30x_check_AdtDetect_receive_handler(void *p_context)
{
	HBD_AdtWearDetectStart_with_initcheck();
	app_timer_start(m_gh30x_AdtDetect_check_timer_id, GH30X_CHECK_ADT_DETECT_TIMER_TICK, NULL);
	gh301_adt_working_flag = 1;
}
/// i2c interface
void hal_gh30x_i2c_init(void)
{
    // code implement by user
    if (g_i2c_init_done)
    {
        return;
    }
    //twi_HBD_master_init();
    gh30x_nrf_io_set_output(GH30X_CLOCK_PIN_NUMBER);
    gh30x_nrf_io_output_HL(GH30X_CLOCK_PIN_NUMBER, OUTPUT_LOW);

    gh30x_nrf_io_set_output(GH30X_DATA_PIN_NUMBER);
    gh30x_nrf_io_output_HL(GH30X_DATA_PIN_NUMBER, OUTPUT_LOW);

    // gh30x_nrf_io_set_output(GH30X_RESET_PIN_NUMBER);
    //gh30x_nrf_io_output_HL(GH30X_RESET_PIN_NUMBER,OUTPUT_LOW);

    nrf_delay_ms(10);
    //  gh30x_nrf_io_output_HL(GH30X_RESET_PIN_NUMBER,OUTPUT_HIGH);
    nrf_delay_ms(40);
    gh30x_twi_master_init();
    g_i2c_init_done = 1;
}

uint8_t hal_gh30x_i2c_write(uint8_t device_id, const uint8_t write_buffer[], uint16_t length)
{
    uint8_t ret = 1;
    ret = gh30x_twi_master_transfer(GH30x_ADDR, (uint8_t *)write_buffer, length, TWI_ISSUE_STOP);
    nrf_delay_us(40);
    return ret;
}

uint8_t hal_gh30x_i2c_read(uint8_t device_id, const uint8_t write_buffer[], uint16_t write_length, uint8_t read_buffer[], uint16_t read_length)
{
    uint8_t ret = 1;
    ret = gh30x_twi_master_transfer(GH30x_ADDR, (uint8_t *)write_buffer, write_length, TWI_DONT_ISSUE_STOP);
    ret &= gh30x_twi_master_transfer(GH30x_ADDR | TWI_READ_BIT, read_buffer, read_length, TWI_ISSUE_STOP);
    nrf_delay_us(40);
    return ret;
}

uint8_t gsensor_drv_motion_det_mode = 0;
/// gsensor driver
int8_t gsensor_drv_init(void)
{
    int8_t ret = 1;
    gsensor_drv_motion_det_mode = 0;
    // code implement by user
    return ret;
}

void gsensor_drv_enter_normal_mode(void)
{
    // code implement by user
    gsensor_drv_motion_det_mode = 0;
}

void gsensor_drv_enter_fifo_mode(void)
{
    // code implement by user
    gsensor_drv_motion_det_mode = 0;
}
void gsensor_drv_enter_motion_det_mode(void)
{
    // code implement by user
    gsensor_drv_motion_det_mode = 1;
}

void gsensor_drv_get_fifo_data(ST_GS_DATA_TYPE gsensor_buffer[], uint16_t *gsensor_buffer_index, uint16_t gsensor_max_len)
{
    // code implement by user
    uint8_t i;
    //NRF_LOG_PRINTF("gsensor_len A = %d\r\n",gsensor_len);
    for (i = 0; i < gsensor_len / 3; i++)
    {
        gsensor_soft_fifo_buffer[i].sXAxisVal = Gsensor_Buffer[i * 3] * 16;
        gsensor_soft_fifo_buffer[i].sYAxisVal = Gsensor_Buffer[i * 3 + 1] * 16;
        gsensor_soft_fifo_buffer[i].sZAxisVal = Gsensor_Buffer[i * 3 + 2] * 16;
    }
    gsensor_soft_fifo_buffer_index = gsensor_len / 3;
    //NRF_LOG_PRINTF("gsensor_soft_fifo_buffer_index A = %d\r\n",gsensor_soft_fifo_buffer_index);
    for (i = 0; i < gsensor_soft_fifo_buffer_index; i++)
    {
     //   NRF_LOG_PRINTF("%-8d %-8d %-8d\n", Gsensor_Buffer[i * 3], Gsensor_Buffer[i * 3 + 1], Gsensor_Buffer[i * 3 + 2]);
    //    NRF_LOG_PRINTF("x =%d,y = %d,z = %d\r\n", gsensor_soft_fifo_buffer[i].sXAxisVal, gsensor_soft_fifo_buffer[i].sYAxisVal, gsensor_soft_fifo_buffer[i].sZAxisVal);
    }
//    timerhandler();
    //NRF_LOG_PRINTF("gsensor_len B = %d\r\n",gsensor_len);
    for (i = 0; i < gsensor_len / 3; i++)
    {
        gsensor_soft_fifo_buffer[i + gsensor_soft_fifo_buffer_index].sXAxisVal = Gsensor_Buffer[i * 3] * 16;
        gsensor_soft_fifo_buffer[i + gsensor_soft_fifo_buffer_index].sYAxisVal = Gsensor_Buffer[i * 3 + 1] * 16;
        gsensor_soft_fifo_buffer[i + gsensor_soft_fifo_buffer_index].sZAxisVal = Gsensor_Buffer[i * 3 + 2] * 16;
    }
    gsensor_soft_fifo_buffer_index += gsensor_len / 3;
    //NRF_LOG_PRINTF("gsensor_soft_fifo_buffer_index B = %d\r\n",gsensor_soft_fifo_buffer_index);
    for (i = 0; i < gsensor_soft_fifo_buffer_index; i++)
    {
       // NRF_LOG_PRINTF("%-8d %-8d %-8d\n", Gsensor_Buffer[i * 3], Gsensor_Buffer[i * 3 + 1], Gsensor_Buffer[i * 3 + 2]);
      //  NRF_LOG_PRINTF("x =%d,y = %d,z = %d\r\n", gsensor_soft_fifo_buffer[i].sXAxisVal, gsensor_soft_fifo_buffer[i].sYAxisVal, gsensor_soft_fifo_buffer[i].sZAxisVal);
    }
    if (gsensor_soft_fifo_buffer_index < 25)
    {
        for (i = gsensor_soft_fifo_buffer_index; i < 25; i++)
        {
            gsensor_soft_fifo_buffer[i].sXAxisVal = gsensor_soft_fifo_buffer[i - 1].sXAxisVal;
            gsensor_soft_fifo_buffer[i].sYAxisVal = gsensor_soft_fifo_buffer[i - 1].sYAxisVal;
            gsensor_soft_fifo_buffer[i].sZAxisVal = gsensor_soft_fifo_buffer[i - 1].sZAxisVal;
        }
        gsensor_soft_fifo_buffer_index = 25;
    }
}

void gsensor_drv_clear_buffer(ST_GS_DATA_TYPE gsensor_buffer[], uint16_t *gsensor_buffer_index, uint16_t gsensor_buffer_len)
{
    memset(gsensor_buffer, 0, sizeof(ST_GS_DATA_TYPE) * gsensor_buffer_len);
    *gsensor_buffer_index = 0;
}

void gsensor_drv_get_data(ST_GS_DATA_TYPE *gsensor_data_ptr)
{
    // code implement by user
}

void gsensor_drv_int1_handler(void)
{
    // code implement by user
    if (gsensor_drv_motion_det_mode != 0)
    {
        gsensor_drv_enter_normal_mode();
        gsensor_drv_clear_buffer(gsensor_soft_fifo_buffer, &gsensor_soft_fifo_buffer_index, GSENSOR_SOFT_FIFO_BUFFER_MAX_LEN);
#if (__NEED_LOAD_NEW_COFIG__)
        HBD_LoadNewConfig(reg_config_array_step1, 0);
        reg_config_load_step = 1;
#endif
        HBD_AdtWearDetectStart_with_initcheck();
        gh301_adt_working_flag = 1;
        //app_timer_start(m_gh30x_int_check_timer_id, GH30X_CHECK_FIFO_INT_TIMER_TICK, NULL);
    }
    else
    {
        /* if using gsensor fifo mode, shouold get data by fifo int 
		 * E.g gsensor_drv_get_fifo_data(gsensor_soft_fifo_buffer, &gsensor_soft_fifo_buffer_index, GSENSOR_SOFT_FIFO_BUFFER_MAX_LEN);   
		*/
    }
}
void GH30x_Int_Msg_Handler(void);

static void gh30x_int_pin_handler(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
    //NRF_LOG("gh30x_int_pin_handler\n");
    if (pin == GH30X_INT_PIN_NUMBER)
    {
         GH30x_Int_Msg_Handler();
    }
}
/// int
void hal_gh30x_int_init(void)
{
    // code implement by user
    nrf_gpio_cfg_input(GH30X_INT_PIN_NUMBER, NRF_GPIO_PIN_NOPULL);
    nrf_drv_gpiote_in_config_t config = GPIOTE_CONFIG_IN_SENSE_LOTOHI(false); //GPIOTE_CONFIG_IN_SENSE_TOGGLE(false); //
                                                                              // config.pull = NRF_GPIO_PIN_PULLUP;
    nrf_drv_gpiote_in_init(GH30X_INT_PIN_NUMBER, &config, gh30x_int_pin_handler);
    nrf_drv_gpiote_in_event_enable(GH30X_INT_PIN_NUMBER, true);
    //HBD_SetIrqPluseWidth(GH301_INT_PLUSE_WIDTH); // set Irq pluse width (50us)
}

void hal_gsensor_int1_init(void)
{
    // code implement by user

    /* if using gsensor fifo mode,
	and gsensor fifo depth is not enough to store 1 second data,
	please connect gsensor fifo interrupt to the host,
	or if using gsensor motion detect mode(e.g  motion interrupt response by 0.5G * 5counts),
	and implement this function to receive gsensor interrupt.
	*/
}

/// ble
void ble_module_send_heartrate(uint32_t heartrate) // send value via heartrate profile
{
    // code implement by user
}

void ble_module_add_rr_interval(uint16_t rr_interval_arr[], uint8_t cnt) // add value to heartrate profile
{
    // code implement by user
}

extern void ble_module_send_data_via_gdcs(uint8_t string[], uint8_t length); // send value via through profile
//{
// code implement by user
//}

/* gh30x module init, include gsensor init. */
int GH30x_module_init(void)
{
#if (!__HB_MODE_ENABLE_FIFO__)
    HbdInitStruct.stHbInitConfig.emHbModeFifoEnable = HBD_FUNCTIONAL_STATE_DISABLE;  //if GH30x fifo disable
    HbdInitStruct.stHbInitConfig.emHrvModeFifoEnable = HBD_FUNCTIONAL_STATE_DISABLE; //if GH30x fifo disable
    HbdInitStruct.stHbInitConfig.emHsmModeFifoEnable = HBD_FUNCTIONAL_STATE_DISABLE; //if GH30x fifo disable
    HbdInitStruct.stHbInitConfig.emBpdModeFifoEnable = HBD_FUNCTIONAL_STATE_DISABLE; //if GH30x fifo disable
    HbdInitStruct.stHbInitConfig.emPfaModeFifoEnable = HBD_FUNCTIONAL_STATE_DISABLE; //if GH30x fifo disable
#endif

    HbdInitStruct.stAdtInitConfig.emLogicChannel0PDSelect = HBD_LED_PD_SEL_EXTERNAL;
    HbdInitStruct.stAdtInitConfig.emLogicChannel1PDSelect = HBD_LED_PD_SEL_EXTERNAL;
    HbdInitStruct.stAdtInitConfig.uchLogicChannel0Current = 0x28;
    HbdInitStruct.stAdtInitConfig.uchLogicChannel1Current = 0x28;
    HbdInitStruct.stAdtInitConfig.emLogicChannel0TiaGain = HBD_TIA_GAIN_2;
    HbdInitStruct.stAdtInitConfig.emLogicChannel1TiaGain = HBD_TIA_GAIN_2;

    /*1. user i2c init. */
    hal_gh30x_i2c_init();

    /*2. register i2c RW. hal_gh30x_i2c_write and  hal_gh30x_i2c_read must be defined by user. */
    HBD_SetI2cRW(HBD_I2C_ID_SEL_1L0L, hal_gh30x_i2c_write, hal_gh30x_i2c_read);

    /*3. Init GH30x. */
    HBD_SimpleInit(&HbdInitStruct);
   //NRF_LOG_PRINTF("chRet = %d\r\n", chRet);
    /*4. gsensor init. gsensor_drv_init must be defined by user, and >40Hz. */
    //	gsensor_drv_init();

    /*5.1 setup EX INT for G-sensor INT pin. hal_gsensor_int1_init must be defined by user. */
    //    hal_gsensor_int1_init();
    /*5.2 setup EX INT for GH30x INT pin. hal_gh30x_int_init must be defined by user. */
    hal_gh30x_int_init();

#if (__GH30X_IRQ_PLUSE_WIDTH_CONFIG__)
    /*5.3 (optional) GH30x INT pin irq pluse width. */
    HBD_SetIrqPluseWidth(255); // set Irq pluse width (50us)
#endif

#if (__NEED_LOAD_NEW_COFIG__)
    /*6 (optional) load new config for GH30x, config array generate by GOODIX APP. */
    HBD_LoadNewConfig(reg_config_array_step1, 0);
    reg_config_load_step = 1;
#endif

#if (__USE_GOODIX_APP__)
    /*7. setup Ble(or other.) send data function. */
    ble_comm_type = HBD_SetSendDataFunc(ble_module_send_data_via_gdcs);
    // ble_comm_type = HBD_SetSendDataFunc(ble_module_send_data_via_gdcs);
    ble_module_gdcs_register_rx_handler(ble_module_gdcs_rx_parse);
#endif

#if (__ENABLE_WEARING__)
    /*8. (optional)enable wearing function, only for GH300. */
    HBD_EnableWearing(wearing_config_array);
#endif

    /*9. (optional)start GH30x. */
    HBD_AdtWearDetectStart_with_initcheck();
    app_timer_create(&m_gh30x_int_check_timer_id, APP_TIMER_MODE_SINGLE_SHOT, gh30x_check_int_receive_handler);
	app_timer_create(&m_gh30x_AdtDetect_check_timer_id, APP_TIMER_MODE_SINGLE_SHOT, gh30x_check_AdtDetect_receive_handler);
	app_timer_start(m_gh30x_AdtDetect_check_timer_id, GH30X_CHECK_ADT_DETECT_TIMER_TICK, NULL);
    return HBD_RET_OK;
}

/* GH30x Int msg handler .*/
void GH30x_Int_Msg_Handler(void)
{
    app_timer_stop(m_gh30x_int_check_timer_id);
	app_timer_stop(m_gh30x_AdtDetect_check_timer_id);
    uint8_t uchChipIntStatus = HBD_GetIntStatus();
    if (uchChipIntStatus == INT_STATUS_FIFO_WATERMARK)
    {
        process_gh301_fifo_int();
    }
    else if (uchChipIntStatus == INT_STATUS_NEW_DATA)
    {
        ST_GS_DATA_TYPE gsensor_data;
        /*1. get gsensor data. gsensor_drv_get_data must be defined by user.*/
        //gsensor_drv_get_data(&gsensor_data);
        //get_kx023_buffer_to_gh30x();
        
       // kx022_get_XYZ((uint8_t *)xyz);
    //    NRF_LOG_PRINTF("xyz %-8d %-8d %-8d\n", xyz[0], xyz[1], xyz[2]);
        gsensor_data.sXAxisVal = xyz[0];
        gsensor_data.sYAxisVal = xyz[1];
        gsensor_data.sZAxisVal = xyz[2];

#if (__USE_GOODIX_APP__)
        if (gh30x_status == COMM_CMD_ALGO_IN_APP_HB_START)
        {
            /*2. send data package. */
            HBD_SendRawdataPackageByNewdataInt(&gsensor_data, __GS_SENSITIVITY_CONFIG__);
        }
        else
#endif
        {
#if (__APP_MODE_CONFIG__ == __APP_MODE_ADT_HB_DET__)
            static uint8_t calc_cnt2 = 0;
            uint8_t hb_value = 0;
            uint8_t wearing_state = 0;
            uint8_t wearing_quality = 0;
            uint8_t voice_broadcast = 0;
            uint16_t rr_value = 0;
            if (1 == HBD_HbCalculateByNewdataInt(&gsensor_data, __GS_SENSITIVITY_CONFIG__, &hb_value, &wearing_state, &wearing_quality, &voice_broadcast, &rr_value))
            {
                //value have reflash.
            }
            calc_cnt2++;
            if (calc_cnt2 >= 25) // 25 Hz
            {
                ble_module_add_rr_interval(&rr_value, 1);
                ble_module_send_heartrate(hb_value); // send data via ble heartrate profile
                calc_cnt2 = 0;
            }
#endif
        }
    }
    else if (uchChipIntStatus == INT_STATUS_WEAR_DETECTED)
    {
    	is_handcheck = true;
        gsensor_drv_enter_normal_mode();
#if (__APP_MODE_CONFIG__ == __APP_MODE_ADT_HB_DET__)

#if (__ENABLE_WEARING__)
        last_wearing_state = 1;
#endif

#if (__HB_MODE_ENABLE_FIFO__)
        gsensor_drv_clear_buffer(gsensor_soft_fifo_buffer, &gsensor_soft_fifo_buffer_index, GSENSOR_SOFT_FIFO_BUFFER_MAX_LEN);
        gsensor_drv_enter_fifo_mode(); // if GH30x fifo enable
#endif

        HBD_HbDetectStart_with_initcheck();
        gh301_adt_working_flag = 0;

        app_timer_start(m_gh30x_int_check_timer_id, GH30X_CHECK_FIFO_INT_TIMER_TICK, NULL);

#endif
    }
    else if (uchChipIntStatus == INT_STATUS_UNWEAR_DETECTED)
    {
#if (__USE_GOODIX_APP__)
        if (gh30x_status == COMM_CMD_ALGO_IN_APP_HB_START)
        {
            gsensor_drv_enter_normal_mode();
            gsensor_drv_clear_buffer(gsensor_soft_fifo_buffer, &gsensor_soft_fifo_buffer_index, GSENSOR_SOFT_FIFO_BUFFER_MAX_LEN);
#if (__HB_MODE_ENABLE_FIFO__)
            HBD_FifoConfig(1, HBD_FUNCTIONAL_STATE_DISABLE);
#endif
#if (__APP_MODE_CONFIG__ == __APP_MODE_ADT_HB_DET__)
            HBD_HbDetectStart_with_initcheck();
            gh301_adt_working_flag = 0;

#endif
#if (__HB_MODE_ENABLE_FIFO__)
            HBD_FifoConfig(1, HBD_FUNCTIONAL_STATE_ENABLE);
#endif
            //NRF_LOG_PRINTF("INT_STATUS_UNWEAR_DETECTED app\n");
        }
        else
#endif
        {
#if ((__NEED_LOAD_NEW_COFIG__) && (__APP_MODE_CONFIG__ == __APP_MODE_ADT_HB_DET__))
            switch (reg_config_load_step)
            {
            case 1:
            {
                HBD_Stop();
                HBD_LoadNewConfig(reg_config_array_step2, 0);
                reg_config_load_step = 2;
                HBD_HbDetectStart_with_initcheck();
                gh301_adt_working_flag = 0;
                app_timer_start(m_gh30x_int_check_timer_id, GH30X_CHECK_FIFO_INT_TIMER_TICK, NULL);
            }
            break;
            case 2:
            default:
            {
                HBD_Stop();
                HBD_LoadNewConfig(reg_config_array_step1, 0);
                reg_config_load_step = 1;
                is_handcheck = false;
                is_hr_touch = false;
                is_hr_ready = false;
                set_hr(0);
                HBD_AdtWearDetectStart_with_initcheck();
				 app_timer_start(m_gh30x_AdtDetect_check_timer_id, GH30X_CHECK_ADT_DETECT_TIMER_TICK, NULL);
                gh301_adt_working_flag = 1;
		return;
            }
            break;
            }
#endif
        }
    }
    else if (uchChipIntStatus == INT_STATUS_CHIP_RESET) // if gh30x reset, need reinit
    {
        GS8 reinit_ret = HBD_RET_OK;
        GU8 reinit_cnt = 5;
        gsensor_drv_enter_normal_mode();
        gsensor_drv_clear_buffer(gsensor_soft_fifo_buffer, &gsensor_soft_fifo_buffer_index, GSENSOR_SOFT_FIFO_BUFFER_MAX_LEN);
        // reinit
        do
        {
            reinit_ret = HBD_SimpleInit(&HbdInitStruct);
            reinit_cnt--;
	    if(reinit_cnt==0)
	    {
	    	break;
	    }
        } while (reinit_ret != HBD_RET_OK);
        if (reinit_ret == HBD_RET_OK)
        {
#if (__NEED_LOAD_NEW_COFIG__)
            HBD_LoadNewConfig(reg_config_array_step1, 0);
            reg_config_load_step = 1;
#endif
            HBD_AdtWearDetectStart_with_initcheck();
 app_timer_start(m_gh30x_AdtDetect_check_timer_id, GH30X_CHECK_ADT_DETECT_TIMER_TICK, NULL);
            gh301_adt_working_flag = 1;
        }
	return;
    }
    else if (uchChipIntStatus == INT_STATUS_FIFO_FULL) // if gh30x fifo full, need restart
    {
#if (__APP_MODE_CONFIG__ == __APP_MODE_ADT_HB_DET__)
        HBD_Stop();
        gh301_adt_working_flag = 0;
        gsensor_drv_enter_normal_mode();
#if (__HB_MODE_ENABLE_FIFO__)
        gsensor_drv_clear_buffer(gsensor_soft_fifo_buffer, &gsensor_soft_fifo_buffer_index, GSENSOR_SOFT_FIFO_BUFFER_MAX_LEN);
        gsensor_drv_enter_fifo_mode(); // if GH30x fifo enable
#endif
        HBD_HbDetectStart_with_initcheck();
        gh301_adt_working_flag = 0;

        app_timer_start(m_gh30x_int_check_timer_id, GH30X_CHECK_FIFO_INT_TIMER_TICK, NULL);
#endif
    }
    if ((gh301_adt_working_flag == 1) && (uchChipIntStatus != INT_STATUS_WEAR_DETECTED))
    {
        HBD_AdtWearDetectStart_with_initcheck();
		app_timer_start(m_gh30x_AdtDetect_check_timer_id, GH30X_CHECK_ADT_DETECT_TIMER_TICK, NULL);
        gh301_adt_working_flag = 1;
        return;
    }
else
{
//	NRF_LOG_PRINTF(" SetHR_IIC_failed(0x08);  else gh301_adt_working_flag =  %d\n",gh301_adt_working_flag);
}
}

#if (__USE_GOODIX_APP__)
static uint8_t nus_rx_data[256] = {0};
uint16_t nus_rx_len = 0;
/* ble rx data handler. */
void app_parse(uint8_t *buffer, uint8_t length)
{
    /*1. parse data. */
    EM_COMM_CMD_TYPE eCommCmdType = HBD_CommParseHandler(ble_comm_type, nus_rx_data, nus_rx_len);
	app_timer_stop(m_gh30x_AdtDetect_check_timer_id);
	app_timer_stop(m_gh30x_int_check_timer_id);
//	NRF_LOG_PRINTF("app_parse  eCommCmdType =  %d\n",eCommCmdType);
	SetHR_App_Parse_status(eCommCmdType);
    if (eCommCmdType < COMM_CMD_INVALID)
    {
        if (eCommCmdType == COMM_CMD_ALGO_IN_MCU_HB_START)
        {
            gsensor_drv_enter_normal_mode();
#if (__HB_MODE_ENABLE_FIFO__)
            gsensor_drv_clear_buffer(gsensor_soft_fifo_buffer, &gsensor_soft_fifo_buffer_index, GSENSOR_SOFT_FIFO_BUFFER_MAX_LEN);
            gsensor_drv_enter_fifo_mode();
#endif
#if (__APP_MODE_CONFIG__ == __APP_MODE_ADT_HB_DET__)
            HBD_HbDetectStart_with_initcheck();
            gh301_adt_working_flag = 0;

#endif
        }
        else if (eCommCmdType == COMM_CMD_ALGO_IN_APP_HB_START)
        {
            gsensor_drv_enter_normal_mode();
            gsensor_drv_clear_buffer(gsensor_soft_fifo_buffer, &gsensor_soft_fifo_buffer_index, GSENSOR_SOFT_FIFO_BUFFER_MAX_LEN);
#if (__HB_MODE_ENABLE_FIFO__)
            HBD_FifoConfig(1, HBD_FUNCTIONAL_STATE_DISABLE);
#endif
#if (__APP_MODE_CONFIG__ == __APP_MODE_ADT_HB_DET__)
            HBD_HbDetectStart_with_initcheck();
            gh301_adt_working_flag = 0;

#endif
#if (__HB_MODE_ENABLE_FIFO__)
            HBD_FifoConfig(1, HBD_FUNCTIONAL_STATE_ENABLE);
#endif
        }
        else if (eCommCmdType == COMM_CMD_ALGO_IN_MCU_HRV_START)
        {
            gsensor_drv_enter_normal_mode();
#if (__HB_MODE_ENABLE_FIFO__)
            gsensor_drv_clear_buffer(gsensor_soft_fifo_buffer, &gsensor_soft_fifo_buffer_index, GSENSOR_SOFT_FIFO_BUFFER_MAX_LEN);
            gsensor_drv_enter_fifo_mode();
#endif
#if (__APP_MODE_CONFIG__ == __APP_MODE_HRV_DET__)
            HBD_HrvDetectStart();
#endif
        }
        else if (eCommCmdType == COMM_CMD_ALGO_IN_APP_HRV_START)
        {
            gsensor_drv_enter_normal_mode();
            gsensor_drv_clear_buffer(gsensor_soft_fifo_buffer, &gsensor_soft_fifo_buffer_index, GSENSOR_SOFT_FIFO_BUFFER_MAX_LEN);
#if (__HB_MODE_ENABLE_FIFO__)
            HBD_FifoConfig(0, HBD_FUNCTIONAL_STATE_DISABLE);
#endif
#if (__APP_MODE_CONFIG__ == __APP_MODE_HRV_DET__)
            HBD_HrvDetectStart();
#endif
#if (__HB_MODE_ENABLE_FIFO__)
            HBD_FifoConfig(0, HBD_FUNCTIONAL_STATE_ENABLE);
#endif
        }
        else if (eCommCmdType == COMM_CMD_ADT_SINGLE_MODE_START)
        {
            gsensor_drv_enter_normal_mode();
            gsensor_drv_clear_buffer(gsensor_soft_fifo_buffer, &gsensor_soft_fifo_buffer_index, GSENSOR_SOFT_FIFO_BUFFER_MAX_LEN);
            HBD_AdtWearDetectStart_with_initcheck();
			 app_timer_start(m_gh30x_AdtDetect_check_timer_id, GH30X_CHECK_ADT_DETECT_TIMER_TICK, NULL);
			
            gh301_adt_working_flag = 1;
        }
        else //stop
        {
            gsensor_drv_enter_normal_mode();
#if (__HB_MODE_ENABLE_FIFO__)
            gsensor_drv_clear_buffer(gsensor_soft_fifo_buffer, &gsensor_soft_fifo_buffer_index, GSENSOR_SOFT_FIFO_BUFFER_MAX_LEN);
#endif
            HBD_Stop();
            gh301_adt_working_flag = 0;
        }
        gh30x_status = eCommCmdType;
    }
}
void ble_module_gdcs_rx_parse(uint8_t *rx_data, uint16_t rx_length)
{
    memcpy((char *)nus_rx_data, (char *)rx_data, rx_length);
    nus_rx_len = rx_length;
    app_sched_event_put(NULL, 0, app_parse);   
}  

#endif


/********END OF FILE********* (C) COPYRIGHT 2018 .********/