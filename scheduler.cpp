// 
// 
// 

#include <string.h>

#include "scheduler.h"

// variable definitions
task_t scheduler[SCHEDULER_SIZE];

#ifndef __task_is_empty
#define __task_is_empty(tp) (tp->func == NULL)
#endif

// function definitions
void scheduler_run(void)
{
	unsigned long tnow = millis();
	task_t *tp = scheduler;

	for (int i = 0; (i < SCHEDULER_SIZE) && (tp->func != NULL); i++, tp++) {
		// if task is not null, and task period elapsed, call function
		if (tnow - tp->ts >= tp->per) {
			tp->func();
			tp->ts = tnow;

			// if flagged for disposal... dispose
			if (tp->flags & TASK_FLAG_DISPOSE) {
				memset((void*)tp, NULL, sizeof(task_t));
			}
		}
	}
}

bool scheduler_add_task_per(fptr_t func, uint16_t per, uint8_t flags)
{
	task_t* tp = NULL;
	int i = 0;

	// if task for function exist, set period and flags, return
	tp = scheduler_get_task(func);
	if (tp != NULL) {
		tp->per = per;
		tp->flags = flags;
		return false;
	}

	// iterate over schedule until an empty task is found
	tp = scheduler;
	for (i = 0; (i < SCHEDULER_SIZE) && (tp->func != NULL); i++, tp++);

	// schedule full, return
	if (i >= SCHEDULER_SIZE) {
		return false;
	}

	tp->func = func;
	tp->per = per;
	tp->flags = flags;
	return true;
}

bool scheduler_add_task_freq(fptr_t func, uint16_t freq, uint8_t flags)
{
	// convert frequency to period, minimum period of 20ms
	int16_t per = 1000 / min(freq, 50);

	return scheduler_add_task_per(func, per);
}

bool scheduler_remove_task(fptr_t func)
{
	task_t *tp = scheduler;

	for (int i = 0; i < SCHEDULER_SIZE; i++, tp++) {
		if (tp->func == func) {
			tp->flags |= TASK_FLAG_DISPOSE;
			return true;
		}
	}

	return false;
}

void scheduler_clear(void)
{
	memset((void*)scheduler, NULL, sizeof(scheduler));
}

// call after removing a task from the scheduler, or periodically depending on scheduler use
void scheduler_justify(void)
{
	task_t *tp0, *tp1;

	for (int i = 0; i < SCHEDULER_SIZE; i++) {
		tp0 = scheduler + i;
		if (__task_is_empty(tp0)) {
			for (int j = 1; (i + j) < SCHEDULER_SIZE; j++) {
				tp1 = tp0 + j;
				if (!__task_is_empty(tp1)) {
					memcpy((void*)tp0, (void*)tp1, sizeof(task_t));
					memset((void*)tp1, NULL, sizeof(task_t));
					break;
				}
			}
		}
	}
}

task_t* scheduler_get_task(fptr_t func)
{
	task_t *tp = scheduler;

	for (int i = 0; i < SCHEDULER_SIZE; i++, tp++) {
		if (tp->func == func) {
			return tp;
		}
	}

	// task for function not found
	return NULL;
}
