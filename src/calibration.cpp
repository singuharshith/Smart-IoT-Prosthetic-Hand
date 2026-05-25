#include "calibration.h"
#include "utilities.h"

CalibrationManager::CalibrationManager() : calibrationValid(false) {}

void CalibrationManager::begin() {
  calibrationValid = validateStoredData();
}

bool CalibrationManager::validateStoredData() const {
  uint8_t signature = EEPROM.read(EEPROM_CALIBRATION_FLAG);
  if (signature != EEPROM_CALIBRATION_SIGNATURE) {
    return false;
  }
  for (uint8_t i = 0; i < SENSOR_COUNT; i++) {
    int minVal = EEPROM.read(EEPROM_OFFSET_MIN_BASE + i);
    int maxVal = EEPROM.read(EEPROM_OFFSET_MAX_BASE + i);
    if (maxVal <= minVal || minVal < 0 || maxVal > 255) {
      return false;
    }
  }
  return true;
}

bool CalibrationManager::loadCalibration(int minValues[SENSOR_COUNT], int maxValues[SENSOR_COUNT]) {
  if (!calibrationValid) {
    return false;
  }
  for (uint8_t i = 0; i < SENSOR_COUNT; i++) {
    minValues[i] = EEPROM.read(EEPROM_OFFSET_MIN_BASE + i);
    maxValues[i] = EEPROM.read(EEPROM_OFFSET_MAX_BASE + i);
  }
  return true;
}

bool CalibrationManager::saveCalibration(const int minValues[SENSOR_COUNT], const int maxValues[SENSOR_COUNT]) {
  for (uint8_t i = 0; i < SENSOR_COUNT; i++) {
    writeByteSafe(EEPROM_OFFSET_MIN_BASE + i, minValues[i]);
    writeByteSafe(EEPROM_OFFSET_MAX_BASE + i, maxValues[i]);
  }
  writeSignature();
  calibrationValid = true;
  return true;
}

void CalibrationManager::writeSignature() {
  EEPROM.write(EEPROM_CALIBRATION_FLAG, EEPROM_CALIBRATION_SIGNATURE);
}

void CalibrationManager::resetCalibration() {
  for (uint8_t i = 0; i < SENSOR_COUNT; i++) {
    writeByteSafe(EEPROM_OFFSET_MIN_BASE + i, 0);
    writeByteSafe(EEPROM_OFFSET_MAX_BASE + i, 255);
  }
  calibrationValid = false;
}

void CalibrationManager::startRoutine(int minValues[SENSOR_COUNT], int maxValues[SENSOR_COUNT]) {
  logDebug("Calibration started.");
  for (uint8_t i = 0; i < SENSOR_COUNT; i++) {
    minValues[i] = 0;
    maxValues[i] = 1023;
  }
}

bool CalibrationManager::isCalibrated() const {
  return calibrationValid;
}

int CalibrationManager::readByteOrDefault(int address, int defaultValue) const {
  int value = EEPROM.read(address);
  if (value < 0 || value > 255) {
    return defaultValue;
  }
  return value;
}

void CalibrationManager::writeByteSafe(int address, int value) {
  value = constrain(value, 0, 255);
  EEPROM.write(address, value);
}
