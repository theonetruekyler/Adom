// temperature_control.h

#ifndef _TEMPERATURE_CONTROL_h
#define _TEMPERATURE_CONTROL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#endif

/************************************************************************/
/* VARIABLE DECLARATIONS                                                */
/************************************************************************/

extern double set_point;



/************************************************************************/
/* FUNCTION DECLARATIONS                                                */
/************************************************************************/

void temp_ctrl_init(void);
void temp_ctrl_update(void);