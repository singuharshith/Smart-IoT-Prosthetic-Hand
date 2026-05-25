#ifndef SERVO_CONTROLLER_H
#define SERVO_CONTROLLER_H

#include <Arduino.h>
#include <Servo.h>
#include "config.h"

class ServoController {
public:
  ServoController();
  void initialize();
  void updateTargets(const int targetAngles[SERVO_COUNT]);
  void homeAll();
  void idle();
  int getCurrentAngle(uint8_t index) const;

private:
  Servo servos[SERVO_COUNT];
  int currentAngles[SERVO_COUNT];
  int targetAngles[SERVO_COUNT];
  void attachServos();
  void safeMove(uint8_t index, int target);
  int interpolate(int current, int target) const;
};

#endif // SERVO_CONTROLLER_H
