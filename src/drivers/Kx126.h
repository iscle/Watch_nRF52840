#pragma once
#include <cstddef>
#include <cstdint>

namespace Watch {
  namespace Drivers {
   class Spi;
    class Kx126 {
      public:
        struct Values {
                 int8_t acc;
                 int8_t x;
                 int8_t y;
                 int8_t z;
        };

      union {
      unsigned char	_uchar;
      unsigned char	_ucharArr[6];
      unsigned int	_uint;
      unsigned int	_uintArr[3];
      int				_intArr[3];
      float			_float;
      } RawSensor;

      explicit Kx126(Spi& spi);
      Kx126(const Kx126&) = delete;
      Kx126& operator=(const Kx126&) = delete;
      Kx126(Kx126&&) = delete;
      Kx126& operator=(Kx126&&) = delete;

      void Init();
      float Process();  
      Values ProcessTest() ;

       private: 

        Spi& spi;

      uint8_t KX126_XOUT_L      =         (0x08+128);
      uint8_t KX126_YOUT_L      =         (0x0A+128);
      uint8_t KX126_ZOUT_L      =         (0x0C+128);
      uint8_t KX126_WHO_AM_I    =         (0x11+128);
      uint8_t KX126_CNTL1       =         (0x1A);
      uint8_t KX126_CNTL2       =         (0x1B);
      uint8_t KX126_CNTL3       =         (0x1C);
      uint8_t KX126_ODCNTL      =         (0x1F);
      uint8_t KX126_TILT_TIMER  =         (0x27);
      uint8_t KX126_INC2		  	=         (0x21);
      uint8_t KX126_WUFC			  =         (0x23);
      uint8_t KX126_ATH	  		  =         (0x30);

      // Set accelerometer to stand-by mode(PC1=0), +/-8g - 16bits and enable tilt position function
      uint8_t KX126_CNTL1_CFGDAT		  =     0x70u;
      // Set Tilt Output Data Rate to 50Hz
      uint8_t KX126_CNTL3_CFGDAT		  =     0x05u;
      uint8_t KX126_BUF_CNTL2         =     0x5b;
      uint8_t KX126_BUF_CNTL2_BUFE    =     0x80;
      uint8_t KX126_BUF_CNTL2_CFGDAT  =     0x01u;
    
        // Set Output Data Rate(ODR) to 100Hz
      uint8_t KX126_ODCNTL_VAL        =   0x03u;
      uint8_t KX126_TILT_TIMER_CFGDAT	=   0x01u;
      uint8_t KX126_INC1_CFGDAT 	  	=   0x28u;	//continue checking here....
      uint8_t KX126_INC2_CFGDAT	    	=   0x3fu;
      uint8_t KX126_INC4_CFGDAT	    	=   0x02u;
      uint8_t KX126_WUFC_CFGDAT	    	=   0x0Au;
      uint8_t KX126_ATH_CFGDAT	      =   0x01u;
      int16_t x=0.0f;
      int16_t y=0.0f;
      int16_t z=0.0f;
      int16_t x1=0.0f;
      int16_t y1=0.0f;
      int16_t z1=0.0f;
    };
  }
}