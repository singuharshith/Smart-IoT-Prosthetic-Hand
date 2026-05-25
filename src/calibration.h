#ifndef CALIBRATION_H
#define CALIBRATION_H

#include <Arduino.h>
#include <EEPROM.h>
#include "config.h"

class CalibrationManager {
public:
  CalibrationManager();
  void begin();
  bool loadCalibration(int minValues[SENSOR_COUNT], int maxValues[SENSOR_COUNT]);
  bool saveCalibration(const int minValues[SENSOR_COUNT], const int maxValues[SENSOR_COUNT]);
  void resetCalibration();
  void startRoutine(int minValues[SENSOR_COUNT], int maxValues[SENSOR_COUNT]);
  bool isCalibrated() const;

private:
  bool calibrationValid;
  void writeSignature();
  bool validateStoredData() const;
  int readByteOrDefault(int address, int defaultValue) const;
  void writeByteSafe(int address, int value);
};
