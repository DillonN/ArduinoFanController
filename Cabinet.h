// Cabinet.h

#ifndef _CABINET_h
#define _CABINET_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Cabinet
{
 protected:


 public:
	void init(int fanPin, int tempPin, int conPin, int tachPin, char side);

	int speed;
	int temp;
	int duty;

 private:
	 int _fanPin;
	 int _tempPin;
	 int _conPin;
	 int _tachPin;
	 char _side;
};

#endif

