#define	PGCR7			*((volatile short *)0xFFFE38C0)
#define	PGCR5			*((volatile short *)0xFFFE38C4)
#define	PGCR4			*((volatile short *)0xFFFE38C6)
#define	PGCR3			*((volatile short *)0xFFFE38C8)
#define	PGCR2			*((volatile short *)0xFFFE38CA)
#define	PGCR1			*((volatile short *)0xFFFE38CC)
#define	PGCR0			*((volatile short *)0xFFFE38CE)
#define	PGIOR1			*((volatile short *)0xFFFE38D0)
#define	PGDR1			*((volatile short *)0xFFFE38D4)
#define	STBCR7			*((volatile char  *)0xFFFE0418)
#define	SGMODE			*((volatile long  *)0xFFFF3800)
#define	SYNCNT			*((volatile long  *)0xFFFF3808)
#define	PANEL_CLKSEL	*((volatile long  *)0xFFFF380C)
#define	SYN_SIZE		*((volatile long  *)0xFFFF3900)
#define	PANEL_VSYNC_TIM	*((volatile long  *)0xFFFF3904)
#define	PANEL_HSYNC_TIM	*((volatile long  *)0xFFFF3908)
#define	GRA_VSYNC_TIM	*((volatile long  *)0xFFFF3910)
#define	GRCMEN2			*((volatile long  *)0xFFFF3000)
#define	GRCBUSCNT2		*((volatile long  *)0xFFFF3004)
#define	GROPSADR2		*((volatile long  *)0xFFFF3308)
#define	GROPSWH2		*((volatile long  *)0xFFFF330C)
#define	GROPSOFST2		*((volatile long  *)0xFFFF3310)
#define	GROPDPHV2		*((volatile long  *)0xFFFF3314)

int main()
{
	volatile unsigned long i;
	volatile unsigned long x, y;
	volatile unsigned short *p;
	PGCR7 = (PGCR7 & ~0x0007) | 0x0001;
	PGCR5 &= ~0x0007;
	PGCR4 = (PGCR4 & ~0x0700) | 0x1011;
	PGCR3 = 0x1111;
	PGCR2 = 0x1111;
	PGCR1 = 0x1111;
	PGCR0 = 0x1110;
	PGIOR1 |= 0x0014;
	PGDR1 &= ~0x0014;
	STBCR7 &= ~0x10;
	SGMODE = 0x00000001;
	SYNCNT = (SYNCNT & ~0x010C000C) | 0x0000000C;
	PANEL_CLKSEL &= ~0x00001000;
	PANEL_CLKSEL = (PANEL_CLKSEL & ~0x0000203F) | 0x00002008;
	PANEL_CLKSEL |= 0x00001000;
	SYN_SIZE = 0x006F01FB;
	PANEL_VSYNC_TIM = 0x00000001;
	PANEL_HSYNC_TIM = 0x00000001;
	GRA_VSYNC_TIM = 0x00000000;
	GRCMEN2 = 0x00000002;
	GRCBUSCNT2 = 0x00000000;
	GROPSWH2 = 0x00600190;
	GROPSOFST2 = 0x00000320;
	GROPDPHV2 = 0x000E005B;
	p = (unsigned short *)0x1C028000;
	for (y = 0; y < 96; y++)
	{
		for (x = 0; x < 400; x++)
		{
			*p = 0xF800;
			p++;
		}
	}
	p = (unsigned short *)0x1C03C000;
	for (y = 0; y < 96; y++)
	{
		for (x = 0; x < 400; x++)
		{
			*p = 0x001F;
			p++;
		}
	}
	while (1)
	{
		GROPSADR2 = 0x1C028000;
		GRCMEN2 |= 0x80000000;
		for (i = 0; i < 0x100000; i++)
		{
			;
		}
		GROPSADR2 = 0x1C03C000;
		GRCMEN2 |= 0x80000000;
		for (i = 0; i < 0x100000; i++)
		{
			;
		}
	}
	return 0;
}
