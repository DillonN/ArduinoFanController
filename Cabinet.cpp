#include "Cabinet.h"

Cabinet::Cabinet(int fanPin, int tempPin, int conPin, int tachPin, char side)
{

}

void Cabinet::init(int fanPin, int tempPin, int conPin, int tachPin, char side)
{
	_fanPin = fanPin;
	_tempPin = tempPin;
	_conPin = conPin;
	_tachPin = tachPin;
	_side = side;
}