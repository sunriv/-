#include <stdint.h>

// Raspberry Pi 3B peripherals are at 0x3F000000
// PL011 UART is at 0x201000
#define UART0_BASE 0x3F201000

// Memory-mapped registers
#define UART0_DR    ((volatile unsigned int*)(UART0_BASE + 0x00))
#define UART0_FR    ((volatile unsigned int*)(UART0_BASE + 0x18))
#define UART0_CR    ((volatile unsigned int*)(UART0_BASE + 0x30))
#define UART0_IMSC  ((volatile unsigned int*)(UART0_BASE + 0x38))
#define UART0_ICR   ((volatile unsigned int*)(UART0_BASE + 0x44))

// Flag Register bits
#define UART_FR_TXFF (1 << 5) // Transmit FIFO full

// Control Register bits
#define UART_CR_UARTEN (1 << 0) // UART enable
#define UART_CR_TXE    (1 << 8) // Transmit enable
#define UART_CR_RXE    (1 << 9) // Receive enable

void uart_init() {
    // Disable UART
    *UART0_CR = 0;

    // Disable all interrupts
    *UART0_IMSC = 0;

    // Clear any pending interrupts
    *UART0_ICR = 0x7FF;

    // Enable UART, TX, and RX
    *UART0_CR = UART_CR_UARTEN | UART_CR_TXE | UART_CR_RXE;
}

void uart_putc(char c) {
    // Wait until the UART transmit FIFO is not full
    while (*UART0_FR & UART_FR_TXFF);
    *UART0_DR = c;
}

void uart_puts(const char *s) {
    while (*s) {
        if (*s == '\n') {
            uart_putc('\r');
        }
        uart_putc(*s++);
    }
}