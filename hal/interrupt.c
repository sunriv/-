/********************************************************
 * Filename: hal/interrupt.c
 *
 * Author: Gemini
 *
 * Description: HAL routines for irq management for Raspberry Pi 3 (AArch64)
 ********************************************************/

#include "irq.h"
#include "type.h"

#define PERIPHERAL_BASE 0x3F000000
#define IRQ_CONTROLLER_BASE (PERIPHERAL_BASE + 0xB200)

typedef struct {
    volatile int32u_t IRQ_basic_pending;
    volatile int32u_t IRQ_pending_1;
    volatile int32u_t IRQ_pending_2;
    volatile int32u_t FIQ_control;
    volatile int32u_t Enable_IRQs_1;
    volatile int32u_t Enable_IRQs_2;
    volatile int32u_t Enable_Basic_IRQs;
    volatile int32u_t Disable_IRQs_1;
    volatile int32u_t Disable_IRQs_2;
    volatile int32u_t Disable_Basic_IRQs;
} irq_controller_t;

static volatile irq_controller_t* const irq_controller = (irq_controller_t*)IRQ_CONTROLLER_BASE;

int32s_t hal_get_irq() {
    if (irq_controller->IRQ_pending_1 != 0) {
        for (int i = 0; i < 32; i++) {
            if ((irq_controller->IRQ_pending_1 >> i) & 1) {
                return i;
            }
        }
    }
    if (irq_controller->IRQ_pending_2 != 0) {
        for (int i = 0; i < 32; i++) {
            if ((irq_controller->IRQ_pending_2 >> i) & 1) {
                return i + 32;
            }
        }
    }
    return -1;
}

void hal_ack_irq(int32u_t irq) {
    // BCM2837 doesn't have a common IRQ acknowledgement register.
    // IRQs are typically acknowledged at the peripheral level.
}

void hal_disable_irq_line(int32u_t irq) {
    if (irq < 32) {
        irq_controller->Disable_IRQs_1 = (1 << irq);
    } else {
        irq_controller->Disable_IRQs_2 = (1 << (irq - 32));
    }
}

void hal_enable_irq_line(int32u_t irq) {
    if (irq < 32) {
        irq_controller->Enable_IRQs_1 = (1 << irq);
    } else {
        irq_controller->Enable_IRQs_2 = (1 << (irq - 32));
    }
}

int32u_t hal_disable_interrupt() {
    int64u_t daif;
    asm volatile (
        "mrs %0, daif\n"   // Read DAIF register
        "msr daifset, #2"  // Set the I bit (bit 1) to disable IRQs
        : "=r" (daif)
        :
        : "memory"
    );
    return (int32u_t)(daif & 0x80); // Return the old I bit state
}

void hal_enable_interrupt() {
    asm volatile (
        "msr daifclr, #2" // Clear the I bit to enable IRQs
        :
        :
        : "memory"
    );
}

void hal_restore_interrupt(int32u_t flags) {
    if (!(flags & 0x80)) { // If the old I bit was 0 (enabled)
        hal_enable_interrupt();
    } else { // If the old I bit was 1 (disabled)
        int64u_t daif;
        asm volatile (
            "mrs %0, daif\n"
            "msr daifset, #2"
            : "=r" (daif)
            :
            : "memory"
        );
    }
}