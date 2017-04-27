// Cabinet.h		

#ifndef _CABINET_h
 #define _CABINET_h

#if defined(ARDUINO) && ARDUINO >= 100
 #include "arduino.h"
 #else
 #include "WProgram.h"
 #endif
#include <LiquidCrystal595.h>
#include "Helpers\TextFormatter.h"

#define SIZE 10  // Number of samples that are gathered before calculations

/**
Represents a thermistor/fan combo. It is responsible for collecting data and controlling the fans, as well as outputting the data.
**/
class Cabinet
{
protected:


public:
	/**
	Initializer
	*/
	Cabinet(int fanPin, int tempPin, int conPin, int tachPin, char side);

	/**
	Gather data from thermistor and fan pins
	*/
	void gatherData(int i);
	/**
	Calculate RPMs and temp from raw data, and fan speed
	*/
	void calculateData();
	/**
	Write data to LCD
	*/
	void postData(LiquidCrystal595 lcd);
	/**
	Update control pins based on most recent data
	*/
	void updatePins(int mode);
	/**
	Complete collection of data and updating
	*/
	void update(LiquidCrystal595 lcd, int mode);

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

	float _rpms[SIZE] = {};
	float _temps[SIZE] = {};
	float _rpm = 0;
	float _temp = 0;
	float _duty = 0;

	double thermistor(double aIn);
};

#endif
