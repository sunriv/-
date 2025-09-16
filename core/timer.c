/********************************************************
 * Filename: core/timer.c
 *
 * Author: Jiyong Park, RTOSLab. SNU
 * Modified by: Seongsoo Hong on 03/30/24
 *
 * Description: User interface for handling interrupts
 ********************************************************/

#include "eos.h"
#include "irq.h"

static eos_counter_t system_timer;

int8u_t eos_init_counter(eos_counter_t *counter, int32u_t init_value)
{
    counter->tick = init_value;
    counter->alarm_queue = NULL;

    return 0;
}

void eos_set_alarm(eos_counter_t *counter, eos_alarm_t *alarm, int32u_t timeout, void (*entry)(void *arg), void *arg)
{
    _os_remove_node(&(counter->alarm_queue), &(alarm->alarm_queue_node));
    if (timeout == 0 || entry == NULL)
        return;
    alarm->alarm_queue_node.priority = timeout;
    alarm->handler = entry;
    alarm->arg = arg;
    if (timeout > counter->tick)
        _os_add_node_priority(&(counter->alarm_queue), &(alarm->alarm_queue_node));
}

eos_counter_t *eos_get_system_timer()
{
    return &system_timer;
}

void eos_trigger_counter(eos_counter_t *counter)
{
    counter->tick++;
    PRINT("tick\n");
    while (counter->alarm_queue != NULL)
    {
        _os_node_t *next_node = counter->alarm_queue;
        eos_tcb_t *next_task = (eos_tcb_t *)(next_node->ptr_data);
        if (next_node->priority > counter->tick)
            break;
        eos_set_alarm(eos_get_system_timer(), next_task->alarm, 0, NULL, NULL);
        next_task->alarm->handler(next_task);
    }

    eos_schedule();
}

/* Timer interrupt handler */
static void timer_interrupt_handler(int8s_t irqnum, void *arg)
{
    /* Triggers alarms */
    eos_trigger_counter(&system_timer);
}

void _os_init_timer()
{
    eos_init_counter(&system_timer, 0);

    /* Registers timer interrupt handler */
    eos_set_interrupt_handler(IRQ_INTERVAL_TIMER0,
                              timer_interrupt_handler, NULL);
}
