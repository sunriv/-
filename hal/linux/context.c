#include <core/eos.h>
#include <core/eos_internal.h>
#include "emulator_asm.h"

typedef struct _os_context {
	/* low address */
	int32u_t edi;
	int32u_t esi;
	int32u_t ebp;
	int32u_t esp;
	int32u_t ebx;
	int32u_t edx;
	int32u_t ecx;
	int32u_t eax;
	int32u_t eflags;
	int32u_t eip;
	/* high address */	
} _os_context_t;

void print_context(addr_t context) {
	if(context == NULL || 1) { return; }
	_os_context_t *ctx = (_os_context_t *)context;
	PRINT("ctx=0x%x\n", (int32u_t)ctx);
	PRINT("eflags  =0x%x\n", ctx->eflags);
	PRINT("eax     =0x%x\n", ctx->eax);
	PRINT("ecx     =0x%x\n", ctx->ecx);
    PRINT("edx     =0x%x\n", ctx->edx);
	PRINT("ebx     =0x%x\n", ctx->ebx);
	PRINT("esp     =0x%x\n", ctx->esp);
    PRINT("ebp     =0x%x\n", ctx->ebp);
	PRINT("esi     =0x%x\n", ctx->esi);
    PRINT("edi     =0x%x\n", ctx->edi);
    PRINT("eip     =0x%x\n", ctx->eip);
}

addr_t _os_create_context(addr_t stack_base, size_t stack_size, void (*entry)(void *), void *arg) {
	int32u_t *sp = (int32u_t*)(stack_base + stack_size);

	*--sp = (int32u_t)arg;		/* argument of the entry function */
	*--sp = (int32u_t)NULL;		/* fake return address */

	/* reserve context area */
	sp -= sizeof(_os_context_t)/sizeof(int32u_t *);
	_os_context_t *ctx = (_os_context_t *)sp;

	/* construct the context */
	ctx->eip = (int32u_t)entry;
	ctx->eflags = 1;

	return (addr_t)sp;
}

void _os_restore_context(addr_t sp) {
    __asm __volatile("\
		movl %0, %%esp;\
		popal;\
		pop _eflags;\
		ret"
		: : "m"(sp));
}

addr_t _os_save_context() {
	__asm __volatile("\
		mov $0, %eax;\
		push $resume_point;\
		push _eflags;\
		pushal;\
		mov %esp, %eax;\
		push 4(%ebp);\
		push 0(%ebp);\
		mov %esp, %ebp;\
	resume_point:\
		leave; ret");
}
