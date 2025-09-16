/********************************************************
 * Filename: core/task.c
 * 
 * Author: parkjy, RTOSLab. SNU.
 * 
 * Description: task management.
 ********************************************************/
#include <core/eos.h>

#define READY		1
#define RUNNING		2
#define WAITING		3
#define SUSPENDED	4

/*
 * Queue (list) of tasks that are ready to run.
 */
static _os_node_t *_os_ready_queue[LOWEST_PRIORITY + 1];

/*
 * Pointer to TCB of running task
 */
static eos_tcb_t *_os_current_task;

/********************************************************
 * function name: eos_create_task
 * description: create a task (initialize a tcb struncture)
 * parameters:
 *		*task: task to be initialized
 *		sblock_start: low address of the stack region
 *		sblock_size: size of the stack region
 *		entry: pointer to the entry point of the task
 *		arg: pointer to the arguments to be passed to entry function
 *		priority: the priority of the new task
 ********************************************************/
int32u_t eos_create_task(eos_tcb_t *task, addr_t sblock_start, size_t sblock_size, void (*entry)(void *arg), void *arg, int32u_t priority) {
	PRINT("task: 0x%x, priority: %d\n", (int32u_t)task, priority);
/* _HIDE_IMPLEMENTATION_START_ */
	/* initialize priority */
	task->priority = priority;

	/* initialize period */
	task->period = 0;
	task->next_period = 0;

	/* initialize list related fields */
	task->queue_node.ptr_data = task;
	task->queue_node.priority = task->priority;

	/* create context of this tcb and record the location of the context in the tcb */
	task->sp = _os_create_context(sblock_start, sblock_size, entry, arg);

	/* insert this tcb into ready queue */
	_os_add_node_tail(&_os_ready_queue[task->priority], &(task->queue_node));
	_os_set_ready(task->priority);
	task->status = READY;

	_os_schedule();
/* _HIDE_IMPLEMENTATION_END_ */
	return 0;
}

/********************************************************
 * function name: eos_destroy_task
 * description: make a task being not used anymore
 * parameters:
 *		*task: task to be used no more
 ********************************************************/
int32u_t eos_destroy_task(eos_tcb_t *task) {
	return 0;
}

/********************************************************
 * function name: eos_get_current_task
 * description: get the currently running task
 * return value: pointer to the tcb of the currently running task
 ********************************************************/
eos_tcb_t *eos_get_current_task() {
	return _os_current_task;
}

/********************************************************
 * function name: eos_change_priority
 * description: change the priority of a task
 * parameters:
 *		task: task of which the priority is to be changed
 *		priority: the priority of the task
 ********************************************************/
void eos_change_priority(eos_tcb_t *task, int32u_t priority) {
/* _HIDE_IMPLEMENTATION_START_ */
	/* if task is READY, update bitmap and ready_queue */
	if (task->status == READY) {
		_os_remove_node(&_os_ready_queue[task->priority], &(task->queue_node));
		if (!_os_ready_queue[task->priority])
			_os_unset_ready(task->priority);

		_os_add_node_tail(&_os_ready_queue[priority], &(task->queue_node));
		_os_set_ready(priority);
	}

	/* change the tcb */
	task->priority = priority;
	task->queue_node.priority = task->priority;
	
	/* schedule with new priority set */
	_os_schedule();
/* _HIDE_IMPLEMENTATION_END_ */
}

/********************************************************
 * function name: eos_get_priority
 * description: get the priority of a task
 * parameters:
 *		task: task of which the priority is to be got
 * return value: the priority of the task
 ********************************************************/
int32u_t eos_get_priority(eos_tcb_t *task) {
	return task->priority;
}
/********************************************************
 * function name: eos_set_period
 * description: set the period of a task
 * parameters:
 *		task: task of which the period is to be set
 *		period: the period of the task
 ********************************************************/
void eos_set_period(eos_tcb_t *task, int32u_t period){
/* _HIDE_IMPLEMENTATION_START_ */
	/* set period and next_period */
	task->period = period;
	task->next_period = eos_get_system_timer()->tick;
/* _HIDE_IMPLEMENTATION_END_ */
}

/********************************************************
 * function name: eos_get_period
 * description: get the period of a task
 * parameters:
 *		task: task of which the period is to be got
 * return value: the period of the task
 ********************************************************/
int32u_t eos_get_period(eos_tcb_t *task) {
	return task->period;
}

/********************************************************
 * function name: eos_suspend_task
 * description: suspend a task
 * parameters:
 *		task: task to be suspended
 ********************************************************/
int32u_t eos_suspend_task(eos_tcb_t *task) {
	if (task->status == READY) {
		_os_remove_node(&_os_ready_queue[task->priority], &(task->queue_node));
		if (!_os_ready_queue[task->priority])
			_os_unset_ready(task->priority);
		task->status = SUSPENDED;
	}
	return 0;
}

/********************************************************
 * function name: eos_resume_task
 * description: resume a suspended task
 * parameters:
 *		task: suspended task
 ********************************************************/
int32u_t eos_resume_task(eos_tcb_t *task) {
	if (task->status == SUSPENDED) {
		_os_add_node_tail(&_os_ready_queue[task->priority], &(task->queue_node));
		_os_set_ready(task->priority);
		task->status = READY;
		_os_schedule();
	}
	return 0;
}

/********************************************************
 * function name: eos_sleep
 * description: sleep for a specified time
 * parameters:
 *		tick:
 *			more than 0: time the task is to sleep
 *			0: wait for a period (for periodic tasks)
 *			   wait undefinitely (for non-periodic tasks)
 ********************************************************/
void eos_sleep(int32u_t tick) {
/* _HIDE_IMPLEMENTATION_START_ */
	/* check whether scheduler is locked */
	if (eos_get_scheduler_lock()) {
		PRINT("scheduler is locked. can't sleep.\n");
		return;
	}

	int32u_t timeout = tick;
	
	if (tick == 0) {
		if(_os_current_task->period != 0) {
			/* if periodic task, wait for next period when tick is 0 */
			_os_current_task->next_period += _os_current_task->period;
			if (_os_current_task->next_period <= eos_get_system_timer()->tick) {
				PRINT("There exist queued jobs, so execute them.\n");
				return;
			}
			timeout = _os_current_task->next_period - eos_get_system_timer()->tick;
		}
	} 
	eos_set_alarm(eos_get_system_timer(), &_os_current_task->alarm, timeout, _os_wakeup_task, _os_current_task);

	/* change to WAITING state */
	_os_current_task->status = WAITING;

	/* select one of ready tasks and run it */
	_os_schedule();
/* _HIDE_IMPLEMENTATION_END_ */
}

/********************************************************
 * function name: _os_init_task
 * description: initialize task management module
 ********************************************************/
void _os_init_task() {
	PRINT("initializing task module.\n");

	/* init current_task */
	_os_current_task = NULL;

	/* init multi-level ready_queue */
	int32u_t i;
	for (i = 0; i < LOWEST_PRIORITY; i++) {
		_os_ready_queue[i] = NULL;
	}
}

/********************************************************
 * function name: _os_schedule
 * description: switch to the task with the highest priority
 ********************************************************/
void _os_schedule() {
/* _HIDE_IMPLEMENTATION_START_ */
	/* check if the scheduler is locked */
	int32u_t flag = eos_disable_interrupt();
	if (_os_scheduler_lock == SCHEDULER_LOCKED) {
		eos_restore_interrupt(flag);
		return;
	}
	eos_restore_interrupt(flag);

	if (_os_current_task) {
		if (_os_current_task->status == RUNNING) {
			/* insert running task into ready queue */
			_os_add_node_tail(&_os_ready_queue[_os_current_task->priority], &(_os_current_task->queue_node));
			_os_set_ready(_os_current_task->priority);
			_os_current_task->status = READY;
		}

		/* save current context into stack. */
		addr_t sp = _os_save_context();
		if (!sp) return;

		/* save stack pointer in the tcb */
		_os_current_task->sp = sp;
	}

	/* select next task to run */
	int32u_t highest_priority = _os_get_highest_priority();
	eos_tcb_t *next_task = (eos_tcb_t*)(_os_ready_queue[highest_priority]->ptr_data);

	/* remove the selected task from ready queue */
	_os_remove_node(&_os_ready_queue[next_task->priority], &(next_task->queue_node));
	if (!_os_ready_queue[next_task->priority])
		_os_unset_ready(next_task->priority);

	/* restore context of the next task */
	next_task->status = RUNNING;
	_os_current_task = next_task;
	_os_restore_context(next_task->sp);
/* _HIDE_IMPLEMENTATION_END_ */
}

/********************************************************
 * function name: _os_wait
 * description: make the current task to wait
 *				on a specified queue
 * parameters:
 *		wait_queue: wait queue the current task will wait
 *		queue_tpe: 0 - FIFO, 1 - priority
 ********************************************************/
void _os_wait(_os_node_t **wait_queue, int8u_t queue_type) {
	/* add current_task to wait_queue */
	if (!queue_type) {
		_os_add_node_tail(wait_queue, &_os_current_task->queue_node);
	} else {
		_os_add_node_priority(wait_queue, &_os_current_task->queue_node);
	}

	_os_current_task->wait_queue = *wait_queue;

	/* change to WAITING state */
	_os_current_task->status = WAITING;

	/* select one of ready tasks and run it */
	_os_schedule();
}

/********************************************************
 * function name: _os_wakeup_queue
 * description: wake up a task from a specified queue
 *				to make it ready and invoke scheduler
 * parameters:
 *		wait_queue: wait queue a task is to be waken up
 ********************************************************/
void _os_wakeup_queue(_os_node_t **wait_queue) {
	/* check whether the wait queue is empty */
	if(*wait_queue == NULL) return ;

	/* choose a task */
	eos_tcb_t *next_task = (eos_tcb_t*)(*wait_queue)->ptr_data;

	/* remove from the wait queue */
	_os_remove_node(wait_queue, &next_task->queue_node);

	/* make the task ready */
	_os_add_node_tail(&_os_ready_queue[next_task->priority], &next_task->queue_node);
	_os_set_ready(next_task->priority);
	next_task->status = READY;

	_os_schedule();
}

void _os_wakeup_all(_os_node_t **wait_queue, int32u_t queue_type) {
}

/********************************************************
 * function name: _os_wakeup_task
 * description: wake up a specified task and make it ready
 * parameters:
 *		arg: tcb of the task
 ********************************************************/
void _os_wakeup_task(eos_tcb_t *task) {
	_os_node_t *head = task->wait_queue;
	if (head != NULL) {
		_os_remove_node(&head, &task->queue_node);
	}
	_os_add_node_tail(&_os_ready_queue[task->priority], &(task->queue_node));
	_os_set_ready(task->priority);
	task->status = READY;

	_os_schedule();
}
