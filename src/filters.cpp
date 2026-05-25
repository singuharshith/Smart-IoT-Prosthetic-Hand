#include "filters.h"
#include "config.h"

int smoothStep(int current, int target, int step) {
  if (current == target) {
    return current;
  }
  if (abs(target - current) <= step) {
    return target;
  }
  return current + ((target > current) ? step : -step);
}

int clampAngle(int angle) {
  return constrain(angle, MIN_SERVO_ANGLE, MAX_SERVO_ANGLE);
}
