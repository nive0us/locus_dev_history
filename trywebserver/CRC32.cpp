//#include "stdafx.h"
#include "CRC32.h"
#define	 CRC32_POLYNOMIAL  ((unsigned int)0x04C11DB7U)      // Standard CRC-32 ppolynomial
#pragma once
namespace CRC
{
	unsigned int crc_table[256];
	void gen_crc32_table(void);
	void gen_crc32_table(void)
	{
		unsigned short i, j;
		unsigned int crc_accum;

		for (i = 0; i < 256; i++)
		{
			crc_accum = ((unsigned int)i << 24U);
			for (j = 0; j < 8; j++)
			{
				if (crc_accum & 0x80000000UL)
					crc_accum = (crc_accum << 1) ^ CRC32_POLYNOMIAL;
				else
					crc_accum = (crc_accum << 1);
			}
			crc_table[i] = crc_accum;
		}
	}
	unsigned int CRC32::crc32(unsigned int crc_accum, unsigned char* data_buff, unsigned int data_blk_size)
	{
		unsigned int i, j, err = 0;
		gen_crc32_table();
		for (j = 0; j < data_blk_size; j++)
		{
			i = ((unsigned int)(crc_accum >> 24U) ^ data_buff[j]) & 0xFFU;
			crc_accum = (crc_accum << 8U) ^ crc_table[i];
		}
		crc_accum = ~crc_accum;
		return crc_accum;
	}
}
