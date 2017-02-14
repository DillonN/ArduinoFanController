#include <LiquidCrystal.h>
#include "LEDHandler.h"
#include <avr/pgmspace.h>
#include <math.h>


#define T_PIN_L A0 // Thermistor input (analog)
#define T_PIN_R 1
#define P_PIN_L 5 // PWM control pin
#define P_PIN_R 6
#define TACH_PIN_L 2 // Tachometer input
#define TACH_PIN_R 10

#define SIZE 10 // Number of elements before averaged and displayed
#define DELAY 100 // Delay in milliseconds the loop should run at

//LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

double A = 3.354016 * pow(10, -3); // A = 3.354016 * 10^-3
double B = 2.884193 * pow(10, -4);
double C = 4.118032 * pow(10, -6);
double D = 1.786790 * pow(10, -7);

float temps[SIZE] = {};
float rpms[SIZE] = {};
unsigned long time = 0;
unsigned long time2 = 0;
unsigned long time3 = 0;
int i = 0;

double Thermistor(double aIn) // Function to calculate temp from analog pin input
{
	int R_ref = 10000; // Resistance of reference resistor in Ohms
	double R = R_ref * (1024 / aIn - 1); // Conversion to get resistance of thermistor. 1024/aIn = V_in/V_out
	double ln = log(R / 10000); // Calculate log now instead of three times later
	double T = 1 / (A + (B * ln) + (C * pow(ln, 2)) + (D * pow(ln, 3))); // Formula for T in lab manual
	T -= 273.15; // Convert to *C
	return T;
}


void setup()
{
	Serial.begin(9600);

	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(TACH_PIN_L, INPUT);
	digitalWrite(TACH_PIN_L, HIGH);
	digitalWrite(LED_BUILTIN, LOW);
	pinMode(12, OUTPUT);
	digitalWrite(12, HIGH);

	analogWrite(P_PIN_L, 200); // Placeholder duty for PWM 
	analogWrite(P_PIN_R, 128); // Placeholder duty for PWM

	/*lcd.begin(16, 2);
	// LCD     ||||||||||||||||
	lcd.print("L:2000R 24C 100%"); // Rotations, temps, duty
	lcd.setCursor(0, 1);
	lcd.print("R:    0RPM 20C");*/
}


void loop()
{
	rpms[i] = pulseIn(TACH_PIN_L, LOW, 95000);
	temps[i] = Thermistor(analogRead(T_PIN_L));
	i++;

	if (i >= SIZE) {
		unsigned int sumT = 0;
		unsigned int sumR = 0;
		for (int j = 0; j < SIZE; j++) {
			sumT += temps[j];
			
			sumR += (1000000 * 60 / (rpms[j] * 4));
		}/*
		lcd.setCursor(3, 0);
		lcd.print(int(sumR / SIZE));
		lcd.print("RPM");
		lcd.setCursor(11, 0);
		lcd.print(int(sumT / SIZE));*/

		Serial.println(int(sumR / SIZE));
		Serial.println(int(sumT / SIZE));

		i = 0;
	}
	
	// Logic to keep a constant loop time
	if (millis() - time2 <= DELAY) {
		delay(DELAY - millis() + time2);
	}
	// Warning that delay is unattainable
	else {
		if (i > 0) { // Allow long loops when calculations are done
			Serial.print(millis() - time2 - DELAY);
			Serial.println(" Too slow!");
		}
	}
	time2 = millis();
}