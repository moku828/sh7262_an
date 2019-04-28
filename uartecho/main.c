#define	PFCR1		*((volatile short *)0xFFFE38AC)
#define	PFCR0		*((volatile short *)0xFFFE38AE)
#define	STBCR4		*((volatile char  *)0xFFFE040C)
#define	SCSMR_2		*((volatile short *)0xFFFE9000)
#define	SCBRR_2		*((volatile char  *)0xFFFE9004)
#define	SCSCR_2		*((volatile short *)0xFFFE9008)
#define	SCFSR_2		*((volatile short *)0xFFFE9010)
#define	SCFRDR_2	*((volatile char  *)0xFFFE9014)
#define	SCFCR_2		*((volatile short *)0xFFFE9018)
#define	SCSPTR_2	*((volatile short *)0xFFFE9020)
#define	SCLSR_2		*((volatile short *)0xFFFE9024)
#define	SCEMR_2		*((volatile short *)0xFFFE9028)
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
	STBCR4 &= ~0x20;
	SCSCR_2 &= ~0x0010;
	SCFCR_2 |= 0x0002;
	SCFSR_2 &= ~0x0091;
	SCLSR_2 &= ~0x0001;
	SCSCR_2 &= ~0x0003;
	SCSMR_2 = 0x0000;
	SCEMR_2 = 0x0000;
	SCBRR_2 = 0x26;
	SCFCR_2 = 0x00C0;
	PFCR0 = (PFCR0 & ~0x0070) | 0x0040;
	SCSCR_2 |= 0x0010;
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
		volatile unsigned char c;
		while ((SCFSR_2 & 0x0002) == 0x0000)
		{
			if ((SCFSR_2 & 0x0001) == 0x0001)
			{
				break;
			}
		}
		c = SCFRDR_2;
		SCFSR_2 &= ~0x0001;
		SCFSR_2 &= ~0x0002;
		while ((SCFSR_3 & 0x0020) == 0x0000) ;
		SCFTDR_3 = c;
		SCFSR_3 &= ~0x0060;
	}
	return 0;
}
