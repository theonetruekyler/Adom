// 
// 
// 

#include "leds.h"
#include "analog.h"
#include "scheduler.h"

#define LEDS_DATA_PIN 51	/// NOTE: this is a SPI_MOSI pin

// global variables
CRGB leds[LEDS_COUNT];
uint8_t led_inc;

// local variables
task_t* led_task_ptr;
uint8_t led_hue;

void leds_init(void)
{
	FastLED.addLeds<NEOPIXEL, LEDS_DATA_PIN>(leds, LEDS_COUNT);

	led_inc = 1;
	led_hue = 0;
	fill_rainbow(leds, LEDS_COUNT, led_hue);
	FastLED.show();

	led_task_ptr = scheduler_add_task_freq(leds_update, 25);
}

void leds_update(void)
{
	// copy from analog backend
	int raw_speed = pots[POT_CONTROL_RGB_SPEED].raw;

	// logic (speed)
	if (1023 == raw_speed) {
		led_inc = 30;
	}
	else if (LEDS_ADC_THRESHOLD * 1023 > raw_speed) {
		led_inc = 0;
	}
	else {
		led_inc = map(raw_speed, LEDS_ADC_THRESHOLD * 1023, 1023, 1, 15);
	}

	// update display
	led_hue += led_inc;
	fill_rainbow(leds, LEDS_COUNT, led_hue);
	FastLED.show();
}


