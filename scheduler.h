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

typedef enum __task_flag_t
{
	TASK_FLAG_DISPOSE = 0x01	// remove this task from the schedule after next call
} task_flag_t;

// the task structure
typedef struct __task_t
{
	unsigned long ts;	// time since boot task was last run (ms)
	uint16_t per;		// period of task execution (ms)
	uint8_t flags;		// per task program flags
	fptr_t func;		// pointer to task function
} task_t;

// variable declaration(s)
extern task_t scheduler[SCHEDULER_SIZE];

// function declarations(s)
void scheduler_run(void);
bool scheduler_add_task_per(fptr_t func, uint16_t per, uint8_t flags = 0);
bool scheduler_add_task_freq(fptr_t func, uint16_t freq, uint8_t flags = 0);
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

