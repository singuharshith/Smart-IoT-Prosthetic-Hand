#include "gesture_mapper.h"
#include "utilities.h"

GestureMapper::GestureMapper() {
  for (uint8_t i = 0; i < SENSOR_COUNT; i++) {
    gestureThresholds[i] = GESTURE_THRESHOLD;
  }
}

void GestureMapper::begin() {
  // Future initialization for gesture states and mode selection.
}

void GestureMapper::mapGestures(const SensorManager& sensors, int outputs[SERVO_COUNT]) {
  for (uint8_t i = 0; i < SENSOR_COUNT; i++) {
    int normalized = sensors.normalize(i);
    applyFingerGesture(i, normalized, outputs[i]);
  }
}

void GestureMapper::setThreshold(uint8_t index, int threshold) {
  if (index < SENSOR_COUNT) {
    gestureThresholds[index] = threshold;
  }
}

int GestureMapper::getThreshold(uint8_t index) const {
  if (index < SENSOR_COUNT) {
    return gestureThresholds[index];
  }
  return GESTURE_THRESHOLD;
}

int GestureMapper::normalizeInput(int sensorValue, uint8_t index) const {
  return constrain(sensorValue, MIN_SERVO_ANGLE, MAX_SERVO_ANGLE);
}

void GestureMapper::applyFingerGesture(uint8_t index, int sourceValue, int& outputAngle) const {
  outputAngle = normalizeInput(sourceValue, index);
  if (abs(outputAngle - SERVO_HOMING_ANGLE) < gestureThresholds[index]) {
    outputAngle = SERVO_HOMING_ANGLE;
  }
}
