// Cabinet.h		

#ifndef _CABINET_h
 #define _CABINET_h

#if defined(ARDUINO) && ARDUINO >= 100
 #include "arduino.h"
 #else
 #include "WProgram.h"
 #endif
#include <LiquidCrystal595.h>
#include "TextFormatter.h"

#define SIZE 10

class Cabinet
{
protected:


public:
	Cabinet(int fanPin, int tempPin, int conPin, int tachPin, char side);

	void gatherData(int i);
	void calculateData();
	void postData(LiquidCrystal595 lcd);
	void updatePins(int mode);

	int rpm() {
		return this->_rpm;
	}
	int temp() {
		return this->_temp;
	};
	int duty() {
		return this->_duty;
	};
	bool on() {
		return this->_on;
	}

private:
	int _fanPin;
	int _tempPin;
	int _conPin;
	int _tachPin;
	char _side;
	bool _on;

	float _rpms[SIZE];
	float _temps[SIZE] = {};
	float _rpm = 0;
	float _temp = 0;
	float _duty = 0;

	double thermistor(double aIn);
};

#endif
