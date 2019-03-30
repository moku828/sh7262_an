#define	PCCR2	*((volatile short *)0xFFFE384A)
#define	PCIOR0	*((volatile short *)0xFFFE3852)
#define	PCDR0	*((volatile short *)0xFFFE3856)

int main()
{
	volatile unsigned long i;
	PCCR2 &= ~0x0003;
	PCIOR0 |= 0x0100;
	while (1)
	{
		for (i = 0; i < 0x100000; i++)
		{
			;
		}
		PCDR0 |= 0x0100;
		for (i = 0; i < 0x100000; i++)
		{
			;
		}
		PCDR0 &= ~0x0100;
	}
	return 0;
}
