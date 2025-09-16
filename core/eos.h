/********************************************************
 * Filename: core/eos.h
 *
 * Author: Jiyong Park, RTOSLab. SNU
 * Modified by: Seongsoo Hong on 03/27/24
 *
 * Description: Header for eOS
 ********************************************************/

#ifndef EOS_H
#define EOS_H

#include "eos_internal.h"

/********************************************************
 * Debugging module
 ********************************************************/

void eos_printf(const char *fmt, ...);

#define PRINT(format, a...)                             \
    eos_printf("[%15s:%30s] ", __FILE__, __FUNCTION__); \
    eos_printf(format, ##a);

#define READY 1
#define RUNNING 2
#define WAITING 3
#define SUSPENDED 4

/**
 * Runqueue of ready tasks
 */
static _os_node_t *_os_ready_queue[LOWEST_PRIORITY + 1];

/********************************************************
 * Hardware abstraction module
 ********************************************************/

/**
 * Returns irq number currently being serviced
 * -1 means no irq is being serviced
 */
int32s_t hal_get_irq(void);

/**
 * Acknowledges the given irq
 */
void hal_ack_irq(int32u_t irq);

/**
 * Enables interrupt service globally
 * Compared to the _os_interrupt_enable() function,
 * this fuction always enables interrupt
 */
void hal_enable_interrupt(void);

/**
 * Disables interrupt service globally
 * This function returns status of previous interrupt flag
 */
int32u_t hal_disable_interrupt(void);

/**
 * Enables interrupt service globally based on the flag
 */
void hal_restore_interrupt(int32u_t flag);

/**
 * Enables specific irq line
 */
void hal_enable_irq_line(int32u_t irq);

/**
 * Disables specific irq line
 */
void hal_disable_irq_line(int32u_t irq);

/********************************************************
 * Interrupt management module
 ********************************************************/

/**
 * Interrupt handler types
 */
typedef void (*eos_interrupt_handler_t)(int8s_t irq_num, void *arg);

/*
 * Registers interrupt handler with given irq number
 *     irqnum: irq number to install handler for
 *     handler: pointer to the function that will handle the interrupt
 *              NULL for unregistering handler
 *     arg: argument to be delivered to the handler
 *              when interrupt occurrs
 */
int8s_t eos_set_interrupt_handler(int8s_t irqnum,
                                  eos_interrupt_handler_t handler, void *arg);

/* Returns interrupt handler installed for irqnum */
eos_interrupt_handler_t eos_get_interrupt_handler(int8s_t irqnum);

/********************************************************
 * Timer management module
 ********************************************************/

typedef struct eos_counter
{
    int32u_t tick;
    _os_node_t *alarm_queue;
} eos_counter_t;

typedef struct eos_alarm
{
    int32u_t timeout;
    void (*handler)(void *arg);
    void *arg;
    _os_node_t alarm_queue_node;
} eos_alarm_t;

int8u_t eos_init_counter(eos_counter_t *counter, int32u_t init_value);

void eos_set_alarm(eos_counter_t *counter, eos_alarm_t *alarm,
                   int32u_t timeout, void (*entry)(void *arg), void *arg);

eos_counter_t *eos_get_system_timer();

void eos_trigger_counter(eos_counter_t *counter);

/********************************************************
 * Wait queue types
 * 	for semaphores, condition variables, message queues
 ********************************************************/

#define FIFO 0
#define PRIORITY 1

/********************************************************
 * Synchronization module
 ********************************************************/

/**
 * Semaphore structure
 */
typedef struct eos_semaphore
{
    int32s_t count;
    _os_node_t *wait_queue;
    int8u_t queue_type;

} eos_semaphore_t;

/**
 * User must allocate memory for the semaphore structure
 * before calling this function
 */
void eos_init_semaphore(eos_semaphore_t *sem, int32u_t initial_count, int8u_t queue_type);

/**
 * Tries to acquire semaphore
 */
int32u_t eos_acquire_semaphore(eos_semaphore_t *sem, int32s_t timeout);

/**
 * Releases semaphore
 */
void eos_release_semaphore(eos_semaphore_t *sem);

/**
 * Condition variable structure
 */
typedef struct eos_condition
{
    _os_node_t *wait_queue;
    int8u_t queue_type;
} eos_condition_t;

/**
 * User must allocate memory for the semaphore structure
 * before calling this function
 */
void eos_init_condition(eos_condition_t *cond, int32u_t queue_type);

/**
 * Puts the running task into the wait queue
 */
void eos_wait_condition(eos_condition_t *cond, eos_semaphore_t *mutex);

/**
 * Moves a task from wait_queue to ready_queue to wake it up
 */
void eos_notify_condition(eos_condition_t *cond);

extern int8u_t eos_lock_scheduler();
extern void eos_restore_scheduler(int8u_t lock);
extern int8u_t eos_get_scheduler_lock();

/********************************************************
 * Message queue module
 ********************************************************/

/**
 * Message queue structure
 */
typedef struct eos_mqueue
{
    int16u_t queue_size;
    int8u_t msg_size;
    void *queue_start;
    void *front;
    void *rear;
    int8u_t queue_type;
    eos_semaphore_t *putsem;
    eos_semaphore_t *getsem;
} eos_mqueue_t;

/**
 * User must allocate memory for the message queue structure
 * before calling this function
 */
void eos_init_mqueue(eos_mqueue_t *mq, void *queue_start, int16u_t queue_size, int8u_t msg_size, int8u_t queue_type);

/**
 * Tries to send a message
 */
int8u_t eos_send_message(eos_mqueue_t *mq, void *message, int32s_t timeout);

/**
 * Tries to recieve a message
 */
int8u_t eos_receive_message(eos_mqueue_t *mq, void *message, int32s_t timeout);

/********************************************************
 * Task management module
 ********************************************************/

/* TCB (task control block) structure */
typedef struct tcb
{
    int32u_t state;
    int32u_t priority;
    addr_t stack_pointer;
    addr_t stack_start;
    int32u_t stack_size;

    int32u_t period;
    int32u_t sleep_at;

    void (*entry)(void *);
    void *arg;

    _os_node_t *queueing_node;
    eos_alarm_t alarm;
} eos_tcb_t;

/**
 * User must allocate memory for tcb structure
 * before calling this function
 */
int32u_t eos_create_task(eos_tcb_t *task, addr_t sblock_start,
                         size_t sblock_size, void (*entry)(void *arg),
                         void *arg, int32u_t priority);

int32u_t eos_destroy_task(eos_tcb_t *task);

void eos_schedule();

void restore_and_erase_new_node(_os_node_t *new_current_node, int32u_t priority);

eos_tcb_t *eos_get_current_task();

/**
 * Sets priority of the specified task
 *     task: tcb of the task
 *     priority: new priority
 */
void eos_change_priority(eos_tcb_t *task, int32u_t priority);

/**
 * Returns priority of the specified task
 *     task: tcb of the task
 */
int32u_t eos_get_priority(eos_tcb_t *task);

/**
 * Sets period of the specified task.
 *     task: tcb of the task
 *     period: period of the task in tick unit
 *         period being 0 means that the task is aperiodic
 */
void eos_set_period(eos_tcb_t *task, int32u_t period);

int32u_t eos_get_period(eos_tcb_t *task);

int32u_t eos_suspend_task(eos_tcb_t *task);

int32u_t eos_resume_task(eos_tcb_t *task);

void eos_sleep(int32u_t tick);
void _eos_sleep(int32u_t tick, _os_node_t **wait_queue);
void _current_task_to_wait_queue(_os_node_t **wait_queue);

#endif /*EOS_H*/
