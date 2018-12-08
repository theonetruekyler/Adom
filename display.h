// display.h

#ifndef _DISPLAY_h
#define _DISPLAY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

/************************************************************************/
/* FUNCTION DECLARATIONS                                                */
/************************************************************************/

void display_init(void);
void display_update(void);
void display_write_int(int i, int place);

#endif


