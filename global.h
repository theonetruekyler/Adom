// global.h

#ifndef _GLOBAL_h
#define _GLOBAL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

typedef struct __g_flags_t
{
	union {
		uint8_t set_temp : 1;
		uint8_t set_shot : 1;
	} bit;
	uint8_t actions;
} g_flags_t;

extern volatile g_flags_t g_flags;

#endif

