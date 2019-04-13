#define	PGCR7			*((volatile short *)0xFFFE38C0)
#define	PGCR5			*((volatile short *)0xFFFE38C4)
#define	PGCR4			*((volatile short *)0xFFFE38C6)
#define	PGCR3			*((volatile short *)0xFFFE38C8)
#define	PGCR2			*((volatile short *)0xFFFE38CA)
#define	PGCR1			*((volatile short *)0xFFFE38CC)
#define	PGCR0			*((volatile short *)0xFFFE38CE)
#define	PGIOR1			*((volatile short *)0xFFFE38D0)
#define	PGIOR0			*((volatile short *)0xFFFE38D2)
#define	PGDR1			*((volatile short *)0xFFFE38D4)
#define	PGDR0			*((volatile short *)0xFFFE38D6)
#define	STBCR7			*((volatile char  *)0xFFFE0418)
#define	PANEL_CLKSEL	*((volatile long  *)0xFFFF380C)

int main()
{
	PGCR7 &= ~0x0007;
	PGCR5 &= ~0x0007;
	PGCR4 = (PGCR4 & ~0x0777) | 0x1000;
	PGCR3 &= ~0x7777;
	PGCR2 &= ~0x7777;
	PGCR1 &= ~0x3333;
	PGCR0 &= ~0x3330;
	PGIOR1 |= 0x0017;
	PGIOR0 = 0xFFFF;
	PGDR1 |= 0x0010;
	PGDR0 = 0x0000;
	STBCR7 &= ~0x10;
	PANEL_CLKSEL &= ~0x00001000;
	PANEL_CLKSEL = (PANEL_CLKSEL & ~0x0000203F) | 0x00002008;
	PANEL_CLKSEL |= 0x00001000;
	while (1)
	{
	}
	return 0;
}
