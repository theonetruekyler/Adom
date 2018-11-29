// 
// 
// 

#include <string.h>

#include "scheduler.h"

// variable definitions
task_t scheduler[SCHEDULER_SIZE];

// function definitions
void scheduler_run(void)
{
	unsigned long tnow = millis();
	task_t *tptr = scheduler;

	for (int i = 0; i < SCHEDULER_SIZE && tptr->func != NULL; i++) {
		if (tnow - tptr->ts >= tptr->per) {
			tptr->func();
			tptr->ts = tnow;
		}
		tptr++;
	}
}

void scheduler_add_task_per(fptr_t func, uint16_t per)
{
	task_t* tptr = scheduler;

	int i;
	for (i = 0; i < SCHEDULER_SIZE && tptr->func != NULL; i++) {
		tptr++;
	}

	if (i >= SCHEDULER_SIZE) {
		// scheduler full, return without adding task
		return;
	}

	tptr->func = func;
	tptr->per = per;
}

void scheduler_add_task_freq(fptr_t func, uint16_t freq)
{
	int16_t per = 1000 / min(freq, 50);

	scheduler_add_task_per(func, per);
}

void scheduler_clear(void)
{
	memset((void*)scheduler, NULL, sizeof(scheduler));
}


