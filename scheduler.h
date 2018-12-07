// scheduler.h

#ifndef _SCHEDULER_h
#define _SCHEDULER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

/************************************************************************/
/* TYPE DEFINITIONS                                                     */
/************************************************************************/

/* syntactical convenience */
typedef unsigned long ulong;

/* pointer to scheduled function */
typedef void(*void_fptr_t)(void);

/* flags that define special beahvior */
typedef struct __task_bit_t
{
	uint8_t dispose	: 1;
	uint8_t pause	: 1;
} task_bit_t;

/* structure of task node in list */
typedef struct __task_t
{
	union {
		task_bit_t bit;
		uint8_t options;
	};
	ulong ts;
	ulong per;
	void_fptr_t func;
	struct __task_t *next;
	struct __task_t *prev;
} task_t;

/************************************************************************/
/* FUNCTION DECLARATIONS                                                */
/************************************************************************/

void scheduler_run(void);
task_t* scheduler_add_task_per(void_fptr_t func, ulong per, uint8_t options = 0);
task_t* scheduler_add_task_freq(void_fptr_t func, ulong freq, uint8_t options = 0);
bool scheduler_remove_task(void_fptr_t func);
bool scheduler_remove_task(task_t *tptr);
task_t* scheduler_get_task(void_fptr_t func);
ulong scheduler_get_task_count(void);

#endif


