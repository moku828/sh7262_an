#define	PFCR3		*((volatile short *)0xFFFE38A8)
#define	PFCR2		*((volatile short *)0xFFFE38AA)
#define	STBCR5		*((volatile char  *)0xFFFE0410)
#define	SPCR_0		*((volatile char  *)0xFFFF8000)
#define	SSLP_0		*((volatile char  *)0xFFFF8001)
#define	SPPCR_0		*((volatile char  *)0xFFFF8002)
#define	SPSR_0		*((volatile char  *)0xFFFF8003)
#define	SPDR_0		*((volatile char  *)0xFFFF8004)
#define	SPSCR_0		*((volatile char  *)0xFFFF8008)
#define	SPSSR_0		*((volatile char  *)0xFFFF8009)
#define	SPBR_0		*((volatile char  *)0xFFFF800A)
#define	SPDCR_0		*((volatile char  *)0xFFFF800B)
#define	SPCKD_0		*((volatile char  *)0xFFFF800C)
#define	SSLND_0		*((volatile char  *)0xFFFF800D)
#define	SPND_0		*((volatile char  *)0xFFFF800E)
#define	SPCMD_00	*((volatile short *)0xFFFF8010)
#define	SPBFCR_0	*((volatile char  *)0xFFFF8020)
#define	SPBFDR_0	*((volatile short *)0xFFFF8022)


int main()
{
	volatile unsigned char dmy, mid, mtyp, mcap;
	STBCR5 &= ~0x02;
	SPCR_0 = 0x08;
	SSLP_0 = 0x00;
	SPPCR_0 = 0x00;
	SPSCR_0 = 0x00;
	SPBR_0 = 0x05;
	SPDCR_0 = 0x20;
	SPCKD_0 = 0x00;
	SSLND_0 = 0x00;
	SPND_0 = 0x00;
	SPCMD_00 = 0xE78B;
	SPBFCR_0 |= 0xC0;
	SPBFCR_0 = (SPBFCR_0 & ~0x37) | 0x00;
	SPBFCR_0 &= ~0xC0;
	SPCR_0 |= 0x40;
	PFCR3 = (PFCR3 & ~0x0007) | 0x0003;
	PFCR2 = (PFCR2 & ~0x7770) | 0x3330;
	while ((SPBFDR_0 & 0x0F3F) != 0x0000) ;
	SPDR_0 = 0x9F;
	while ((SPBFDR_0 & 0x0F00) != 0x0000) ;
	while ((SPBFDR_0 & 0x003F) == 0x0000) ;
	dmy = SPDR_0;
	SPDR_0 = 0xFF;
	while ((SPBFDR_0 & 0x003F) == 0x0000) ;
	mid = SPDR_0;
	SPDR_0 = 0xFF;
	while ((SPBFDR_0 & 0x003F) == 0x0000) ;
	mtyp = SPDR_0;
	SPDR_0 = 0xFF;
	while ((SPBFDR_0 & 0x003F) == 0x0000) ;
	mcap = SPDR_0;
	SPDR_0 = 0xFF;
	while (1)
	{
	}
	return 0;
}
