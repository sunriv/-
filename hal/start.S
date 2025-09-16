.section ".text.boot"

.globl _start
_start:
    // Check current exception level
    mrs x1, CurrentEL
    cmp x1, #0x8 // EL2?
    beq from_el2
    cmp x1, #0x4 // EL1?
    beq from_el1

    // If we are in EL3 or EL0, hang. We don't support this.
hang:
    wfe
    b hang

from_el2:
    // Set up to enter EL1
    // EL1 will be AArch64
    mov x0, #(1 << 31)  // AArch64
    msr hcr_el2, x0

    // Set up SPSR_EL2 to enter EL1 with interrupts disabled
    mov x0, #0x3c4 // EL1h (SPSel=1), DAIF masked
    msr spsr_el2, x0

    // Set EL1 entry point
    adr x0, from_el1
    msr elr_el2, x0

    // Return to EL1
    eret

from_el1:
    // Set the stack pointer
    ldr x0, =0x100000 // Set stack top to 1MB
    mov sp, x0

    // Clear the .bss section
    ldr x1, =__bss_start
    ldr x2, =__bss_end
    sub x2, x2, x1
clear_bss:
    cbz x2, bss_cleared
    str xzr, [x1], #8
    sub x2, x2, #8
    cbnz x2, clear_bss
bss_cleared:

    // Jump to the C entry point
    bl main

    // In case main returns, hang
hang_main:
    wfe
    b hang_main