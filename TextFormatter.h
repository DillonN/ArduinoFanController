// TextFormatter.h

#ifndef _TEXTFORMATTER_h
#define _TEXTFORMATTER_h

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

extern String lcdData(String side, float rpm, float temp, float duty);

#endif

