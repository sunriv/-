/********************************************************
 * Filename: core/sync.c
 * 
 * Author: wsyoo, RTOSLab. SNU.
 * 
 * Description: semaphore, condition variable management.
 ********************************************************/
#include <core/eos.h>

/********************************************************
 * function name: eos_init_semaphore
 * description: initialize a semaphore structure
 * parameters:
 *		sem: pointer to the semaphore structure
 *		initial_count: number of resources
 *		queue_type: type of the wait queue (0: FIFO, 1: priority)
 ********************************************************/
void eos_init_semaphore(eos_semaphore_t *sem, int32u_t initial_count, int8u_t queue_type) {
/* _HIDE_IMPLEMENTATION_START_ */
	/* initialization */
	sem->count = initial_count;
	sem->wait_queue = NULL;
	sem->queue_type = queue_type;
/* _HIDE_IMPLEMENTATION_END_ */
}

/********************************************************
 * function name: eos_acquire_semaphore
 * description: try to acquire a semaphore
 * parameters:
 *		sem: pointer to the semaphore structure to acquire
 *		timeout: waiting time when no resource is available
 *			less than 0: return immediately
 *			0: wait undefinitely
 *			more than 0: wait for the specified time
 * return value:
 *		1: succeeded to acquire the semaphore
 *		0: failed to acquire the semaphore
 ********************************************************/
int32u_t eos_acquire_semaphore(eos_semaphore_t *sem, int32s_t timeout) {
/* _HIDE_IMPLEMENTATION_START_ */
	/* check whether scheduler is locked */
	if (eos_get_scheduler_lock()) {
		PRINT("scheduler is locked. sem acquire failed.\n");
		return 0;
	}

	/* store the current system tick value */
	int32u_t start_tick = eos_get_system_timer()->tick;

	int32u_t flag = eos_disable_interrupt();
	if (sem->count <= 0) {
		/* you can't acquire semaphore right now. */
		if (timeout < 0) {
			eos_restore_interrupt(flag);
			return 0;
		}
		eos_set_alarm(eos_get_system_timer(), &eos_get_current_task()->alarm, (int32u_t)timeout, _os_wakeup_task, eos_get_current_task());
		do {
			eos_restore_interrupt(flag);
			_os_wait(&sem->wait_queue, sem->queue_type);

			if ( timeout != 0 && start_tick+(int32u_t)timeout <= eos_get_system_timer()->tick) { 
				/* the task is waken up by alarm */
				return 0;
			}
			flag = eos_disable_interrupt();
		} while (sem->count <= 0);
		/* remove the alarm (the task is waken up by another task) */
		eos_set_alarm(eos_get_system_timer(), &eos_get_current_task()->alarm, 0, NULL, NULL);
	}
	sem->count--;
	eos_restore_interrupt(flag);
	
/* _HIDE_IMPLEMENTATION_END_ */
	return 1;
}

/********************************************************
 * function name: eos_release_semaphore
 * description: try to release a semaphore
 * parameters:
 *		sem: pointer to the semaphore structure to release
 ********************************************************/
void eos_release_semaphore(eos_semaphore_t *sem) {
/* _HIDE_IMPLEMENTATION_START_ */
	int32u_t flag = eos_disable_interrupt();
	sem->count++;
	eos_restore_interrupt(flag);
	if(sem->wait_queue) {
		/* select a task waiting for this semaphore */
		_os_wakeup_queue(&sem->wait_queue);
	}
/* _HIDE_IMPLEMENTATION_END_ */
}

/********************************************************
 * function name: eos_init_condition
 * description: initialize a condition variable structure
 * parameters:
 *		cond: pointer to the condition variable structure
 *		queue_type: type of the wait queue (0:FIFO, 1:priority)
 ********************************************************/
void eos_init_condition(eos_condition_t *cond, int32u_t queue_type) {
	/* initialization */
	cond->wait_queue = NULL;
	cond->queue_type = queue_type;
}

/********************************************************
 * function name: eos_wait_condition
 * description: wait until the condition is fulfilled
 * parameters:
 *		cond: pointer to the condition variable structure to wait
 *		mutex: pointer to the semaphore structure used to pretect condition variable
 ********************************************************/
void eos_wait_condition(eos_condition_t *cond, eos_semaphore_t *mutex) {
	/* check whether scheduler is locked */
	if (eos_get_scheduler_lock()) {
		PRINT("scheduler is locked. condition wait failed.\n");
		return 0;
	}

	/* release acquired semaphore */
	eos_release_semaphore(mutex);
	/* wait on condition's wait_queue */
	_os_wait(&cond->wait_queue, cond->queue_type);
	/* acquire semaphore before return */
	eos_acquire_semaphore(mutex, 0);
}

/********************************************************
 * function name: eos_notify_condition
 * description: notify that the condition is fulfilled
 * parameters:
 *		cond: pointer to the condition variable structure to notify
 ********************************************************/
void eos_notify_condition(eos_condition_t *cond) {
	/* select a task that is waiting on this wait_queue */
	_os_wakeup_queue(&cond->wait_queue);
}

int8u_t eos_lock_scheduler() {
	int32u_t flag = eos_disable_interrupt();
	int8u_t temp = _os_scheduler_lock;
	_os_scheduler_lock = SCHEDULER_LOCKED;
	eos_restore_interrupt(flag);
	return temp;
}

void eos_restore_scheduler(int8u_t scheduler_state) {
	int32u_t flag = eos_disable_interrupt();
	_os_scheduler_lock = scheduler_state;
	eos_restore_interrupt(flag);
	_os_schedule();
}

int8u_t eos_get_scheduler_lock() {
	return _os_scheduler_lock;
}
