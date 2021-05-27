#pragma once

#include <cstdint>

namespace Watch {
  class MotionTask;
  namespace Controllers {
    class MotionControllerTask {
      public:
        enum class States { NotEnoughData, NoTouch, Running};
        explicit MotionControllerTask(Watch::MotionTask& motionTask);

        void Start();
        void Stop();
        States State() const { return state; }
        void Update(States newState, uint16_t accx, uint16_t accy, uint16_t accz, uint32_t nbSteps);

        uint16_t AccX() const { return accx; }
        uint16_t AccY() const { return accy; }
        uint16_t AccZ() const { return accz; }
        uint32_t NbSteps() { return nbSteps; }   
 

      private:
        Watch::MotionTask& motionTask;
        States state = States::NotEnoughData;
        uint32_t nbSteps;
        uint16_t accx;
        uint16_t accy;
        uint16_t accz;
    };
  }
}