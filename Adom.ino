// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       Adom.ino
    Created:	11/29/2018 1:22:25 AM
    Author:     DESKTOP-EB5ON9U\Kyler
*/

// Define User Types below here or use a .h file
//
#include "display.h"
#include "analog.h"
#include "serial_printf.h"
#include "leds.h"
#include "scheduler.h"

// Define Function Prototypes that use User Types below here or use a .h file
//

// Define Functions below here or use other .ino or cpp files
//

// The setup() function runs once each time the micro-controller starts
void setup()
{
	delay(500);
	Serial.begin(38400);

	scheduler_init();

	analog_init();
	leds_init();
	display_init();
}

// Add the main program code into the continuous loop() function
void loop()
{
	scheduler_run();
}

/// TODO: functions called by the scheduler should accept a pointer to their containing task!