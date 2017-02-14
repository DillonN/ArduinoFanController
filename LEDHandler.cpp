// LEDHandler.h

#ifndef _LEDHANDLER_h
#define _LEDHANDLER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

class LEDHandler
{
protected:


public:
	void init();
	void blink(int dely, int pin);
	void blinkMultiple(int delay1, int delay2, int pin, int times);
};

#endif


void LEDHandler::init()
{


}

void LEDHandler::blink(int dely, int pin)
{
	digitalWrite(pin, HIGH);
	delay(dely);
	digitalWrite(pin, LOW);
	delay(dely);
}

void LEDHandler::blinkMultiple(int delay1, int delay2, int pin, int times)
{
	for (int i = 0; i <= times; i++) {
		this->blink(delay1, pin);
	}
	delay(delay2);
}


