// 
// 
// 

#include "analog.h"
#include "scheduler.h"
#include "serial_printf.h"

#define POT_RGB_SPEED_PIN A0

#define ANALOG_REF EXTERNAL
#define ANALOG_DEBUG 1

// varaiable definitions
analog_t pots[] = {
	{POT_RGB_SPEED_PIN, 0, 0}
};

// function definitions
void analog_init(void)
{
	analogReference(ANALOG_REF);

	scheduler_add_task_freq(analog_update, 25);
}

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

void analog_update(void)
{
	analog_t* ap;

	// read potentiometers
	for (int i = 0; i < POTENTIOMETER_COUNT; i++) {
		ap = pots + i;
		ap->raw = analogRead(POT_RGB_SPEED_PIN);
		ap->mv = map(ap->raw, 0, 1023, 0, (long)(1000 * analog_ref_enum_to_float()));
#if ANALOG_DEBUG
		serial_printf("pot%i: raw %i, mV %i", i, ap->raw, ap->mv);
#endif
	}
}