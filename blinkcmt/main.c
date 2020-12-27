#define	PCCR2	*((volatile short *)0xFFFE384A)
#define	PCIOR0	*((volatile short *)0xFFFE3852)
#define	PCDR0	*((volatile short *)0xFFFE3856)
#define	STBCR7	*((volatile char  *)0xFFFE0418)
#define	CMSTR	*((volatile short *)0xFFFEC000)
#define	CMCSR_0	*((volatile short *)0xFFFEC002)
#define	CMCNT_0	*((volatile short *)0xFFFEC004)
#define	CMCOR_0	*((volatile short *)0xFFFEC006)
#define	IPR10	*((volatile short *)0xFFFE0C08)

void sleep();

void set_imask(unsigned char imask)
{
	volatile unsigned long sr;
	__asm__("STC SR, %0":"=r"(sr));
	sr = (sr & ~0x000000F0) | ((imask << 4) & 0x000000F0);
	__asm__("LDC %0, SR"::"r"(sr));
}

void __attribute__((interrupt_handler)) isr_cmi0()
{
	CMCSR_0 &= ~0x0080;
}

int main()
{
	volatile unsigned long i;
	PCCR2 &= ~0x0003;
	PCIOR0 |= 0x0100;
	set_imask(14);
	IPR10 = (IPR10 & ~0x00F0) | 0x00F0;
	STBCR7 &= ~0x04;
	CMCSR_0 = (CMCSR_0 & ~0x0043) | 0x0040;
	CMCOR_0 = 0x0BB8;
	CMSTR |= 0x01;
	while (1)
	{
		sleep();
		set_imask(15);
		if (PCDR0 & 0x0100)
		{
			PCDR0 &= ~0x0100;
		}
		else
		{
			PCDR0 |= 0x0100;
		}
		set_imask(14);
	}
	return 0;
}
