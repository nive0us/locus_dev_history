#include <iostream>
#define Byte BYTE
//typedef unsigned char Byte;
#include "ser.h"
#include"Comport.h"

//#include<windows.h>
#include <array>
#define demo 0
#define Error_toobig 3
#define Error_toosmall 4
#define Fail 2
#define Timeout 5
#define RS485ID 0xFF
#define success 1
#define None_Stop 6
#define Outputvalue3 0xFF

namespace rfid
{
	//using namespace System;
	//using namespace System::IO::Ports;
	int crc16( array<Byte,256> buffer, int size);
	//int ss;
	int Comport_link(SerialPort *serialPort, int write_length, array<Byte, 2048> write_buf, int &read_length, array<Byte, 2048>  read_buf);
	void send_cmd_data(SerialPort serialPort, int cmdID, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
	int check_data_crc(array<Byte,2048> encodedBytes, int length, int offset, unsigned char* buff, int data_len);
	int  crc16(array<Byte, 256>  buffer, int size)
	{

		unsigned short tmp;
		unsigned short crc = 0xffff;
		int crc2[256] = {
			0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7,
			0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef,
			0x1231, 0x0210, 0x3273, 0x2252, 0x52b5, 0x4294, 0x72f7, 0x62d6,
			0x9339, 0x8318, 0xb37b, 0xa35a, 0xd3bd, 0xc39c, 0xf3ff, 0xe3de,
			0x2462, 0x3443, 0x0420, 0x1401, 0x64e6, 0x74c7, 0x44a4, 0x5485,
			0xa56a, 0xb54b, 0x8528, 0x9509, 0xe5ee, 0xf5cf, 0xc5ac, 0xd58d,
			0x3653, 0x2672, 0x1611, 0x0630, 0x76d7, 0x66f6, 0x5695, 0x46b4,
			0xb75b, 0xa77a, 0x9719, 0x8738, 0xf7df, 0xe7fe, 0xd79d, 0xc7bc,
			0x48c4, 0x58e5, 0x6886, 0x78a7, 0x0840, 0x1861, 0x2802, 0x3823,
			0xc9cc, 0xd9ed, 0xe98e, 0xf9af, 0x8948, 0x9969, 0xa90a, 0xb92b,
			0x5af5, 0x4ad4, 0x7ab7, 0x6a96, 0x1a71, 0x0a50, 0x3a33, 0x2a12,
			0xdbfd, 0xcbdc, 0xfbbf, 0xeb9e, 0x9b79, 0x8b58, 0xbb3b, 0xab1a,
			0x6ca6, 0x7c87, 0x4ce4, 0x5cc5, 0x2c22, 0x3c03, 0x0c60, 0x1c41,
			0xedae, 0xfd8f, 0xcdec, 0xddcd, 0xad2a, 0xbd0b, 0x8d68, 0x9d49,
			0x7e97, 0x6eb6, 0x5ed5, 0x4ef4, 0x3e13, 0x2e32, 0x1e51, 0x0e70,
			0xff9f, 0xefbe, 0xdfdd, 0xcffc, 0xbf1b, 0xaf3a, 0x9f59, 0x8f78,
			0x9188, 0x81a9, 0xb1ca, 0xa1eb, 0xd10c, 0xc12d, 0xf14e, 0xe16f,
			0x1080, 0x00a1, 0x30c2, 0x20e3, 0x5004, 0x4025, 0x7046, 0x6067,
			0x83b9, 0x9398, 0xa3fb, 0xb3da, 0xc33d, 0xd31c, 0xe37f, 0xf35e,
			0x02b1, 0x1290, 0x22f3, 0x32d2, 0x4235, 0x5214, 0x6277, 0x7256,
			0xb5ea, 0xa5cb, 0x95a8, 0x8589, 0xf56e, 0xe54f, 0xd52c, 0xc50d,
			0x34e2, 0x24c3, 0x14a0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
			0xa7db, 0xb7fa, 0x8799, 0x97b8, 0xe75f, 0xf77e, 0xc71d, 0xd73c,
			0x26d3, 0x36f2, 0x0691, 0x16b0, 0x6657, 0x7676, 0x4615, 0x5634,
			0xd94c, 0xc96d, 0xf90e, 0xe92f, 0x99c8, 0x89e9, 0xb98a, 0xa9ab,
			0x5844, 0x4865, 0x7806, 0x6827, 0x18c0, 0x08e1, 0x3882, 0x28a3,
			0xcb7d, 0xdb5c, 0xeb3f, 0xfb1e, 0x8bf9, 0x9bd8, 0xabbb, 0xbb9a,
			0x4a75, 0x5a54, 0x6a37, 0x7a16, 0x0af1, 0x1ad0, 0x2ab3, 0x3a92,
			0xfd2e, 0xed0f, 0xdd6c, 0xcd4d, 0xbdaa, 0xad8b, 0x9de8, 0x8dc9,
			0x7c26, 0x6c07, 0x5c64, 0x4c45, 0x3ca2, 0x2c83, 0x1ce0, 0x0cc1,
			0xef1f, 0xff3e, 0xcf5d, 0xdf7c, 0xaf9b, 0xbfba, 0x8fd9, 0x9ff8,
			0x6e17, 0x7e36, 0x4e55, 0x5e74, 0x2e93, 0x3eb2, 0x0ed1, 0x1ef0
		};

		for (int i = 0; i < size; i++)
		{

			tmp = (crc >> 8) ^ buffer[i];
			crc = (crc << 8) ^ crc2[tmp];

		}
		return crc;
	}

	void send_cmd_data(SerialPort serialPort, int cmdID, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag)
	{
		array<Byte, 2048>  buf_temp ;//= new array<Byte,2048>;
		int temp_length = 0,crc_velue=0,read_length=0;
		array<Byte,2048>  buffer ;//= gcnew array<Byte>(2048);

		array<Byte,256>  buffer_256 ;

		unsigned char temp[] = { 0xF8, 0xFA, 0x00, 0x06, 0x00, 0x04, (unsigned char)cmdID, (unsigned char)RW };
		for (size_t i = 0; i < sizeof(temp); i++)
			buffer[i] = temp[i];
		if (RW == 1)
		{
			temp_length = buffer[4] * 256 + buffer[5] + 6 + set_length;
			buffer[4] = (temp_length - 6) / 256;
			buffer[5] = (temp_length - 6) % 256;
			for (size_t i = 0; i < (unsigned int)set_length; i++)
				buffer[8 + i] = Set_data[i];
		}
		else
			temp_length = buffer[4] * 256 + buffer[5] + 6;

        printf( "buffer_256 size is : %d\n" ,  sizeof(buffer_256 ) ) ;

        for ( int i = 0 ; i < sizeof(buffer_256) ; i++)
            buffer_256[i] = buffer[i];

		crc_velue = crc16(buffer_256, temp_length - 2);
		printf( "crc val : %d\n", crc_velue ) ;

		for ( int i = 0 ; i < sizeof(buffer_256) ; i++)
            buffer[i] = buffer_256[i];

		buffer[temp_length - 2] = crc_velue / 256;
		buffer[temp_length - 1] = crc_velue % 256;


		try{
			//serialPort->DiscardInBuffer();
			//serialPort->DiscardOutBuffer();
			flag = Comport_link(&serialPort, temp_length, buffer, read_length, buf_temp);
			if (flag == success)
				flag = check_data_crc(buf_temp, read_length, 6, buff, read_length - 9);
			else
			{
				int test = 1;
			}
		}
		catch (exception )
		{
		}
	}
	int check_data_crc(array<Byte,2048>  encodedBytes, int length, int offset, unsigned char* buff, int data_len)
	{
		int crc_value = 0;

		array<Byte,256>  buffer_256 ;
		for ( int i = 0 ; i < sizeof(buffer_256) ; i++)
            buffer_256[i] = encodedBytes[i];

		crc_value = crc16(buffer_256, length - 2);

		for ( int i = 0 ; i < sizeof(buffer_256) ; i++)
            encodedBytes[i] = buffer_256[i];


		if (encodedBytes[0] == 0)
			return  Timeout;
		else if ((crc_value / 256 == encodedBytes[length - 2]) && (crc_value % 256 == encodedBytes[length - 1]) && (encodedBytes[length - 3] == 0x01))
		{
			for (size_t i = 0; i < (unsigned int)data_len; i++)
				buff[i] = encodedBytes[offset + i];
			return success;
		}
		else
			return Fail;
	}
	void Comport::send_cmd(SerialPort  serialPort, unsigned char* buff_temp, unsigned int length, unsigned char* return_buff_temp)
	{
		////char buff[1024] = { 0 };
		//int temp_length = 0, read_length = 0;

		//unsigned char buffer[1024] = { 0 };
		//for (size_t i = 0; i < length; i++)
		//	buffer[i] = buff_temp[i];
		//temp_length = length;
		//crc16(buffer, temp_length - 2, s);
		//char* mybytes = new char[temp_length];
		//for (size_t i = 0; i < temp_length - 2; i++)
		//	mybytes[i] = buffer[i];

		//mybytes[temp_length - 2] = s / 256;
		//mybytes[temp_length - 1] = s % 256;
		//TCP_link(ip_addr, ip_port, temp_length, read_length, mybytes, (char*)return_buff_temp);
		////flag = check_data(buff, Set_ip_addr);

		//delete[] mybytes;


		array<Byte,2048>  buf_temp ;//= gcnew array<Byte>(2048);
		int temp_length = 0, crc_velue = 0, read_length = 0;
		array<Byte,2048>  buffer ;//= gcnew array<Byte>(2048);
		//unsigned char buffer[1024] = { 0 };
		//unsigned char temp[] = { 0xF8, 0xFA, 0x00, 0x06, 0x00, 0x04, cmdID, RW };
		for (size_t i = 0; i < length; i++)
			buffer[i] = buff_temp[i];
		//if (RW == 1)
		//{
		//	temp_length = buffer[4] * 256 + buffer[5] + 6 + set_length;
		//	buffer[4] = (temp_length - 6) / 256;
		//	buffer[5] = (temp_length - 6) % 256;
		//	for (size_t i = 0; i < set_length; i++)
		//		buffer[8 + i] = Set_data[i];
		//}
		//else
		//	temp_length = buffer[4] * 256 + buffer[5] + 6;
        array<Byte,256>  buffer_256;
		for ( int i = 0 ; i < sizeof(buffer_256) ; i++)
            buffer_256[i] = buffer[i];


		crc_velue = crc16(buffer_256, length - 2);
		for ( int i = 0 ; i < sizeof(buffer_256) ; i++)
            buffer[i] = buffer_256[i];


		buffer[length - 2] = crc_velue / 256;
		buffer[length - 1] = crc_velue % 256;
		try{
			//serialPort->DiscardInBuffer();
			//serialPort->DiscardOutBuffer();
			Comport_link(&serialPort, length, buffer, read_length, buf_temp);
			for (size_t i = 0; i < (unsigned int)read_length; i++)
			{
				return_buff_temp[i] = buf_temp[i];
			}
		}
		catch ( exception )
		{
		}
		//if (flag == success)
			//flag = check_data_crc(buf_temp, read_length, 6, buff, read_length - 9);
	}
	void Comport::Read_Version(SerialPort serialPort, unsigned char* buff, int &flag)
	{
		int cmdID = 0x1D;
		send_cmd_data(serialPort, cmdID, 0, NULL, 0, buff, flag);
	}
	void Comport::RW_SMARTPOWER(SerialPort  serialPort, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag)
	{
		int cmdID = 0x42;
		send_cmd_data(serialPort, cmdID, RW, Set_data, set_length, buff, flag);
	}
	void Comport::RW_SFD_Timeout(SerialPort  serialPort, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag)
	{
		int cmdID = 0x41;
		send_cmd_data(serialPort, cmdID, RW, Set_data, set_length, buff, flag);
	}
	void Comport::RW_NSD(SerialPort  serialPort, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag)
	{
		int cmdID = 0x40;
		send_cmd_data(serialPort, cmdID, RW, Set_data, set_length, buff, flag);
	}
	void Comport::RW_TX_POWER(SerialPort  serialPort, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag)
	{
		int cmdID = 0x3F;
		send_cmd_data(serialPort, cmdID, RW, Set_data, set_length, buff, flag);
	}
	void Comport::RW_TX_PGDELAY(SerialPort  serialPort, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag)
	{
		int cmdID = 0x3E;
		send_cmd_data(serialPort, cmdID, RW, Set_data, set_length, buff, flag);
	}
	void Comport::RW_PAC(SerialPort  serialPort, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag)
	{
		int cmdID = 0x3D;
		send_cmd_data(serialPort, cmdID, RW, Set_data, set_length, buff, flag);
	}
	void Comport::RW_PreambleLength(SerialPort  serialPort, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag)
	{
		int cmdID = 0x3C;
		send_cmd_data(serialPort, cmdID, RW, Set_data, set_length, buff, flag);
	}
	void Comport::RW_Preamblecode(SerialPort  serialPort, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag)
	{
		int cmdID = 0x3B;
		send_cmd_data(serialPort, cmdID, RW, Set_data, set_length, buff, flag);
	}
	void Comport::RW_PRF(SerialPort  serialPort, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag)
	{
		int cmdID = 0x3A;
		send_cmd_data(serialPort, cmdID, RW, Set_data, set_length, buff, flag);
	}
	void Comport::RW_Datarate(SerialPort  serialPort, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag)
	{
		int cmdID = 0x39;
		send_cmd_data(serialPort, cmdID, RW, Set_data, set_length, buff, flag);
	}
	void Comport::RW_Channel(SerialPort  serialPort, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag)
	{
		int cmdID = 0x38;
		send_cmd_data(serialPort, cmdID, RW, Set_data, set_length, buff, flag);
	}
	void Comport::Read_MODE(SerialPort  serialPort, unsigned char* buff, int &flag)
	{
		int cmdID = 0x2D;
		send_cmd_data(serialPort, cmdID, 0, NULL, 0, buff, flag);
	}
	void Comport::RW_active_ID(SerialPort  serialPort, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag)
	{
		int cmdID = 0x35;
		send_cmd_data(serialPort, cmdID, RW, Set_data, set_length, buff, flag);
	}
	void Comport::RW_NTM_MULT(SerialPort  serialPort, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag)
	{
		int cmdID = 0x44;
		send_cmd_data(serialPort, cmdID, RW, Set_data, set_length, buff, flag);
	}
	void Comport::RW_Transmission_Cycle(SerialPort  serialPort, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag)
	{
		int cmdID = 0x2E;
		send_cmd_data(serialPort, cmdID, RW, Set_data, set_length, buff, flag);
	}
	void Comport::Reset_Chip(SerialPort  serialPort, int &flag)
	{
		flag = 0;
		int cmdID = 0x1F;
		char buff[2048] = { 0 };
		send_cmd_data(serialPort, cmdID, 1, NULL, 0, (unsigned char*)buff, flag);
	}
	void Comport::update_data(SerialPort  serialPort, unsigned char* binch, int length, int &flag)
	{
		flag = 0;
		int cmdID = 0x18;
		char buff[2048] = { 0 };
		send_cmd_data(serialPort, cmdID, 1, binch, length, (unsigned char*)buff, flag);
	}
	void Comport::update_check(SerialPort  serialPort, unsigned char* binch, int length, int &flag)
	{
		int cmdID = 0x19;
		char buff[2048] = { 0 };
		send_cmd_data(serialPort, cmdID, 1, binch, length, (unsigned char*)buff, flag);
	}
int Comport_link(SerialPort  *serialPort, int write_length, array<Byte,2048>  write_buf,int &read_length, array<Byte,2048>  read_buf)
	{
		//serialPort->Write(write_buf, 0, write_length);
		unsigned char write_buf2 [2048] = {0};
		for ( int i = 0 ; i < sizeof(write_buf) ; i++)
            write_buf2[i] = (unsigned char)write_buf[i];

		serialPort->Port_Write( write_buf2, write_length );
		cout << "write OK" << endl ;

		int crc_value = 0,read_count=0;

		//win
		//serialPort->ReadTimeout = 1000;

		//linux
		//serialPort->ReadTimeout = 10;

		try
		{
			//serialPort->DiscardOutBuffer();
			while (1)
			{
				//serialPort->Read(read_buf, read_count, 1);

				serialPort->Port_Read(read_buf,read_count);

				//serialPort->ReadTimeout = 5; // 5 ms
				//serialPort->ReadTimeout = 1 ; // 0.1s
				read_count++;
				if ((((read_buf[4] << 8) + read_buf[5] + 6) == read_count) && (((read_buf[4] << 8) + read_buf[5] + 6)!=6))
					break;
			}
		}
		catch ( exception )
		{
			return Timeout;
		}
		read_length = read_count;
		return success;
	}

}
