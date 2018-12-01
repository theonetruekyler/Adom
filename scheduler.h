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

typedef struct __task_bit_t
{
	uint8_t dispose	: 1;	// remove this task after the next time its function is called
	uint8_t pause	: 1;	// do not call this task's function, but do not remove task from scheduler
} task_bit_t;

// the task structure
typedef struct __task_t
{
	union {
		task_bit_t bit;
		uint8_t flags;
	};
	unsigned long ts;	// time since boot task was last run (ms)
	uint16_t per;		// period of task execution (ms)
	fptr_t func;		// pointer to task function
} task_t;

// variable declaration(s)
extern task_t scheduler[SCHEDULER_SIZE];

// function declarations(s)
void scheduler_run(void);
task_t* scheduler_add_task_per(fptr_t func, uint16_t per, uint8_t flags = 0);
task_t* scheduler_add_task_freq(fptr_t func, uint16_t freq, uint8_t flags = 0);
bool scheduler_remove_task(fptr_t func);
void scheduler_clear(void);
void scheduler_justify(void);

task_t* scheduler_get_task(fptr_t func);

// alias for scheduler_clear for syntactical tidiness 
#ifndef scheduler_init
#define scheduler_init() \
	scheduler_clear();
#endif

#endif

