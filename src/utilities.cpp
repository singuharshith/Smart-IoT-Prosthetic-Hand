#include "utilities.h"

void logDebug(const char* message) {
  if (!ENABLE_DEBUG) {
    return;
  }
  Serial.print("[DEBUG] ");
  Serial.println(message);
}

void logDebug(const char* label, int value) {
  if (!ENABLE_DEBUG) {
    return;
  }
  Serial.print("[DEBUG] ");
  Serial.print(label);
  Serial.print(": ");
  Serial.println(value);
}

void printHeader() {
  Serial.println(F("========================================"));
  Serial.println(F("Smart IoT Prosthetic Hand - Startup"));
  Serial.println(F("Firmware Version: 1.0.0"));
  Serial.println(F("Mode: Prototype / Demo"));
  Serial.println(F("========================================"));
}

void handleSerialCommands() {
  if (Serial.available()) {
    char command = Serial.read();
    if (command == 'C' || command == 'c') {
      Serial.println(F("Calibration command received."));
    } else if (command == 'R' || command == 'r') {
      Serial.println(F("Reset command acknowledged."));
    } else if (command == 'S' || command == 's') {
      Serial.println(F("Status requested."));
    }
  }
}

char waitForSerialCommand() {
  while (!Serial.available()) {
    delay(10);
  }
  return Serial.read();
}
