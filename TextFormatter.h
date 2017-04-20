// TextFormatter.h

#ifndef _TEXTFORMATTER_h
#define _TEXTFORMATTER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

/**
Takes a number x that has max n digits and right justifies it for LCD
*/
extern String rightJust(int x, int n);

/**
Returns formatted string for fan rotation
*/
extern String rpmS(float rpm);

extern String tempS(float temp);

extern String dutyS(float duty);

extern String lcdData(char side, float rpm, float temp, float duty);

#endif