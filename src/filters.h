#ifndef FILTERS_H
#define FILTERS_H

#include <Arduino.h>

int smoothStep(int current, int target, int step);
int clampAngle(int angle);

#endif // FILTERS_H
