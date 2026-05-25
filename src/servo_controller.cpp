#include "servo_controller.h"
#include "utilities.h"

ServoController::ServoController() {
  for (uint8_t i = 0; i < SERVO_COUNT; i++) {
    currentAngles[i] = SERVO_HOMING_ANGLE;
    targetAngles[i] = SERVO_HOMING_ANGLE;
  }
}

void ServoController::initialize() {
  attachServos();
  homeAll();
}

void ServoController::attachServos() {
  for (uint8_t i = 0; i < SERVO_COUNT; i++) {
    servos[i].attach(SERVO_PINS[i]);
  }
}

void ServoController::homeAll() {
  logDebug("Starting servo homing routine...");
  for (uint8_t i = 0; i < SERVO_COUNT; i++) {
    targetAngles[i] = SERVO_HOMING_ANGLE;
    safeMove(i, SERVO_HOMING_ANGLE);
  }
  delay(250);
  logDebug("Servo homing complete.");
}

void ServoController::updateTargets(const int newTargets[SERVO_COUNT]) {
  for (uint8_t i = 0; i < SERVO_COUNT; i++) {
    targetAngles[i] = constrain(newTargets[i], MIN_SERVO_ANGLE, MAX_SERVO_ANGLE);
  }
  for (uint8_t i = 0; i < SERVO_COUNT; i++) {
    safeMove(i, targetAngles[i]);
  }
}

void ServoController::safeMove(uint8_t index, int target) {
  if (index >= SERVO_COUNT) {
    return;
  }
  int current = currentAngles[index];
  int next = interpolate(current, target);
  if (next == current) {
    return;
  }
  next = constrain(next, MIN_SERVO_ANGLE, MAX_SERVO_ANGLE);
  servos[index].write(next);
  currentAngles[index] = next;
  delay(SERVO_STEP_DELAY_MS);
}

int ServoController::interpolate(int current, int target) const {
  if (current == target) {
    return current;
  }
  if (abs(target - current) <= SAFE_SERVO_STEP) {
    return target;
  }
  if (target > current) {
    return current + SAFE_SERVO_STEP;
  }
  return current - SAFE_SERVO_STEP;
}

int ServoController::getCurrentAngle(uint8_t index) const {
  if (index >= SERVO_COUNT) {
    return SERVO_HOMING_ANGLE;
  }
  return currentAngles[index];
}

void ServoController::idle() {
  // Placeholder for future low-power or idle behavior
}
