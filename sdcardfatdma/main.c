#define	PCCR1		*((volatile short *)0xFFFE384C)
#define	PCIOR0		*((volatile short *)0xFFFE3852)
#define	PCDR0		*((volatile short *)0xFFFE3856)
#define	PFCR3		*((volatile short *)0xFFFE38A8)
#define	PFCR2		*((volatile short *)0xFFFE38AA)
#define	STBCR5		*((volatile char  *)0xFFFE0410)
#define	SPCR_0		*((volatile char  *)0xFFFF8000)
#define	SPPCR_0		*((volatile char  *)0xFFFF8002)
#define	SPSR_0		*((volatile char  *)0xFFFF8003)
#define	SPDR_0		*((volatile char  *)0xFFFF8004)
#define	SPSCR_0		*((volatile char  *)0xFFFF8008)
#define	SPSSR_0		*((volatile char  *)0xFFFF8009)
#define	SPBR_0		*((volatile char  *)0xFFFF800A)
#define	SPDCR_0		*((volatile char  *)0xFFFF800B)
#define	SPCKD_0		*((volatile char  *)0xFFFF800C)
#define	SPND_0		*((volatile char  *)0xFFFF800E)
#define	SPCMD_00	*((volatile short *)0xFFFF8010)
#define	SPBFCR_0	*((volatile char  *)0xFFFF8020)
#define	SPBFDR_0	*((volatile short *)0xFFFF8022)
#define	STBCR2		*((volatile char  *)0xFFFE0018)
#define	SAR_0		*((volatile long  *)0xFFFE1000)
#define	DAR_0		*((volatile long  *)0xFFFE1004)
#define	DMATCR_0	*((volatile long  *)0xFFFE1008)
#define	CHCR_0		*((volatile long  *)0xFFFE100C)
#define	DMAOR		*((volatile short *)0xFFFE1200)
#define	DMARS0		*((volatile short *)0xFFFE1300)

unsigned char spi_trans(unsigned char tx)
{
	unsigned char rx;

	SPDR_0 = tx;
	while ((SPBFDR_0 & 0x0F00) != 0x0000) ;
	while ((SPBFDR_0 & 0x003F) == 0x0000) ;
	rx = SPDR_0;

	return rx;
}

void spi_cs_assert(unsigned int assert)
{
	if (assert)
		PCDR0 &= ~0x0080;
	else
		PCDR0 |= 0x0080;
}

void spi_speed_lowspeed(unsigned int lowspeed)
{
	if (lowspeed)
	{
		SPCR_0 &= ~0x40;
		SPBR_0 = 0x3B;
		SPCR_0 |= 0x40;
	}
	else
	{
		SPCR_0 &= ~0x40;
		SPBR_0 = 0x05;
		SPCR_0 |= 0x40;
	}
}

void sd_trans_dmyclk()
{
	volatile unsigned char rx;
	volatile unsigned long i;

	while ((SPBFDR_0 & 0x0F3F) != 0x0000) ;
	for (i = 0; i < 10; i++)
	{
		SPDR_0 = 0xFF;
		while ((SPBFDR_0 & 0x0F00) != 0x0000) ;
		while ((SPBFDR_0 & 0x003F) == 0x0000) ;
		rx = SPDR_0;
	}
}

int sd_trans_cmd(unsigned char *cmd, unsigned int resp_len, unsigned char *resp, unsigned int spi_mode)
{
	int ret = 0;
	volatile unsigned long i, j;

	spi_cs_assert(spi_mode ? 1 : 0);
	spi_trans(0xFF);

	for (i = 0; i < 6; i++)
		spi_trans(cmd[i]);

	for (j = 0; j < 8; j++)
	{
		resp[0] = spi_trans(0xFF);
		if ((resp[0] & 0x80) == 0x80) continue;
		for (i = 1; i < resp_len; i++)
			resp[i] = spi_trans(0xFF);
		break;
	}
	if (j == 8)
		ret = -1;

	spi_cs_assert(0);
	spi_trans(0xFF);

	return ret;
}

int sd_trans_data_rx(unsigned int data_len, unsigned char *data, unsigned int spi_mode)
{
	int ret = 0;
	volatile unsigned long i, j;
	volatile unsigned char rx;

	spi_cs_assert(spi_mode ? 1 : 0);
	spi_trans(0xFF);

	while (1)
	{
		rx = spi_trans(0xFF);
		if ((rx & 0xE0) == 0x00) return -1;
		if (rx == 0xFE) break;
		for (i = 0; i < 0x40000; i++) ;
	}
	SAR_0 = (long)&SPDR_0;
	DAR_0 = (long)data;
	DMATCR_0 = data_len;
	SPDCR_0 = 0xA0;
	CHCR_0 |= 0x00000001;
	while (1)
	{
		if (CHCR_0 & 0x00000002) break;
	}
	CHCR_0 &= ~0x00000002;
	SPDCR_0 = 0x20;
	spi_trans(0xFF);
	spi_trans(0xFF);

	spi_cs_assert(0);
	spi_trans(0xFF);

	return ret;
}

int main()
{
	unsigned char resp[5];
	unsigned char data[512];
	int ret;
	unsigned char sdsc;
	volatile unsigned long i;
	PCCR1 &= ~0x3330;
	PCIOR0 = (PCIOR0 & ~0x00E0) | 0x0080;
	PCDR0 |= 0x0080;
	STBCR5 &= ~0x02;
	SPCR_0 = 0x08;
	SPPCR_0 = 0x00;
	SPSCR_0 = 0x00;
	SPBR_0 = 0x05;
	SPDCR_0 = 0x20;
	SPCKD_0 = 0x00;
	SPND_0 = 0x00;
	SPCMD_00 = 0xA78B;
	SPBFCR_0 |= 0xC0;
	SPBFCR_0 = (SPBFCR_0 & ~0x37) | 0x00;
	SPBFCR_0 &= ~0xC0;
	SPCR_0 |= 0xC0;
	PFCR3 = (PFCR3 & ~0x0007) | 0x0003;
	PFCR2 = (PFCR2 & ~0x7070) | 0x3030;
	STBCR2 &= ~0x20;
	DMAOR &= ~0x01;
	CHCR_0 &= ~0x00000001;
	CHCR_0 = (CHCR_0 & ~0xB014FF3C) | 0x00004800;
	DMARS0 = (DMARS0 & ~0x00FF) | 0x0052;
	DMAOR |= 0x0007;
	sd_trans_dmyclk();
	spi_speed_lowspeed(1);
	{
		unsigned char cmd0[6] = {0x40, 0x00, 0x00, 0x00, 0x00, 0x95};
		ret = sd_trans_cmd(cmd0, 1, resp, 1);
		if ((ret != 0) || (resp[0] != 0x01)) while (1) ;
	}
	{
		unsigned char cmd8[6] = {0x48, 0x00, 0x00, 0x01, 0xAA, 0x87};
		ret = sd_trans_cmd(cmd8, 5, resp, 1);
		if (ret != 0) while (1) ;
		if ((resp[0] & 0x04) == 0x04) sdsc = 1;
		else
		{
			sdsc = 0;
			if (((resp[3] & 0x0F) != 0x01) || (resp[4] != 0xAA)) while (1) ;
		}
	}
	if (sdsc)
	{
		while (1)
		{
			unsigned char cmd55[6] = {0x77, 0x00, 0x00, 0x00, 0x00, 0x01};
			unsigned char cmd41[6] = {0x69, 0x00, 0x00, 0x00, 0x00, 0x01};
			ret = sd_trans_cmd(cmd55, 1, resp, 1);
			if (ret != 0) while (1) ;
			ret = sd_trans_cmd(cmd41, 1, resp, 1);
			if (ret != 0) while (1) ;
			if (resp[0] == 0x00) break;
			for (i = 0; i < 0x40000; i++) ;
		}
	}
	else
	{
		while (1)
		{
			unsigned char cmd55[6] = {0x77, 0x00, 0x00, 0x00, 0x00, 0x01};
			unsigned char cmd41[6] = {0x69, 0x40, 0x00, 0x00, 0x00, 0x01};
			ret = sd_trans_cmd(cmd55, 1, resp, 1);
			if (ret != 0) while (1) ;
			ret = sd_trans_cmd(cmd41, 1, resp, 1);
			if (ret != 0) while (1) ;
			if (resp[0] == 0x00) break;
			sd_trans_dmyclk();
		}
		{
			unsigned char cmd58[6] = {0x7A, 0x00, 0x00, 0x00, 0x00, 0x01};
			ret = sd_trans_cmd(cmd58, 5, resp, 1);
			if ((ret != 0) || (resp[0] != 0x00)) while (1) ;
			if ((resp[1] & 0x40) == 0x40) sdsc = 1;
			else sdsc = 0;
		}
	}
	spi_speed_lowspeed(0);
	{
		unsigned char cmd16[6] = {0x50, 0x00, 0x00, 0x02, 0x00, 0x01};
		ret = sd_trans_cmd(cmd16, 1, resp, 1);
		if ((ret != 0) || (resp[0] != 0x00)) while (1) ;
	}
	{
		unsigned char cmd17[6] = {0x51, 0x00, 0x00, 0x00, 0x00, 0x01};
		ret = sd_trans_cmd(cmd17, 1, resp, 1);
		if ((ret != 0) || (resp[0] != 0x00)) while (1) ;
	}
	{
		ret = sd_trans_data_rx(512, data, 1);
		if (ret != 0) while (1) ;
	}
	while (1) ;
	return 0;
}
