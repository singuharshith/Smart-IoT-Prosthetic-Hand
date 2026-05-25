#ifndef GESTURE_MAPPER_H
#define GESTURE_MAPPER_H

#include <Arduino.h>
#include "config.h"
#include "sensor_manager.h"

class GestureMapper {
public:
  GestureMapper();
  void begin();
  void mapGestures(const SensorManager& sensors, int outputs[SERVO_COUNT]);
  void setThreshold(uint8_t index, int threshold);
  int getThreshold(uint8_t index) const;

private:
  int gestureThresholds[SENSOR_COUNT];
  int normalizeInput(int sensorValue, uint8_t index) const;
  void applyFingerGesture(uint8_t index, int sourceValue, int& outputAngle) const;
};
