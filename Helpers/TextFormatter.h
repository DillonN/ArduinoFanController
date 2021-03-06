//
//   TextFormatter.h
//   fan
//   
//   Created by Dillon Newell on 27-4-2017
//   Copyright (c) 2017 Newell Labs. All rights reserved.
//

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

/**
Returns formatted string for temperature
*/
extern String tempS(float temp);

/**
Returns formatted string for PWM duty
*/
extern String dutyS(float duty);

/**
Returns formatted string for LCD
*/
extern String lcdData(int side, float rpm, float temp, float duty);

#endif