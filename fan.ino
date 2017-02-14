#include "Cabinet.h"
#include "TextFormatter.h"
#include <LiquidCrystal.h>
#include "LEDHandler.h"
#include <avr/pgmspace.h>
#include <math.h>


#define T_PIN_L A0 // Thermistor input (analog)
#define T_PIN_R A1
#define BUTTON 2 // Control button
#define P_PIN_L 5 // PWM control pin
#define P_PIN_R 6
#define TACH_PIN_L 3 // Tachometer input
#define TACH_PIN_R 4
#define C_PIN_L 7 // Transistor shutoff
#define C_PIN_R 8 

#define SIZE 10 // Number of elements before averaged and displayed
#define DELAY 100 // Delay in milliseconds the loop should run at

#define A 3.354016 * pow(10, -3) // A = 3.354016 * 10^-3
#define B 2.884193 * pow(10, -4)
#define C 4.118032 * pow(10, -6)
#define D 1.786790 * pow(10, -7)

//LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

float temps[SIZE] = {};
float rpms[SIZE] = {};
unsigned long time = 0;
unsigned long time2 = 0;
unsigned long time3 = 0;
int i = 0;

bool leftFanOn = false; // Control for left fan

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
	pinMode(TACH_PIN_L, INPUT_PULLUP);
	pinMode(C_PIN_L, OUTPUT);
	pinMode(BUTTON, INPUT_PULLUP);

	digitalWrite(LED_BUILTIN, LOW);

	analogWrite(P_PIN_L, 200); // Placeholder duty for PWM 
	analogWrite(P_PIN_R, 128); // Placeholder duty for PWM

	attachInterrupt(digitalPinToInterrupt(BUTTON), buttonPressed, FALLING); // Get button presses
	
	/*lcd.begin(16, 2);
	// LCD     ||||||||||||||||   <- 16 digits across
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

		Serial.println(rightJust(int(sumR / SIZE), 4));
		Serial.println(rightJust(int(sumT / SIZE), 2));

		i = 0;
	}

	digitalWrite(C_PIN_L, leftFanOn);
	analogWrite(P_PIN_L, 128); // Placeholder duty for PWM 
	
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

// Called when button is pressed
void buttonPressed()
{
	Serial.println("Button pressed!");

	leftFanOn = !leftFanOn;
}