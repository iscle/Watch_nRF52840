#include <nrfx_log.h>
#include <nrf_delay.h>
#include "Kx022.h"
#include "TwiMaster.h"
#include <math.h>
#include <algorithm>
#include "drivers/Gh301/gh30x.h"

using namespace Watch::Drivers;

Kx022::Kx022(TwiMaster& twiMaster, uint8_t twiAddress) : twiMaster{twiMaster}, twiAddress{twiAddress} {}

void Kx022::Read(uint8_t registerAddress, uint8_t *buffer, size_t size) {
  twiMaster.Read(twiAddress, registerAddress, buffer, size);
}

void Kx022::Write(uint8_t registerAddress, const uint8_t *data, size_t size) {
  twiMaster.Write(twiAddress, registerAddress, data, size);
}


void Kx022::PowerUp()
{
	uint8_t data = 0;
	Read(KX022_CNTL1,&data,1);
	data = data |0x80;
    Write(KX022_CNTL1,&data,1);
}

void Kx022::PowerDown()
{ 	uint8_t data = 0;
	Read(KX022_CNTL1,&data,1);
	data = data & 0x7f;
    Write(KX022_CNTL1,&data,1);
}


void Kx022::Init() {
   //Original Sensor Platform Tool
	Write(KX022_CNTL1, &KX022_CNTL1_CFGDAT, 1);	
	Write(KX022_TILT_TIMER, &KX022_TILT_TIMER_CFGDAT, 1);	
	Write(KX022_ODCNTL,&KX022_ODCNTL_CFGDAT, 1);
	Write(KX022_CNTL3, &KX022_CNTL3_CFGDAT, 1);
	//Write(KX022_INC1,&KX022_INC1_CFGDAT, 1);
	Write(KX022_INC2,&KX022_INC2_CFGDAT, 1);
	//Write(KX022_INC4, &KX022_INC4_CFGDAT, 1);
	Write(KX022_WUFC, &KX022_WUFC_CFGDAT, 1);
	Write( KX022_ATH, &KX022_ATH_CFGDAT, 1);	
	// Set accelerometer to operating mode (PC1=1)
	RawSensor._uchar = (unsigned char)(KX022_CNTL1_CFGDAT|0x80);
	Write( KX022_CNTL1, &RawSensor._uchar, 1);	
	
}

float Kx022::Process() {

	
	// Calculate acceleration
//	Read(KX022_XOUTL,RawSensor._ucharArr, 2);
//	x =RawSensor._intArr[0];	// X	
//	Read(KX022_YOUTL,RawSensor._ucharArr, 2);
//	y =RawSensor._intArr[0];	// Y
//	Read(KX022_ZOUTL,RawSensor._ucharArr, 2);
//	z =RawSensor._intArr[0];	// z

	// Start read tilt position with start address is TSCP
/*	Read(KX022_TSCP,RawSensor._ucharArr, 2);
	switch(RawSensor._ucharArr[0])
	{
		case 0x01u:	  break;	// FU: Face-Up State (Z+). 
		case 0x02u:	  break;	// FD: Face-Down State (Z-). 
		case 0x04u:	  break;	// UP: Up State (Y+). 
		case 0x08u:	  break;	// DO: Down State (Y-). 
		case 0x10u:	  break;	// RI: Right State (X+). 
		case 0x20u:	  break;	// LE: Left State (X-).
		default:	  break;	// NONE
	}
	*/
//x = (x+4096.0f)/8192.0f;
//y = (y+4096.0f)/8192.0f;
//z = (z+4096.0f)/8192.0f;


//if(data.x >9) data.x =8;
//if(data.y >9) data.y =8;
//if(data.z >9) data.z =8;
//if(data.x <-8) data.x =-8;
//if(data.y <-8) data.y =-8;
////if(data.z >-8) data.z =-8;
//data.x =data.x;// +abs(data.y) + abs(data.z);
//data.x =data.y;
//float value =sqrt(x*x+y*y+z*z)/3;
// std::max(std::abs(x), std::max(std::abs(y), std::abs(z)));
//float valuex=(x+4096.0f)/8192.0f*16.0f-8.0f ; 
//float valuey=(y+4096.0f)/8192.0f*16.0f-8.0f ;
//float valuez=(z+4096.0f)/8192.0f*16.0f-8.0f ;
float valuex =x/4096.0f;
float valuey =y/4096.0f;
float valuez =z/4096.0f;
//xyz[0]=x;
//xyz[1]=y;
//xyz[2]=z;

//return  sqrt(valuex*valuex+valuey*valuey+valuez*valuez)/3.0f;
return   std::max(std::abs(valuex), std::max(std::abs(valuey), std::abs(valuez)));                                                                                                                                                                                                                                                                                                                                                                                    
}



