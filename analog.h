// analog.h

#ifndef _ANALOG_h
#define _ANALOG_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

/************************************************************************/
/* TYPE DEFINITIONS                                                     */
/************************************************************************/

typedef struct __analog_t
{
	int pin;	// external pin
	int raw;	// raw value
	int mv;		// scaled voltage (mV)
} analog_t;

typedef enum
{
	POT_CONTROL_RGB_SPEED = 0,
	POT_CONTROL_RGB_VARIETY = 1,
	POT_CONTROl_RGB_BRIGHTNESS = 2
} pot_control_t;



/************************************************************************/
/* FUNCTION DECLARATIONS                                                */
/************************************************************************/

void analog_init(void);
void analog_update(void);
int analog_get_raw(pot_control_t ctrl);
int analog_get_mv(pot_control_t ctrl);

#endif


