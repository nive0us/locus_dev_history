
#pragma once
namespace CRC
{
	class CRC32
	{
	public: static  unsigned int crc32(unsigned int crc_accum, unsigned char* data_buff, unsigned int data_blk_size);
	};
}
