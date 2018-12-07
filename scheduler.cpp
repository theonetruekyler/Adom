// 
// 
// 

#include <stdlib.h>
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

task_t* create_task(void_fptr_t func, ulong per, uint8_t options)
{
	task_t *tptr = (task_t*)calloc(1, sizeof(task_t));

	/* heap allocation failure, do nothing forever */
	while (NULL == tptr);

	tptr->func = func;
	tptr->per = per;
	tptr->options = options;

	return tptr;
}

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

	/* clear memory, free memory, decrement task count */
	memset((void*)tptr, NULL, sizeof(task_t));
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

	for (task_t *tptr = head; NULL != tptr; tptr = tptr->next) {
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

task_t* scheduler_add_task_per(void_fptr_t func, ulong per, uint8_t options)
{
	task_t *tptr = NULL;

	/* first node */
	if (NULL == head && NULL == tail) {
		tptr = create_task(func, per, options);
		head = tail = tptr;
		task_count++;
		return tptr;
	}

	/* existing node */
	tptr = scheduler_get_task(func);
	if (NULL != tptr) {
		tptr->per = per;
		tptr->options = options;
		return tptr;
	}

	/* new node */
	for (tptr = head; NULL != tptr->next; tptr = tptr->next);
	tptr->next = create_task(func, per, options);
	tptr->next->prev = tptr;
	tptr = tptr->next;
	tail = tptr;

	task_count++;
	return tptr;
}

task_t* scheduler_add_task_freq(void_fptr_t func, ulong freq, uint8_t options)
{
	/* convert frequency to period, minimum period of 20ms */
	ulong per = 1000 / min(freq, 50);

	return scheduler_add_task_per(func, per, options);
}

task_t* scheduler_one_shot(void_fptr_t func, ulong per)
{
	task_t *tptr = scheduler_add_task_per(func, per);

	/* "func" will be called, and then removed after "per" milliseconds */
	tptr->ts = millis();
	tptr->bit.dispose = 1;

	return tptr;
}

bool scheduler_remove_task(void_fptr_t func)
{
	/* no task to remove */
	if (task_count < 1 || NULL == head) {
		return false;
	}

	for (task_t *tptr = head; NULL != tptr; tptr = tptr->next) {
		if (func == tptr->func ) {
			tptr->bit.dispose = 1;
			return true;
		}
	}

	return false;
}

bool scheduler_remove_task(task_t *tptr)
{
	tptr->bit.dispose = 1;
	return true;
}

task_t* scheduler_get_task(void_fptr_t func)
{
	task_t *tptr = NULL;

	if (task_count < 1 || NULL == head) {
		return tptr;
	}

	for (tptr = head; NULL != tptr; tptr = tptr->next) {
		if (func == tptr->func) {
			break;
		}
	}

	return tptr;
}

ulong scheduler_get_task_count(void)
{
	return task_count;
}


