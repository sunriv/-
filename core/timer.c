/********************************************************
 * Filename: core/timer.c
 *
 * Author: wsyoo, RTOSLab. SNU.
 * 
 * Description: 
 ********************************************************/
#include <core/eos.h>

static eos_counter_t system_timer;

/********************************************************
 * function name:	eos_init_counter
 * description:		Initialize a counter
 * parameters:
 *		counter: a counter structure to set
 *		init_value: initial counter value
 ********************************************************/
int8u_t eos_init_counter(eos_counter_t *counter, int32u_t init_value) {
	counter->tick = init_value;
	counter->alarm_queue = NULL;
	return 0;
}

/********************************************************
 * function name: eos_set_alarm
 * description: set an alarm
 * parameters:
 *		counter: specifying the counter this alarm will use
 *		alarm: an alarm structure to set
 *		timeout: time when this alarm expires
 *		entry: pointer to the handler which will be invoked when this alarm expires
 *		arg: pointer to the parameters for the handler
 ********************************************************/
void eos_set_alarm(eos_counter_t* counter, eos_alarm_t* alarm, int32u_t timeout, void (*entry)(void *arg), void *arg) {
/* _HIDE_IMPLEMENTATION_START_ */
	/* Remove the alarm from the counter*/
	_os_remove_node(&counter->alarm_queue, &alarm->alarm_queue_node);

	/* Remove only when timeout is 0 or entry is NULL */
	if (timeout == 0 || entry == NULL) return ;

	/* Set alarm structure fields */
	alarm->timeout = timeout + counter->tick;
	alarm->handler = entry;
	alarm->arg = arg;
	alarm->alarm_queue_node.ptr_data = (void*)alarm;
	alarm->alarm_queue_node.priority = alarm->timeout;

	/* Add the alarm to the counter */
	_os_add_node_priority(&counter->alarm_queue, &alarm->alarm_queue_node);
/* _HIDE_IMPLEMENTATION_END_ */
}

/********************************************************
 * function name: eos_get_system_timer
 * description: get the system timer
 * return value: pointer to the system timer
 ********************************************************/
eos_counter_t* eos_get_system_timer() {
	return &system_timer;
}

/********************************************************
 * function name: eos_trigger_counter
 * description: increase a counter and wake up expired alrams
 * parameters:
 *		counter: counter to increase
 ********************************************************/
void eos_trigger_counter(eos_counter_t* counter) {
/* _HIDE_IMPLEMENTATION_START_ */
	/* increase the counter */
	counter->tick++;
	if (counter == &system_timer) {
		PRINT("system clock: %d\n", counter->tick);
	}

	eos_alarm_t *alarm;
	if (counter->alarm_queue) {
		alarm = (eos_alarm_t*)counter->alarm_queue->ptr_data;
		while (alarm) {
			if (alarm->timeout > counter->tick) break;

			_os_remove_node(&counter->alarm_queue, &alarm->alarm_queue_node);

			alarm->handler(alarm->arg);		// invoke alarm handler

			if (counter->alarm_queue) {
				alarm = (eos_alarm_t*)counter->alarm_queue->ptr_data;
			} else {
				alarm = NULL;
			}
		}
	}
/* _HIDE_IMPLEMENTATION_END_ */
}

/* Timer interrupt handler */
static void timer_interrupt_handler(int8s_t irqnum, void *arg) {
	/* check alarms */
	eos_trigger_counter(&system_timer);
}

void _os_init_timer() {
	eos_init_counter(&system_timer, 0);

	/* register timer interrupt handler */
	eos_set_interrupt_handler(IRQ_INTERVAL_TIMER0, timer_interrupt_handler, NULL);
}
