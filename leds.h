// leds.h

#ifndef _LEDS_h
#define _LEDS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define FASTLED_INTERNAL
#include "FastLED.h"

#define LEDS_COUNT 12
#define LEDS_ADC_THRESHOLD 0.15f

// variable declaration(s)
extern CRGB leds[LEDS_COUNT];
extern uint8_t led_inc;

// function declarations(s)
void leds_init(void);
void leds_update(void);


#endif

