// 
// 
// 

#include <string.h>

#include "scheduler.h"

/************************************************************************/
/* VARIABLE DEFINITIONS (LOCAL)                                         */
/************************************************************************/

task_t* head = NULL;
task_t* tail = NULL;
size_t task_count = 0;

/************************************************************************/
/* FUNCTION DEFINITIONS (LOCAL)                                         */
/************************************************************************/

void remove_task(task_t *tptr)
{
	/* null check */
	if (NULL == tptr) {
		return;
	}

	/* remove head */
	if (head == tptr && NULL != tptr->next) {
		head = tptr->next;
		tptr->next->prev = NULL;
	}
	/* remove tail*/
	else if (tail == tptr && NULL != tptr->prev) {
		tail = tptr->prev;
		tptr->prev->next = NULL;
	}
	/* remove normal node */
	else {
		tptr->next->prev = tptr->prev;
		tptr->prev->next = tptr->next;
	}

	/* free memory, decrement task count */
	free((void*)tptr);
	task_count--;
}

/************************************************************************/
/* FUNCTION DEFINITIONS (GLOBAL)                                        */
/************************************************************************/

void scheduler_run(void)
{
	/* no task to run */
	if (task_count < 1 || NULL == head) {
		return;
	}

	ulong now = millis();

	for (task_t *tptr = head; NULL != tptr->next; tptr = tptr->next) {
		if (tptr->bit.pause) {
			continue;
		}
		if (now - tptr->ts >= tptr->per) {
			tptr->func();
			tptr->ts = now;
			if (tptr->bit.dispose) {
				remove_task(tptr);
			}
		}
	}
}

task_t* scheduler_add_task_per(task_fptr_t func, uint16_t per, uint8_t flags)
{
	task_t* tp = NULL;
	int i = 0;

	// if task for function exist, set period and flags
	tp = scheduler_get_task(func);
	if (tp != NULL) {
		tp->per = per;
		tp->flags = flags;
		return tp;
	}

	// iterate over schedule until an empty task is found
	tp = scheduler;
	for (i = 0; (i < SCHEDULER_SIZE) && (tp->func != NULL); i++, tp++);

	// schedule full, return
	if (i >= SCHEDULER_SIZE) {
		return NULL;
	}

	tp->func = func;
	tp->per = per;
	tp->flags = flags;
	return tp;
}

task_t* scheduler_add_task_freq(task_fptr_t func, uint16_t freq, uint8_t flags)
{
	// convert frequency to period, minimum period of 20ms
	int16_t per = 1000 / min(freq, 50);

	return scheduler_add_task_per(func, per);
}

bool scheduler_remove_task(void_fptr_t func)
{
	/* no task to remove */
	if (task_count < 1 || NULL == head) {
		return false;
	}

	for (task_t *tptr = head; NULL != tptr->next; tptr = tptr->next) {
		if (func == tptr->func ) {
			tptr->bit.dispose = 1;
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

task_t* scheduler_get_task(task_fptr_t func)
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
