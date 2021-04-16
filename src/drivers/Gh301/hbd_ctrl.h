/*
*File Name: hbd_ctrl.h
************************************************************************
*
* Copyright 2018 All rights reserved. Goodix Inc.
*
* Description: GH30x sensor control library header.
* Note:	
* Identifier abbreviation:  Wnd - Window
*                           Msg - Message
* MODIFICATION HISTORY
* Date            Name            Version      
* ============    ==========      ========     
* 2019-03-22      Chris-Chan      0.3.2        
**********************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

#ifndef __HBD_CTRL_H__
#define __HBD_CTRL_H__

typedef unsigned char GU8;
typedef signed char GS8;
typedef unsigned short GU16;
typedef signed short GS16;
typedef long int GS32;
typedef unsigned long int GU32;
typedef float GF32;

extern uint8_t  heartrate;
extern  int16_t xyz[3];
extern  int HeartRateValue;
extern int real_spo;
extern bool vcHr02IRQFlag ;
extern bool checktemp ;
extern bool checktemp1;
/* Hbd functiional state enum. */
typedef enum 
{
    HBD_FUNCTIONAL_STATE_DISABLE = 0, 
    HBD_FUNCTIONAL_STATE_ENABLE = 1,
} EM_HBD_FUNCTIONAL_STATE;

/* Int status enum. */
enum EM_INT_STATUS
{
    INT_STATUS_CHIP_RESET = 0,
    INT_STATUS_NEW_DATA,
    INT_STATUS_FIFO_WATERMARK,
    INT_STATUS_FIFO_FULL,
    INT_STATUS_WEAR_DETECTED,
    INT_STATUS_UNWEAR_DETECTED,
    INT_STATUS_INVALID,
} ;

/* I2c Low Two bit select enum. */
enum EM_HBD_I2C_ID_SEL
{
    HBD_I2C_ID_SEL_1L0L = 0,
    HBD_I2C_ID_SEL_1L0H,
    HBD_I2C_ID_SEL_1H0L,
    HBD_I2C_ID_SEL_1H0H,
    HBD_I2C_ID_INVALID,
};

/* Led pd select enum. */
typedef enum 
{
    HBD_LED_PD_SEL_INTERNAL = 0,
    HBD_LED_PD_SEL_EXTERNAL,
} EM_HBD_LED_PD_SEL;

/* Led logic channel map to hw led enum. */
typedef enum
{
    HBD_LED_LOGIC_CHANNEL_MAP_PHY012 = 0,
    HBD_LED_LOGIC_CHANNEL_MAP_PHY021,
    HBD_LED_LOGIC_CHANNEL_MAP_PHY102,
    HBD_LED_LOGIC_CHANNEL_MAP_PHY120,
    HBD_LED_LOGIC_CHANNEL_MAP_PHY201,
    HBD_LED_LOGIC_CHANNEL_MAP_PHY210,
} EM_HBD_LED_LOGIC_CHANNEL_MAP;

/* sample time enum. */
typedef enum 
{
    HBD_SAMPLE_TIME_32CYCLES = 0,
    HBD_SAMPLE_TIME_64CYCLES,
    HBD_SAMPLE_TIME_128CYCLES,
    HBD_SAMPLE_TIME_256CYCLES,
    HBD_SAMPLE_TIME_512CYCLES,
    HBD_SAMPLE_TIME_1024CYCLES,
    HBD_SAMPLE_TIME_2048CYCLES,
} EM_HBD_SAMPLE_TIME;

/* tia gain enum. */
typedef enum
{
    HBD_TIA_GAIN_0 = 0,
    HBD_TIA_GAIN_1,
    HBD_TIA_GAIN_2,
    HBD_TIA_GAIN_3,
    HBD_TIA_GAIN_4,
    HBD_TIA_GAIN_5,
    HBD_TIA_GAIN_6,
    HBD_TIA_GAIN_7,
} EM_HBD_TIA_GAIN;

/* G-sensor sensitivity(counts/g) enum. */
typedef enum
{
    HBD_GSENSOR_SENSITIVITY_512_COUNTS_PER_G = 0, 
    HBD_GSENSOR_SENSITIVITY_1024_COUNTS_PER_G,    
    HBD_GSENSOR_SENSITIVITY_2048_COUNTS_PER_G,
    HBD_GSENSOR_SENSITIVITY_4096_COUNTS_PER_G,
    HBD_GSENSOR_SENSITIVITY_8192_COUNTS_PER_G,
} EM_HBD_GSENSOR_SENSITIVITY;

/* Hb config struct type. */
typedef struct
{
    EM_HBD_FUNCTIONAL_STATE emHbModeFifoEnable;     // HB fifo enable flag
    EM_HBD_FUNCTIONAL_STATE emHrvModeFifoEnable;    // HRV fifo enable flag
    EM_HBD_FUNCTIONAL_STATE emHsmModeFifoEnable;     // HB fifo enable flag
    EM_HBD_FUNCTIONAL_STATE emBpdModeFifoEnable;     // HB fifo enable flag
    EM_HBD_FUNCTIONAL_STATE emPfaModeFifoEnable;     // HB fifo enable flag
} ST_HB_CONFIG_TYPE;

/* Adt config struct type. Notes: only logic channel0 & channel1 valid in adt mode. */
typedef struct
{
    EM_HBD_FUNCTIONAL_STATE emGINTEnable;                  // GINT enable flag
    EM_HBD_LED_LOGIC_CHANNEL_MAP emLedLogicChannelMap;     // Logic map
    EM_HBD_LED_PD_SEL emLogicChannel0PDSelect;             // Logic Channel0 PD select
    EM_HBD_LED_PD_SEL emLogicChannel1PDSelect;             // Logic Channel1 PD select
    GU8 uchLogicChannel0Current;                           // Logic Channel0 current cofig(1 step = 400uA)
    GU8 uchLogicChannel1Current;                           // Logic Channel1 current cofig(1 step = 400uA)
    EM_HBD_TIA_GAIN emLogicChannel0TiaGain;                // Logic Channel0 tia gain(valid value:0-7)
    EM_HBD_TIA_GAIN emLogicChannel1TiaGain;                // Logic Channel1 tia gain(valid value:0-7)
    EM_HBD_SAMPLE_TIME emSampleTime;                       // Sample time
} ST_ADT_CONFIG_TYPE;

/* Hbd init config struct type. */
typedef struct
{
    ST_HB_CONFIG_TYPE stHbInitConfig;
    ST_ADT_CONFIG_TYPE stAdtInitConfig;
} ST_HBD_INIT_CONFIG_TYPE;

/* Gsensor data struct type. */
typedef struct
{
    GS16 sXAxisVal; // X-Axis Value
    GS16 sYAxisVal; // Y-Axis Value
    GS16 sZAxisVal; // Z-Axis Value
} ST_GS_DATA_TYPE;

 
/* Hbd function return code definitions list. */
#define HBD_RET_OK                          (0)                /**< There is no error */
#define HBD_RET_GENERIC_ERROR               (-1)               /**< A generic error happens */
#define HBD_RET_PARAMETER_ERROR             (-2)               /**< Parameter error */
#define HBD_RET_COMM_NOT_REGISTERED_ERROR   (-3)               /**< I2c/Spi communication interface not registered error */
#define HBD_RET_COMM_ERROR                  (-4)               /**< I2c/Spi Communication error */
#define HBD_RET_RESOURCE_ERROR              (-5)               /**< Resource full or not available error */
#define HBD_RET_NO_INITED_ERROR             (-6)               /**< No inited error */
#define HBD_RET_LED_CONFIG_ALL_OFF_ERROR    (-7)               /**< Led config all off error */

/******* hbd init default config ****************
 * stHbInitConfig = { HBD_FUNCTIONAL_STATE_ENABLE,          /// hb mode fifo enable 
 *                    HBD_FUNCTIONAL_STATE_ENABLE           /// hrv mode fifo enable 
 *                    HBD_FUNCTIONAL_STATE_ENABLE           /// hsm mode fifo enable 
 *                    HBD_FUNCTIONAL_STATE_ENABLE           /// bpd mode fifo enable 
 *                    HBD_FUNCTIONAL_STATE_ENABLE           /// pfa mode fifo enable 
 *                  }                         
 * stAdtInitConfig = { HBD_FUNCTIONAL_STATE_DISABLE,        /// GINT disable
 *                     HBD_LED_LOGIC_CHANNEL_MAP_PHY012,    /// Logic map
 *                     HBD_LED_PD_SEL_INTERNAL,             /// Logic Channel0 PD select
 *                     HBD_LED_PD_SEL_INTERNAL,             /// Logic Channel1 PD select
 *                     0x19,                                /// Logic Channel0 current 10mA (1 step = 400uA)
 *                     0x19,                                /// Logic Channel1 current 10mA (1 step = 400uA)
 *                     HBD_TIA_GAIN_3,                      /// Logic Channel0 tia gain
 *                     HBD_TIA_GAIN_3,                      /// Logic Channel1 tia gain
 *                     HBD_SAMPLE_TIME_128CYCLES,           /// sample time
 *                   }
 */
#define HBD_INIT_CONFIG_DEFAULT_DEF(var) ST_HBD_INIT_CONFIG_TYPE var={\
                                                                      {HBD_FUNCTIONAL_STATE_ENABLE,\
                                                                      HBD_FUNCTIONAL_STATE_ENABLE,\
                                                                      HBD_FUNCTIONAL_STATE_ENABLE,\
                                                                      HBD_FUNCTIONAL_STATE_ENABLE,\
                                                                      HBD_FUNCTIONAL_STATE_ENABLE},\
                                                                      {HBD_FUNCTIONAL_STATE_DISABLE,\
                                                                      HBD_LED_LOGIC_CHANNEL_MAP_PHY012, \
                                                                      HBD_LED_PD_SEL_INTERNAL, \
                                                                      HBD_LED_PD_SEL_INTERNAL,\
                                                                      0x19, 0x19, HBD_TIA_GAIN_3, HBD_TIA_GAIN_3, HBD_SAMPLE_TIME_128CYCLES}\
                                                                    }


/****************************************************************
* Description: set i2c operation function
* Input:  uchI2cIdLowTwoBitsSelect: i2c low two bits addr selected, see EM_HBD_I2C_ID_SEL
          pI2cWriteFunc: i2c write function pointer
          pI2cReadFunc: i2c read function pointer
* Return: HBD_RET_PARAMETER_ERROR: function pointer parameter set null error,
          HBD_RET_OK: register success
******************************************************************/
GS8 HBD_SetI2cRW (GU8 uchI2cIdLowTwoBitsSelect,
                   GU8 (*pI2cWriteFunc)(GU8 uchDeviceId, const GU8 uchWriteBytesArr[], GU16 usWriteLen),  
                   GU8 (*pI2cReadFunc)(GU8 uchDeviceId, const GU8 uchCmddBytesArr[], GU16 usCmddLen, GU8 uchReadBytesArr[], GU16 usMaxReadLen));

/****************************************************************
* Description: load new GH30x config
* Input:    uchNewConfigArr: config array ,
            uchForceUpdateConfig: 1:force update, 0:auto select, 
* Return: HBD_RET_OK:use new config arr, HBD_RET_GENERIC_ERROR:use the storage config arr,
******************************************************************/
GS8 HBD_LoadNewConfig(GU8 uchNewConfigArr[], GU8 uchForceUpdateConfig);

/****************************************************************
* Description: Communication operation interface confirm.
* Output:  None
* Return: HBD_RET_OK=GH30x comunicate ok, 
          HBD_RET_COMM_ERROR=GH30x comunicate error,
          HBD_RET_COMM_NOT_REGISTERED_ERROR=GH30x i2c/spi interface not registered,
******************************************************************/
GS8 HBD_CommunicationInterfaceConfirm (void);

/****************************************************************
* Description: simple init hbd configure parameters
* Input:    stHbInitConfigParam: Init Config struct ,see ST_HBD_INIT_CONFIG_TYPE,
* Return: HBD_RET_OK=success, 
          HBD_RET_PARAMETER_ERROR=paramters error,
          HBD_RET_COMM_ERROR=GH30x comunicate error, 
          HBD_RET_COMM_NOT_REGISTERED_ERROR=GH30x i2c interface not registered
******************************************************************/
GS8 HBD_SimpleInit (ST_HBD_INIT_CONFIG_TYPE *stHbdInitConfigParam);

/****************************************************************
* Description: start hbd
* Input:  None
* Return: HBD_RET_OK=success, 
          HBD_RET_NO_INITED_ERROR=not inited,
******************************************************************/
GS8 HBD_HbDetectStart (void);

/****************************************************************
* Description: restart hbd if read done stop, must use with HBD_HbCalculateByOneFifoInt_Ex
* Input:  none, 
* Return: HBD_RET_OK=success, 
          HBD_RET_NO_INITED_ERROR=not inited,
******************************************************************/
GS8 HBD_HbRestart_Ex (void);

/****************************************************************
* Description: start Wear state confirm.
* Input:  None, 
* Return: HBD_RET_OK=success, 
          HBD_RET_NO_INITED_ERROR=not inited,
          HBD_RET_LED_CONFIG_ALL_OFF_ERROR=all Led disable error,
          HBD_RET_GENERIC_ERROR=don't need check wear state, 
******************************************************************/
GS8 HBD_WearStateConfirmStart (void);

/****************************************************************
* Description: start in-ear ep wear detect, only use with hb detect
* Input:  None, 
* Return: HBD_RET_OK=success, 
          HBD_RET_NO_INITED_ERROR=not inited,
          HBD_RET_LED_CONFIG_ALL_OFF_ERROR=all Led disable error,
          HBD_RET_GENERIC_ERROR=wear detect function is disabled.
******************************************************************/
GS8 HBD_InearEpWearDetectStart (void);

/****************************************************************
* Description: start hrv
* Input:  None
* Return: HBD_RET_OK=success, 
          HBD_RET_NO_INITED_ERROR=not inited,
******************************************************************/
GS8 HBD_HrvDetectStart (void);

/****************************************************************
* Description: start sleep monitor
* Input:  None
* Return: HBD_RET_OK=success, 
          HBD_RET_NO_INITED_ERROR=not inited,
******************************************************************/
GS8 HBD_HsmDetectStart (void);

/****************************************************************
* Description: start blood pressure detect
* Input:  None
* Return: HBD_RET_OK=success, 
          HBD_RET_LED_CONFIG_ALL_OFF_ERROR=all Led disable error,
          HBD_RET_NO_INITED_ERROR=not inited,
******************************************************************/
GS8 HBD_BpdDetectStart (void);

/****************************************************************
* Description: start pfa detect
* Input:  None
* Return: HBD_RET_OK=success, 
          HBD_RET_LED_CONFIG_ALL_OFF_ERROR=all Led disable error,
          HBD_RET_NO_INITED_ERROR=not inited,
******************************************************************/
GS8 HBD_PfaDetectStart (void);

/****************************************************************
* Description: stop hbd
* Input:  None
* Return: HBD_RET_OK=success, 
          HBD_RET_NO_INITED_ERROR=fail:don't init success 
******************************************************************/
GS8 HBD_Stop (void);

/****************************************************************
* Description: start adt wear detect
* Input:  None
* Return: HBD_RET_OK=success, 
          HBD_RET_NO_INITED_ERROR=fail:don't init success 
******************************************************************/
GS8 HBD_AdtWearDetectStart (void);

/****************************************************************
* Description: get Int status 
* Input:  None
* Return: Status, see EM_INT_STATUS
******************************************************************/
GU8 HBD_GetIntStatus (void);

/****************************************************************
* Description: calculate hbd_value and wearing detect by newdata int.
* Input:  stGsAxisValue: gsensor data
          emGsensorSensitivity: G-sensor sensitivity (counts/g), see EM_HBD_GSENSOR_SENSITIVITY
* Output:   puchHbValue:ptr of heartbeat value output
            puchWearingState:ptr of wearing state output
            puchWearingQuality: ptr of wearing quality output
            puchVoiceBroadcast: ptr of voice broadcast output
            pusRRvalue: ptr of RR value output 
* Return: refresh flag, if heartbeat value have refresh that return 1.
******************************************************************/
GU8 HBD_HbCalculateByNewdataInt(ST_GS_DATA_TYPE *stGsAxisValue, EM_HBD_GSENSOR_SENSITIVITY emGsensorSensitivity, 
                                GU8 *puchHbValue, GU8 *puchWearingState, GU8 *puchWearingQuality, GU8 *puchVoiceBroadcast, GU16 *pusRRvalue);

/****************************************************************
* Description: calculate hbd_value and wearing detect by fifo int.
* Input:  stGsAxisValue: gsensor data buffer
             usGsDataNum: gsensor data count
             emGsensorSensitivity: G-sensor sensitivity (counts/g), see EM_HBD_GSENSOR_SENSITIVITY
* Output:   puchHbValue:ptr of heartbeat value output
            puchWearingState:ptr of wearing state output
            puchWearingQuality: ptr of wearing quality output
            puchVoiceBroadcast: ptr of voice broadcast output
            pusRRvalue: ptr of RR value output 
* Return: refresh flag, if heartbeat value have refresh that return 1.
******************************************************************/
GU8 HBD_HbCalculateByFifoInt(ST_GS_DATA_TYPE stGsAxisValue[], GU16 usGsDataNum, EM_HBD_GSENSOR_SENSITIVITY emGsensorSensitivity, 
                            GU8 *puchHbValue, GU8 *puchWearingState, GU8 *puchWearingQuality, GU8 *puchVoiceBroadcast, GU16 *pusRRvalue);

/****************************************************************
* Description: calculate hbd_value by one fifo int.
* Input:  stGsAxisValue: gsensor data buffer
             usGsDataNum: gsensor data count
             emGsensorSensitivity: G-sensor sensitivity (counts/g), see EM_HBD_GSENSOR_SENSITIVITY
             puchReadingFlag: ptr of reading data flag 
          puchTimeoutFlag: ptr of timer timeout flag
* Output:   puchHbValue:ptr of heartbeat value output
* Return: refresh flag, if heartbeat value have refresh that return 1.
******************************************************************/
GU8 HBD_HbCalculateByOneFifoInt_Ex(ST_GS_DATA_TYPE stGsAxisValue[], GU16 usGsDataNum, EM_HBD_GSENSOR_SENSITIVITY emGsensorSensitivity, 
                                    GU8 *puchReadingFlag, GU8 *puchTimeoutFlag, GU8 *puchHbValue);

/****************************************************************
* Description: calculate hbd_value by one fifo int.
* Input:  stGsAxisValue: gsensor data buffer
             usGsDataNum: gsensor data count
             emGsensorSensitivity: G-sensor sensitivity (counts/g), see EM_HBD_GSENSOR_SENSITIVITY
             puchReadingFlag: ptr of reading data flag 
          puchTimeoutFlag: ptr of timer timeout flag
* Output:   puchHbValue:ptr of heartbeat value output
* Return: refresh flag, if heartbeat value have refresh that return 1.
******************************************************************/
GU8 HBD_HbCalculateByOneFifoInt_Ex2(ST_GS_DATA_TYPE stGsAxisValue[], GU16 usGsDataNum, EM_HBD_GSENSOR_SENSITIVITY emGsensorSensitivity, 
                                    GU8 *puchReadingFlag, GU8 *puchTimeoutFlag, GU8 *puchHbValue);

/****************************************************************
* Description: Wear state confirm.
* Output:   None,
* Return: wear state, 0: during wear state detect;
                      1: state output wear 
                      2: state output unwaer 
******************************************************************/
GU8 HBD_WearStateConfirm (void);

/****************************************************************
* Description: enable wearing and setting direction array
* Input:    fDirectionArr: gsensor direction 
* Return: None
******************************************************************/
void HBD_EnableWearing (GF32 fDirectionArr[3]);

/****************************************************************
* Description: calculate hrv_value by newdata int.
* Input:  stGsAxisValue: gsensor data, if want get algo static state value, could set NULL.
          emGsensorSensitivity: G-sensor sensitivity (counts/g), see EM_HBD_GSENSOR_SENSITIVITY
* Output: pusHrvRRValue:ptr of hrv RR value output
* Return: refresh flag, if hrv RR value have refresh that return 1.
******************************************************************/
GU8 HBD_HrvCalculateByNewdataInt(ST_GS_DATA_TYPE *stGsAxisValue, EM_HBD_GSENSOR_SENSITIVITY emGsensorSensitivity, GU16 *pusHrvRRValue);

/****************************************************************
* Description: calculate hrv_value by fifo int.
* Input:  stGsAxisValue: gsensor data buffer, if want get algo static state value, could set NULL.
          usGsDataNum: gsensor data count, if want get algo static state value, could set less thah 100.
          emGsensorSensitivity: G-sensor sensitivity (counts/g), see EM_HBD_GSENSOR_SENSITIVITY
* Output: pusHrvRRValueArr:ptr of hrv RR value output array
* Return: refresh cnt, all count of RR value have refresh.
******************************************************************/
GU16 HBD_HrvCalculateByFifoInt(ST_GS_DATA_TYPE stGsAxisValue[], GU16 usGsDataNum, EM_HBD_GSENSOR_SENSITIVITY emGsensorSensitivity, GU16 *pusHrvRRValueArr);

/****************************************************************
* Description: calculate sleep state by newdata int.
* Input:  stGsAxisValue: gsensor data, if want get algo static state value, could set NULL.
          emGsensorSensitivity: G-sensor sensitivity (counts/g), see EM_HBD_GSENSOR_SENSITIVITY
* Output: puchSleepState:ptr of sleep state value output, 0:deep sleep, 1:light sleep, 2: REM, 3: sober
          puchHbValue:ptr of hb value output 
          puchRespiratoryRate:ptr of respiratory rate value output 
* Return: refresh flag, if Hsm sleep state value have refresh that return 1.
******************************************************************/
GU8 HBD_HsmCalculateByNewdataInt(ST_GS_DATA_TYPE *stGsAxisValue, EM_HBD_GSENSOR_SENSITIVITY emGsensorSensitivity, 
                                GU8 *puchSleepState, GU8 *puchHbValue, GU8 *puchRespiratoryRate);

/****************************************************************
* Description: calculate sleep state by fifo int.
* Input:  stGsAxisValue: gsensor data buffer, if want get algo static state value, could set NULL.
          usGsDataNum: gsensor data count, if want get algo static state value, could set less thah 25. 
          emGsensorSensitivity: G-sensor sensitivity (counts/g), see EM_HBD_GSENSOR_SENSITIVITY
* Output: puchSleepState:ptr of sleep state value output, 0:deep sleep, 1:light sleep, 2: REM, 3: sober
          puchHbValue:ptr of hb value output 
          puchRespiratoryRate:ptr of respiratory rate value output 
* Return: refresh flag, if Hsm sleep state value have refresh that return 1.
******************************************************************/
GU16 HBD_HsmCalculateByFifoInt(ST_GS_DATA_TYPE stGsAxisValue[], GU16 usGsDataNum, EM_HBD_GSENSOR_SENSITIVITY emGsensorSensitivity, 
                                GU8 *puchSleepState, GU8 *puchHbValue, GU8 *puchRespiratoryRate);

/****************************************************************
* Description: calculate sleep state info by sleep state.
* Input:  pusSleepStateValueArr: sleep state array.
          nSleepStateValueLength: sleep state array length.
* Output: pnSleepStateInfo[0]:sleep start time, x minutes
          pnSleepStateInfo[1]:sleep stop time, x minutes
          pnSleepStateInfo[2]:percent of deep sleep  
          pnSleepStateInfo[3]:percent of light sleep 
          pnSleepStateInfo[4]:percent of REM
          pnSleepStateInfo[5]:percent of sober
          pnSleepStateInfo[6]:score of sleep quality
* Return: None.
******************************************************************/
void HBD_HsmGetSleepStateInfo(GS16 *pusSleepStateValueArr, GS32 nSleepStateValueLength, GS32 *pnSleepStateInfo);

/****************************************************************
* Description: calculate blood pressure by newdata int.
* Input:  stGsAxisValue: gsensor data, if want get algo static state value, could set NULL.
          emGsensorSensitivity: G-sensor sensitivity (counts/g), see EM_HBD_GSENSOR_SENSITIVITY
* Output: pusSbpValue:ptr of spd value output
          pusDbpValue:ptr of dbp value output  
* Return: refresh flag, if blood pressure value have refresh that return 1.
******************************************************************/
GU8 HBD_BpdCalculateByNewdataInt(ST_GS_DATA_TYPE *stGsAxisValue, EM_HBD_GSENSOR_SENSITIVITY emGsensorSensitivity, 
                                  GU16 *pusSbpValue, GU16 *pusDbpValue);

/****************************************************************
* Description: calculate sleep state by fifo int.
* Input:  stGsAxisValue: gsensor data buffer, if want get algo static state value, could set NULL.
          usGsDataNum: gsensor data count, if want get algo static state value, could set less thah 25. 
          emGsensorSensitivity: G-sensor sensitivity (counts/g), see EM_HBD_GSENSOR_SENSITIVITY
* Output: pusSbpValue:ptr of sbp value output
          pusDbpValue:ptr of dbp value output 
* Return: refresh flag, if Hsm sleep state value have refresh that return 1.
******************************************************************/
GU16 HBD_BpdCalculateByFifoInt(ST_GS_DATA_TYPE stGsAxisValue[], GU16 usGsDataNum, EM_HBD_GSENSOR_SENSITIVITY emGsensorSensitivity, 
                                GU16 *pusSbpValue, GU16 *pusDbpValue);

/****************************************************************
* Description: calculate Pfa level by newdata int.
* Input:  stGsAxisValue: gsensor data, if want get algo static state value, could set NULL.
          emGsensorSensitivity: G-sensor sensitivity (counts/g), see EM_HBD_GSENSOR_SENSITIVITY
* Output: puchPressureLevel:ptr of pressure level output
          puchFatigueLevel:ptr of fatigue level output 
          puchBodyAge:ptr of body-age output 
* Return: refresh flag, if pfa value have refresh that return 1.
******************************************************************/
GU8 HBD_PfaCalculateByNewdataInt(ST_GS_DATA_TYPE *stGsAxisValue, EM_HBD_GSENSOR_SENSITIVITY emGsensorSensitivity, 
                                 GU8 *puchPressureLevel, GU8 *puchFatigueLevel, GU8 *puchBodyAge);

/****************************************************************
* Description: calculate sleep state by fifo int.
* Input:  stGsAxisValue: gsensor data buffer, if want get algo static state value, could set NULL.
          usGsDataNum: gsensor data count, if want get algo static state value, could set less thah 25. 
          emGsensorSensitivity: G-sensor sensitivity (counts/g), see EM_HBD_GSENSOR_SENSITIVITY
* Output: puchPressureLevel:ptr of pressure level output
          puchFatigueLevel:ptr of fatigue level output 
          puchBodyAge:ptr of body-age output
* Return: refresh flag, if pfa value have refresh that return 1.
******************************************************************/
GU16 HBD_PfaCalculateByFifoInt(ST_GS_DATA_TYPE stGsAxisValue[], GU16 usGsDataNum, EM_HBD_GSENSOR_SENSITIVITY emGsensorSensitivity, 
                               GU8 *puchPressureLevel, GU8 *puchFatigueLevel, GU8 *puchBodyAge);

/****************************************************************
* Description: get fifo count has read
* Input:  None,  
* Return: fifo count has read, 
******************************************************************/
GU8 HBD_GetFifoCntHasRead (void);

/****************************************************************
* Description: Reset chip
* Input:  None
* Return: HBD_RET_OK=success, 
          HBD_RET_COMM_NOT_REGISTERED_ERROR=GH30x i2c interface not registered
******************************************************************/
GS8 HBD_ChipReset (void);

/****************************************************************
* Description: set irq pluse width 
* Input:  uchIrqPluseWidth: irq width(us) setting ,
                            if set 0: fixed 1us and return HBD_RET_PARAMETER_ERROR
* Return: HBD_RET_OK=success, 
          HBD_RET_PARAMETER_ERROR=fail:parameter error
******************************************************************/
GS8 HBD_SetIrqPluseWidth(GU8 uchIrqPluseWidth);

/****************************************************************
* Description: change Hb config
* Input:  uchMode: 0:Hrv reconfig, else Hb reconfig
*         emFifoEnable: see EM_HBD_FUNCTIONAL_STATE
* Return: HBD_RET_OK=success, 
          HBD_RET_PARAMETER_ERROR=fail:parameter error,
******************************************************************/
GS8 HBD_FifoConfig(GU8 uchMode, EM_HBD_FUNCTIONAL_STATE emFifoEnable);

/****************************************************************
* Description: Get version
* Input:    None,
* Return: library Hbd ctrl version
******************************************************************/
GS8 * HBD_GetHbdVersion (void);

/****************************************************************
* Description: Get hba algorithm version
* Input:    None,
* Return: library hba algorithm version
******************************************************************/
GS8 * HBD_GetHbaVersion (void);

#endif /* __HBD_CTRL_H__ */

/********END OF FILE********* (C) COPYRIGHT 2018 .********/
#ifdef __cplusplus
}
#endif