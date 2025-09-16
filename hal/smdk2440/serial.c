#include "type.h"

#define UART_NR S3C24X0_UART0
#define S3C24X0_UART_BASE		0x50000000

typedef volatile int8u_t	S3C24X0_REG8;
typedef volatile int16u_t	S3C24X0_REG16;
typedef volatile int32u_t	S3C24X0_REG32;

/* UART (see manual chapter 11) */
typedef struct {
	S3C24X0_REG32	ULCON;
	S3C24X0_REG32	UCON;
	S3C24X0_REG32	UFCON;
	S3C24X0_REG32	UMCON;
	S3C24X0_REG32	UTRSTAT;
	S3C24X0_REG32	UERSTAT;
	S3C24X0_REG32	UFSTAT;
	S3C24X0_REG32	UMSTAT;
#ifdef __BIG_ENDIAN
	S3C24X0_REG8	res1[3];
	S3C24X0_REG8	UTXH;
	S3C24X0_REG8	res2[3];
	S3C24X0_REG8	URXH;
#else /* Little Endian */
	S3C24X0_REG8	UTXH;
	S3C24X0_REG8	res1[3];
	S3C24X0_REG8	URXH;
	S3C24X0_REG8	res2[3];
#endif
	S3C24X0_REG32	UBRDIV;
} /*__attribute__((__packed__))*/ S3C24X0_UART;

typedef enum {
	S3C24X0_UART0,
	S3C24X0_UART1,
	S3C24X0_UART2
} S3C24X0_UARTS_NR;

static inline S3C24X0_UART * const S3C24X0_GetBase_UART(S3C24X0_UARTS_NR nr)
{
	return (S3C24X0_UART * const)(S3C24X0_UART_BASE + (nr * 0x4000));
}

void _os_serial_putc (const char c) {
	S3C24X0_UART * const uart = S3C24X0_GetBase_UART(UART_NR);

	/* wait for room in the tx FIFO */
	while (!(uart->UTRSTAT & 0x2));

	uart->UTXH = c;

	/* If \n, also do \r */
	if (c == '\n')
		_os_serial_putc ('\r');
}

void _os_serial_puts(const char *s) {
	while (*s) {
		_os_serial_putc(*s++);
	}
}
