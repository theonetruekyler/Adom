// analog.h

#ifndef _ANALOG_h
#define _ANALOG_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define ANALOG_POT_COUNT 1

typedef struct __analog_t
{
	int pin;	// external pin
	int raw;	// raw value
	int mv;		// scaled voltage (mV)
} analog_t;

// this enumeration describes the use of each potentiometer and maps to
// the analog backend instance of that pot in the pots array
typedef enum
{
	POT_CONTROL_RGB_SPEED = 0,
	POT_CONTROL_RGB_VARIETY = 1,
	POT_CONTROl_RGB_BRIGHTNESS = 2
} pot_control_t;

// variable declaration
extern analog_t pots[ANALOG_POT_COUNT];

// function declaration
void analog_init(void);
void analog_update(void);

#endif

