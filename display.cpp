// 
// hardware abstraction of MAX7219
// 

#include "display.h"
#include "scheduler.h"

#include "LedControl.h"

#define DISPLAY_DATA_IN 51
#define DISPLAY_CLK 52
#define DISPLAY_CS 53

/************************************************************************/
/* VARIABLE DEFINITIONS (LOCAL)                                         */
/************************************************************************/

LedControl led_control = LedControl(DISPLAY_DATA_IN, DISPLAY_CLK, DISPLAY_CS, 1);



/************************************************************************/
/* FUNCTION DEFINITIONS (GLOBAL)                                        */
/************************************************************************/

void display_init(void)
{
	led_control.shutdown(0, false);
	led_control.setIntensity(0, 8);
	led_control.setScanLimit(0, 8);
	led_control.clearDisplay(0);

	scheduler_add_task_freq(display_update, 1);
}

void display_update(void)
{
	static int display_count_debug = 0;
	display_count_debug++;

	display_write_int(display_count_debug, 0);

	/// TODO: remove function and task, or implement scrolling display?
}

void display_write_int(int value, int x)
{
	/* integer out-of-range */
	if (9999 < value || -999 > value) {
		return;
	}

	/* store each decimal place in an array element */
	byte digits[4];
	digits[0] = value % 10;
	digits[1] = (value / 10) % 10;
	digits[2] = (value / 100) % 10;
	digits[3] = (value / 1000);

	int i, j;
	for (i = 0, j = x; i < 4 && j < 8; i++, j++) {
		led_control.setDigit(0, j, (byte)digits[i], false);
	}

	/// TODO: implement '-' character for negative numbers.
}


