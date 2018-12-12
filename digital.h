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
	digital_t dig_a;
	digital_t dig_b;
	uint16_t value;
} encoder_t;



/************************************************************************/
/* VARIABLE DECLARATIONS                                                */
/************************************************************************/

extern volatile int digital_temp_sel;
extern volatile int digital_temp_set;



/************************************************************************/
/* FUNCTION DECLARATIONS                                                */
/************************************************************************/

void digital_init(void);

#endif


