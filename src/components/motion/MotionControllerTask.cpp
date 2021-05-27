#include "MotionControllerTask.h"
#include <motionTask/MotionTask.h>

using namespace Watch::Controllers;

MotionControllerTask::MotionControllerTask(Watch::MotionTask &motionTask) : motionTask{motionTask} {
}

void MotionControllerTask::Update(MotionControllerTask::States newState, uint16_t accx, uint16_t accy, uint16_t accz, uint32_t nbSteps) {
  this->state = newState;
  this->accx = accx;
  this->accy = accy;
  this->accz = accz;
  this->nbSteps=nbSteps;
}

void MotionControllerTask::Start() {
 motionTask.PushMessage(MotionTask::Messages::StartMeasurement);
}

void MotionControllerTask::Stop() {
 motionTask.PushMessage(MotionTask::Messages::StopMeasurement);
}
