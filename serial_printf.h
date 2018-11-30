// serial_printf.h

#ifndef _NICE_PRINT_h
#define _NICE_PRINT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


static inline void serial_printf(const char* fmt, ...)
{
	char str[64];

	va_list args;
	va_start(args, fmt);
	vsprintf(str, fmt, args);
	va_end(args);

	Serial.println((const char*)str);
}

#endif

