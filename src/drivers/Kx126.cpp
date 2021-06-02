#include "Kx126.h"
#include <hal/nrf_gpio.h>
#include <libraries/delay/nrf_delay.h>
#include <libraries/log/nrf_log.h>
#include "Spi.h"
#include <math.h>
#include <algorithm>
#include "SEGGER_RTT.h" 
using namespace Watch::Drivers;

Kx126::Kx126(Spi& spi) : spi{spi} {
}

void Kx126::Init() {
 spi.WriteCmdAndBuffer(&KX126_CNTL1, 1,&KX126_CNTL1_CFGDAT, 1);
  // spi.WriteCmdAndBuffer(&KX126_TILT_TIMER, 1,&KX126_TILT_TIMER_CFGDAT, 1);	
  // spi.WriteCmdAndBuffer(&KX126_ODCNTL,1, &KX126_ODCNTL_VAL, 1);
  // spi.WriteCmdAndBuffer(&KX126_CNTL3,1, & KX126_CNTL3_CFGDAT, 1);
	// spi.WriteCmdAndBuffer(&KX126_INC2,1,&KX126_INC2_CFGDAT, 1);
	spi.WriteCmdAndBuffer(&KX126_WUFC,1, &KX126_WUFC_CFGDAT, 1);
  //spi.WriteCmdAndBuffer(&KX126_ATH,1, &KX126_ATH_CFGDAT, 1);  
  spi.WriteCmdAndBuffer(&KX126_BUF_CNTL2,1, &KX126_BUF_CNTL2_CFGDAT, 1);  
	// Set accelerometer to operating mode (PC1=1)
	RawSensor._uchar = (unsigned char)(KX126_CNTL1_CFGDAT|0x80);
	spi.WriteCmdAndBuffer(&KX126_CNTL1,1, &RawSensor._uchar, 1);	  
}

float Kx126::Process() {
    spi.Read(&KX126_XOUT_L, 1, RawSensor._ucharArr, 2);
    x =RawSensor._intArr[0];
    spi.Read(&KX126_YOUT_L, 1, RawSensor._ucharArr, 2);
    y =RawSensor._intArr[0];
    spi.Read(&KX126_ZOUT_L, 1, RawSensor._ucharArr, 2);
    z =RawSensor._intArr[0];

    float valuex =x/4096.0f;
    float valuey =y/4096.0f;
    float valuez =z/4096.0f;
   return  std::max(std::abs(valuex), std::max(std::abs(valuey), std::abs(valuez)));   
 // return 0;                                                                                                                                                                                                                                                                                                                                                                          
}


/*
Kx126::Values Kx126::ProcessTest() {

    spi.Read(&KX126_XOUT_L, 1, RawSensor._ucharArr, 2);
    x1 =RawSensor._intArr[0];
    spi.Read(&KX126_YOUT_L, 1, RawSensor._ucharArr, 2);
    y1 =RawSensor._intArr[0];
    spi.Read(&KX126_ZOUT_L, 1, RawSensor._ucharArr, 2);
    z1 =RawSensor._intArr[0];

	int8_t valuex =x1*10.0f/4096.0f;
	int8_t valuey =y1*10.0f/4096.0f;
	int8_t valuez =z1*10.0f/4096.0f;
//return  sqrt(valuex*valuex+valuey*valuey+valuez*valuez)/3.0f;
return   {1, valuex, valuey, valuez};                                                                                                                                                                                                                                                                                                                                                                                    
}
*/

