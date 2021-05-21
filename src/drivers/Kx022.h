#pragma once

namespace Watch {
  namespace Drivers {
    class TwiMaster;
    class Kx022 {
      public:
        struct Values {
         int16_t steps;
          float x;
          float y;
          float z;
        };

      union {
      unsigned char	_uchar;
      unsigned char	_ucharArr[6];
      unsigned int	_uint;
      unsigned int	_uintArr[3];
      int				_intArr[3];
      float			_float;
      } RawSensor;

        Kx022(TwiMaster& twiMaster, uint8_t twiAddress);
        Kx022(const Kx022&) = delete;
        Kx022& operator=(const Kx022&) = delete;
        Kx022(Kx022&&) = delete;
        Kx022& operator=(Kx022&&) = delete;       
        void Init();
        float Process();  
        void PowerUp();
        void PowerDown();   
       
       private:       
        void Read(uint8_t registerAddress, uint8_t *buffer, size_t size);
        void Write(uint8_t registerAddress, const uint8_t *data, size_t size);
        TwiMaster& twiMaster;
        // ID of KX022
        uint8_t KX022_WAI_VAL    = 0x14;
        // I2C device address of KX022
        uint8_t twiAddress = 0x1eu;    
      
        // Register addresses of KX022
      // uint8_t KX022_XHPL		  	= 0x00u;
      // uint8_t KX022_XHPH		  	= 0x01u;
      // uint8_t KX022_YHPL		  	= 0x02u;
      // uint8_t KX022_YHPH		  	= 0x03u;
      // uint8_t KX022_ZHPL		  	= 0x04u;
      // uint8_t KX022_ZHPH			  = 0x05u;
       uint8_t KX022_XOUTL			= 0x06u;
       //uint8_t KX022_XOUTH			= 0x07u;
       uint8_t KX022_YOUTL			= 0x08u;
      // nt8_t KX022_YOUTH			= 0x09u;
       uint8_t KX022_ZOUTL			= 0x0au;
      // nt8_t KX022_ZOUTH			= 0x0bu;
      // uint8_t KX022_COTR		  	= 0x0cu;
       uint8_t KX022_WHO_AM_I		= 0x0fu;
       //uint8_t KX022_TSCP		  	= 0x10u;
      // uint8_t KX022_TSPP		  	= 0x11u;
      // uint8_t KX022_INS1		  	= 0x12u;
      // uint8_t KX022_INS2		  	= 0x13u;
      // uint8_t KX022_INS3		  	= 0x14u;
      // uint8_t KX022_STAT		  	= 0x15u;
       //uint8_t KX022_INT_REL		= 0x17u;
       uint8_t KX022_CNTL1			= 0x18u;
       //uint8_t KX022_CNTL2			= 0x19u;
       uint8_t KX022_CNTL3			= 0x1au;
       uint8_t KX022_ODCNTL	  	= 0x1bu;
      // uint8_t KX022_INC1		  	= 0x1cu;
       uint8_t KX022_INC2		  	= 0x1du;
      // uint8_t KX022_INC3		  	= 0x1eu;
       //uint8_t KX022_INC4		  	= 0x1fu;
      // uint8_t KX022_INC5		  	= 0x20u;
      // uint8_t KX022_INC6		  	= 0x21u;
       uint8_t KX022_TILT_TIMER	= 0x22u;
       uint8_t KX022_WUFC			  = 0x23u;
      // uint8_t KX022_TDTRC			= 0x24u;
      // uint8_t KX022_TDTC		  	= 0x25u;
      // uint8_t KX022_TTH		  	= 0x26u;
      // uint8_t KX022_TTL	  		= 0x27u;
      // uint8_t KX022_FTD		  	= 0x28u;
      // uint8_t KX022_STD	  		= 0x29u;
      // uint8_t KX022_TLT	  		= 0x2au;
      // uint8_t KX022_TWS	  		= 0x2bu;
       uint8_t KX022_ATH	  		= 0x30u;
      // uint8_t KX022_TILT_ANGLE_LL	= 0x32u;
      // uint8_t KX022_TILT_ANGLE_HL	= 0x33u;
      // uint8_t KX022_HYST_SET		= 0x34u;
      // uint8_t KX022_LP_CNTL		= 0x35u;
      // uint8_t KX022_BUF_CNTL1		= 0x3au;
       //uint8_t KX022_BUF_CNTL2		= 0x3bu;
      // uint8_t KX022_BUF_STATUS_1	= 0x3cu;
      // uint8_t KX022_BUF_STATUS_2	= 0x3du;
       //uint8_t KX022_BUF_CLEAR		= 0x3eu;
      // uint8_t KX022_BUF_READ		  = 0x3fu;
      // uint8_t KX022_SELF_TEST		= 0x60u;
        // Configuration data
        // Set accelerometer to stand-by mode(PC1=0), +/-8g - 16bits and enable tilt position function
        uint8_t KX022_CNTL1_CFGDAT		= 0x12u;
        // Set Output Data Rate(ODR) to 100Hz
        uint8_t KX022_ODCNTL_CFGDAT		= 0x03u;
        // Set Tilt Output Data Rate to 50Hz
        uint8_t KX022_CNTL3_CFGDAT		= 0x05u;
        // Set Tilt Timer to 20ms
        uint8_t KX022_TILT_TIMER_CFGDAT	= 0x01u;
        uint8_t KX022_INC1_CFGDAT 		= 0x28u;	//continue checking here....
        uint8_t KX022_INC2_CFGDAT		= 0x3fu;
        uint8_t KX022_INC4_CFGDAT		= 0x02u;
        uint8_t KX022_WUFC_CFGDAT		= 0x0Au;
        uint8_t KX022_ATH_CFGDAT		 = 0x01u;
        int16_t x=0.0f;
        int16_t y=0.0f;
        int16_t z=0.0f;
        uint8_t buf;
    };
  }
}