#pragma once

#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <drivers/Gh301.h>
#include <components/heartrate/HeartRateController.h>

namespace Watch {
  class HeartRateTask {
    public:
      enum class Messages : uint8_t {GoToSleep, WakeUp, StartMeasurement, StopMeasurement };
      enum class States {Idle, Running};

      explicit HeartRateTask(Drivers::Gh301& heartRateSensor);
      void Start();
      void Work();
      void PushMessage(Messages msg);

      Watch::Controllers::HeartRateController& HeartRateController() { return heartRateController; }

    private:
      TaskHandle_t taskHandle;
      QueueHandle_t messageQueue;
      States state = States::Running;
      Drivers::Gh301& heartRateSensor;
      Watch::Controllers::HeartRateController heartRateController;
      bool measurementStarted = false;

      static void Process(void* instance);

      void StartMeasurement();

      void StopMeasurement();
  };
}


