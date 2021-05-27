#include <nrfx_log.h>
#include "MotionTask.h"
using namespace Watch;


MotionTask::MotionTask(Drivers::Kx022 &motionSensor) :
        motionSensor{motionSensor},
        motionControllerTask{*this} {
  messageQueue = xQueueCreate(10, 1);
}

void MotionTask::Start() {
  if (pdPASS != xTaskCreate(MotionTask::Process, "Motion", 100, this, 0, &taskHandle))
    APP_ERROR_HANDLER(NRF_ERROR_NO_MEM);
}

void MotionTask::Process(void *instance) {
  //auto *app = static_cast<MotionTask *>(instance);
 // app->Work();
}

void MotionTask::Work() {
  while (true) {
    Messages msg;
    uint32_t delay;
    if (state == States::Running) {
      if (measurementStarted) delay = 50;
      else delay = 100;
    } else
      delay = portMAX_DELAY;

    if (xQueueReceive(messageQueue, &msg, delay)) {
      switch (msg) {
        case Messages::GoToSleep:
          StopMeasurement();
          state = States::Idle;
          break;
        case Messages::WakeUp:
          state = States::Running;
          break;
        case Messages::StartMeasurement:
          StartMeasurement();
          break;
        case Messages::StopMeasurement:
          StopMeasurement();
          break;
      }
    }

    if (measurementStarted) {
      auto accData = motionSensor.Process();
      motionControllerTask.Update(Controllers::MotionControllerTask::States::Running,accData.x,accData.y,accData.z,accData.steps);
     }    
  }
}

void MotionTask::PushMessage(MotionTask::Messages msg) {
  BaseType_t xHigherPriorityTaskWoken;
  xHigherPriorityTaskWoken = pdFALSE;
  xQueueSendFromISR(messageQueue, &msg, &xHigherPriorityTaskWoken);
  if (xHigherPriorityTaskWoken) {
    /* Actual macro used here is port specific. */
    // TODO : should I do something here?
  }
}

void MotionTask::StartMeasurement() {
  motionSensor.Init();
  measurementStarted = true;
}

void MotionTask::StopMeasurement() {
  motionSensor.PowerDown();
  measurementStarted = false;
}


