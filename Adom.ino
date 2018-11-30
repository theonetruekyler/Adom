// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       Adom.ino
    Created:	11/29/2018 1:22:25 AM
    Author:     DESKTOP-EB5ON9U\Kyler
*/

// Define User Types below here or use a .h file
//
#include "analog.h"
#include "serial_printf.h"
#include "leds.h"
#include "scheduler.h"


// Define Function Prototypes that use User Types below here or use a .h file
//


// Define Functions below here or use other .ino or cpp files
//

void foo(void)
{
	static unsigned long uptime_sec = 0;
	uptime_sec++;

	serial_printf("uptime: %u", uptime_sec);
}

void bar(void)
{
	Serial.println("hi, i'm adom!");
}

// The setup() function runs once each time the micro-controller starts
void setup()
{
	delay(500);

	Serial.begin(38400);

	scheduler_init();

	analog_init();

	leds_init();
}

// Add the main program code into the continuous loop() function
void loop()
{
	scheduler_run();

	/// TODO: remove this hack
	task_t* led_task_ptr = scheduler_get_task(leds_update);
	led_task_ptr->per = 1000 / map(pots[0].raw, 0, 1023, 1, 50);

}

/// TODO: functions called by the scheduler should accept a pointer to their containing task!