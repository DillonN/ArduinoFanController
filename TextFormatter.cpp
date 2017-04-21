#include "TextFormatter.h"

String rightJust(int x, int n)
{
	if ((x > 0 && pow(10, n - 1) > x) || (x == 0 && n > 1)) {
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

String lcdData(int side, float rpm, float temp, float duty)
{
	String sideS = (side == 0) ? "L" : "R";
	return sideS + ":" + rpmS(rpm) + " " + tempS(temp) + " " + dutyS(duty);
}