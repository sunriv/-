#include "type.h"

#define MPLL 0
#define UPLL 1

#define MPLLCON			(*(volatile unsigned *)0x4C000004)
#define UPLLCON			(*(volatile unsigned *)0x4C000008)
#define CLKDIVN			(*(volatile unsigned *)0x4C000014)
#define CAMDIVN			(*(volatile unsigned *)0x4C000018)

#define S3C24X0_TIMER_BASE		0x51000000

/* input clock of PLL */
#define CONFIG_SYS_CLK_FREQ 16934400/* the SMDK2440 has 12MHz input clock */

typedef volatile int8u_t	S3C24X0_REG8;
typedef volatile int16u_t	S3C24X0_REG16;
typedef volatile int32u_t	S3C24X0_REG32;

/* PWM TIMER (see manual chapter 10) */
typedef struct {
	S3C24X0_REG32	TCNTB;
	S3C24X0_REG32	TCMPB;
	S3C24X0_REG32	TCNTO;
} /*__attribute__((__packed__))*/ S3C24X0_TIMER;

typedef struct {
	S3C24X0_REG32	TCFG0;
	S3C24X0_REG32	TCFG1;
	S3C24X0_REG32	TCON;
	S3C24X0_TIMER	ch[4];
	S3C24X0_REG32	TCNTB4;
	S3C24X0_REG32	TCNTO4;
} /*__attribute__((__packed__))*/ S3C24X0_TIMERS;

static inline S3C24X0_TIMERS * const S3C24X0_GetBase_TIMERS(void)
{
	return (S3C24X0_TIMERS * const)S3C24X0_TIMER_BASE;
}

static int32u_t get_PLLCLK(int pllreg)
{
	int32u_t r, m, p, s;

	if (pllreg == MPLL)
		r = MPLLCON;
	else if (pllreg == UPLL)
		r = UPLLCON;
	else
		//hang();

	m = ((r & 0xFF000) >> 12) + 8;
	p = ((r & 0x003F0) >> 4) + 2;
	s = r & 0x3;

	return( 2 * m * (CONFIG_SYS_CLK_FREQ / (p << s )) );  
}

/* return FCLK frequency */
int32u_t get_FCLK(void)
{
	return(get_PLLCLK(MPLL));
}

/* return HCLK frequency */
int32u_t get_HCLK(void)
{
	switch(CLKDIVN & 0x6)
	{
		case 0x0: return (get_FCLK());
		case 0x2: return (get_FCLK()/2);  
		case 0x4: return((CAMDIVN & 0x200) ? get_FCLK()/8 : get_FCLK()/4);
		case 0x6: return((CAMDIVN & 0x100) ? get_FCLK()/6 : get_FCLK()/3);
	}
	return 0;
}

/* return PCLK frequency */
int32u_t get_PCLK(void)
{
	return((CLKDIVN & 0x1) ? get_HCLK()/2 : get_HCLK());
}

void _os_init_PWM(void) {
	S3C24X0_TIMERS * const timers = S3C24X0_GetBase_TIMERS();

	/* use PWM Timer 4 because it has no output */
	/* prescaler for Timer 4 is 16 */
	timers->TCFG0 = 0xff00;
	//timers->TCFG0 = 0x0f00;
	/* divider for Timer 4 is 2 */
	timers->TCFG1 = 0x30000;
	//timers->TCFG1 = 0x0;

	int32u_t pclk = get_PCLK();
	/* load value for 10 ms timeout */
	//timers->TCNTB4 = pclk / (2 * 16 * 100);	
	timers->TCNTB4 = 0x2222;

	/* auto load, manual update of Timer 4 */
	timers->TCON = (timers->TCON & ~0x0700000) | 0x600000;

	/* auto load, start Timer 4 */
	timers->TCON = (timers->TCON & ~0x0700000) | 0x500000;
}
