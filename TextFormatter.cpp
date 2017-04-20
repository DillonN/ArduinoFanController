#include "TextFormatter.h"

String rightJust(int x, int n)
{
	if (x == 0) { 
		return String("   0");
	}
	else if (pow(10, n - 1) > x) {
		return " " + rightJust(x, n - 1);
	}
	return String(x);
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