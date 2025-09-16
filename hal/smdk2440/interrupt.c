#include "type.h"

#define SRCPND			(*(volatile unsigned *)0x4A000000)
#define INTMSK			(*(volatile unsigned *)0x4A000008)
#define INTPND			(*(volatile unsigned *)0x4A000010)

/* enable IRQ interrupts */
void eos_enable_interrupt(void) {
	int32u_t temp;
	__asm__ __volatile__("\
		mrs %0, cpsr; \
		bic %0, %0, #0x80; \
		msr cpsr_c, %0;"
		: "=r" (temp)
		:
		: "memory");
}

/*
 * disable IRQ interrupts
 * returns true if interrupts had been enabled before we disabled them
 */
int32u_t eos_disable_interrupt(void) {
	int32u_t old, temp;
	__asm__ __volatile__("\
		mrs %0, cpsr; \
		orr %1, %0, #0x80; \
		msr cpsr_c, %1;"
		: "=r" (old), "=r" (temp)
		:
		: "memory");
	return (old & 0x80) == 0;
}

void eos_restore_interrupt(int32u_t flag) {
	int32u_t temp;
	if (flag)
		eos_enable_interrupt();
	else
		__asm__ __volatile__("\
			mrs %0, cpsr; \
			orr %0, %0, #0x80; \
			msr cpsr_c, %0;"
			: "=r" (temp)
			:
			: "memory");
}

/* ack the specified irq */
void eos_ack_irq(int32u_t irq) {
	/* clear the corresponding bit in _irq_pending register */
	SRCPND = (0x1 << irq);
	INTPND = INTPND;
	INTPND;
}

/* get the irq number */
int32s_t eos_get_irq() {
	/* get the highest bit position in the _irq_pending register */
	int i = 31;
	for(; i>=0; i--) {
		if (INTPND & (0x1 << i)) {
			return i;
		}
	}
	return -1;
}

/* mask an irq */
void eos_disable_irq_line(int32u_t irq) {
	INTMSK |= (0x1 << irq);
	eos_ack_irq(irq);
}

/* unmask an irq */
void eos_enable_irq_line(int32u_t irq) {
	INTMSK &= ~(0x1 << irq);
	eos_ack_irq(irq);
}
