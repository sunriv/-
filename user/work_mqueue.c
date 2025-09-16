#include <core/eos.h>

static eos_tcb_t tcb1;
static eos_tcb_t tcb2;
static eos_tcb_t tcb3;
static int8u_t stack1[8096];
static int8u_t stack2[8096];
static int8u_t stack3[8096];
static int8u_t queue[12];
eos_mqueue_t mq;

static void sender_task1(void *arg) {
	int32u_t a[3] = {1, 11, 111};
	int8u_t result;
	int8u_t i = 0;

	while (1) {
		for (i = 0; i<6; i++) {	
			PRINT("Sender_task1: [MQ] try to send message\n");
			result = eos_send_message(&mq, a, 2) ;
			if (result == 0) {
				PRINT("Sender_task1: [MQ] fail to send message\n");
				break;
			}
			PRINT("Sender_task1: [LOG] doing some job.\n");
		}
		PRINT("Sender_task1: [LOG] waiting period...\n");
		eos_sleep(0);
	}
}

static void sender_task2(void *arg) {
	int32u_t a[3] = {3, 33, 333};
	int8u_t result;
	int8u_t j = 0;
	
	while (1) {
		for (j = 0; j<6; j++) {
			PRINT("Sender_task2: [MQ] try to send message\n");
			result = eos_send_message(&mq, a, 2) ;
			if (result == 0) {
				PRINT("Sender_task2: [MQ] fail to send message\n");
				break;
			}
			PRINT("Sender_task2: [LOG] doing some job.\n");
		}
		PRINT("Sender_task2: [LOG] waiting period...\n");
		eos_sleep(0);
	}
}

static void receiver_task(void *arg) {
	int32u_t b[3] = {2, 22, 222};
	int8u_t result;
	int8u_t k = 0;

	while (1) {
		for (k = 0; k < 2; k++) {
			PRINT("Receiver_task: [MQ] try to receive message.\n");
			result = eos_receive_message(&mq, b, 1);	
			if (result == 0) {
				PRINT("Receiver_task: [MQ] fail to receive message\n");
				break;
			}
		}
		PRINT("Receiver_task: [LOG] waiting period...\n");
		eos_sleep(0);
	}
}

void eos_user_main() {
	eos_create_task(&tcb1, (addr_t)stack1, 8096, sender_task1, NULL, 45);
	eos_create_task(&tcb2, (addr_t)stack2, 8096, sender_task2, NULL, 40);
	eos_create_task(&tcb3, (addr_t)stack3, 8096, receiver_task, NULL, 30);
	eos_set_period(&tcb1, 3);
	eos_set_period(&tcb2, 3);
	eos_set_period(&tcb3, 4);

	eos_init_mqueue(&mq, queue, 4, 3, FIFO);
}
