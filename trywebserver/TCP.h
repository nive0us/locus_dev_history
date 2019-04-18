
namespace rfid
{
//	using namespace System;
	class TCP
	{
	public: static  void send_cmd(char* ip_addr, int ip_port, unsigned char* buff_temp, unsigned int length, unsigned char* return_buff_temp);
	public: static  void RW_IP(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
	public: static  void RW_GatewayIP(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
	public: static  void RW_MaskIP(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
	public: static  void RW_ClientIP(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
	public: static  void RW_Channel(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
	public: static  void RW_Datarate(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
	public: static  void RW_PRF(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
	public: static  void RW_Preamblecode(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
	public: static  void RW_PreambleLength(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
	public: static  void RW_PAC(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
	public: static  void RW_TX_PGDELAY(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
	public: static  void RW_TX_POWER(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
	public: static  void RW_NSD(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
	public: static  void RW_SFD_Timeout(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
	public: static  void RW_SMARTPOWER(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
	public: static  void Read_MODE(char* ip_addr, int ip_port, unsigned char* buff, int &flag);
	public: static 	void RW_active_ID(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
	public: static  void RW_NTM_MULT(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
	public: static 	void RW_Transmission_Cycle(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
	public: static  void Reset_Chip(char* ip_addr, int ip_port, int &flag);
	public: static  void Read_Version(char* ip_addr, int ip_port, unsigned char* buff, int &flag);
	public: static  void update_data(char* ip_addr, int ip_port, unsigned char* binch, int length, int &flag);
	public: static  void update_check(char* ip_addr, int ip_port, unsigned char* binch, int length, int &flag);
	public: static  void TCP_sendpackage(char* ip_addr, int ip_port, int net_str_length, int eoco_length, char* net_str, char* buff);
	public: static	void crc16(const unsigned char* buffer, int size, int &crc_value);
	};
}


