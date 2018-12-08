// 
// 
// 

#include "leds.h"
#include "analog.h"

#define FASTLED_INTERNAL
#include "FastLED.h"

#define LEDS_DATA_PIN 37	/// NOTE: 51 is SPI_MOSI
#define LEDS_COUNT 12

#define LEDS_STATIC_COEF 0.15f

/************************************************************************/
/* VARIABLE DEFINITIONS (GLOBAL)                                        */
/************************************************************************/

task_t *led_task_ptr;



/************************************************************************/
/* VARIABLE DEFINITIONS (LOCAL)                                         */
/************************************************************************/

CRGB leds[LEDS_COUNT];
uint8_t led_hue;
uint8_t led_inc;



/************************************************************************/
/* FUNCTION DEFINITIONS (GLOBAL)                                        */
/************************************************************************/

void leds_init(void)
{
	FastLED.addLeds<NEOPIXEL, LEDS_DATA_PIN>(leds, LEDS_COUNT);

	led_hue = 0;
	led_inc = 1;
	fill_rainbow(leds, LEDS_COUNT, led_hue);
	FastLED.show();

	led_task_ptr = scheduler_add_task_freq(leds_update, 30);
}

void leds_update(void)
{
	/* copy from analog 'backend' */
	int raw_speed = analog_get_raw(POT_CONTROL_RGB_SPEED);

	/* set speed */
	if (1023 == raw_speed) {
		led_inc = 30;
	}
	else if (LEDS_STATIC_COEF * 1023 > raw_speed) {
		led_inc = 0;
	}
	else {
		led_inc = map(raw_speed, LEDS_STATIC_COEF * 1023, 1023, 1, 15);
	}

	/* write to LED's */
	led_hue += led_inc;
	fill_rainbow(leds, LEDS_COUNT, led_hue);
	FastLED.show();
}


