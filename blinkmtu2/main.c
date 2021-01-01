#define	PCCR2	*((volatile short *)0xFFFE384A)
#define	PCIOR0	*((volatile short *)0xFFFE3852)
#define	PCDR0	*((volatile short *)0xFFFE3856)
#define	STBCR3	*((volatile char  *)0xFFFE0408)
#define	TSTR	*((volatile char  *)0xFFFE4280)
#define	TCR_1	*((volatile char  *)0xFFFE4380)
#define	TCNT_1	*((volatile short *)0xFFFE4386)
#define	TCR_2	*((volatile char  *)0xFFFE4000)
#define	TCNT_2	*((volatile short *)0xFFFE4006)

long time()
{
	volatile unsigned short cnt1, cnt1_, cnt2;
	volatile unsigned long cnt;
	cnt1 = TCNT_1;
	cnt2 = TCNT_2;
	cnt1_ = TCNT_1;
	if (cnt1 < cnt1_)
	{
		if (cnt2 < 16)
		{
			cnt1 = cnt1_;
		}
	}
	cnt = cnt1 << 16 | cnt2;
	return cnt;
}

int main()
{
	volatile unsigned long i;
	volatile unsigned long time_now, time_last;
	PCCR2 &= ~0x0003;
	PCIOR0 |= 0x0100;
	STBCR3 &= ~0x20;
	TCR_1 |= 0x07;
	TCR_2 = (TCR_2 & ~0x07) | 0x03;
	TSTR &= ~0x06;
	TSTR |= 0x06;
	time_last = time();
	while (1)
	{
		while (1)
		{
			time_now = time();
			if ((time_now - time_last) > 350000)
			{
				time_last = time_now;
				break;
			}
		}
		if (PCDR0 & 0x0100)
		{
			PCDR0 &= ~0x0100;
		}
		else
		{
			PCDR0 |= 0x0100;
		}
	}
	return 0;
}
