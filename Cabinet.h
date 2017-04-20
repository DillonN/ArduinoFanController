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
		Cabinet(int fanPin, int tempPin, int conPin, int tachPin, char side);

		void init(int fanPin, int tempPin, int conPin, int tachPin, char side);

		int speed() {
			return this->_speed;
		}
		int temp() {
			return this->_temp;
		};
		int duty() {
			return this->_duty;
		};
				
	private:
		int _fanPin;
		int _tempPin;
		int _conPin;
		int _tachPin;
		char _side;

		int _speed;
		int _duty;
		int _temp;
};

#endif
