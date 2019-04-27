#define	PFCR1		*((volatile short *)0xFFFE38AC)
#define	STBCR4		*((volatile char  *)0xFFFE040C)
#define	SCSMR_3		*((volatile short *)0xFFFE9800)
#define	SCBRR_3		*((volatile char  *)0xFFFE9804)
#define	SCSCR_3		*((volatile short *)0xFFFE9808)
#define	SCFTDR_3	*((volatile char  *)0xFFFE980C)
#define	SCFSR_3		*((volatile short *)0xFFFE9810)
#define	SCFCR_3		*((volatile short *)0xFFFE9818)
#define	SCSPTR_3	*((volatile short *)0xFFFE9820)
#define	SCLSR_3		*((volatile short *)0xFFFE9824)
#define	SCEMR_3		*((volatile short *)0xFFFE9828)


int main()
{
	STBCR4 &= ~0x10;
	SCSCR_3 &= ~0x0020;
	SCFCR_3 |= 0x0004;
	SCSCR_3 &= ~0x0003;
	SCSMR_3 = 0x0000;
	SCEMR_3 = 0x0000;
	SCBRR_3 = 0x26;
	SCFCR_3 = 0x0030;
	SCSPTR_3 = 0x0053;
	PFCR1 = (PFCR1 & ~0x0007) | 0x0004;
	SCSCR_3 |= 0x0020;
	while (1)
	{
		while ((SCFSR_3 & 0x0020) == 0x0000) ;
		SCFTDR_3 = 0x30;
		SCFSR_3 &= ~0x0060;
	}
	return 0;
}
