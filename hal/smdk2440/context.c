#include "type.h"

typedef struct _os_context {
	/* low address */
	int32u_t r0;
	int32u_t r1;
	int32u_t r2;
	int32u_t r3;
	int32u_t r4;
	int32u_t r5;
	int32u_t r6;
	int32u_t r7;
	int32u_t r8;
	int32u_t r9;
	int32u_t r10;
	int32u_t r11;	//fp
	int32u_t r12;	//ip
//	int32u_t r13;	//sp
	int32u_t r14;	//lr
//	int32u_t cpsr;
//	int32u_t r15;	//pc
	/* high address */	
} _os_context_t;

addr_t _os_create_context(addr_t stack_base, size_t stack_size, void (*entry)(void *), void *arg) {
	int32u_t *sp = (int32u_t*)(stack_base + stack_size);

	*--sp = (int32u_t)arg;		/* argument of the entry function */
	*--sp = (int32u_t)0;		/* fake return address */

	/* reserve context area */
	sp -= sizeof(_os_context_t)/sizeof(int32u_t *);
	_os_context_t *ctx = (_os_context_t *)sp;

	/* construct the context */
	ctx->r14 = (int32u_t)entry;

	return (addr_t)sp;
}

void _os_restore_context(addr_t sp) {
	__asm __volatile("\
		ldr sp, %0; \
		ldmfd sp!, {r0 - r12, pc};"
		: : "m"(sp));
}

addr_t _os_save_context() {
	__asm __volatile("\
		mov r0, #0; \
		stmfd sp!, {r0 - r12, lr}; \
		mov r0, sp;");
}
