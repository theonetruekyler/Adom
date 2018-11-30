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

// variable declaration(s)
extern CRGB leds[LEDS_COUNT];

// function declarations(s)
void leds_init(void);
void leds_update(void);


#endif

