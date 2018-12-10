// leds.h

#ifndef _LEDS_h
#define _LEDS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "scheduler.h"

/************************************************************************/
/* VARIABLE DECLARATIONS                                                */
/************************************************************************/

extern task_t *leds_task_ptr;

/************************************************************************/
/* FUNCTION DECLARATIONS                                                */
/************************************************************************/

void leds_init(void);
void leds_update(void);

#endif


