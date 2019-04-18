#include "SerialPort.h"
namespace rfid
{
	//using namespace System::IO::Ports;
	class Comport
	{
	public: static  void RW_Channel(SerialPort  serialPort, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
	public: static  void RW_Datarate(SerialPort serialPort, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
	public: static  void RW_PRF(SerialPort serialPort, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
	public: static  void RW_Preamblecode(SerialPort serialPort, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
	public: static  void RW_PreambleLength(SerialPort serialPort, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
	public: static  void RW_PAC(SerialPort serialPort, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
	public: static  void RW_TX_PGDELAY(SerialPort serialPort, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
	public: static  void RW_TX_POWER(SerialPort serialPort, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
	public: static  void RW_NSD(SerialPort serialPort, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
	public: static  void RW_SFD_Timeout(SerialPort serialPort, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
	public: static  void RW_SMARTPOWER(SerialPort serialPort, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
	public: static  void Read_MODE(SerialPort serialPort, unsigned char* buff, int &flag);
	public: static 	void RW_active_ID(SerialPort serialPort, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
	public: static  void RW_NTM_MULT(SerialPort serialPort, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
	public: static  void RW_Transmission_Cycle(SerialPort serialPort, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
	public: static  void Reset_Chip(SerialPort serialPort, int &flag);
	public: static  void Read_Version(SerialPort serialPort, unsigned char* buff, int &flag);
	public: static  void update_data(SerialPort serialPort, unsigned char* binch, int length, int &flag);
	public: static  void update_check(SerialPort serialPort, unsigned char* binch, int length, int &flag);
	//public: static	void crc16(const unsigned char* buffer, int size, int &crc_value);
	public: static	void send_cmd(SerialPort serialPort, unsigned char* buff_temp, unsigned int length, unsigned char* return_buff_temp);
	};
}
