#include "config.h"
#include "sensor_manager.h"
#include "servo_controller.h"
#include "gesture_mapper.h"
#include "calibration.h"
#include "utilities.h"

SensorManager sensorManager;
ServoController servoController;
GestureMapper gestureMapper;
CalibrationManager calibrationManager;

unsigned long lastSerialLog = 0;
int targetAngles[SERVO_COUNT];
int calibrationMin[SENSOR_COUNT];
int calibrationMax[SENSOR_COUNT];

void performCalibration();
void logRuntimeStatus();
void applySensorMapping();

void setup() {
  Serial.begin(DEBUG_BAUD_RATE);
  while (!Serial) {
    ;
  }

  printHeader();
  sensorManager.begin();
  servoController.initialize();
  calibrationManager.begin();

  if (calibrationManager.loadCalibration(calibrationMin, calibrationMax)) {
    for (uint8_t i = 0; i < SENSOR_COUNT; i++) {
      sensorManager.setCalibrationRange(i, calibrationMin[i], calibrationMax[i]);
    }
    Serial.println(F("Calibration loaded from EEPROM."));
  } else {
    Serial.println(F("No valid calibration found. Using default range."));
    for (uint8_t i = 0; i < SENSOR_COUNT; i++) {
      sensorManager.setCalibrationRange(i, 0, 1023);
    }
  }

  gestureMapper.begin();
  Serial.println(F("Initialization complete. Ready for operation."));
}

void loop() {
  sensorManager.update();
  applySensorMapping();
  servoController.updateTargets(targetAngles);

  if (millis() - lastSerialLog >= SERIAL_LOG_INTERVAL_MS) {
    logRuntimeStatus();
    lastSerialLog = millis();
  }

  if (Serial.available()) {
    char command = Serial.read();
    if (command == 'C' || command == 'c') {
      performCalibration();
    } else if (command == 'R' || command == 'r') {
      calibrationManager.resetCalibration();
      Serial.println(F("Calibration reset. Restart to re-run calibration."));
    }
  }

  delay(SENSOR_SAMPLE_INTERVAL_MS);
}

void applySensorMapping() {
  gestureMapper.mapGestures(sensorManager, targetAngles);
}

void performCalibration() {
  Serial.println(F("Beginning calibration routine."));
  Serial.println(F("Please position each finger in the rest state and press any key."));
  waitForSerialCommand();

  int minValues[SENSOR_COUNT];
  int maxValues[SENSOR_COUNT];

  for (uint8_t i = 0; i < SENSOR_COUNT; i++) {
    minValues[i] = analogRead(SENSOR_PINS[i]);
    Serial.print(F("Rest position recorded for finger "));
    Serial.print(i + 1);
    Serial.print(F(" = "));
    Serial.println(minValues[i]);
    delay(200);
  }

  Serial.println(F("Now move each finger to the extension position and press any key."));
  waitForSerialCommand();

  for (uint8_t i = 0; i < SENSOR_COUNT; i++) {
    maxValues[i] = analogRead(SENSOR_PINS[i]);
    Serial.print(F("Extended position recorded for finger "));
    Serial.print(i + 1);
    Serial.print(F(" = "));
    Serial.println(maxValues[i]);
    delay(200);
  }

  for (uint8_t i = 0; i < SENSOR_COUNT; i++) {
    if (maxValues[i] <= minValues[i]) {
      maxValues[i] = minValues[i] + 16;
      Serial.print(F("Adjusted calibration range for finger "));
      Serial.println(i + 1);
    }
    sensorManager.setCalibrationRange(i, minValues[i], maxValues[i]);
  }

  calibrationManager.saveCalibration(minValues, maxValues);
  Serial.println(F("Calibration saved to EEPROM."));
}

void logRuntimeStatus() {
  Serial.println(F("--- Runtime Status ---"));
  for (uint8_t i = 0; i < SENSOR_COUNT; i++) {
    Serial.print(F("Sensor "));
    Serial.print(i + 1);
    Serial.print(F(": raw="));
    Serial.print(sensorManager.getRaw(i));
    Serial.print(F(" filtered="));
    Serial.print(sensorManager.getFiltered(i));
    Serial.print(F(" => angle="));
    Serial.println(targetAngles[i]);
  }
  Serial.println(F("----------------------"));
}
