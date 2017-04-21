#include "Cabinet.h"

// Constants for thermistor equation
#define A 3.354016 * pow(10, -3) // A = 3.354016 * 10^-3
#define B 2.884193 * pow(10, -4)
#define C 4.118032 * pow(10, -6)
#define D 1.786790 * pow(10, -7)
#define R_ref 10000 // Reference resistor value for temp monitoring

//Constants for fan line
#define MIN_TEMP 25
#define MAX_TEMP 40
#define m 100 / (MAX_TEMP - MIN_TEMP)

Cabinet::Cabinet(int fanPin, int tempPin, int conPin, int tachPin, char side)
{
	_fanPin = fanPin;
	_tempPin = tempPin;
	_conPin = conPin;
	_tachPin = tachPin;
	_side = side;
}

void Cabinet::gatherData(int i)
{
	_rpms[i] = pulseIn(_tachPin, LOW, 95000);
	_temps[i] = thermistor(analogRead(_tempPin));
}

void Cabinet::calculateData()
{
	float tempSum = 0;
	float rpmSum = 0;
	for (int j = 0; j < SIZE; j++) {
		tempSum += _temps[j];
		rpmSum += (1000000 * 60 / (_rpms[j] * 4));
	}

	_rpm = rpmSum / SIZE;
	_temp = tempSum / SIZE;

	_duty = m * (_temp - MIN_TEMP);
	_duty = min(100, max(0, _duty));

	if (_duty <= 0) {
		_on = false;
	}
	else {
		_on = true;
	}
}

void Cabinet::postData(LiquidCrystal595 lcd)
{
	String text = lcdData(_side, _rpm, _temp, _duty);
	lcd.setCursor(0, _side);
	lcd.print(text);
	Serial.println(text);
}

void Cabinet::updatePins(int mode)
{
	if (mode == 0) {
		analogWrite(_conPin, 255 * _duty / 100);
	}
	else if (mode == 1) {
		analogWrite(_conPin, 0);
		_on = false;
	}
	else {
		analogWrite(_conPin, 255);
		_on = true;
	}
	digitalWrite(_fanPin, _on);
}

double Cabinet::thermistor(double aIn) // Function to calculate temp from analog pin input
{
	double R = R_ref * (1024 / aIn - 1); // Conversion to get resistance of thermistor. 1024/aIn = V_in/V_out
	double ln = log(R / 10000); // Calculate log now instead of three times later
	double T = 1 / (A + (B * ln) + (C * pow(ln, 2)) + (D * pow(ln, 3))); // Formula for T in lab manual
	T -= 273.15; // Convert to *C
	return T;
}