// analog.h

#ifndef _ANALOG_h
#define _ANALOG_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define POTENTIOMETER_COUNT 1

typedef struct __analog_t
{
	int pin;	// external pin
	int raw;	// raw value
	int mv;		// scaled voltage (mV)
} analog_t;

// variable declaration
extern analog_t pots[POTENTIOMETER_COUNT];

// function declaration
void analog_init(void);
void analog_update(void);

#endif

