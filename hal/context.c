/********************************************************
 * Filename: hal/context.c
 *
 * Author: Gemini
 *
 * Description: Context management for AArch64
 ********************************************************/

#include "eos.h"

/*
 * This structure holds the registers that need to be saved during a 
 * cooperative context switch, according to the AArch64 Procedure Call Standard (AAPCS64).
 */
typedef struct _os_context {
    int64u_t x19;
    int64u_t x20;
    int64u_t x21;
    int64u_t x22;
    int64u_t x23;
    int64u_t x24;
    int64u_t x25;
    int64u_t x26;
    int64u_t x27;
    int64u_t x28;
    int64u_t fp; // x29
    int64u_t lr; // x30
} _os_context_t;

// Declare the context switching functions implemented in context.S
extern addr_t _os_save_context(void);
extern void _os_restore_context(addr_t sp);


/*
 * Creates the initial context for a new task.
 */
addr_t _os_create_context(addr_t stack_base, size_t stack_size, void (*entry)(void *), void *arg) {
    int8u_t *stack_top = (int8u_t *)stack_base + stack_size;
    
    // Align stack to 16-byte boundary
    addr_t aligned_stack_base = (addr_t)(((int64u_t)stack_top - sizeof(_os_context_t)) & ~0xF);
    _os_context_t *context = (_os_context_t *)aligned_stack_base;

    // Zero out the context
    int i;
    for (i = 0; i < sizeof(_os_context_t) / sizeof(int64u_t); i++) {
        ((int64u_t*)context)[i] = 0;
    }

    // For a new task, we set lr to the entry point.
    context->lr = (int64u_t)entry;
    
    // We use a callee-saved register (x19) to pass the argument.
    // The task function must be aware that its argument is in x19.
    // _os_restore_context will move this to x0 before calling the task.
    context->x19 = (int64u_t)arg;

    return (addr_t)context;
}