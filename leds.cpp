// 
// 
// 

#include "leds.h"
#include "scheduler.h"

#define LEDS_DATA_PIN 51	/// NOTE: this is a SPI_MOSI pin

// global variables
CRGB leds[LEDS_COUNT];

// local variables
task_t* led_task_ptr;
uint8_t led_hue;

void leds_init(void)
{
	FastLED.addLeds<NEOPIXEL, LEDS_DATA_PIN>(leds, LEDS_COUNT);

	led_hue = 0;
	fill_rainbow(leds, LEDS_COUNT, led_hue);
	FastLED.show();

	// init "framerate" to 1Hz, will be overridden by potentiometer
	led_task_ptr = scheduler_add_task_freq(leds_update, 1);
}

void leds_update(void)
{
	led_hue++;
	fill_rainbow(leds, LEDS_COUNT, led_hue);
	FastLED.show();
}


