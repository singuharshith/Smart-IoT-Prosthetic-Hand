#include <Arduino.h>
#include <Servo.h>
#include "config.h"

Servo testServos[SERVO_COUNT];
int position = MIN_SERVO_ANGLE;
int direction = 1;

void setup() {
  Serial.begin(DEBUG_BAUD_RATE);
  while (!Serial) {
    ;
  }
  Serial.println(F("Servo test startup."));
  for (uint8_t i = 0; i < SERVO_COUNT; i++) {
    testServos[i].attach(SERVO_PINS[i]);
    testServos[i].write(SERVO_HOMING_ANGLE);
  }
  delay(1000);
}

void loop() {
  for (uint8_t i = 0; i < SERVO_COUNT; i++) {
    testServos[i].write(position);
  }
  Serial.print(F("Servo sweep position: "));
  Serial.println(position);
  position += direction * SAFE_SERVO_STEP;
  if (position >= MAX_SERVO_ANGLE || position <= MIN_SERVO_ANGLE) {
    direction = -direction;
  }
  delay(100);
}
