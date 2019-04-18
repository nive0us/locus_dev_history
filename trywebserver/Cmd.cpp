#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <map>
#include <functional>
#include <fstream>

#include "CRC32.h"
#include <Cmd.h>
#include <TCP.h>
#include "json.hpp"
#include <Comport.h>

#include "ser.h"
using namespace std;
using json = nlohmann::json;

map<string, func_cmd_detail_7_arg> g_function_7_arg_map;
map<string, func_cmd_detail_6_arg> g_function_6_arg_map;
map<string, func_cmd_detail_5_1_arg> g_function_51_arg_map;
map<string, func_cmd_detail_5_2_arg> g_function_52_arg_map;
map<string, func_cmd_detail_4_arg> g_function_4_arg_map;
map<string, func_cmd_detail_3_1_arg> g_function_31_arg_map;
map<string, func_cmd_detail_3_2_arg> g_function_32_arg_map;


extern map<string, Callback_Fun0> g_RW_json_package;




// from main.cpp*******************

extern string Interface_name  ;
extern std::string dev_transmission_cycle_time ;
extern std::string dev_active_ID               ;
extern std::string dev_IP[4]           ;
extern std::string dev_Mask[4]         ;
extern std::string dev_GW[4]           ;
extern std::string dev_Client_IP[4]    ;


extern unsigned char g_Reader_value;
extern string Model_Name,Version_Name ;

extern unsigned int UWB_channel, UWB_prf, UWB_datarate;
extern unsigned int UWB_preambleCode, UWB_preambleLength;
extern unsigned int UWB_PAC, UWB_NSD, UWB_SMARTPOWER ;
extern unsigned int UWB_SFD_timeout, UWB_PGdelay ;
extern unsigned int UWB_Power, UWB_MODE, active_ID ;
extern unsigned int NTM_value, PMULT_value, transmission_cycle_time ;



extern int UDP_Server_Port ;
extern int TCP_Server_Port ;
extern int TCP_Client_Des_Port ;

//extern char* target_ip ;
extern SerialPort *serialPort1 ;
extern int dev_count ;
extern string fw_name ;


extern string main_extern ;

extern json g_json_single ;
extern json g_json_multi ;



extern std::string rf_channel          ;
extern std::string rf_datarate         ;
extern std::string rf_prf              ;
extern std::string rf_preambleCode     ;
extern std::string rf_preambleLength   ;
extern std::string rf_PAC              ;
extern std::string rf_PGdelay          ;
extern std::string rf_Power            ;
extern std::string rf_NSD              ;
extern std::string rf_SFD_timeout      ;
extern std::string rf_SMARTPOWER       ;
extern std::string rf_MODE             ;
extern std::string rf_active_ID        ;
extern std::string rf_NTM_value        ;
extern std::string rf_PMULT_value      ;


extern char* ip_addr ;
extern char* ip_addr_temp ;
extern unsigned char* cmd_buff ;
extern unsigned char* IP_temp ;
extern unsigned char* GW_temp ;
extern unsigned char* MASK_temp ;
extern unsigned char* CLIENT_IP_temp ;

// from main.cpp END*******************





void arg_IP( int rw, unsigned char * set_Reader_value, unsigned char* Reader_value )
{
    if ( rw == 2 )   // write to device

        for (size_t i = 0; i < 4; i++)
            set_Reader_value[i] = IP_temp[i];


    else if  ( rw == 1 )   // read from device

        for (size_t i = 0; i < 4; i++)

            IP_temp[i] = Reader_value[i];



    else
    {
        cout << "rw flag error" << endl ;
    }
}


void arg_ClientIP( int rw, unsigned char * set_Reader_value, unsigned char* Reader_value )
{
    if ( rw == 2 )   // write to device
        for (size_t i = 0; i < 4; i++)
            set_Reader_value[i] = CLIENT_IP_temp[i];


    else if  ( rw == 1 )   // read from device
        for (size_t i = 0; i < 4; i++)
            CLIENT_IP_temp[i] = set_Reader_value[i] ;


    else
    {
        cout << "rw flag error" << endl ;
    }
}

void arg_GW( int rw, unsigned char * set_Reader_value, unsigned char* Reader_value )
{
    if ( rw == 2 )   // write to device
    {
        for (size_t i = 0; i < 4; i++)
            set_Reader_value[i] = GW_temp[i];
    }

    else if  ( rw == 1 )   // read from device
    {
        for (size_t i = 0; i < 4; i++)
            GW_temp[i] = Reader_value[i];
    }

    else
    {
        cout << "rw flag error" << endl ;
    }
}

void arg_Mask( int rw, unsigned char * set_Reader_value, unsigned char* Reader_value )
{
    if ( rw == 2 )   // write to device
    {
        for (size_t i = 0; i < 4; i++)
            set_Reader_value[i] = MASK_temp[i];
    }

    else if  ( rw == 1 )   // read from device
    {
        for (size_t i = 0; i < 4; i++)
            MASK_temp[i] = Reader_value[i];
    }

    else
    {
        cout << "rw flag error" << endl ;
    }
}

void arg_Channel( int rw, unsigned char * set_Reader_value, unsigned char* Reader_value )
{
    if ( rw == 2 )   // write to device
    {
        for (size_t i = 0; i < 1; i++)
            set_Reader_value[i] = UWB_channel;
    }

    else if  ( rw == 1 )   // read from device
    {
        UWB_channel = Reader_value[0];
    }

    else
    {
        cout << "rw flag error" << endl ;
    }
}

void arg_Datarate( int rw, unsigned char * set_Reader_value, unsigned char* Reader_value )
{
    if ( rw == 2 )   // write to device
    {
        for (size_t i = 0; i < 1; i++)
            set_Reader_value[i] = UWB_datarate;
    }

    else if  ( rw == 1 )   // read from device
    {
        UWB_datarate = Reader_value[0];
    }

    else
    {
        cout << "rw flag error" << endl ;
    }
}

void arg_PRF( int rw, unsigned char * set_Reader_value, unsigned char* Reader_value )
{
    if ( rw == 2 )   // write to device
    {
        for (size_t i = 0; i < 1; i++)
            set_Reader_value[i] = UWB_prf;
    }

    else if  ( rw == 1 )   // read from device
    {
        UWB_prf = Reader_value[0];
    }

    else
    {
        cout << "rw flag error" << endl ;
    }
}

void arg_Preamblecode( int rw, unsigned char * set_Reader_value, unsigned char* Reader_value )
{
    if ( rw == 2 )   // write to device
    {
        for (size_t i = 0; i < 1; i++)
            set_Reader_value[i] = UWB_preambleCode;
    }

    else if  ( rw == 1 )   // read from device
    {
        UWB_preambleCode = Reader_value[0];
    }

    else
    {
        cout << "rw flag error" << endl ;
    }
}

void arg_PreambleLength( int rw, unsigned char * set_Reader_value, unsigned char* Reader_value )
{
    if ( rw == 2 )   // write to device
    {
        for (size_t i = 0; i < 1; i++)
            set_Reader_value[i] = UWB_preambleLength;
    }

    else if  ( rw == 1 )   // read from device
    {
        UWB_preambleLength = Reader_value[0];
    }

    else
    {
        cout << "rw flag error" << endl ;
    }
}

void arg_PAC( int rw, unsigned char * set_Reader_value, unsigned char* Reader_value )
{
    if ( rw == 2 )   // write to device
    {
        for (size_t i = 0; i < 1; i++)
            set_Reader_value[i] = UWB_PAC;
    }

    else if  ( rw == 1 )   // read from device
    {
        UWB_PAC = Reader_value[0];
    }

    else
    {
        cout << "rw flag error" << endl ;
    }
}

void arg_TX_PGDELAY( int rw, unsigned char * set_Reader_value, unsigned char* Reader_value )
{
    if ( rw == 2 )   // write to device
    {
        for (size_t i = 0; i < 1; i++)
            set_Reader_value[i] = UWB_PGdelay;
    }

    else if  ( rw == 1 )   // read from device
    {
        UWB_PGdelay = Reader_value[0];
    }

    else
    {
        cout << "rw flag error" << endl ;
    }
}

void arg_TX_POWER( int rw, unsigned char * set_Reader_value, unsigned char* Reader_value )
{
    if ( rw == 2 )   // write to device
    {
        set_Reader_value[0] = ((UWB_Power & 0xFF000000) >> 24);
        set_Reader_value[1] = ((UWB_Power & 0xFF0000) >> 16);
        set_Reader_value[2] = ((UWB_Power & 0xFF00) >> 8);
        set_Reader_value[3] = ((UWB_Power & 0xFF));
    }

    else if  ( rw == 1 )   // read from device
    {
        UWB_Power = ((unsigned int)Reader_value[0] << 24) + ((unsigned int)Reader_value[1] << 16) + ((unsigned int)Reader_value[2] << 8) + ((unsigned int)Reader_value[3]);
    }

    else
    {
        cout << "rw flag error" << endl ;
    }
}

void arg_NSD( int rw, unsigned char * set_Reader_value, unsigned char* Reader_value )
{
    if ( rw == 2 )   // write to device
    {
        for (size_t i = 0; i < 1; i++)
            set_Reader_value[i] = UWB_NSD;
    }

    else if  ( rw == 1 )   // read from device
    {
        UWB_NSD = Reader_value[0];
    }

    else
    {
        cout << "rw flag error" << endl ;
    }
}

void arg_SFD_Timeout( int rw, unsigned char * set_Reader_value, unsigned char* Reader_value )
{
    if ( rw == 2 )   // write to device
    {
        set_Reader_value[0] = ((UWB_SFD_timeout & 0xFF00) >> 8);
        set_Reader_value[1] = ((UWB_SFD_timeout & 0xFF));
    }

    else if  ( rw == 1 )   // read from device
    {
        UWB_SFD_timeout = ((unsigned int)Reader_value[0] << 8) + ((unsigned int)Reader_value[1]);
    }

    else
    {
        cout << "rw flag error" << endl ;
    }
}

void arg_SMARTPOWER( int rw, unsigned char * set_Reader_value, unsigned char* Reader_value )
{
    if ( rw == 2 )   // write to device
    {
        for (size_t i = 0; i < 1; i++)
            set_Reader_value[i] = UWB_SMARTPOWER;
    }

    else if  ( rw == 1 )   // read from device
    {
        UWB_SMARTPOWER = Reader_value[0];
    }

    else
    {
        cout << "rw flag error" << endl ;
    }
}

void arg_active_ID( int rw, unsigned char * set_Reader_value, unsigned char* Reader_value )
{
    int len_temp = 0;

    if (UWB_MODE == 1)
        len_temp = 4;
    else
        len_temp = 2;

    if ( rw == 2 )   // write to device
    {
        if (UWB_MODE == 1)
        {
            set_Reader_value[0] = ((active_ID & 0xFF000000) >> 24);
            set_Reader_value[1] = ((active_ID & 0xFF0000) >> 16);
            set_Reader_value[2] = ((active_ID & 0xFF00) >> 8);
            set_Reader_value[3] = ((active_ID & 0xFF));
        }
        else
        {
            set_Reader_value[0] = ((active_ID & 0xFF00) >> 8);
            set_Reader_value[1] = ((active_ID & 0xFF));
        }
    }

    else if  ( rw == 1 )   // read from device
    {
        if (len_temp == 4)
            active_ID = ((unsigned int)Reader_value[0] << 24) + ((unsigned int)Reader_value[1] << 16) + ((unsigned int)Reader_value[2] << 8) + ((unsigned int)Reader_value[3]);
        else
            active_ID = ((unsigned int)Reader_value[0] << 8) + ((unsigned int)Reader_value[1]);
    }

    else
    {
        cout << "rw flag error" << endl ;
    }
}

void arg_NTM_MULT( int rw, unsigned char * set_Reader_value, unsigned char* Reader_value )
{
    if ( rw == 2 )   // write to device
    {
        set_Reader_value[0] = PMULT_value;
        set_Reader_value[1] = NTM_value;
    }

    else if  ( rw == 1 )   // read from device
    {
        PMULT_value = Reader_value[0];
        NTM_value = Reader_value[1];
    }

    else
    {
        cout << "rw flag error" << endl ;
    }
}

void arg_Transmission_Cycle( int rw, unsigned char * set_Reader_value, unsigned char* Reader_value )
{
    if ( rw == 2 )   // write to device
    {
        set_Reader_value[0] = (transmission_cycle_time & 0xFF0000) >> 16;
        set_Reader_value[1] = (transmission_cycle_time & 0xFF00) >> 8;
        set_Reader_value[2] = (transmission_cycle_time & 0xFF);

    }

    else if  ( rw == 1 )   // read from device
    {
        transmission_cycle_time = (((unsigned int)Reader_value[0] << 16) + ((unsigned int)Reader_value[1] << 8) + ((unsigned int)Reader_value[2]));


    }

    else
    {
        cout << "rw flag error" << endl ;
    }
}




void arg_update( char* target_ip ,string fw_name, int &flag )
{
    int Value_flag = 0 ;
    const char* Filename = fw_name.c_str() ;
//    const char* Filename = (char*)path;
    if ( Filename != "")
    {
        unsigned char binch[400000] = { 0 };
        int u = 0;
        int n_h = 0, n_l = 0, n = 0;
        long s = 0;
        std::fstream file;
        char ch;
        std::ifstream fin(Filename, std::ios::in | std::ios::binary);

        while (!fin.eof())
        {
            fin.get(ch);
            binch[u] = ch;
            u++;
        }
        fin.close();
        file.close();
        unsigned int Size = u - 5;
        s = CRC::CRC32::crc32(0xFFFFFFFF, (unsigned char*)binch, Size);
        int temp1 = binch[u - 5], temp2 = binch[u - 4], temp3 = binch[u - 3], temp4 = binch[u - 2];
        if ((binch[u - 5] == ((s & 0xFF000000) >> 24)) && (binch[u - 4] == ((s & 0x00FF0000) >> 16)) && (binch[u - 3] == ((s & 0x0000FF00) >> 8)) && (binch[u - 2] == ((s & 0xFF))))
        {
            //displaymesgbox2(11);
            //Settab();
            n_h = (Size - 32) / 256;
            n_l = (Size - 32) % 256;
            int maxmun = n_h + 1;
            if (n_l > 0)
                maxmun++;
            unsigned  int o = 0, p = 0, t = 0;
            if (n_h > 0)
            {
                for (o = 0; o < (unsigned int)n_h; o++)
                {
                    unsigned char temp_buf[2048] = { 0 };

                    temp_buf[0] = (((o * 256) & 0xFF000000) >> 24);
                    temp_buf[1] = (((o * 256) & 0xFF0000) >> 16);
                    temp_buf[2] = (((o * 256) & 0xFF00) >> 8);
                    temp_buf[3] = (((o * 256) & 0xFF));

                    for (size_t i = 0; i < 256; i++)
                        temp_buf[4 + i] = binch[32 + o * 256 + i];
                    if (Interface_name == UWB_Interface1)
                        rfid::TCP::update_data(target_ip, TCP_Server_Port, temp_buf, 256 + 4, Value_flag);
                    else
                        rfid::Comport::update_data(*serialPort1, temp_buf, 256 + 4, Value_flag);
                    if ((Value_flag != 1) && (Value_flag != 0xFC))
                    {
                        cout << "update failed!" << endl ;
//                        goto return_error;
                    }

//                    if (stopvalue == false)
//                    {
//                        //displaymesgbox(13);
//                        //Setbarvalue();
//                        break;
//                    }

                    //Setbar(maxmun);
                }
                //Setbar(maxmun);
            }
            else if (n_l > 0)
            {
                unsigned char temp_buf[2048] = { 0 };
                temp_buf[0] = (((o * 256) & 0xFF000000) >> 24);
                temp_buf[1] = (((o * 256) & 0xFF0000) >> 16);
                temp_buf[2] = (((o * 256) & 0xFF00) >> 8);
                temp_buf[3] = (((o * 256) & 0xFF));

                for (size_t i = 0; i < (unsigned int)n_l; i++)
                    temp_buf[4 + i] = binch[32 + o * 256 + i];
                if (Interface_name == UWB_Interface1)
                    rfid::TCP::update_data(target_ip, TCP_Server_Port, temp_buf, n_l + 4, Value_flag);
                else
                    rfid::Comport::update_data(*serialPort1, temp_buf, n_l + 4, Value_flag);
                if (Value_flag != 1)
                {
                    cout << "update failed!" << endl ;
                    flag = 0 ;
                    return;
//                    goto return_error;
                }
                //Setbar(maxmun);
            }
            if (Interface_name == UWB_Interface1)
                rfid::TCP::update_check(target_ip, TCP_Server_Port, (unsigned char*)binch, 8, Value_flag);
            else
                rfid::Comport::update_check(*serialPort1, (unsigned char*)binch, 8, Value_flag);
            if (Value_flag != 1)
            {
                cout << "update failed!" << endl ;
                flag = 0 ;
                return;
//                goto return_error;
            }


//            if (stopvalue == true)
//            {
//                //displaymesgbox(12);
//            }
//            else if (stopvalue == false)
//            {
//                //displaymesgbox(13);
//                //Setbarvalue();
//            }

        }
          flag = 1 ;
          return;
//        goto return_ok;
    }
    else
    {
        flag = 0 ;
        return;
        //displaymesgbox(21);
//        goto return_error;
    }
    flag = 1 ;
    return;
//    goto return_ok;
}




void arg_cmd() {
//    for (int i = 0; i < (int)strlen(ip_addr_temp); i++)
//		{
//			ip_addr[i] = ip_addr_temp[i];
//			ip_addr[i + 1] = 0;
//		}
//		unsigned char return_buff[1024] = { 0 };
//		char str_buff[2048] = { 0 };
//		char str[] = "TimeOut";
//		int32_t len_temp;
//		if (buff != nullptr)
//			len_temp = (Int32)buff;
//		int flag = 0, length = len_temp;
//		if (Interface_name == UWB_Interface1)
//			rfid::TCP::send_cmd(ip_addr, TCP_Server_Port, cmd_buff, length, return_buff);
//		else
//			rfid::Comport::send_cmd(serialPort1, cmd_buff, length, return_buff);
//		for (size_t i = 0, j = 0; i < (unsigned int)(((return_buff[4] * 256 + return_buff[5] + 6))); i++, j = j + 2)
//		{
//			if ((return_buff[4] * 256 + return_buff[5] == 0))
//				break;
//			str_buff[j] = return_buff[i] / 16 + 0x30;
//			if (str_buff[j] > 0x39)
//				str_buff[j] = str_buff[j] + 0x07;
//			str_buff[j + 1] = return_buff[i] % 16 + 0x30;
//			if (str_buff[j + 1] > 0x39)
//				str_buff[j + 1] = str_buff[j + 1] + 0x07;
//		}
//		if ((return_buff[4] * 256 + return_buff[5] == 0))
//			display_cmd(Marshal::PtrToStringAnsi((IntPtr)(char *)str));
//		else
//			display_cmd(Marshal::PtrToStringAnsi((IntPtr)(char *)str_buff));


}


void arg_Read_version( int rw, unsigned char * set_Reader_value, unsigned char* Reader_value  ) {
    Model_Name = ((char*)Reader_value) ;
    Version_Name = ((char*)Reader_value+8);

}

void arg_Read_Mode ( int rw, unsigned char * set_Reader_value, unsigned char* Reader_value  ) {
    UWB_MODE = Reader_value[0];

}






void construct_func_map()
{

//    static  void RW_IP(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
//	  static  void RW_GatewayIP(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
//	  static  void RW_MaskIP(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
//	  static  void RW_ClientIP(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
//	  static  void RW_Channel(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
//	  static  void RW_Datarate(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
//	  static  void RW_PRF(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
//	  static  void RW_Preamblecode(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
//	  static  void RW_PreambleLength(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
//	  static  void RW_PAC(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
//	  static  void RW_TX_PGDELAY(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
//	  static  void RW_TX_POWER(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
//	  static  void RW_NSD(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
//	  static  void RW_SFD_Timeout(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
//	  static  void RW_SMARTPOWER(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
//	  static  void RW_active_ID(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
//	  static  void RW_NTM_MULT(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
//	  static  void RW_Transmission_Cycle(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);


    map<string, func_cmd_detail_7_arg> function_7_arg_map;
    func_cmd_detail_7_arg new_func ;

    new_func.callback = rfid::TCP::RW_IP ;
    new_func.func_name = "RW_IP" ;
    new_func.RW_arg = arg_IP;
    new_func.set_length = 4 ;
    function_7_arg_map["dev_IP"] = new_func ;


    new_func.callback = rfid::TCP::RW_GatewayIP ;
    new_func.func_name = "RW_GatewayIP" ;
    new_func.RW_arg = arg_GW;
    new_func.set_length = 4 ;
    function_7_arg_map["dev_GW"] = new_func ;


    new_func.callback = rfid::TCP::RW_MaskIP ;
    new_func.func_name = "RW_MaskIP" ;
    new_func.RW_arg = arg_Mask;
    new_func.set_length = 4 ;
    function_7_arg_map["dev_Mask"] = new_func ;

    new_func.callback = rfid::TCP::RW_ClientIP ;
    new_func.func_name = "RW_ClientIP" ;
    new_func.RW_arg = arg_ClientIP;
    new_func.set_length = 4 ;
    function_7_arg_map["dev_Client_IP"] = new_func ;

    new_func.callback = rfid::TCP::RW_Channel ;
    new_func.func_name = "RW_Channel" ;
    new_func.RW_arg = arg_Channel;
    new_func.set_length = 1 ;
    function_7_arg_map["rf_channel"] = new_func ;

    new_func.callback = rfid::TCP::RW_Datarate ;
    new_func.func_name = "RW_Datarate" ;
    new_func.RW_arg = arg_Datarate;
    new_func.set_length = 1 ;
    function_7_arg_map["rf_datarate"] = new_func ;

    new_func.callback = rfid::TCP::RW_PRF ;
    new_func.func_name = "RW_PRF" ;
    new_func.RW_arg = arg_PRF;
    new_func.set_length = 1 ;
    function_7_arg_map["rf_prf"] = new_func ;

    new_func.callback = rfid::TCP::RW_Preamblecode ;
    new_func.func_name = "RW_Preamblecode" ;
    new_func.RW_arg = arg_Preamblecode;
    new_func.set_length = 1 ;
    function_7_arg_map["rf_preambleCode"] = new_func ;

    new_func.callback = rfid::TCP::RW_PreambleLength ;
    new_func.func_name = "RW_PreambleLength" ;
    new_func.RW_arg = arg_PreambleLength;
    new_func.set_length = 1 ;
    function_7_arg_map["rf_preambleLength"] = new_func ;

    new_func.callback = rfid::TCP::RW_PAC ;
    new_func.func_name = "RW_PAC" ;
    new_func.RW_arg = arg_PAC;
    new_func.set_length = 1 ;
    function_7_arg_map["rf_PAC"] = new_func ;

    new_func.callback = rfid::TCP::RW_TX_PGDELAY ;
    new_func.func_name = "RW_TX_PGDELAY" ;
    new_func.RW_arg = arg_TX_PGDELAY;
    new_func.set_length = 1 ;
    function_7_arg_map["rf_PGdelay"] = new_func ;

    new_func.callback = rfid::TCP::RW_TX_POWER ;
    new_func.func_name = "RW_TX_POWER" ;
    new_func.RW_arg = arg_TX_POWER;
    new_func.set_length = 4 ;
    function_7_arg_map["rf_Power"] = new_func ;

    new_func.callback = rfid::TCP::RW_NSD ;
    new_func.func_name = "RW_NSD" ;
    new_func.RW_arg = arg_NSD;
    new_func.set_length = 1 ;
    function_7_arg_map["rf_NSD"] = new_func ;

    new_func.callback = rfid::TCP::RW_SFD_Timeout ;
    new_func.func_name = "RW_SFD_Timeout" ;
    new_func.RW_arg = arg_SFD_Timeout;
    new_func.set_length = 2 ;
    function_7_arg_map["rf_SFD_timeout"] = new_func ;

    new_func.callback = rfid::TCP::RW_SMARTPOWER ;
    new_func.func_name = "RW_SMARTPOWER" ;
    new_func.RW_arg = arg_SMARTPOWER;
    new_func.set_length = 1 ;
    function_7_arg_map["rf_SMARTPOWER"] = new_func ;

    new_func.callback = rfid::TCP::RW_active_ID ;
    new_func.func_name = "RW_active_ID" ;
    new_func.RW_arg = arg_active_ID;
    new_func.set_length = 2 ;
    function_7_arg_map["rf_active_ID"] = new_func ;

    new_func.callback = rfid::TCP::RW_NTM_MULT ;
    new_func.func_name = "RW_NTM_MULT" ;
    new_func.RW_arg = arg_NTM_MULT;
    new_func.set_length = 2 ;
    function_7_arg_map["rf_NTM_value"] = new_func ;

    new_func.callback = rfid::TCP::RW_NTM_MULT ;
    new_func.func_name = "RW_NTM_MULT" ;
    new_func.RW_arg = arg_NTM_MULT;
    new_func.set_length = 2 ;
    function_7_arg_map["rf_PMULT_value"] = new_func ;




    new_func.callback = rfid::TCP::RW_Transmission_Cycle ;
    new_func.func_name = "RW_Transmission_Cycle" ;
    new_func.RW_arg = arg_Transmission_Cycle;
    new_func.set_length = 3 ;
    function_7_arg_map["dev_transmission_cycle_time"] = new_func ;

    new_func.callback = rfid::TCP::RW_active_ID ;
    new_func.func_name = "RW_active_ID" ;
    new_func.RW_arg = arg_active_ID;
    new_func.set_length = 2 ;
    function_7_arg_map["dev_active_ID"] = new_func ;





//static  void TCP_sendpackage(char* ip_addr, int ip_port, int net_str_length, int eoco_length, char* net_str, char* buff);
    map<string, func_cmd_detail_6_arg> function_6_arg_map;

    func_cmd_detail_6_arg new_func6 ;
    new_func6.callback = rfid::TCP::TCP_sendpackage ;
    new_func6.func_name = "TCP_sendpackage" ;
    function_6_arg_map["TCP_sendpackage"] = new_func6 ;



//    static  void send_cmd(char* ip_addr, int ip_port, unsigned char* buff_temp, unsigned int length, unsigned char* return_buff_temp);
    map<string, func_cmd_detail_5_1_arg> function_51_arg_map;

    func_cmd_detail_5_1_arg new_func51 ;
    new_func51.callback = rfid::TCP::send_cmd ;
    new_func51.func_name = "send_cmd" ;
    function_51_arg_map["send_cmd"] = new_func51 ;


//    static  void update_data(char* ip_addr, int ip_port, unsigned char* binch, int length, int &flag);
//    static  void update_check(char* ip_addr, int ip_port, unsigned char* binch, int length, int &flag);
    map<string, func_cmd_detail_5_2_arg> function_52_arg_map;

    func_cmd_detail_5_2_arg new_func52 ;
//    new_func52.callback = arg_update ;
    new_func52.func_name = "update_data" ;
    new_func52.RW_arg = arg_update;
    function_52_arg_map["update_data"] = new_func52 ;

    new_func52.callback = rfid::TCP::update_check ;
    new_func52.func_name = "update_check" ;
    function_52_arg_map["update_check"] = new_func52 ;


//   static  void Read_MODE(char* ip_addr, int ip_port, unsigned char* buff, int &flag);
//	 static  void Read_Version(char* ip_addr, int ip_port, unsigned char* buff, int &flag);
    map<string, func_cmd_detail_4_arg> function_4_arg_map;

    func_cmd_detail_4_arg new_func4 ;
    new_func4.callback = rfid::TCP::Read_MODE ;
    new_func4.func_name = "Read_MODE" ;
    new_func4.RW_arg = arg_Read_Mode;
    function_4_arg_map["rf_MODE"] = new_func4 ;

    new_func4.callback = rfid::TCP::Read_Version ;
    new_func4.func_name = "Read_Version" ;
    new_func4.RW_arg = arg_Read_version;
    function_4_arg_map["Version_Name"] = new_func4 ;

    new_func4.callback = rfid::TCP::Read_Version ;
    new_func4.func_name = "Read_Version" ;
    new_func4.RW_arg = arg_Read_version;
    function_4_arg_map["Model_Name"] = new_func4 ;


//    static  void Reset_Chip(char* ip_addr, int ip_port, int &flag);
    map<string, func_cmd_detail_3_1_arg> function_31_arg_map;

    func_cmd_detail_3_1_arg new_func31 ;
    new_func31.callback = rfid::TCP::Reset_Chip ;
    new_func31.func_name = "Reset_Chip" ;
    function_31_arg_map["Reset_Chip"] = new_func31 ;


//static	 void crc16(const unsigned char* buffer, int size, int &crc_value);
    map<string, func_cmd_detail_3_2_arg> function_32_arg_map;

    func_cmd_detail_3_2_arg new_func32 ;
    new_func32.callback = rfid::TCP::crc16 ;
    new_func32.func_name = "crc16" ;
    function_32_arg_map["crc16"] = new_func32 ;




    g_function_7_arg_map = function_7_arg_map ;
    g_function_6_arg_map = function_6_arg_map ;
    g_function_51_arg_map = function_51_arg_map ;
    g_function_52_arg_map = function_52_arg_map ;
    g_function_4_arg_map = function_4_arg_map ;
    g_function_31_arg_map = function_31_arg_map ;
    g_function_32_arg_map = function_32_arg_map ;

    int cnt_7   = function_7_arg_map.size();
    int cnt_6   = function_6_arg_map.size();
    int cnt_51  = function_51_arg_map.size();
    int cnt_52  = function_52_arg_map.size();
    int cnt_4   = function_4_arg_map.size();
    int cnt_31  = function_31_arg_map.size();
    int cnt_32  = function_32_arg_map.size();


    cout << cnt_31+cnt_32+cnt_4+cnt_51+cnt_52+cnt_6+cnt_7 << endl ;


}






void Write_RF_json()
{

    try
    {

//        version_flag = 1;
//        channel_flag = 2;
//        datarate_flag = 2;
//        prf_flag = 2;
//        preamblecode_flag = 2;
//        preamblelength_flag = 2;
//        pac_flag = 2;
//        pgdelay_falg = 2;
//        power_flag = 2;
//        nsd_flag = 2;
//        sfd_timeout_flag = 2;
//        smartpower_flag = 2;
//        mode_falg = 1;
//        NTM_PMULT_flag = 2;
//        write_Parameter_flag = 1;


        rf_channel          = g_json_single["rf_channel"];
        rf_datarate         = g_json_single["rf_datarate"];
        rf_prf              = g_json_single["rf_prf"];
        rf_preambleCode     = g_json_single["rf_preambleCode"];
        rf_preambleLength   = g_json_single["rf_preambleLength"];
        rf_PAC              = g_json_single["rf_PAC"];
        rf_PGdelay          = g_json_single["rf_PGdelay"];
        rf_Power            = g_json_single["rf_Power"];
        rf_NSD              = g_json_single["rf_NSD"];
        rf_SFD_timeout      = g_json_single["rf_SFD_timeout"];
        rf_SMARTPOWER       = g_json_single["rf_SMARTPOWER"];
        rf_NTM_value        = g_json_single["rf_NTM_value"];
        rf_PMULT_value      = g_json_single["rf_PMULT_value"];



        if (rf_channel == CH1_freq)
            UWB_channel = 1;
        else if (rf_channel == CH2_freq)
            UWB_channel = 2;
        else if (rf_channel == CH4_freq)
            UWB_channel = 4;
        else if (rf_channel == CH5_freq)
            UWB_channel = 5;
        else if (rf_channel == CH7_freq)
            UWB_channel = 7;
        else
            UWB_channel = 3;

        if (rf_datarate == Dararate1)
            UWB_datarate = 0;
        else if (rf_datarate == Dararate2)
            UWB_datarate = 1;
        else
            UWB_datarate = 2;

        if (rf_prf == PRF64M)
            UWB_prf = 2;
        else
            UWB_prf = 1;

        UWB_preambleCode = std::stoi(rf_preambleCode);
        if ((UWB_preambleCode < 1) || (UWB_preambleCode > 20) || ((UWB_preambleCode > 12) && (UWB_preambleCode < 17)))
            UWB_preambleCode = 5;
        if (rf_preambleLength == UWB_preambleLength64)
            UWB_preambleLength = 0x04;
        else if (rf_preambleLength == UWB_preambleLength256)
            UWB_preambleLength = 0x24;
        else if (rf_preambleLength == UWB_preambleLength512)
            UWB_preambleLength = 0x34;
        else if (rf_preambleLength == UWB_preambleLength1024)
            UWB_preambleLength = 0x08;
        else if (rf_preambleLength == UWB_preambleLength1536)
            UWB_preambleLength = 0x18;
        else if (rf_preambleLength == UWB_preambleLength2048)
            UWB_preambleLength = 0x28;
        else if (rf_preambleLength == UWB_preambleLength4096)
            UWB_preambleLength = 0x0C;
        else
            UWB_preambleLength = 0x14;

        if (rf_PAC == UWB_PAC16)
            UWB_PAC = 1;
        else if (rf_PAC == UWB_PAC32)
            UWB_PAC = 2;
        else if (rf_PAC == UWB_PAC64)
            UWB_PAC = 3;
        else
            UWB_PAC = 0;

        //UWB_PGdelay = (Convert::ToInt32(comboBox8->Text));
        if (rf_PGdelay == CH1_PGDELAY)
            UWB_PGdelay = 0xC9;
        else if (rf_PGdelay == CH2_PGDELAY)
            UWB_PGdelay = 0xC2;
        else if (rf_PGdelay == CH4_PGDELAY)
            UWB_PGdelay = 0x95;
        else if (rf_PGdelay == CH5_PGDELAY)
            UWB_PGdelay = 0xC0;
        else if (rf_PGdelay == CH7_PGDELAY)
            UWB_PGdelay = 0x93;
        else
            UWB_PGdelay = 0xC5;

        UWB_Power = std::stoi(rf_Power);

        UWB_NSD = std::stoi(rf_NSD);
        if (rf_NSD == UWB_NSD1)
            UWB_NSD = 1;
        else
            UWB_NSD = 0;

        UWB_SFD_timeout = std::stoi(rf_SFD_timeout);

        if (rf_SMARTPOWER == UWB_SMARTPOWER1)
            UWB_SMARTPOWER = 1;
        else
            UWB_SMARTPOWER = 0;

        NTM_value = std::stoi(rf_NTM_value);
        PMULT_value = std::stoi(rf_PMULT_value);

    }
    catch ( exception &e )
    {
        cout << "Write_RF_json parse error" << endl ;
        return ;
    }


}

void Read_RF_json() {
     //RC_linuxFrame::StaticText8->SetLabelText(Model_Name);
    //RC_linuxFrame::StaticText10->SetLabelText(Version_Name);
    if (UWB_channel == 1)
        rf_channel = CH1_freq ;
    else if (UWB_channel == 2)
        rf_channel = CH2_freq ;
    else if (UWB_channel == 3)
        rf_channel = CH3_freq ;
    else if (UWB_channel == 4)
        rf_channel = CH4_freq ;
    else if (UWB_channel == 5)
        rf_channel = CH5_freq ;
    else if (UWB_channel == 7)
        rf_channel = CH7_freq ;
    //else
    //RC_linuxFrame::ComboBox3->SetValue(UWB_channel+"");
    //rf_channel = UWB_channel + "" ;


    if (UWB_datarate == 0)
        rf_datarate = Dararate1 ;
    else if (UWB_datarate == 1)
        rf_datarate = Dararate2 ;
    else if (UWB_datarate == 2)
        rf_datarate = Dararate3 ;
    //else
    //RC_linuxFrame::ComboBox5->SetValue( int2wx(UWB_datarate));
    //rf_datarate = to_string(UWB_datarate);


    if (UWB_prf == 1)
        rf_prf = PRF16M ;
    else if (UWB_prf == 2)
        rf_prf = PRF64M ;
    //else
    //RC_linuxFrame::ComboBox7->SetValue( int2wx(UWB_prf) );
    //rf_prf = to_string(UWB_prf);

    //UWB_preambleCode=(Convert::ToInt32(comboBox4->Text));
    //RC_linuxFrame::ComboBox9->SetValue( wxString::Format(wxT("%i"),UWB_preambleCode) );
    rf_preambleCode = to_string(UWB_preambleCode) ;


    if (UWB_preambleLength == 0x04)
        rf_preambleLength = UWB_preambleLength64 ;
    else if (UWB_preambleLength == 0x14)
        rf_preambleLength = UWB_preambleLength128 ;
    else if (UWB_preambleLength == 0x24)
        rf_preambleLength = UWB_preambleLength256 ;
    else if (UWB_preambleLength == 0x34)
        rf_preambleLength = UWB_preambleLength512 ;
    else if (UWB_preambleLength == 0x08)
        rf_preambleLength = UWB_preambleLength1024 ;
    else if (UWB_preambleLength == 0x18)
        rf_preambleLength = UWB_preambleLength1536 ;
    else if (UWB_preambleLength == 0x28)
        rf_preambleLength = UWB_preambleLength2048 ;
    else if (UWB_preambleLength == 0x0C)
        rf_preambleLength = UWB_preambleLength4096 ;
    //else
    //RC_linuxFrame::ComboBox11->SetValue( int2wx(UWB_preambleLength));
    //rf_preambleLength = to_string( UWB_preambleLength ) ;

    if (UWB_PAC == 0)
        rf_PAC = UWB_PAC8 ;
    else if (UWB_PAC == 1)
        rf_PAC = UWB_PAC16 ;
    else if (UWB_PAC == 2)
        rf_PAC = UWB_PAC32 ;
    else if (UWB_PAC == 3)
        rf_PAC = UWB_PAC64 ;
    //else
    //RC_linuxFrame::ComboBox13->SetValue( int2wx(UWB_PAC));
    //rf_PAC = to_string(rf_PAC);

    if (UWB_PGdelay == 0xC9)
        rf_PGdelay = CH1_PGDELAY ;
    else if (UWB_PGdelay == 0xC2)
        rf_PGdelay = CH2_PGDELAY ;
    else if (UWB_PGdelay == 0xC5)
        rf_PGdelay = CH3_PGDELAY ;
    else if (UWB_PGdelay == 0x95)
        rf_PGdelay = CH4_PGDELAY ;
    else if (UWB_PGdelay == 0xC0)
        rf_PGdelay = CH5_PGDELAY ;
    else if (UWB_PGdelay == 0x93)
        rf_PGdelay = CH7_PGDELAY ;
    //else
    //RC_linuxFrame::ComboBox15->SetValue( int2wx(UWB_PGdelay));
    //rf_PGdelay = to_string(UWB_PGdelay);

    //RC_linuxFrame::ComboBox4->SetValue(int2wx(UWB_Power));
    rf_Power = to_string(UWB_Power);


    if (UWB_NSD == 0)
        rf_NSD = UWB_NSD0 ;
    else if (UWB_NSD == 1)
        rf_NSD = UWB_NSD1 ;
    //else
    //RC_linuxFrame::ComboBox6->SetValue( int2wx(UWB_NSD) );
    //rf_NSD = to_string(UWB_NSD);

    //RC_linuxFrame::ComboBox8->SetValue( int2wx(UWB_SFD_timeout) );
    rf_SFD_timeout = to_string(UWB_SFD_timeout);


    if (UWB_SMARTPOWER == 0)
        rf_SMARTPOWER = UWB_SMARTPOWER0 ;
    else if (UWB_SMARTPOWER == 1)
        rf_SMARTPOWER = UWB_SMARTPOWER1 ;
    //else
    //RC_linuxFrame::ComboBox10->SetValue( int2wx(UWB_SMARTPOWER) );
    //rf_SMARTPOWER = to_string(UWB_SMARTPOWER) ;


    if (UWB_MODE == 0)
        rf_MODE = UWB_ANCHOR ;
    else if (UWB_MODE == 1)
        rf_MODE = UWB_TAG ;
    else if (UWB_MODE == 2)
        rf_MODE = UWB_Gateway ;
    //else
    //RC_linuxFrame::StaticText12->SetLabelText( int2wx(UWB_MODE) );


    rf_active_ID = to_string(active_ID) ;
    rf_NTM_value = to_string(NTM_value) ;
    rf_PMULT_value = to_string(PMULT_value) ;
    //*/
    // }

    g_json_single["Model_Name"]          = Model_Name;
    g_json_single["Version_Name"]        = Version_Name;
    g_json_single["rf_channel"]          = rf_channel;
    g_json_single["rf_datarate"]         = rf_datarate;
    g_json_single["rf_prf"]              = rf_prf;
    g_json_single["rf_preambleCode"]     = rf_preambleCode;
    g_json_single["rf_preambleLength"]   = rf_preambleLength;
    g_json_single["rf_PAC"]              = rf_PAC;
    g_json_single["rf_PGdelay"]          = rf_PGdelay;
    g_json_single["rf_Power"]            = rf_Power;
    g_json_single["rf_NSD"]              = rf_NSD;
    g_json_single["rf_SFD_timeout"]      = rf_SFD_timeout ;
    g_json_single["rf_SMARTPOWER"]       = rf_SMARTPOWER ;
    g_json_single["rf_MODE"]             = rf_MODE ;
    g_json_single["rf_active_ID"]        = rf_active_ID ;
    g_json_single["rf_NTM_value"]        = rf_NTM_value ;
    g_json_single["rf_PMULT_value"]      = rf_PMULT_value ;


}

void Write_Basic_json() {
    try
    {
        cout << "here" << endl ;

        if (Interface_name == UWB_Interface1)
        {
            dev_active_ID = g_json_single["dev_active_ID"] ;
            active_ID = stoi(dev_active_ID);
//            active_ID_flag = 2;
        }
        else
        {
            dev_transmission_cycle_time = g_json_single["dev_transmission_cycle_time"] ;
            dev_active_ID = g_json_single["dev_active_ID"] ;
            transmission_cycle_time = stoi(dev_transmission_cycle_time);
            active_ID = stoi(dev_active_ID);
//            transmission_cycle_flag = 2;
//            active_ID_flag = 2;
        }
//        write_device_flag = 1;

    }
    catch ( exception &e )
    {
        cout << "Write_Basic_json parser error"<< e.what() << endl ;
        return;

    }


}


void Read_Basic_json() {

     if(Interface_name != UWB_Interface1)
        //TextCtrl22->SetValue( int2wx(transmission_cycle_time) );
        dev_transmission_cycle_time = to_string(transmission_cycle_time);
    //TextCtrl23->SetValue( int2wx(active_ID) );
    dev_active_ID = to_string(active_ID);

    // }


    g_json_single["dev_transmission_cycle_time"] = dev_transmission_cycle_time;
    g_json_single["dev_active_ID"] = dev_active_ID ;
    cout << "dev cycle time :" << dev_transmission_cycle_time << endl ;
    cout << "dev id :" << dev_active_ID << endl ;
}

void Write_Network_json() {

    try {
    for ( int i = 0 ; i < 4 ; i++)
        {
            dev_IP[i]           = g_json_single["dev_IP"][i];
            dev_Mask[i]         = g_json_single["dev_Mask"][i];
            dev_GW[i]           = g_json_single["dev_GW"][i];
            dev_Client_IP[i]    = g_json_single["dev_Client_IP"][i];

            IP_temp[i]           = stoi(dev_IP[i]);
            MASK_temp[i]         = stoi(dev_Mask[i]);
            GW_temp[i]           = stoi(dev_GW[i]);
            CLIENT_IP_temp[i]    = stoi(dev_Client_IP[i]);
        }
    }catch ( exception &e )
    {
        cout << "Write_Network_json parser error" << endl ;
        return;

    }

}

void Read_Network_json(){
    for ( int i = 0 ; i < 4 ; i++)
    {
        dev_IP[i]           = to_string(IP_temp[i]) ;
        dev_Mask[i]         = to_string(MASK_temp[i]) ;
        dev_GW[i]           = to_string(GW_temp[i]) ;
        dev_Client_IP[i]    = to_string(CLIENT_IP_temp[i]) ;

        g_json_single["dev_IP"][i]      = dev_IP[i] ;
        g_json_single["dev_Mask"][i]    = dev_Mask[i];
        g_json_single["dev_GW"][i]      = dev_GW[i];
        g_json_single["dev_Client_IP"][i]  = dev_Client_IP[i];
    }


}


void construct_RW_json_map() {
    map<string, Callback_Fun0> temp_json_package;

    temp_json_package["Write_RF"] = Write_RF_json;
    temp_json_package["Read_RF"] = Read_RF_json;

    temp_json_package["Write_Basic"] = Write_Basic_json;
    temp_json_package["Read_Basic"] = Read_Basic_json;


    temp_json_package["Read_Network"] = Read_Network_json;
    temp_json_package["Write_Network"] = Write_Network_json;



    g_RW_json_package = temp_json_package ;
}



