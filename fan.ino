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

#define DELAY 100 // Delay in milliseconds the loop should run at, loop will be at least this long and give warning if longer

LiquidCrystal595 lcd(LCD_PIN_1, LCD_PIN_2, LCD_PIN_3);

Cabinet left(C_PIN_L, T_PIN_L, P_PIN_L, TACH_PIN_L, Left);
Cabinet right(C_PIN_R, T_PIN_R, P_PIN_R, TACH_PIN_R, Right);

unsigned long time = 0;
int i = 0;
int mode = Auto;

void setup()
{
	Serial.begin(9600);

	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(C_PIN_L, OUTPUT);
	pinMode(C_PIN_R, OUTPUT);

	pinMode(TACH_PIN_L, INPUT_PULLUP);
	pinMode(BUTTON, INPUT_PULLUP);
	pinMode(TACH_PIN_R, INPUT_PULLUP);

	digitalWrite(LED_BUILTIN, LOW);  // Turn off built in LED

	attachInterrupt(digitalPinToInterrupt(BUTTON), buttonPressed, FALLING); // Get button presses
	
	lcd.begin(16, 2);  // Activate LCD and start with backlight off
	lcd.setLED2Pin(LOW);
}


void loop()
{
	left.gatherData(i);  // Gather raw data and hold on until SIZE loops are held
	right.gatherData(i);
	i++;


	if (i >= SIZE) {
		left.update(lcd, mode);  // Update cabinets with gathered info
		right.update(lcd, mode);

		if (left.on() || right.on()) {
			lcd.setLED2Pin(HIGH);  // Turn on LCD backlight
		}
		else {
			lcd.setLED2Pin(LOW);  // Turn off LCD backlight
		}

		i = 0;
	}
	
	// Logic to keep a constant loop time
	if (millis() - time <= DELAY) {
		delay(DELAY - millis() + time);
	}
	// Warning that delay is unattainable
	else {
		if (i > 0) { // Allow long loops when calculations are done
			Serial.print(millis() - time - DELAY);
			Serial.println(" Too slow!");
		}
	}
	time = millis();
}

// Called when button is pressed
void buttonPressed()
{
	mode = (mode > 1) ? 0 : mode + 1;  // Cycle through modes 0,1,2
	Serial.print("Mode switched to ");
	Serial.println(mode);
}