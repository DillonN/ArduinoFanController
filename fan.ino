#include <LiquidCrystal595.h>
#include "Cabinet.h"
#include "TextFormatter.h"
#include <avr/pgmspace.h>
#include <math.h>
#include "Enums.h"


#define T_PIN_L A0 // Thermistor input (analog)
#define T_PIN_R A1
#define BUTTON 2 // Control button
#define P_PIN_L 5 // PWM control pin
#define P_PIN_R 6
#define TACH_PIN_L 3 // Tachometer input
#define TACH_PIN_R 4
#define C_PIN_L 7 // Transistor shutoff
#define C_PIN_R 8 
#define LCD_PIN_1 9 // Pins for LCD shift register control
#define LCD_PIN_2 10
#define LCD_PIN_3 11

#define SIZE 10 // Number of elements before averaged and displayed
#define DELAY 100 // Delay in milliseconds the loop should run at

LiquidCrystal595 lcd(LCD_PIN_1, LCD_PIN_2, LCD_PIN_3);

Cabinet left(C_PIN_L, T_PIN_L, P_PIN_L, TACH_PIN_L, Left);
Cabinet right(C_PIN_R, T_PIN_R, P_PIN_R, TACH_PIN_R, Right);

float temps_l[SIZE] = {};
float rpms_l[SIZE] = {};
float temps_r[SIZE] = {};
float rpms_r[SIZE] = {};
unsigned long time = 0;
unsigned long time2 = 0;
unsigned long time3 = 0;
int i = 0;
char duty_l = 0;
char duty_r = 0;
int mode = Auto;

bool leftFanOn = false; // Control for left fan


void setup()
{
	Serial.begin(9600);

	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(TACH_PIN_L, INPUT_PULLUP);
	pinMode(C_PIN_L, OUTPUT);
	pinMode(BUTTON, INPUT_PULLUP);
	pinMode(TACH_PIN_R, INPUT_PULLUP);
	pinMode(C_PIN_R, OUTPUT);

	digitalWrite(LED_BUILTIN, LOW);

	analogWrite(P_PIN_L, 200); // Placeholder duty for PWM 
	analogWrite(P_PIN_R, 128); // Placeholder duty for PWM

	attachInterrupt(digitalPinToInterrupt(BUTTON), buttonPressed, FALLING); // Get button presses
	
	lcd.begin(16, 2);
	lcd.setLED2Pin(LOW);
}


void loop()
{
	left.gatherData(i);
	right.gatherData(i);
	i++;


	if (i >= SIZE) {
		left.calculateData();
		right.calculateData();
		left.postData(lcd);
		right.postData(lcd);
		left.updatePins(mode);
		right.updatePins(mode);

		if (left.on() || right.on()) {
			lcd.setLED2Pin(HIGH);
		}
		else {
			lcd.setLED2Pin(LOW);
		}

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

// Called when button is pressed
void buttonPressed()
{
	mode = (mode > 1) ? 0 : mode + 1;
	Serial.print("Mode switched to ");
	Serial.println(mode);
}