#pragma once

#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <drivers/Kx022.h>
#include <components/motion/MotionControllerTask.h>

namespace Watch {
  class MotionTask {
    public:
      enum class Messages : uint8_t {GoToSleep, WakeUp, StartMeasurement, StopMeasurement };
      enum class States {Idle, Running};

      explicit MotionTask(Drivers::Kx022& motionSensor);
      void Start();
      void Work();
      void PushMessage(Messages msg);

      Watch::Controllers::MotionControllerTask& MotionControllerTask() { return motionControllerTask; }

    private:
      TaskHandle_t taskHandle;
      QueueHandle_t messageQueue;
      States state = States::Running;
      Drivers::Kx022& motionSensor;
      Watch::Controllers::MotionControllerTask motionControllerTask;
      bool measurementStarted = false;

      static void Process(void* instance);

      void StartMeasurement();

      void StopMeasurement();
  };
}



