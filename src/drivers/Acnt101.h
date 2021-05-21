#pragma once

#include <cstdint>
#include <drivers/Acnt101.h>


namespace Watch {
  namespace Drivers {
    //static constexpr uint8_t pinTempOut = 35;
    //static constexpr uint8_t pinTempIn = 34;

    class Acnt101 {
      public:
        void Init();
        void setIsCount( bool data) ;
        bool getIsCount() { return is_lock_counting;}
        void timer_temp_start();
        void timer_temp_stop();
        void start();
        void stop();
        float Update() {return  dataTemp;}
        void ReadData(uint32_t data);

      private:
      float dataTemp=0; //is_lock_counting in the first rising edge
      bool is_lock_counting=0; //It has been set high when it is off, and the subsequent pulse interrupts in this cycle will enter the else branch.
      uint32_t sumtemp =0;
      uint8_t count=0;
   

    };
  }
}