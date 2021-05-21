#include "MotionController.h"

using namespace Watch::Controllers;

void MotionController::Update(uint16_t x, uint16_t y, uint16_t z, uint32_t nbSteps) {
  this->x = x;
  this->y = y;
  this->z = z;
  this->nbSteps = nbSteps;
}
