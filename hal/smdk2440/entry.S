.globl _start
_start:
	/* vector table */
	b	reset
	ldr	pc, _undefined_instruction
	ldr pc, _software_interrupt
	ldr pc, _prefetch_abort
	ldr pc, _data_abort
	ldr pc, _not_used
	ldr pc, _irq
	ldr pc, _fiq
	b	sleep_mode

_undefined_instruction:	.word undefined_instruction
_software_interrupt:	.word software_interrupt
_prefetch_abort:	.word prefetch_abort
_data_abort:		.word data_abort
_not_used:		.word not_used
_irq:			.word irq
_fiq:			.word fiq

.globl _armboot_end
/* stack for the kernel initialization */
_armboot_end:
	.word armboot_end

reset:
	/* set up the stack */
	ldr r0, _armboot_end
	add r0, r0, #131072
	sub sp, r0, #12
	
	/* jump to the kernel initialization routine */
	bl _os_initialization

undefined_instruction:
	movs pc, r14
software_interrupt:
	movs pc, r14
prefetch_abort:
	subs pc, r14, #4
data_abort:
	subs pc, r14, #8
not_used:

irq:
	/* From this time, cpu is in irq mode and interrupt is disabled. */
	/* save pc (r14_irq), cpsr (spsr_irq) of previous mode */
	ldr r13, 1f
	sub r14, r14, #4
	str r14, [r13]
	mrs r14, spsr
	str r14, [r13, #4]

	/* change to svc mode */
	mrs r14, cpsr
	bic r14, r14, #0x1f
	orr r14, r14, #0x13
	msr cpsr, r14

	/* make interrupt frame */
	sub r13, r13, #68

	/* save r0-r12 */
	stmia r13, {r0-r12}

	/* save r13, r14, pc, cpsr of previous mode */
	add r0, r13, #68 /* previous r13 */
	mov r1, r14 /* previous r14 */
	ldr r12, 1f
	ldmia r12, {r2, r3} /* previous pc and cpsr */
	add r12, r13, #52
	stmia r12, {r0-r3}

	/* jump to C handler */
	bl _os_common_interrupt_handler

	/* restore interrupt frame */
	ldr r0, [r13, #64]
	msr spsr, r0
	ldmia r13, {r0-pc}^

1: .word _temp_stack
	.align 4

_temp_stack:
	.skip 8

fiq:
	subs pc, r14, #4
sleep_mode:
