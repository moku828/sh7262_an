#define	PECR0	*((volatile short *)0xFFFE388E)
#define	PEIOR0	*((volatile short *)0xFFFE3892)
#define	PEPR0	*((volatile short *)0xFFFE389A)
#define	STBCR7	*((volatile char  *)0xFFFE0418)
#define	CMSTR	*((volatile short *)0xFFFEC000)
#define	CMCSR_1	*((volatile short *)0xFFFEC008)
#define	CMCNT_1	*((volatile short *)0xFFFEC00A)
#define	CMCOR_1	*((volatile short *)0xFFFEC00C)
#define	IPR10	*((volatile short *)0xFFFE0C08)
#define	PCCR2	*((volatile short *)0xFFFE384A)
#define	PCIOR0	*((volatile short *)0xFFFE3852)
#define	PCDR0	*((volatile short *)0xFFFE3856)

void sleep();

void set_imask(unsigned char imask)
{
	volatile unsigned long sr;
	__asm__("STC SR, %0":"=r"(sr));
	sr = (sr & ~0x000000F0) | ((imask << 4) & 0x000000F0);
	__asm__("LDC %0, SR"::"r"(sr));
}

unsigned char __attribute__ ((section (".bss"))) count[128];
unsigned char __attribute__ ((section (".bss"))) idx;
unsigned char __attribute__ ((section (".bss"))) len;

void __attribute__((interrupt_handler)) isr_cmi1()
{
	CMCSR_1 &= ~0x0080;
	
	if (len != 0)
	{
		return;
	}
	
	if (PEPR0 & 0x0001)
	{
		if (idx == 0)
		{
			count[0] = 0x80;
		}
		else
		{
			if ((count[idx] & 0x80) == 0x00)
			{
				idx++;
				count[idx] = 0x81;
			}
			else
			{
				count[idx]++;
				if ((count[idx] & ~0x80) > 32)
				{
					len = idx;
					idx = 0;
				}
			}
		}
	}
	else
	{
		if (idx == 0)
		{
			idx++;
			count[idx] = 0x01;
		}
		else
		{
			if ((count[idx] & 0x80) == 0x80)
			{
				idx++;
				count[idx] = 0x01;
			}
			else
			{
				count[idx]++;
			}
		}
	}
}

void* memcpy(void * buf1, const void * buf2, unsigned long n)
{
	volatile unsigned char *_buf1;
	volatile unsigned char *_buf2;
	volatile unsigned long i;
	_buf1 = (unsigned char *)buf1;
	_buf2 = (unsigned char *)buf2;
	for (i = 0; i < n; i++)
	{
		_buf1[i] = _buf2[i];
	}
	return buf1;
}

int main()
{
	volatile unsigned long i;
	idx = 0;
	len = 0;
	for (i = 0; i < sizeof(count)/sizeof(count[0]); i++)
	{
		count[i] = 0;
	}
	set_imask(14);
	IPR10 = (IPR10 & ~0x000F) | 0x000F;
	PECR0 &= ~0x0003;
	PEIOR0 &= ~0x0001;
	STBCR7 &= ~0x04;
	CMCSR_1 = (CMCSR_1 & ~0x0043) | 0x0041;
	CMCOR_1 = 0x00D2;
	PCCR2 &= ~0x0003;
	PCIOR0 |= 0x0100;
	CMSTR |= 0x02;
	while (1)
	{
		sleep();
		set_imask(15);
		if (len != 0)
		{
			if (len == 2+(32*2)+1+1)
			{
				unsigned char power[2+(32*2)+1+1] = {
					0x20, 0x90,
					0x02, 0x82, 0x02, 0x82, 0x02, 0x82, 0x02, 0x82, 0x02, 0x82, 0x02, 0x82, 0x02, 0x82, 0x02, 0x82,
					0x02, 0x86, 0x02, 0x86, 0x02, 0x86, 0x02, 0x86, 0x02, 0x86, 0x02, 0x86, 0x02, 0x86, 0x02, 0x86,
					0x02, 0x82, 0x02, 0x86, 0x02, 0x86, 0x02, 0x82, 0x02, 0x82, 0x02, 0x82, 0x02, 0x86, 0x02, 0x82,
					0x02, 0x86, 0x02, 0x82, 0x02, 0x82, 0x02, 0x86, 0x02, 0x86, 0x02, 0x86, 0x02, 0x82, 0x02, 0x86,
					0x02, 0xA1,
				};
				for (i = 0; i < sizeof(power)/sizeof(power[0]); i++)
				{
					if ((count[i+1] < (power[i] - 1)) || (count[i+1] > (power[i] + 1)))
					{
						break;
					}
				}
				if (i == (sizeof(power)/sizeof(power[0])))
				{
					if (PCDR0 & 0x0100)
					{
						PCDR0 &= ~0x0100;
					}
					else
					{
						PCDR0 |= 0x0100;
					}
				}
				else
				{
					i = 0;
				}
			}
			len = 0;
		}
		set_imask(14);
	}
	return 0;
}
