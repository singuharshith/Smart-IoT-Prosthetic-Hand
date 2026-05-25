#include "sensor_manager.h"
#include "utilities.h"

SensorManager::SensorManager() : filterIndex(0) {
  for (uint8_t i = 0; i < SENSOR_COUNT; i++) {
    rawValues[i] = 0;
    filteredValues[i] = 0;
    minCalibration[i] = 0;
    maxCalibration[i] = 1023;
  }
}

void SensorManager::begin() {
  for (uint8_t i = 0; i < SENSOR_COUNT; i++) {
    pinMode(SENSOR_PINS[i], INPUT);
  }
  initializeBuffers();
}

void SensorManager::initializeBuffers() {
  for (uint8_t i = 0; i < SENSOR_COUNT; i++) {
    for (uint8_t j = 0; j < MOVING_AVERAGE_WINDOW; j++) {
      filterBuffer[i][j] = analogRead(SENSOR_PINS[i]);
    }
    filteredValues[i] = applyMovingAverage(i);
  }
}

void SensorManager::update() {
  filterIndex = (filterIndex + 1) % MOVING_AVERAGE_WINDOW;
  for (uint8_t i = 0; i < SENSOR_COUNT; i++) {
    rawValues[i] = analogRead(SENSOR_PINS[i]);
    filterBuffer[i][filterIndex] = rawValues[i];
    filteredValues[i] = applyMovingAverage(i);
  }
}

int SensorManager::applyMovingAverage(uint8_t index) const {
  long sum = 0;
  for (uint8_t sample = 0; sample < MOVING_AVERAGE_WINDOW; sample++) {
    sum += filterBuffer[index][sample];
  }
  return (int)(sum / MOVING_AVERAGE_WINDOW);
}

int SensorManager::getRaw(uint8_t index) const {
  if (index >= SENSOR_COUNT) {
    return 0;
  }
  return rawValues[index];
}

int SensorManager::getFiltered(uint8_t index) const {
  if (index >= SENSOR_COUNT) {
    return 0;
  }
  return filteredValues[index];
}

void SensorManager::setCalibrationRange(uint8_t index, int minValue, int maxValue) {
  if (index >= SENSOR_COUNT) {
    return;
  }
  minCalibration[index] = minValue;
  maxCalibration[index] = maxValue;
}

int SensorManager::normalize(uint8_t index) const {
  if (index >= SENSOR_COUNT) {
    return 0;
  }
  int value = filteredValues[index];
  int minValue = minCalibration[index];
  int maxValue = maxCalibration[index];
  if (maxValue <= minValue) {
    return 0;
  }
  int mapped = map(value, minValue, maxValue, MIN_SERVO_ANGLE, MAX_SERVO_ANGLE);
  return constrain(mapped, MIN_SERVO_ANGLE, MAX_SERVO_ANGLE);
}

bool SensorManager::isValid() const {
  for (uint8_t i = 0; i < SENSOR_COUNT; i++) {
    if (maxCalibration[i] <= minCalibration[i]) {
      return false;
    }
  }
  return true;
}
