#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <Arduino.h>
#include "config.h"

class SensorManager {
public:
  SensorManager();
  void begin();
  void update();
  int getRaw(uint8_t index) const;
  int getFiltered(uint8_t index) const;
  void setCalibrationRange(uint8_t index, int minValue, int maxValue);
  int normalize(uint8_t index) const;
  bool isValid() const;

private:
  int rawValues[SENSOR_COUNT];
  int filteredValues[SENSOR_COUNT];
  int filterBuffer[SENSOR_COUNT][MOVING_AVERAGE_WINDOW];
  uint8_t filterIndex;
  int minCalibration[SENSOR_COUNT];
  int maxCalibration[SENSOR_COUNT];
  void initializeBuffers();
  int applyMovingAverage(uint8_t index) const;
};

#endif // SENSOR_MANAGER_H
