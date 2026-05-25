#ifndef UTILITIES_H
#define UTILITIES_H

#include <Arduino.h>
#include "config.h"

void logDebug(const char* message);
void logDebug(const char* label, int value);
void printHeader();
void handleSerialCommands();
char waitForSerialCommand();

#endif // UTILITIES_H
