#define	PECR0	*((volatile short *)0xFFFE388E)
#define	PEPR0	*((volatile short *)0xFFFE389A)
#define	STBCR7	*((volatile char  *)0xFFFE0418)
#define	CMSTR	*((volatile short *)0xFFFEC000)
#define	CMCSR_0	*((volatile short *)0xFFFEC002)
#define	CMCNT_0	*((volatile unsigned short *)0xFFFEC004)
#define	CMCOR_0	*((volatile short *)0xFFFEC006)
#define	IPR01	*((volatile short *)0XFFFE0818)
#define	IPR10	*((volatile short *)0xFFFE0C08)
#define	PCCR2	*((volatile short *)0xFFFE384A)
#define	PCIOR0	*((volatile short *)0xFFFE3852)
#define	PCDR0	*((volatile short *)0xFFFE3856)
#define	ICR1	*((volatile short *)0xFFFE0802)
#define	IRQRR	*((volatile short *)0xFFFE0806)

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
unsigned long __attribute__ ((section (".bss"))) tick;
unsigned long __attribute__ ((section (".bss"))) now_ms;
unsigned long __attribute__ ((section (".bss"))) last_ms;
unsigned short __attribute__ ((section (".bss"))) now_3khz_cnt;
unsigned short __attribute__ ((section (".bss"))) last_3khz_cnt;
signed char __attribute__ ((section (".bss"))) last_pe0;

void __attribute__((interrupt_handler)) isr_irq0()
{
	volatile unsigned long span;
	IRQRR &= ~0x0001;
	if (len != 0)
	{
		return;
	}
	now_ms = tick;
	now_3khz_cnt = CMCNT_0;
	span = (now_ms - last_ms) * 3000;
	if (now_3khz_cnt < last_3khz_cnt)
	{
		if (now_ms == last_ms)
		{
			span += 3000;
		}
		span -= last_3khz_cnt;
		span += now_3khz_cnt;
	}
	else
	{
		span += (now_3khz_cnt - last_3khz_cnt);
	}
	if ((now_ms - last_ms) > 10)
	{
		idx = 0;
	}
	else
	{
		count[idx] = span / 840;
		if (last_pe0 == 1)
		{
			count[idx] |= 0x80;
		}
		idx++;
		if (idx == 2+(32*2)+1)
		{
			len = idx;
			idx = 0;
		}
	}
	last_ms = now_ms;
	last_3khz_cnt = now_3khz_cnt;
	last_pe0 = (PEPR0 & 0x0001) ? 1 : 0;
}

void __attribute__((interrupt_handler)) isr_cmi0()
{
	CMCSR_0 &= ~0x0080;
	tick++;
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
	tick = 0;
	last_ms = 0;
	last_3khz_cnt = 0;
	last_pe0 = 0;
	idx = 0;
	len = 0;
	for (i = 0; i < sizeof(count)/sizeof(count[0]); i++)
	{
		count[i] = 0;
	}
	set_imask(14);
	IPR10 = (IPR10 & ~0x00F0) | 0x00F0;
	PECR0 = (PECR0 & ~0x0003) | 0x0003;
	ICR1 = (ICR1 & ~0x0003) | 0x0003;
	IPR01 = (IPR01 & ~0xF000) | 0xF000;
	STBCR7 &= ~0x04;
	CMCSR_0 = (CMCSR_0 & ~0x0043) | 0x0040;
	CMCOR_0 = 0x0BB8;
	PCCR2 &= ~0x0003;
	PCIOR0 |= 0x0100;
	CMCNT_0 = 0x0000;
	CMSTR |= 0x01;
	while (1)
	{
		sleep();
		set_imask(15);
		if (len != 0)
		{
			if (len == 2+(32*2)+1)
			{
				unsigned char power[2+(32*2)+1] = {
					0x20, 0x90,
					0x02, 0x82, 0x02, 0x82, 0x02, 0x82, 0x02, 0x82, 0x02, 0x82, 0x02, 0x82, 0x02, 0x82, 0x02, 0x82,
					0x02, 0x86, 0x02, 0x86, 0x02, 0x86, 0x02, 0x86, 0x02, 0x86, 0x02, 0x86, 0x02, 0x86, 0x02, 0x86,
					0x02, 0x82, 0x02, 0x86, 0x02, 0x86, 0x02, 0x82, 0x02, 0x82, 0x02, 0x82, 0x02, 0x86, 0x02, 0x82,
					0x02, 0x86, 0x02, 0x82, 0x02, 0x82, 0x02, 0x86, 0x02, 0x86, 0x02, 0x86, 0x02, 0x82, 0x02, 0x86,
					0x02,
				};
				for (i = 0; i < sizeof(power)/sizeof(power[0]); i++)
				{
					if ((count[i] < (power[i] - 1)) || (count[i] > (power[i] + 1)))
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
