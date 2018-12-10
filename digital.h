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

/* rotary encoder */
typedef struct __encoder_t
{
	digital_t dig[2];
	uint8_t value;
} encoder_t;

/* push button */
typedef digital_t button_t;

/* button status, bit set if pressed */
typedef union __button_status_t
{
	struct {
		uint8_t button0 : 1;
		uint8_t button1 : 1;
		uint8_t button2 : 1;
	} bit;
	uint8_t pressed;
} button_status_t;



/************************************************************************/
/* VARIABLE DECLARATIONS                                                */
/************************************************************************/

extern button_status_t button_status;



/************************************************************************/
/* FUNCTION DECLARATIONS                                                */
/************************************************************************/

void digital_init(void);

#endif


