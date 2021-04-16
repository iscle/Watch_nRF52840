/*lint ++flb "Enter library region" */
#ifdef __cplusplus
 extern "C" {
#endif 

#include "vcHr02Hci.h"
#include "stdint.h"
#include "string.h"
#include "nrf_delay.h"
#include "nrf_gpio.h"
#include "nrf_drv_gpiote.h"
#include "app_scheduler.h"

#include "gh30x_twi_master.h"
#include "nrf_log.h"
#include "app_timer.h"
#include  "drivers/Gh301/hbd_ctrl.h"

void HeartInt();
void SpO2Int();
void vcHr02PhyInit(void);
void vcHr02Init(vcHr02_t *pVcHr02,vcHr02Mode_t vcHr02WorkMode);
void vcHr02_process(AlgoSportMode_t vcSportMode);
void hal_gh30x_int_init(void);
void process();
void Stopprocess();
void HeartSpO2Int();
#ifdef __cplusplus
}
#endif
