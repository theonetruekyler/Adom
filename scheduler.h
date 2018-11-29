// scheduler.h

#ifndef _SCHEDULER_h
#define _SCHEDULER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

// maximum quantity of schedule-able tasks
#define SCHEDULER_SIZE 16

// function pointer for tasks, which accept no arguments and return void
typedef void(*fptr_t)(void);

// the task structure
typedef struct __task_t
{
	unsigned long ts;	// time since boot task was last run (ms)
	uint16_t per;		// period of task execution (ms)
	fptr_t func;		// pointer to task function
} task_t;

// variable declaration(s)
extern task_t scheduler[SCHEDULER_SIZE];

// function declarations(s)
void scheduler_run(void);
void scheduler_add_task_per(fptr_t func, uint16_t per);
void scheduler_add_task_freq(fptr_t func, uint16_t freq);
void scheduler_clear(void);

// alias for scheduler_clear for syntactical tidiness 
#ifndef scheduler_init
#define scheduler_init() \
	scheduler_clear();
#endif

#endif

