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

extern String lcdData(char side, float rpm, float temp, float duty);

#endif

String rightJust(int x, int n)
{
	if (pow(10, n - 1) > x) {
		return " " + rightJust(x, n - 1);
	}
	return x;
}

String rpmS(float rpm)
{
	return rightJust(int(rpm), 4) + "R";
}

String tempS(float temp)
{
	return rightJust(int(temp), 2) + "C";
}

String dutyS(float duty)
{
	return rightJust(int(duty), 3) + "%";
}

String lcdData(char side, float rpm, float temp, float duty)
{
	return side + ":" + rpmS(rpm) + " " + tempS(temp) + " " + dutyS(duty);
}

