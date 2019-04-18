
#define _BSD_SOURCE


#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>


#define NO_ERROR 0L                                                 // dderror
#define SEC_E_OK                         ((HRESULT)0x00000000L)

typedef struct timeval TIMEVAL;
#include <sys/ioctl.h>
#include <sys/time.h>
#include <unistd.h>
#define SOCKET_ERROR            (-1)

//#include "stdafx.h"
#include <string>
#include"TCP.h"
//#include <WinSock2.h>
//#pragma comment(lib, "Ws2_32.lib")
#define demo 0
#define Error_toobig 3
#define Error_toosmall 4
#define Fail 2
#define Timeout 5
#define RS485ID 0xFF
#define success 1
#define Outputvalue3 0xFF
using namespace std;
namespace rfid
{
//	using namespace System::Runtime::InteropServices;
//	using namespace System;
	void TCP_link(char* ip_addr, int ip_port, int net_str_length, int &eoco_length, char* net_str, char* buff);
	void check_data_ID(char* buff, int length);
	void check_data_Version(char* buff, int length);
	void check_data_value(char* buff, int length);
	void check_data_Parameter(char* buff, int length);
	void check_data_Parameter_test(char* buff, int length);
	void ADDR(char* addr, int &addr1, int &addr2, int &addr3, int &addr4);
	int check_data(char* buff, int length);
	volatile unsigned short ID_NUM = 0;
	int cheakCRCbuff = 0;
	volatile long check_connect = 0;
	int IDlength = 10, LVlength = 33, cheak_set = 13, Valuelength = 33, Power_set = 9, Delay_set = 9, Db_set = 9, Freq_set = 9, Output_set = 9, Area_set = 9, Em_set = 9, Updatelength = 9, Set_ip_port = 9, Set_gateway = 9, Set_ipaddr = 9, Set_netmask = 9;
	int Set_ip_addr = 9;
	int s;
	int EPClen = 0;
	static int *tag_data_temp;
	int check_data_crc(char* encodedBytes, int length, int offset, unsigned char* buff, int data_len);
	void send_cmd_data(char* ip_addr, int ip_port, int cmdID, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);

	void TCP::send_cmd(char* ip_addr, int ip_port, unsigned char* buff_temp, unsigned int length, unsigned char* return_buff_temp)
	{
		//char buff[1024] = { 0 };
		int temp_length = 0,read_length=0;

		unsigned char buffer[1024] = {0};
		for (size_t i = 0; i < length; i++)
			buffer[i]=buff_temp[i];
		temp_length = length;
		crc16(buffer, temp_length - 2, s);
		char* mybytes = new char[temp_length];
		for (size_t i = 0; i < (unsigned int)(temp_length - 2); i++)
			mybytes[i] = buffer[i];

		mybytes[temp_length - 2] = s / 256;
		mybytes[temp_length - 1] = s % 256;
		TCP_link(ip_addr, ip_port, temp_length, read_length, mybytes, (char*)return_buff_temp);
		//flag = check_data(buff, Set_ip_addr);

		delete[] mybytes;
	}
	void ADDR(char* addr, int &addr1, int &addr2, int &addr3, int &addr4)
	{
		int count = 0;
		char add1[3] = { 0 }, add2[3] = { 0 }, add3[3] = { 0 }, add4[3] = { 0 };
		for (size_t i = 0, j = 0; addr[i] != '\0'; i++, j++)
		{
			if (addr[i] == '.')
			{
				count++;
				j = -1;
			}
			else if (count == 0)
			{
				add1[j] = addr[i];
				add1[j + 1] = 0;
			}
			else if (count == 1)
			{
				add2[j] = addr[i];
				add2[j + 1] = 0;
			}
			else if (count == 2)
			{
				add3[j] = addr[i];
				add3[j + 1] = 0;
			}
			else if (count == 3)
			{
				add4[j] = addr[i];
				add4[j + 1] = 0;
			}
		}
		//std::string* addr_temp = Marshal::PtrToStringAnsi((IntPtr)(char *)add1);
		//addr1 = (Convert::ToInt32(addr_temp));
//		addr_temp = Marshal::PtrToStringAnsi((IntPtr)(char *)add2);
//		addr2 = (Convert::ToInt32(addr_temp));
//		addr_temp = Marshal::PtrToStringAnsi((IntPtr)(char *)add3);
//		addr3 = (Convert::ToInt32(addr_temp));
//		addr_temp = Marshal::PtrToStringAnsi((IntPtr)(char *)add4);
//		addr4 = (Convert::ToInt32(addr_temp));
        addr1 = atoi(add1);
        addr2 = atoi(add2);
        addr3 = atoi(add3);
        addr4 = atoi(add4);

	}
	void send_cmd_data(char* ip_addr, int ip_port,int cmdID, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag)
	{
		char buf_temp[2048] = { 0 };
		int temp_length = 0,read_length=0;
		unsigned char buffer[2048] = { 0xF8, 0xFA, 0x00, 0x06, 0x00, 0x04, (unsigned char)cmdID, (unsigned char)RW };
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
		TCP::crc16(buffer, temp_length - 2, s);
		buffer[temp_length - 2] = s / 256;
		buffer[temp_length - 1] = s % 256;
		TCP_link(ip_addr, ip_port, temp_length, read_length, (char*)buffer, (char*)buf_temp);
		flag = check_data_crc((char*)buf_temp, read_length, 6, buff, (read_length - 9));
	}
	void TCP::RW_Transmission_Cycle(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag)
	{
		int cmdID = 0x2E;
		send_cmd_data(ip_addr, ip_port, cmdID, RW, Set_data, set_length, buff, flag);
	}
	void TCP::RW_SMARTPOWER(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag)
	{
		int cmdID = 0x42;
		send_cmd_data(ip_addr, ip_port, cmdID, RW, Set_data, set_length, buff, flag);
	}
	void TCP::RW_SFD_Timeout(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag)
	{
		int cmdID = 0x41;
		send_cmd_data(ip_addr, ip_port, cmdID, RW, Set_data, set_length, buff, flag);
	}
	void TCP::RW_NSD(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag)
	{
		int cmdID = 0x40;
		send_cmd_data(ip_addr, ip_port, cmdID, RW, Set_data, set_length, buff, flag);
	}
	void TCP::RW_TX_POWER(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag)
	{
		int cmdID = 0x3F;
		send_cmd_data(ip_addr, ip_port, cmdID, RW, Set_data, set_length, buff, flag);
	}
	void TCP::RW_TX_PGDELAY(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag)
	{
		int cmdID = 0x3E;
		send_cmd_data(ip_addr, ip_port, cmdID, RW, Set_data, set_length, buff, flag);
	}
	void TCP::RW_PAC(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag)
	{
		int cmdID = 0x3D;
		send_cmd_data(ip_addr, ip_port, cmdID, RW, Set_data, set_length, buff, flag);
	}
	void TCP::RW_PreambleLength(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag)
	{
		int cmdID = 0x3C;
		send_cmd_data(ip_addr, ip_port, cmdID, RW, Set_data, set_length, buff, flag);
	}
	void TCP::RW_Preamblecode(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag)
	{
		int cmdID = 0x3B;
		send_cmd_data(ip_addr, ip_port, cmdID, RW, Set_data, set_length, buff, flag);
	}
	void TCP::RW_PRF(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag)
	{
		int cmdID = 0x3A;
		send_cmd_data(ip_addr, ip_port, cmdID, RW, Set_data, set_length, buff, flag);
	}
	void TCP::RW_Datarate(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag)
	{
		int cmdID = 0x39;
		send_cmd_data(ip_addr,ip_port,cmdID,RW,Set_data,set_length,buff,flag);
	}
	void TCP::RW_IP(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag)
	{
		int cmdID = 0x01;
		send_cmd_data(ip_addr, ip_port, cmdID, RW, Set_data, set_length, buff, flag);
	}
	void TCP::RW_GatewayIP(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag)
	{
		int cmdID = 0x02;
		send_cmd_data(ip_addr, ip_port, cmdID, RW, Set_data, set_length, buff, flag);
	}
	void TCP::RW_MaskIP(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag)
	{
		int cmdID = 0x03;
		send_cmd_data(ip_addr, ip_port, cmdID, RW, Set_data, set_length, buff, flag);
	}
	void TCP::RW_ClientIP(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag)
	{
		int cmdID = 0x07;
		send_cmd_data(ip_addr, ip_port, cmdID, RW, Set_data, set_length, buff, flag);
	}
	void TCP::RW_Channel(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag)
	{
		int cmdID = 0x38;
		send_cmd_data(ip_addr, ip_port, cmdID, RW, Set_data, set_length, buff, flag);
	}
	void TCP::Read_MODE(char* ip_addr, int ip_port, unsigned char* buff, int &flag)
	{
		int cmdID = 0x2D;
		send_cmd_data(ip_addr, ip_port, cmdID, 0, NULL, 0, buff, flag);
	}
	void TCP::RW_active_ID(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag)
	{
		int cmdID = 0x35;
		send_cmd_data(ip_addr, ip_port, cmdID, RW, Set_data, set_length, buff, flag);
	}
	void TCP::RW_NTM_MULT(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag)
	{
		int cmdID = 0x44;
		send_cmd_data(ip_addr, ip_port, cmdID, RW, Set_data, set_length, buff, flag);
	}
	void TCP::Read_Version(char* ip_addr, int ip_port, unsigned char* buff, int &flag)
	{
		int cmdID = 0x1D;
		send_cmd_data(ip_addr, ip_port, cmdID, 0, NULL, 0, buff, flag);
	}
	void TCP::Reset_Chip(char* ip_addr, int ip_port, int &flag)
	{
		flag = 0;
		int cmdID = 0x1F;
		char buff[2048] = { 0 };
		send_cmd_data(ip_addr, ip_port, cmdID, 1, NULL, 0, (unsigned char*)buff, flag);
	}
	void TCP::update_data(char* ip_addr, int ip_port, unsigned char* binch, int length, int &flag)
	{
		flag = 0;
		int cmdID = 0x18;
		char buff[2048] = { 0 };
		send_cmd_data(ip_addr, ip_port, cmdID, 1, binch, length, (unsigned char*)buff, flag);
	}
	void TCP::update_check(char* ip_addr, int ip_port, unsigned char* binch, int length, int &flag)
	{
		int cmdID = 0x19;
		char buff[2048] = { 0 };
		send_cmd_data(ip_addr, ip_port, cmdID, 1, binch, length, (unsigned char*)buff, flag);
	}
	int check_data_crc(char* encodedBytes, int length,int offset,unsigned char* buff,int data_len)
	{
		TCP::crc16((unsigned char*)encodedBytes, length - 2, s);
		if (encodedBytes[0] == 0)
			return  Timeout;
		else if (s / 256 == (unsigned char)encodedBytes[length - 2] && s % 256 == (unsigned char)encodedBytes[length - 1] && (unsigned char)encodedBytes[length - 3] == 0x01)
		{
			for (size_t i = 0; i < (unsigned int)data_len; i++)
				buff[i] = encodedBytes[offset + i];
			return success;
		}
		else
			return Fail;
	}
	int check_data(char* encodedBytes, int length)
	{

		unsigned char cheakbuff[20] = { 0 };
		for (size_t i = 0; i < (unsigned int)(length - 2); i++)
		{
			cheakbuff[i] = encodedBytes[i];
		}
		TCP::crc16(cheakbuff, length - 2, s);
		for (size_t i = 0; i < (unsigned int)length; i++)
		{
			cheakbuff[0] = encodedBytes[i] + cheakbuff[0];
			if (cheakbuff[0] != 0)
				break;
		}
		if (cheakbuff[0] == 0)
		{
			cheakCRCbuff = Timeout;
		}
		else if (s / 256 == (unsigned char)encodedBytes[length - 2] && s % 256 == (unsigned char)encodedBytes[length - 1] && (unsigned char)encodedBytes[length - 3] == 0x01)
		{
			cheakCRCbuff = success;
		}
		else
		{
			cheakCRCbuff = Fail;
		}

		return cheakCRCbuff;
	}
	void TCP::TCP_sendpackage(char* ip_addr, int ip_port, int net_str_length, int eoco_length, char* net_str, char* buff)
	{
		//array<Byte>^ encoded_string = gcnew array<Byte>(3000);
		//		rfid::TCP::Close_connect();
		//WSADATA wsaData;
		int sockClient;
        struct sockaddr_in addrSrv;

		//SOCKADDR_IN addrSrv;
		//SOCKET sockClient;

		//WSACleanup();
		//	char buff[3000] = { 0 };
		try
		{
		    /*
			if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
			{
				//			System::Windows::Forms::DialogResult result = MessageBox::Show(this, "Failed to load Winsock", "注意", MessageBoxButtons::OK);
				//closesocket(sockClient);
				//WSACleanup();
				return;
				//return buff;

			}
			*/

			addrSrv.sin_family = AF_INET;
			addrSrv.sin_port = htons(ip_port);
			addrSrv.sin_addr.s_addr = inet_addr(ip_addr);



			//****add part*******************
			/*
			struct sockaddr_in client_addr;
            //bzero(&client_addr,sizeof(client_addr)); //把一段内存区的内容全部设置为0
            client_addr.sin_family = AF_INET;    //internet协议族
            client_addr.sin_addr.s_addr = htons(INADDR_ANY);//INADDR_ANY表示自动获取本机地址
            client_addr.sin_port = htons(0);    //0表示让系统自动分配一个空闲端口
            //*/
			///****add end******************************

			sockClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if ( sockClient == SOCKET_ERROR  ){
				//System::Windows::Forms::DialogResult result = MessageBox::Show(this, "Socket() error:" + WSAGetLastError(), "注意", MessageBoxButtons::OK);
                //closesocket(sockClient);
                //WSACleanup();
                close(sockClient);
				return;
				//return buff;
			}



			//***add part**********************
			/*
			if( bind(sockClient,(struct sockaddr*)&client_addr,sizeof(client_addr)))
            {
                printf("Client Bind Port Failed!\n");
                return;
            }
            //*/
			// ***add end*************************



			TIMEVAL D_timeout;
			D_timeout.tv_sec = 0;
			D_timeout.tv_usec = 100000;


            //unsigned long iMode = 1;
            //int iResult = ioctlsocket(sockClient, FIONBIO, &iMode);

			int flags = fcntl(sockClient, F_GETFL, 0);
            int iResult = fcntl(sockClient, F_SETFL, flags|O_NONBLOCK);

			if (iResult != NO_ERROR)
			{	//return buff;
                //closesocket(sockClient);
                //WSACleanup();
                close(sockClient);
				return;
			}

			if ( connect(sockClient, (struct  sockaddr*)&addrSrv, sizeof(addrSrv) ) < 0 ) {
                printf("Connection error");
			}

            //iMode = 0;
            //iResult = ioctlsocket(sockClient, FIONBIO, &iMode);

            flags = fcntl(sockClient, F_GETFL, 0);
            //iResult = fcntl(sockClient, F_SETFL, flags|O_NONBLOCK);
            iResult = fcntl(sockClient, F_SETFL, flags&~O_NONBLOCK);

			if (iResult != NO_ERROR)
			{
                //closesocket(sockClient);
                //WSACleanup();
				close(sockClient);
				return;
				//return buff;
			}

			fd_set Write, Err;
			FD_ZERO(&Write);
			FD_ZERO(&Err);
			FD_SET(sockClient, &Write);
			FD_SET(sockClient, &Err);

			select(0, NULL, &Write, &Err, &D_timeout);

            //if (Write.fd_count != 1)
            if (FD_ISSET(0, &Err))
                printf("A key was pressed!\n");
            else
                printf("Timed out.\n");

            if ( FD_SETSIZE !=1 )
			{
                //closesocket(sockClient);
                //WSACleanup();
				close(sockClient);
				return;
				//return buff;
			}

			/*/ win
			int nNetTimeout = 5000;//1秒 //傳送時限 setsockopt(socket，SOL_S0CKET,SO_SNDTIMEO，(char *)&nNetTimeout,sizeof(int));
			setsockopt(sockClient, SOL_SOCKET, SO_SNDTIMEO, (char *)&nNetTimeout, sizeof(int));
			setsockopt(sockClient, SOL_SOCKET, SO_RCVTIMEO, (char *)&nNetTimeout, sizeof(int));
			//*/

			struct timeval timeout={5,0};// {sec,ms}
			int sndto = setsockopt(sockClient,SOL_SOCKET, SO_SNDTIMEO,(const void*) &timeout, sizeof(timeout));
            int rcvto = setsockopt(sockClient,SOL_SOCKET, SO_RCVTIMEO,(const void*) &timeout, sizeof(timeout));
            if ( sndto != 0 || rcvto != 0 )
                printf( "time eor\n" );


			//	Sleep(100);
			send(sockClient, net_str, net_str_length, 0);
			int test_cheak = 0;
			int testi = 0, i = 0;
			//Sleep(100);
			while (1)
			{
				if (eoco_length == 0)
					break;
				test_cheak = recv(sockClient, buff + i * 1446, eoco_length, 0);
				//if (test_cheak == 1446)
				//{
				//}
				if (test_cheak != 0)
					break;
				if (testi == 100)
					break;
				testi++;
			}
			/*if (test_cheak != 0)
			{
			for (size_t neti = 0; neti < eoco_length; neti++)
			{
			encoded_string[neti] = buff[neti];
			}
			}*/
            //closesocket(sockClient);
            //WSACleanup();
			close(sockClient);
			return;
		}
		catch ( exception e) {
            //closesocket(sockClient);
            //WSACleanup();
			close(sockClient);
			return;
			//return buff;
		}
	}
	void TCP_link(char* ip_addr, int ip_port, int net_str_length, int &eoco_length, char* net_str, char* buff)
	{
		//array<Byte>^ encoded_string = gcnew array<Byte>(3000);
        //rfid::TCP::Close_connect();

        /*
		WSADATA wsaData;
		SOCKADDR_IN addrSrv;
		SOCKET sockClient;
		WSACleanup();
		*/
		int sockClient;
        struct sockaddr_in addrSrv;

		//	char buff[3000] = { 0 };
		try
		{
		    /*
			if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
			{
				//			System::Windows::Forms::DialogResult result = MessageBox::Show(this, "Failed to load Winsock", "注意", MessageBoxButtons::OK);
				//closesocket(sockClient);
				//WSACleanup();
				return;
				//return buff;

			}
			*/
			addrSrv.sin_family = AF_INET;
			addrSrv.sin_port = htons(ip_port);
			addrSrv.sin_addr.s_addr = inet_addr(ip_addr);

			sockClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if ( sockClient == SOCKET_ERROR  ){
				//			System::Windows::Forms::DialogResult result = MessageBox::Show(this, "Socket() error:" + WSAGetLastError(), "注意", MessageBoxButtons::OK);
                //closesocket(sockClient);
                //WSACleanup();
				close(sockClient);
				return;
				//return buff;
			}
			TIMEVAL D_timeout;
			D_timeout.tv_sec = 0;
			D_timeout.tv_usec = 100000;

            //unsigned long iMode = 1;
            //int iResult = ioctlsocket(sockClient, FIONBIO, &iMode);
			int flags = fcntl(sockClient, F_GETFL, 0);
            int iResult = fcntl(sockClient, F_SETFL, flags|O_NONBLOCK);


			if (iResult != NO_ERROR)
			{	//return buff;
                //closesocket(sockClient);
                //WSACleanup();
				close(sockClient);
				return;
			}
			connect(sockClient, (struct  sockaddr*)&addrSrv, sizeof(addrSrv));

            //iMode = 0;
            //iResult = ioctlsocket(sockClient, FIONBIO, &iMode);

			flags = fcntl(sockClient, F_GETFL, 0);
            //iResult = fcntl(sockClient, F_SETFL, flags|O_NONBLOCK);
            iResult = fcntl(sockClient, F_SETFL, flags&~O_NONBLOCK);

			if (iResult != NO_ERROR)
			{
                //closesocket(sockClient);
                //WSACleanup();
				close(sockClient);
				return;
				//return buff;
			}

			fd_set Write, Err;
			FD_ZERO(&Write);
			FD_ZERO(&Err);
			FD_SET(sockClient, &Write);
			FD_SET(sockClient, &Err);

			int ret = select(sockClient+1, NULL, &Write, &Err, &D_timeout);

            //if (Write.fd_count != 1)


            if ( ret <= 0 )
            {
                printf( "connection time out\n" );
                close( sockClient  );
                return ;
            }

            if ( ! FD_ISSET( sockClient, &Write  ) )
            {
                printf( "no events on sockClient found\n" );
                close( sockClient );
                return ;
            }




            /*
            if ( FD_SETSIZE !=1 )
			{
			    printf( "size oops\n");
                //closesocket(sockClient);
                //WSACleanup();
				//close(sockClient);
				//return;
				//return buff;
			}
			*/

			/*/ windows
			int nNetTimeout = 5000;//1秒 //傳送時限 setsockopt(socket，SOL_S0CKET,SO_SNDTIMEO，(char *)&nNetTimeout,sizeof(int));
			setsockopt(sockClient, SOL_SOCKET, SO_SNDTIMEO, (char *)&nNetTimeout, sizeof(int));
			setsockopt(sockClient, SOL_SOCKET, SO_RCVTIMEO, (char *)&nNetTimeout, sizeof(int));
			//*/

			//linux
			struct timeval timeout={5,0};// {sec,ms}
			int sndto = setsockopt(sockClient,SOL_SOCKET, SO_SNDTIMEO,(const void*) &timeout, sizeof(timeout));
            int rcvto = setsockopt(sockClient,SOL_SOCKET, SO_RCVTIMEO,(const void*) &timeout, sizeof(timeout));

            if ( sndto != 0 || rcvto != 0 )
                printf( "timeout err\n") ;


		//	Sleep(100);
			send(sockClient, net_str, net_str_length, 0);
			int test_cheak = 0;
			int testi = 0,i=0;
			//Sleep(100);
			while (1)
			{
				//if (eoco_length == 0)
				//	break;
				test_cheak = recv(sockClient, buff+i*1446, 2048, 0);
				//if (test_cheak == 1446)
				//{
				//}
				if (test_cheak != 0)
					break;
				if (testi == 50)
					break;
				testi++;
			}
			eoco_length = test_cheak;
			/*if (test_cheak != 0)
			{
				for (size_t neti = 0; neti < eoco_length; neti++)
				{
					encoded_string[neti] = buff[neti];
				}
			}*/
//			closesocket(sockClient);
//			WSACleanup();
            close(sockClient);
			return ;
		}
		catch ( exception e ) {
//			closesocket(sockClient);
//			WSACleanup();
			close(sockClient);
			return;
			//return buff;
		}
	}

	void  TCP::crc16(const unsigned char* buffer, int size, int &crc_value){

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
		crc_value = crc;
	}
}

