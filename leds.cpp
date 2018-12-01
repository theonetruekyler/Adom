// 
// 
// 

#include "leds.h"
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
	led_hue += led_inc;
	fill_rainbow(leds, LEDS_COUNT, led_hue);
	FastLED.show();
}


