// 
// 
// 

#include "LEDHandler.h"
#include "Arduino.h"

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


