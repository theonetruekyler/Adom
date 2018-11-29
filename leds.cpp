// 
// 
// 

#include "leds.h"

CRGB leds[LEDS_COUNT];
uint8_t hue;

void leds_init(void)
{
	FastLED.addLeds<NEOPIXEL, LEDS_DATA_PIN>(leds, LEDS_COUNT);

	hue = 0;
	fill_rainbow(leds, LEDS_COUNT, hue);
	FastLED.show();

	scheduler_add_task_freq(leds_update, LEDS_FRAMERATE);
}

void leds_update(void)
{
	hue++;
	fill_rainbow(leds, LEDS_COUNT, hue);
	FastLED.show();
}


