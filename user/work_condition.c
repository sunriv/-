#include <core/eos.h>

#define SOME_VALUE	2

static eos_tcb_t tcb1;
static eos_tcb_t tcb2;
static int8u_t stack1[8096];
static int8u_t stack2[8096];

eos_semaphore_t sem;
eos_condition_t cond;
int32u_t shared_data = 0;

static void task_entry_waiter(void *arg) {
	while (1) {
		PRINT("Thread1: [SEM] acquire semaphore.\n");
		eos_acquire_semaphore(&sem, 0);
		PRINT("Thread1: [SEM] acquire success.\n");
		while (shared_data != SOME_VALUE) {
			PRINT("Thread1: [COND] condition wait. Because shared_data[%d] is not equal to SOME_VALUE[%d].\n", shared_data, SOME_VALUE);
			eos_wait_condition(&cond, &sem);
			PRINT("Thread1: [COND] wake up. now shared_data is %d\n", shared_data);
		}
		shared_data = 0;
		PRINT("Thread1: [SEM] release semaphore.\n");
		eos_release_semaphore(&sem);
		PRINT("Thread1: [LOG] doing some job.\n");
	}
}

static void task_entry_notifier(void *arg) {
	while (1) {
		PRINT("Thread2: [SEM] acquire semaphore.\n");
		eos_acquire_semaphore(&sem, 0);
		PRINT("Thread2: [SEM] acquire success.\n");
		shared_data++;
		PRINT("Thread2: [LOG] shared_data is %d\n", shared_data);
		if (shared_data == SOME_VALUE) {
			PRINT("Thread2: [COND] shared_data is equal to SOME_VALUE, so condition notify.\n");
			eos_notify_condition(&cond);
			PRINT("Thread2: [COND] after condition notify.\n");
		}
		PRINT("Thread2: [SEM] release semaphore.\n");
		eos_release_semaphore(&sem);
		PRINT("Thread2: [LOG] waiting period...\n");
		eos_sleep(0);
	}
}

void eos_user_main() {
	eos_create_task(&tcb1, (addr_t)stack1, 8096, task_entry_waiter, NULL, 45);
	eos_create_task(&tcb2, (addr_t)stack2, 8096, task_entry_notifier, NULL, 50);
	eos_set_period(&tcb2, 2);

	eos_init_semaphore(&sem, 1, 0);
	eos_init_condition(&cond, 0);
}
