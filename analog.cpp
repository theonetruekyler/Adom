// 
// 
// 

#include "analog.h"
#include "scheduler.h"
#include "serial_printf.h"

#define POT_CONTROL_RGB_SPEED_PIN A0
//#define POT_CONTROL_RGB_VARIETY_PIN
//#define POT_CONTROL_RGB_BRIGHTNESS_PIN

#define ANALOG_REF EXTERNAL
#define ANALOG_DEBUG 1

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(arr) \
	(sizeof(arr) / sizeof(arr[0]))
#endif

/************************************************************************/
/* VARIABLE DEFINITIONS (LOCAL)                                         */
/************************************************************************/

/* the order of list initialization must follow the pot_control_t enumeration */
analog_t pots[] = {
	{POT_CONTROL_RGB_SPEED_PIN, 0, 0}
};



/************************************************************************/
/* FUNCTION DEFINITIONS (LOCAL)                                         */
/************************************************************************/

float analog_ref_enum_to_float(void)
{
	switch (ANALOG_REF) {
	case EXTERNAL:
		return 3.3;
		break;
	case DEFAULT:
	default:
		return 5.0f;
		break;
	}
}



/************************************************************************/
/* FUNCTION DEFINITIONS (GLOBAL)                                        */
/************************************************************************/

void analog_init(void)
{
	analogReference(ANALOG_REF);

	scheduler_add_task_freq(analog_update, 10);
}

void analog_update(void)
{
	analog_t* ap;

	/* read potentiometers */
	for (int i = 0; i < ARRAY_SIZE(pots); i++) {
		ap = pots + i;
		ap->raw = analogRead(ap->pin);
		ap->mv = map(ap->raw, 0, 1023, 0, (long)(1000 * analog_ref_enum_to_float()));
#if ANALOG_DEBUG
		serial_printf("pot%i: raw %i, mV %i", i, ap->raw, ap->mv);
#endif
	}
}

int analog_get_raw(pot_control_t ctrl)
{
	return pots[ctrl].raw;
}


