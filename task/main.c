#define	PCCR2	*((volatile short *)0xFFFE384A)
#define	PCIOR0	*((volatile short *)0xFFFE3852)
#define	PCDR0	*((volatile short *)0xFFFE3856)

typedef struct tagTSKINF {
	int (*addr)(void);
	long* sp;
} TSKINF;

TSKINF tskinf2[2];
extern long tskid;

void sta_tsk(int id, int (*addr)(void))
{
	tskinf2[id].addr = addr;
	tskinf2[id].sp = (long*)(0xFFF8C000 + (0x100 * id));
}

void swt_tsk();

int task2();

int task1()
{
	volatile unsigned long i;
	sta_tsk(1, task2);
	while (1)
	{
		swt_tsk();
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

int task2()
{
	volatile unsigned long i;
	while (1)
	{
		swt_tsk();
		for (i = 0; i < 0x80000; i++)
		{
			;
		}
		PCDR0 |= 0x0100;
		for (i = 0; i < 0x80000; i++)
		{
			;
		}
		PCDR0 &= ~0x0100;
	}
	return 0;
}

int main()
{
	volatile unsigned long i;
	tskid = 0;
	PCCR2 &= ~0x0003;
	PCIOR0 |= 0x0100;
	sta_tsk(0, task1);
	while (1)
	{
	}
	return 0;
}
