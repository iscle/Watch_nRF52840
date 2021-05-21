#pragma once
#include <cstdint>
#include <drivers/include/nrfx_saadc.h>
#include "nrf_drv_pwm.h"
#include <array>
#include <numeric>
#include "components/motor/MotorController.h"
#include <lvgl/lvgl.h>
namespace Watch {
  namespace Controllers {
    
    class Battery {
      public:
        Battery();
        void Init();
        void Update();
        float PercentRemaining() const { return percentRemaining;}
        bool IsCharging() { return isCharging; }
        bool IsPowerPresent() { return isPowerPresent; }
       
        void setButtonData( uint8_t data);
        void setButtonDataNoVibrate( uint8_t data);
        void setIsVibrate(void);
        void setIsTouch( bool data);
        void setisTimer1Done( bool data);
        void setisTimer2Done( bool data);
        void setAccData( float data);       
        void setimpactyy(uint8_t data);
        void setfallyy(uint8_t data);
        void setisTimer1Display(bool data);
        void setisTimer2Display(bool data);
        void setGoToSleep(bool data);
        bool CheckCharging();
        void setIsAlert(uint8_t data);    
        void setCurrentHour(uint8_t data) ;
        void setCurrentMinute(uint8_t data);
        void setCurrentSecond(uint8_t data);
        void setIsheartbeat(bool data);
        void setIstracking(bool data);
        void setIslowbattery(bool data);
        void setcheckVibrate(bool data);
        void setisButtonPushed(bool data);
        void setDisturnOff(bool data);
        void setTouch( uint8_t x, uint8_t y);
        void setTimeOff(uint32_t data);

        uint8_t getCurrentHour(){return currentHour;} ;
        uint8_t getCurrentMinute(){return currentMinute;};  
        uint8_t getCurrentSecond(){return currentSecond;};     
        float getimpactzz(){return (impactzz&0x0f)*0.1+((impactzz&0xf0)>>4);};
        uint8_t getimpactyy() { return impactyy; };
        uint8_t getcheckinzz() {return checkinzz;};
        uint8_t getcheckinyy() {return checkinyy;};
        float getfallHighpeak() {return (fallHighpeak&0x0f)*0.1+((fallHighpeak&0xf0)>>4);};
        float getfallLowpeak() {return (fallLowpeak&0x0f)*0.1+((fallLowpeak&0xf0)>>4);};
        uint8_t getfalltime() {return (falltime&0x0f)+((falltime&0xf0)>>4)*10;};
        uint8_t getCheckinTime1() {return (CheckinTime1&0x0f)+((CheckinTime1&0xf0)>>4)*10;};
        uint8_t getCheckinTime2() {return (CheckinTime2&0x0f)+((CheckinTime2&0xf0)>>4)*10;};
        uint8_t getButtonData() { return buttonData;}
        bool getisButtonPushed(){ return isButtonPushed;};
        bool getIsTouch() { return isTouch;};
        bool isTimerStart1() { return isTimer1Start; };
        bool isTimerStart2() { return isTimer2Start; };
        bool isTimerDone1() { return isTimer1Done; };
        bool isTimerDone2() { return isTimer2Done; };
        bool getisTimer1Display() { return isTimer1Display;};
        bool getisTimer2Display() { return isTimer2Display;};
        bool getGoToSleep() { return GoToSleep;};
        uint8_t getIsAlert() { return isAlert;};
        bool Istracking() { return istracking;};
        bool Isheartbeat() { return isheartbeat;};
        bool getcheckVibrate() {return checkVibrate;}
        uint8_t getfallyy() {return fallyy;};
        float getAccData(){return AccData;};
        void impactCharacteristic(uint8_t yy, uint8_t zz);
        void checkinCharacteristic(uint8_t yy, uint8_t zz);
        void fallCharacteristic(uint8_t yy, uint8_t zz);
        void trackCharacteristic(uint8_t zz, uint8_t yy,uint8_t nn);
        uint8_t gettouchx() {return touchx;};
        uint8_t gettouchy() {return touchy;};
        uint8_t gettimetracking(){return timetracking;}
        uint8_t getnumtracking(){return numtracking;}
        uint8_t gettimeheartbeat(){return timeheartbeat;}
        bool getIslowbattery(){return islowbattery;}
        bool getDisturnOff(){return isDisturnOff;}
        void StopVibrate(void);
        void setxyz( int8_t _x,int8_t _y,int8_t _z);
        void setXmax(int8_t x);
        void setYmax(int8_t y);
        void setZmax(int8_t z);
        int8_t getx() { return x;};
        int8_t gety() { return y;};
        int8_t getz() { return z;};
        int8_t getxmax() { return xmax;};
        int8_t getymax() { return ymax;};
        int8_t getzmax() { return zmax;};



      private:
        static Battery *instance;
        nrf_saadc_value_t  saadc_value;
        uint8_t chargingPin = 19;
        uint8_t powerPresentPin = 20;
        static constexpr nrf_saadc_input_t batteryVoltageAdcInput = NRF_SAADC_INPUT_AIN4;
        void SaadcInit();

        void SaadcEventHandler(nrfx_saadc_evt_t const * p_event);
        static void adcCallbackStatic(nrfx_saadc_evt_t const *event);
        static constexpr uint8_t percentRemainingSamples = 5;
        bool isReading = false;
        uint8_t samples = 0;
        float percentRemaining = 0.0f;
        float voltage = 0.0f;
        bool isCharging = false;
        bool isPowerPresent = false;
        bool isTouch = true;
        bool isVibrate = false;
        uint8_t buttonData = 0x02;
        uint8_t impactzz =0x25;
        uint8_t impactyy=0x02;
        uint8_t checkinzz=0x00;
        uint8_t checkinyy=0x00;
        uint8_t fallHighpeak=0x35;
        uint8_t fallLowpeak=0x25;
        uint8_t falltime=0x03;
        uint8_t fallyy=0x02;
        uint8_t CheckinTime1 =0x00;
        uint8_t CheckinTime2 =0x00;
        bool isTimer1Start = false;
        bool isTimer2Start = false;
        bool isTimer1Done = false;
        bool isTimer2Done = false;
        bool isTimer1Display = false;
        bool isTimer2Display = false;
        bool GoToSleep= true;
        uint8_t isAlert =0x00;        
        float AccData=0.0f;
        uint8_t currentHour = 0;
        uint8_t currentMinute = 0;
        uint8_t currentSecond = 0;
        uint32_t count =0, sum=0;
        uint8_t touchx=0,touchy=0;
        bool istracking = false;
        bool isheartbeat = false;
        uint8_t numtracking =0x00;
        uint8_t timetracking =0x00;
        uint8_t timeheartbeat =0x00;
        bool islowbattery = false;
        bool checkVibrate= true;
        bool isButtonPushed = false;
        bool isDisturnOff = false; 
        int8_t x =0;
        int8_t y=0;
        int8_t z=0;
        int8_t xmax =0;
        int8_t ymax=0;
        int8_t zmax=0;
       
    };
  }
}