#pragma once

#include <cstdint>

namespace Watch {
  class HeartRateTask;
  namespace Controllers {
    class HeartRateController {
      public:
        enum class States { NotEnoughData, NoTouch, Running};
        explicit HeartRateController(Watch::HeartRateTask& heartRateTask);

        void Start();
        void Stop();
        void Update(States newState, uint8_t heartRate);

        States State() const { return state; }
        uint8_t HeartRate() { return heartRate; }

      private:
        Watch::HeartRateTask& heartRateTask;
        States state = States::NotEnoughData;
        uint8_t heartRate = 0;
    };
  }
}