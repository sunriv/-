// Forward declarations for our HAL functions.
// In a larger project, these would be in header files.
void uart_init();
void uart_puts(const char *s);

void main() {
    // Initialize the UART
    uart_init();

    // Print a welcome message
    uart_puts("Hello eOS on Raspberry Pi 3!\n");
    uart_puts("Successfully booted and UART is working.\n");

    // Loop forever
    while (1) {
        // We can add a wait-for-interrupt instruction here later
    }
}
