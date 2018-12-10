// digital.h

#ifndef _DIGITAL_h
#define _DIGITAL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

/************************************************************************/
/* TYPE DEFINITIONS                                                     */
/************************************************************************/

typedef struct __digital_t
{
	int pin;
	bool state;
} digital_t;

/* push button */
typedef digital_t button_t;

/* rotary encoder */
typedef struct __encoder_t
{
	digital_t dig[2];
	uint8_t value;
} encoder_t;



/************************************************************************/
/* FUNCTION DECLARATIONS                                                */
/************************************************************************/

void digital_init(void);

#endif


