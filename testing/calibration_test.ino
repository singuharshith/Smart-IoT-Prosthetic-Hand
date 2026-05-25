#include <Arduino.h>
#include <EEPROM.h>
#include "config.h"

void setup() {
  Serial.begin(DEBUG_BAUD_RATE);
  while (!Serial) {
    ;
  }
  Serial.println(F("Calibration EEPROM test."));
  for (uint8_t i = 0; i < SENSOR_COUNT; i++) {
    uint8_t minVal = EEPROM.read(EEPROM_OFFSET_MIN_BASE + i);
    uint8_t maxVal = EEPROM.read(EEPROM_OFFSET_MAX_BASE + i);
    Serial.print(F("Channel "));
    Serial.print(i + 1);
    Serial.print(F(": min="));
    Serial.print(minVal);
    Serial.print(F(" max="));
    Serial.println(maxVal);
  }
  uint8_t flag = EEPROM.read(EEPROM_CALIBRATION_FLAG);
  Serial.print(F("Calibration signature: "));
  Serial.println(flag, HEX);
}

void loop() {
  delay(1000);
}
