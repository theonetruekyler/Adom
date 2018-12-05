// 
// hardware abstraction of MAX7219
// 

#include "display.h"

#define DISPLAY_DATA_IN 51
#define DISPLAY_CLK 52
#define DISPLAY_CS 53

// "local" variables
LedControl led_control = LedControl(DISPLAY_DATA_IN, DISPLAY_CLK, DISPLAY_CS, 1);

void display_init(void)
{
	// wake up
	led_control.shutdown(0, false);

	// set brightness
	led_control.setIntensity(0, 8);

	// clear display
	led_control.clearDisplay(0);

	/// TODO: testing, remove
	for (int i = 0; i < 8; i++) {
		led_control.setDigit(0, i, (byte)(7-i), false);
	}

	/// TODO: schedule update task
}
