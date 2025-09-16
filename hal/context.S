/*
 * Filename: hal/context.S
 *
 * Author: Gemini
 *
 * Description: Context switching functions for AArch64
 */

.global _os_save_context
.global _os_restore_context

/*
 * addr_t _os_save_context(void)
 * Saves the context of the current task.
 * Returns the stack pointer of the saved task in x0.
 */
_os_save_context:
    // Save callee-saved registers (x19-x29) and the link register (x30)
    stp x19, x20, [sp, #-16]!
    stp x21, x22, [sp, #-16]!
    stp x23, x24, [sp, #-16]!
    stp x25, x26, [sp, #-16]!
    stp x27, x28, [sp, #-16]!
    stp x29, x30, [sp, #-16]! // Save fp (x29) and lr (x30)
    
    // The return value is the new stack pointer, which should be in x0
    mov x0, sp
    
    // Return to the caller (eos_schedule)
    ret

/*
 * void _os_restore_context(addr_t sp)
 * Restores the context from the given stack pointer.
 * This function does not return.
 */
_os_restore_context:
    // The first argument (sp) is in x0. Move it to the stack pointer register.
    mov sp, x0
    
    // Restore callee-saved registers
    ldp x19, x20, [sp], #16
    ldp x21, x22, [sp], #16
    ldp x23, x24, [sp], #16
    ldp x25, x26, [sp], #16
    ldp x27, x28, [sp], #16
    ldp x29, x30, [sp], #16  // Restore fp (x29) and lr (x30)
    
    // The argument for the task was stored in x19 by _os_create_context.
    // Move it to x0, as per AAPCS64 for the first argument.
    mov x0, x19
    
    // Jump to the address in the link register (x30).
    // For a new task, this is the entry point.
    // For a restored task, this is the instruction after the call to _os_save_context.
    ret
