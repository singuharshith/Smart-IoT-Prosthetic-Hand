#include <Arduino.h>
#include "config.h"

void setup() {
  Serial.begin(DEBUG_BAUD_RATE);
  while (!Serial) {
    ;
  }
  Serial.println(F("Sensor test starting."));
}

void loop() {
  for (uint8_t i = 0; i < SENSOR_COUNT; i++) {
    int rawValue = analogRead(SENSOR_PINS[i]);
    Serial.print(F("Sensor "));
    Serial.print(i + 1);
    Serial.print(F(" (A"));
    Serial.print(i);
    Serial.print(F("): "));
    Serial.println(rawValue);
  }
  Serial.println(F("---"));
  delay(500);
}
