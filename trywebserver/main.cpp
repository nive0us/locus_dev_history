#include <iostream>
#include <stdio.h>
#include <ifaddrs.h>
#include <arpa/inet.h>

//*****custom*******
#include <TCP.h>
#include <UDP.h>
#include <Comport.h>
#include "ser.h"
#include "def.h"
#include "CRC32.h"
#include "json.hpp"
#include "Cmd.h"
#include "SQL_Cmd.h"
//*****************/

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <string.h>
#include <errno.h>
#include <thread>
#include <fstream>
#include <dlfcn.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
//#include <arpa/inet.h>
#include <fcntl.h>

#define INVALID_SOCKET  (SOCKET)(~0)
#define SOCKET_ERROR            (-1)


// include from .h

//
vector<string> port_list;
using json = nlohmann::json;
json g_json_single ;
json g_json_multi ;
map<string, Callback_Fun0> g_RW_json_package;
using namespace std;

// sql connect
// remember to add the linker option : -lmysqlcppconn
//#include "DBPool.h"
#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <string>
#include <sstream>
//DBPool  connpool = DBPool::GetInstance();



// function/path call
//#define LIB_CACULATE_PATH "./libtest.so"
#define LIB_CACULATE_PATH "./lib_UPOS_Location_API.so"

#define Location_Set_Anchor                 "_Z19Location_Set_AnchorP19Main_Anchor_MessageiP14Anchor_Messagei"
#define Location_Cleanup                    "_Z16Location_Cleanupv"
#define Device_Signal_mode                  "_Z18Device_Signal_ModebPcS_"
#define Location_init                       "_Z13Location_Initv"
#define Load_Location_coordinate_record     "_Z31Load_Location_coordinate_recordRj"
#define Load_Location_status_record         "_Z27Load_Location_status_recordRj"





//*************************************************
#define ROW_x 3
#define ROW 100
#define COL 150
#define TAG_LEN 16
#define Time_LEN 23
struct Status_info
{
    int Status = 0;
    char System_Time[Time_LEN + 1] = { 0 };
};
struct Status_record
{
    char Tag_ID[TAG_LEN + 1] = { 0 };
    Status_info Status_info_record[20];
    unsigned int Info_count = 0;
};
struct tag_info_status
{
    std::string Tag_ID = "";
    std::string System_Time = "";
    int Status = 0;
};
struct Signal_info
{
    char Source_ID[TAG_LEN + 1] = { 0 };
    char Anchor_ID[TAG_LEN + 1] = { 0 };
    int count = 0;
    unsigned int Signal = 0;
};
struct Anchor_Message
{
    int item = 0;
    int main_group = 0;
    int id = 0;
    int x = 0;
    int y = 0;
};
struct Tag_info
{
    int x = 0;
    int y = 0;
    char System_Time[Time_LEN + 1] = { 0 };
};
struct Tag_record
{
    char Tag_ID[TAG_LEN + 1] = { 0 };
    Tag_info Tag_info_record[20];
    unsigned int Info_count = 0;
};
struct Main_Anchor_Message
{
    int id = 0;
    int x = 0;
    int y = 0;
};




//*******************************************



//unsigned char **allconn_temp = NULL;
volatile int cmd_flag = 0,version_flag = 0, ip_flag = 0, gw_flag = 0, mask_flag = 0, client_ip_flag = 0, channel_flag = 0, datarate_flag = 0, prf_flag = 0, preamblecode_flag = 0, preamblelength_flag = 0, pac_flag = 0, pgdelay_falg = 0, power_flag = 0, nsd_flag = 0, sfd_timeout_flag = 0, smartpower_flag = 0, mode_falg = 0, active_ID_flag = 0, NTM_PMULT_flag = 0, read_Parameter_flag = 0, read_network_flag = 0, read_device_flag = 0, write_Parameter_flag = 0, write_network_flag = 0, write_device_flag = 0, connect_flag = 0, update_flag = 0, transmission_cycle_flag = 0;
volatile int textvalue = 1,Only_IP_flag = 0, stop_lock = 1;
const char*  Filename;
bool stopvalue = true;
double image_scale = 1;
volatile int Map_Scale = 3;
volatile int select_flag = 0;
bool anchor_point_mode = 0;
bool record_mode_flag = false;
typedef void(*Location_Set_Anchor_fun)(Main_Anchor_Message* achor_main, int len_main, Anchor_Message* anchor_child, int len_child);
typedef bool(*Location_Init_fun)(void);
typedef void(*Device_Signal_Mode)(bool Switch, char* source_id, char* anchor_id);
typedef Tag_record*(*Load_Location_Coordinate)(unsigned int &Tag_count);
typedef Status_record*(*Load_Location_Status)(unsigned int &Tag_count);
typedef Signal_info (*Load_Anchor_Signal)(void);
typedef bool(*Cleanup)(void);
Location_Set_Anchor_fun Init_Anchor;
Location_Init_fun Location_Init;
Load_Location_Coordinate Load_Location_coordinate;
Load_Location_Status Load_Location_status;
Load_Anchor_Signal Load_anchor_signal;
Device_Signal_Mode Device_signal_mode;
Cleanup Location_cleanup;


Anchor_info* Anchor_List = NULL;
Anchor_info* Main_Anchor_List = NULL;
Anchor_Message * Init_Group_Anchor_List = NULL;
Main_Anchor_Message* Init_Group_Main_Anchor_List =NULL;
Signal_info* signal_info_temp = new Signal_info[1];
unsigned long Anchor_List_count = 0, Main_Anchor_List_count = 0;
unsigned long Init_Group_Anchor_List_count = 0, Init_Group_Main_Anchor_List_count = 0;
char* ip_addr = new char[15];
char* ip_addr_temp = new char[15];
unsigned char* cmd_buff = new unsigned char[2048];
unsigned char* IP_temp = new unsigned char[5];
unsigned char* GW_temp = new unsigned char[5];
unsigned char* MASK_temp = new unsigned char[5];
unsigned char* CLIENT_IP_temp = new unsigned char[5];
volatile long Mouse_X = 0, Mouse_Y = 0,point_count=0,point_record_count = 0, point_record_count_temp = 0, point_count_temp = 0, status_record_count_temp=0;
unsigned int tag_list_height = 0,alarm_list_width=0,status_window_height = 0;
volatile bool openserver_flag = false;
bool Signal_server_flag = false;
bool Inventory_server_flag = false;
bool Anchor_Display_flag = true;
int status_count = 0;


tag_info_point* Tag_Map_point = new tag_info_point[Max_Tag_Count];
tag_info_point* Tag_Map_Record_point = new tag_info_point[Max_Tag_Record_Count];
tagid_info* Tag_Map_id = NULL;
tag_info_status* Tag_Map_Status = new tag_info_status[Max_Tag_Count];
tag_info_status* Tag_Map_Status_temp = new tag_info_status[1];


tag_info_status* Request_Alarm_Status_temp = new tag_info_status[20];
unsigned int request_alarm_count = 0;
unsigned char **allconn_temp = NULL;



//**********************************************
rfid::Network_Interface_Info* Info ;
int net_len = 0 ;
string str_inferface_ip = "" ;

int getSubnetMask( string &tmpIP )
{
    /*
    delete[] Info;
    Info = NULL;

    count = 0;
    int count_temp = 0;
    int first_flag = 0;
    //*/
    struct sockaddr_in *sin = NULL;
    struct ifaddrs *ifa = NULL, *ifList;


    if ( getifaddrs(&ifList) < 0)
    {
        return -1;
    }


    for (ifa = ifList; ifa != NULL; ifa = ifa->ifa_next)
    {
        int family = ifa->ifa_addr->sa_family;
        if(ifa->ifa_addr->sa_family == AF_INET)
        {
            net_len++;
        }
        else if ( ifa->ifa_addr->sa_family == AF_INET6 )
        {

        }
        else if ( ifa->ifa_addr->sa_family == AF_PACKET )
        {

        }
        else
        {
            printf("Unknown address family\n");
        }
    }


    Info = new rfid::Network_Interface_Info[net_len];
    int i = 0 ;

    for (ifa = ifList; ifa != NULL; ifa = ifa->ifa_next)
    {
        int family = ifa->ifa_addr->sa_family;
        if(ifa->ifa_addr->sa_family == AF_INET)
        {
            printf(">>> interfaceName: %s\n", ifa->ifa_name);


            sin = (struct sockaddr_in *)ifa->ifa_addr;
            //printf(">>> ipAddress: %s\n", sin->sin_addr );
            printf(">>> ipAddress: %s\n", inet_ntoa(sin->sin_addr));
            char adrs[INET_ADDRSTRLEN];
            unsigned char IP[4] = {0};
            inet_ntop(AF_INET, &(sin->sin_addr), adrs, INET_ADDRSTRLEN);
            string ip = adrs ;
            stringstream s(ip);
            int a,b,c,d; //to store the 4 ints
            char ch; //to temporarily store the '.'
            s >> a >> ch >> b >> ch >> c >> ch >> d;
            cout << "single unsigned char : "<< a << "-" << b << "-" << c << "-"<< d << endl ;



            //Info[i].Network_Interface_ID = ifa->ifa_name ;
            strcpy( Info[i].Network_Interface_ID,ifa->ifa_name );
            strcpy ( Info[i].IP_address,  adrs) ;

            /*
            Info[i].IP_address[0] = a;
            Info[i].IP_address[1] = b;
            Info[i].IP_address[2] = c;
            Info[i].IP_address[3] = d;
            */
            //cout << Info[i].IP_address[0] << endl ;

            cout << Info[i].Network_Interface_ID << endl ;
            printf("a is : %u\n", a);


            cout << "unsigned char to string : " << adrs << endl ;
            tmpIP = adrs ;
            //printf ( "%s\n", adrs ) ;


            sin = (struct sockaddr_in *)ifa->ifa_dstaddr;
            printf(">>> broadcast: %s\n", inet_ntoa(sin->sin_addr));

            sin = (struct sockaddr_in *)ifa->ifa_netmask;
            printf(">>> subnetMask: %s\n", inet_ntoa(sin->sin_addr));
            cout << endl <<endl ;
            i++ ;


        }

        else if ( ifa->ifa_addr->sa_family == AF_INET6 )
        {
            /*
            printf("%s  address family: %d%s\n", ifa->ifa_name, family, " AF_INET6");
            struct sockaddr_in6 *s = (struct sockaddr_in6 *) ifa->ifa_addr;
            //char * aip = inet_ntoa(s->sin_addr);
            char aip[40];
            inet_ntop(AF_INET6,&s->sin6_addr,aip,sizeof(aip));
            printf("\tIPv6 Address:<%s>\n", aip);
            //*/

        }

        else if ( ifa->ifa_addr->sa_family == AF_PACKET )
        {

        }

        else
        {
            printf("Unknown address family\n");

        }
    }

    freeifaddrs(ifList);

    return 0;
}



rfid::Device_Info* device_info = NULL;

//unsigned char **allconn_temp = NULL;

int Search_dev( string interface_ip )
{

    delete[] allconn_temp;
    allconn_temp = NULL;

    rfid::Device_Info* search_temp;
    char Local_ipaddr[20] = { 0 };
    memset(Local_ipaddr, 0, 20);
    int UDP_count = 0, Max_data_len = 0;
    string local_ip ;
    char tmp_str[20] = { 0 };


    /*
    for ( int i = 0 ; i < Ip_len ; i++ )
        cout << Info[1].IP_address[i] ;
    cout << endl ;
    printf( "%u\n", Info[1].IP_address[0] ) ;

    for ( int i = 0 ; i < 4 ; i++ )
    {
        sprintf( tmp_str, "%u", Info[1].IP_address[i] );
        local_ip += tmp_str ;
        if ( i < 3 )
            local_ip += ".";
    }
    //*/


    local_ip = std::string(interface_ip) ;
    cout << local_ip << endl ;


    for (size_t i = 0; i < interface_ip.length() ; i++)
        Local_ipaddr[i] = interface_ip[i];

    cout << "local IP length : "<< local_ip.length() << endl ;

    cout << "local_ipaddr : " << Local_ipaddr << endl ;

    int UDP_Server_Port = DF_UDP_PORT;

    search_temp = rfid::UDP::Search_ip(UDP_Server_Port, Local_ipaddr, UDP_count);
    allconn_temp = new unsigned char*[UDP_count];
    for (size_t i = 0; i < (unsigned int)UDP_count; i++)
        allconn_temp[i] = new unsigned char[20];
    for (size_t i = 0; i < (unsigned int)UDP_count; i++)
    {
        for (size_t j = 0; j < 20; j++)
            allconn_temp[i][j] = 0;
    }

    for (size_t i = 0; i < (unsigned int)UDP_count; i++)
    {
        cout <<  search_temp[i].IP_address << "\t: " << search_temp[i].MAC_address << endl ;
    }
    //*/
    device_info = search_temp;

    return UDP_count;


    /*
    for (size_t i = 0; i < (unsigned int)UDP_count; i++)
    {
    	String ^ MyStr1 = gcnew String(search_temp[i].Machine_Number.c_str());
    	String ^ MyStr2 = gcnew String(search_temp[i].Model.c_str());
    	String ^ MyStr3 = gcnew String(search_temp[i].IP_address.c_str());
    	String ^ MyStr4 = gcnew String(search_temp[i].Gateway_address.c_str());
    	String ^ MyStr5 = gcnew String(search_temp[i].Mask_address.c_str());
    	String ^ MyStr6 = gcnew String(search_temp[i].Client_ip_addr.c_str());
    	String ^ MyStr7 = gcnew String(search_temp[i].MAC_address.c_str());
    	String ^ MyStr8 = gcnew String(search_temp[i].TCP_Serve_Port.c_str());
    	String ^ MyStr9 = gcnew String(search_temp[i].UDP_Serve_Port.c_str());
    	String ^ MyStr10 = gcnew String(search_temp[i].TCP_Client_Src_Port.c_str());
    	String ^ MyStr11 = gcnew String(search_temp[i].TCP_Client_Des_Port.c_str());
    	for (size_t j = 0; j < (unsigned int)MyStr3->Length; j++)
    		allconn_temp[i][j + 1] = (unsigned char)MyStr3[j];
    	dataGridView1->Rows->Add(true, MyStr1, MyStr2, MyStr3, MyStr4, MyStr5, MyStr6, MyStr7, MyStr8, MyStr9, MyStr10, MyStr11);
    }
    //*/
}




void Update_net_interface()
{

    string interface_name ;
    net_len = 0 ;
    getSubnetMask(interface_name);
    cout << "update_net" << endl ;

    for ( int i = 0 ; i < net_len ; i++ )
    {
        cout << Info[i].Network_Interface_ID << endl ;
        cout << Info[i].IP_address << endl ;
        //wxString trans(Info[i].Network_Interface_ID.c_str(), wxConvUTF8 );
        //ComboBox2->Append(trans);
    }


    cout << interface_name.c_str() << endl ;
    //wxString wxtmp (interface_name.c_str(), wxConvUTF8 );
    //TextCtrl1->ChangeValue( wxtmp );


}

int Update_search_dev( string ip )
{

    //string interface_ip = string(TextCtrl1->GetValue().mbc_str());
    //ip = IntToString(Info[net_len-1].IP_address[0]) +"."+ IntToString(Info[net_len-1].IP_address[1]) + "."+
    //     IntToString(Info[net_len-1].IP_address[2])+"."+ IntToString(Info[net_len-1].IP_address[3]) ;

    int udp_count = Search_dev(ip);

    for ( int i = 0 ; i < udp_count ; i++ )  // row
    {
        g_json_single["Machine_Number"]  = device_info[i].Machine_Number    ;
        g_json_single["Model"]           = device_info[i].Model             ;
        g_json_single["IP_address"]      = device_info[i].IP_address        ;
        g_json_single["Gateway_address"] = device_info[i].Gateway_address   ;
        g_json_single["Mask_address"]    = device_info[i].Mask_address      ;
        g_json_single["Client_ip_addr"]  = device_info[i].Client_ip_addr    ;
        g_json_single["MAC_address"]     = device_info[i].MAC_address       ;
        g_json_single["TCP_Serve_Port"]  = device_info[i].TCP_Serve_Port    ;
        g_json_single["UDP_Serve_Port"]  = device_info[i].UDP_Serve_Port    ;
        g_json_single["TCP_Client_Src_Port"] = device_info[i].TCP_Client_Src_Port ;
        g_json_single["TCP_Client_Des_Port"] = device_info[i].TCP_Client_Des_Port ;
        g_json_multi.push_back(g_json_single);
        g_json_single.clear();

    }

    return udp_count ;

}




//****** for Command()*****************************************

string Interface_name = UWB_Interface1 ;
unsigned char g_Reader_value[2048] = { 0 };
string Model_Name = "" ;

string Version_Name = "" ;

unsigned int UWB_channel = 2, UWB_prf = 1, UWB_datarate = 0;
unsigned int UWB_preambleCode = 4, UWB_preambleLength = 0x8;
unsigned int UWB_PAC = 3, UWB_NSD = 1, UWB_SMARTPOWER = 0;
unsigned int UWB_SFD_timeout = 1089, UWB_PGdelay = 0xC2;
unsigned int UWB_Power = 0x75757575, UWB_MODE = 0, active_ID = 0;
unsigned int NTM_value = 0, PMULT_value = 0, transmission_cycle_time = 0;



int UDP_Server_Port = DF_UDP_PORT;
int TCP_Server_Port = DF_TCP_PORT;
int TCP_Client_Des_Port = DF_TCP_CLIENT_PORT;

char* target_ip = "192.168.1.72";
SerialPort *serialPort1 = new SerialPort();
int dev_count = 0 ;
string fw_name = "" ;
/*
unsigned char* cmd_buff = new unsigned char[2048];
unsigned char* IP_temp = new unsigned char[5];
unsigned char* GW_temp = new unsigned char[5];
unsigned char* MASK_temp = new unsigned char[5];
unsigned char* CLIENT_IP_temp = new unsigned char[5];
*/
//**********************************/**************************/

void SetMyForm_Lock()
{
    /*
    if (this->InvokeRequired)
    {
        SetTextDelegate3^ d =
            gcnew SetTextDelegate3(this, &MyForm::SetMyForm_Lock);
        this->Invoke(d);
    }
    else
    {
        //this->button5->Enabled = true;
        MyForm::Enabled = true;
        Wait_Form->Close();
        cmd_flag = 0, version_flag = 0, ip_flag = 0, gw_flag = 0, mask_flag = 0, client_ip_flag = 0, channel_flag = 0, datarate_flag = 0, prf_flag = 0, preamblecode_flag = 0, preamblelength_flag = 0, pac_flag = 0, pgdelay_falg = 0, power_flag = 0, nsd_flag = 0, sfd_timeout_flag = 0, smartpower_flag = 0, mode_falg = 0, active_ID_flag = 0, NTM_PMULT_flag = 0, read_Parameter_flag = 0, read_network_flag = 0, read_device_flag = 0, write_Parameter_flag = 0, connect_flag = 0, update_flag = 0, transmission_cycle_flag = 0;
    }
    */
    cmd_flag = 0, version_flag = 0, ip_flag = 0, gw_flag = 0, mask_flag = 0, client_ip_flag = 0, channel_flag = 0, datarate_flag = 0, prf_flag = 0, preamblecode_flag = 0, preamblelength_flag = 0, pac_flag = 0, pgdelay_falg = 0, power_flag = 0, nsd_flag = 0, sfd_timeout_flag = 0, smartpower_flag = 0, mode_falg = 0, active_ID_flag = 0, NTM_PMULT_flag = 0, read_Parameter_flag = 0, read_network_flag = 0, read_device_flag = 0, write_Parameter_flag = 0, connect_flag = 0, update_flag = 0, transmission_cycle_flag = 0;


}
volatile int Command_success = 0 ;
void Set_device_arg();
void Set_network_arg();
void Set_read_arg();
void Command()
{
    Command_success = 0 ;
    int temp = dev_count ;
    unsigned int total_count = 0;
    if ((write_device_flag == 0) && (write_network_flag == 0)&&(read_device_flag == 0) && (read_network_flag == 0) && (read_Parameter_flag == 0) && (Interface_name == UWB_Interface1) && (update_flag == 0) && (ip_flag == 0) && (gw_flag == 0) && (mask_flag == 0) && (client_ip_flag == 0) && (Only_IP_flag == 0))
        total_count = temp;
    else
        total_count = 1;

    int Value_flag = 0;
    unsigned char Reader_value[2048] = { 0 };
    unsigned char set_Reader_value[2048] = { 0 };


    if ( version_flag )
    {

        Value_flag = 0;
        memset(Reader_value, 0, sizeof(Reader_value));
        if (Interface_name == UWB_Interface1)
        {
            rfid::TCP::Read_Version(target_ip, TCP_Server_Port, Reader_value, Value_flag);
            //RC_linuxFrame::ComboBox16->Append(wxT("AAAA"));
        }
        else
            rfid::Comport::Read_Version(*serialPort1, Reader_value, Value_flag);

        if (Value_flag != 1)
        {
            Value_flag = 0;
            memset(Reader_value, 0, sizeof(Reader_value));
            if (Interface_name == UWB_Interface1)
                rfid::TCP::Read_Version(target_ip, TCP_Server_Port, Reader_value, Value_flag);

            else
                rfid::Comport::Read_Version(*serialPort1, Reader_value, Value_flag);

            if (Value_flag != 1)
                goto return_error;
            //RC_linuxFrame::ComboBox16->Append(wxT("BBBBBBBBBB"));


        }
        cout << "Model name : " << ((char*)Reader_value) << endl ;
        cout << "Version_Name : "  <<((char*)Reader_value + 8) << endl ;
        //for ( int i = 0 ; i < sizeof(Reader_value); i++)
        //    g_Reader_value[i] = Reader_value[i] ;
        Model_Name = ((char*)Reader_value) ;
        Version_Name = ((char*)Reader_value+8);

    }

    if (mode_falg)
    {
        Value_flag = 0;
        memset(Reader_value, 0, sizeof(Reader_value));

        if (Interface_name == UWB_Interface1)
            rfid::TCP::Read_MODE(target_ip, TCP_Server_Port, Reader_value, Value_flag);
        else
            rfid::Comport::Read_MODE(*serialPort1, Reader_value, Value_flag);

        if (Value_flag != 1)
            goto return_error;
        UWB_MODE = Reader_value[0];


    }
    if (mask_flag)
    {
        Value_flag = 0;
        memset(Reader_value, 0, sizeof(Reader_value));
        if (mask_flag == 2)
        {
            for (size_t i = 0; i < 4; i++)
                set_Reader_value[i] = MASK_temp[i];
        }
        if (Interface_name == UWB_Interface1)
            rfid::TCP::RW_MaskIP(target_ip, TCP_Server_Port, (mask_flag - 1), set_Reader_value, 4, Reader_value, Value_flag);
        mask_flag = 0;
        if (Value_flag != 1)
            goto return_error;
        if (read_network_flag != 0)
        {

            for (size_t i = 0; i < 4; i++)
                MASK_temp[i] = Reader_value[i];
        }
        //Sleep(20); // 20ms
        usleep(2000);
    }
    if (gw_flag)
    {
        Value_flag = 0;
        memset(Reader_value, 0, sizeof(Reader_value));
        if (gw_flag == 2)
        {
            for (size_t i = 0; i < 4; i++)
                set_Reader_value[i] = GW_temp[i];
        }
        if (Interface_name == UWB_Interface1)
            rfid::TCP::RW_GatewayIP(target_ip, TCP_Server_Port, (gw_flag - 1), set_Reader_value, 4, Reader_value, Value_flag);
        gw_flag = 0;
        if (Value_flag != 1)
            goto return_error;
        if (read_network_flag != 0)
        {
            for (size_t i = 0; i < 4; i++)
                GW_temp[i] = Reader_value[i];
        }
        //sleep(20);
        usleep(2000);
    }

    if (client_ip_flag)
    {
        Value_flag = 0;
        memset(Reader_value, 0, sizeof(Reader_value));
        if (client_ip_flag == 2)
        {
            for (size_t i = 0; i < 4; i++)
                set_Reader_value[i] = CLIENT_IP_temp[i];
        }
        if (Interface_name == UWB_Interface1)
            rfid::TCP::RW_ClientIP(target_ip, TCP_Server_Port, (client_ip_flag - 1), set_Reader_value, 4, Reader_value, Value_flag);
        client_ip_flag = 0;
        if (Value_flag != 1)
            goto return_error;
        if (read_network_flag != 0)
        {
            for (size_t i = 0; i < 4; i++)
                CLIENT_IP_temp[i] = Reader_value[i];
        }
        //sleep(20);
        usleep(2000);
    }
    if (ip_flag)
    {
        //cout << "ip flag :" <<target_ip << endl ;
        Value_flag = 0;
        memset(Reader_value, 0, sizeof(Reader_value));
        if (ip_flag == 2)
        {
            for (size_t i = 0; i < 4; i++)
                set_Reader_value[i] = IP_temp[i];
        }
        if (Interface_name == UWB_Interface1)
            rfid::TCP::RW_IP(target_ip, TCP_Server_Port, (ip_flag - 1), set_Reader_value, 4, Reader_value, Value_flag);
        ip_flag = 0;
        if (Value_flag != 1)
            goto return_error;
        if (read_network_flag != 0)
        {

            for (size_t i = 0; i < 4; i++)
            {
                IP_temp[i] = Reader_value[i];
                //printf( "%hu " , IP_temp[i] ) ;
            }
            // cout << endl ;
        }
        //sleep(10);
        usleep(1000);
    }
    if (channel_flag)
    {
        Value_flag = 0;
        memset(Reader_value, 0, sizeof(Reader_value));
        if (channel_flag == 2)
        {
            for (size_t i = 0; i < 1; i++)
                set_Reader_value[i] = UWB_channel;
        }
        if (Interface_name == UWB_Interface1)
            rfid::TCP::RW_Channel(target_ip, TCP_Server_Port, (channel_flag - 1), set_Reader_value, 1, Reader_value, Value_flag);
        else
            rfid::Comport::RW_Channel(*serialPort1, (channel_flag - 1), set_Reader_value, 1, Reader_value, Value_flag);
        if (Value_flag != 1)
            goto return_error;
        if (read_Parameter_flag != 0)
            UWB_channel = Reader_value[0];
    }
    if (datarate_flag)
    {
        Value_flag = 0;
        memset(Reader_value, 0, sizeof(Reader_value));
        if (datarate_flag == 2)
        {
            for (size_t i = 0; i < 1; i++)
                set_Reader_value[i] = UWB_datarate;
        }
        if (Interface_name == UWB_Interface1)
            rfid::TCP::RW_Datarate(target_ip, TCP_Server_Port, (datarate_flag - 1), set_Reader_value, 1, Reader_value, Value_flag);
        else
            rfid::Comport::RW_Datarate(*serialPort1, (datarate_flag - 1), set_Reader_value, 1, Reader_value, Value_flag);
        if (Value_flag != 1)
            goto return_error;
        if (read_Parameter_flag != 0)
            UWB_datarate = Reader_value[0];
    }
    if (prf_flag)
    {
        Value_flag = 0;
        memset(Reader_value, 0, sizeof(Reader_value));
        if (prf_flag == 2)
        {
            for (size_t i = 0; i < 1; i++)
                set_Reader_value[i] = UWB_prf;
        }
        if (Interface_name == UWB_Interface1)
            rfid::TCP::RW_PRF(target_ip, TCP_Server_Port, (prf_flag - 1), set_Reader_value, 1, Reader_value, Value_flag);
        else
            rfid::Comport::RW_PRF(*serialPort1, (prf_flag - 1), set_Reader_value, 1, Reader_value, Value_flag);
        if (Value_flag != 1)
            goto return_error;
        if (read_Parameter_flag != 0)
            UWB_prf = Reader_value[0];
    }
    if (preamblecode_flag)
    {
        Value_flag = 0;
        memset(Reader_value, 0, sizeof(Reader_value));
        if (preamblecode_flag == 2)
        {
            for (size_t i = 0; i < 1; i++)
                set_Reader_value[i] = UWB_preambleCode;
        }
        if (Interface_name == UWB_Interface1)
            rfid::TCP::RW_Preamblecode(target_ip, TCP_Server_Port, (preamblecode_flag - 1), set_Reader_value, 1, Reader_value, Value_flag);
        else
            rfid::Comport::RW_Preamblecode(*serialPort1, (preamblecode_flag - 1), set_Reader_value, 1, Reader_value, Value_flag);
        if (Value_flag != 1)
            goto return_error;
        if (read_Parameter_flag != 0)
            UWB_preambleCode = Reader_value[0];
    }
    if (preamblelength_flag)
    {
        Value_flag = 0;
        memset(Reader_value, 0, sizeof(Reader_value));
        if (preamblelength_flag == 2)
        {
            for (size_t i = 0; i < 1; i++)
                set_Reader_value[i] = UWB_preambleLength;
        }
        if (Interface_name == UWB_Interface1)
            rfid::TCP::RW_PreambleLength(target_ip, TCP_Server_Port, (preamblelength_flag - 1), set_Reader_value, 1, Reader_value, Value_flag);
        else
            rfid::Comport::RW_PreambleLength(*serialPort1, (preamblelength_flag - 1), set_Reader_value, 1, Reader_value, Value_flag);
        if (Value_flag != 1)
            goto return_error;
        if (read_Parameter_flag != 0)
            UWB_preambleLength = Reader_value[0];
    }
    if (pac_flag)
    {
        Value_flag = 0;
        memset(Reader_value, 0, sizeof(Reader_value));
        if (pac_flag == 2)
        {
            for (size_t i = 0; i < 1; i++)
                set_Reader_value[i] = UWB_PAC;
        }
        if (Interface_name == UWB_Interface1)
            rfid::TCP::RW_PAC(target_ip, TCP_Server_Port, (pac_flag - 1), set_Reader_value, 1, Reader_value, Value_flag);
        else
            rfid::Comport::RW_PAC(*serialPort1, (pac_flag - 1), set_Reader_value, 1, Reader_value, Value_flag);
        if (Value_flag != 1)
            goto return_error;
        if (read_Parameter_flag != 0)
            UWB_PAC = Reader_value[0];
    }
    if (pgdelay_falg)
    {
        Value_flag = 0;
        memset(Reader_value, 0, sizeof(Reader_value));
        if (pgdelay_falg == 2)
        {
            for (size_t i = 0; i < 1; i++)
                set_Reader_value[i] = UWB_PGdelay;
        }
        if (Interface_name == UWB_Interface1)
            rfid::TCP::RW_TX_PGDELAY(target_ip, TCP_Server_Port, (pgdelay_falg - 1), set_Reader_value, 1, Reader_value, Value_flag);
        else
            rfid::Comport::RW_TX_PGDELAY(*serialPort1, (pgdelay_falg - 1), set_Reader_value, 1, Reader_value, Value_flag);
        if (Value_flag != 1)
            goto return_error;
        if (read_Parameter_flag != 0)
            UWB_PGdelay = Reader_value[0];
    }
    if (power_flag)
    {
        Value_flag = 0;
        memset(Reader_value, 0, sizeof(Reader_value));
        if (power_flag == 2)
        {
            set_Reader_value[0] = ((UWB_Power & 0xFF000000) >> 24);
            set_Reader_value[1] = ((UWB_Power & 0xFF0000) >> 16);
            set_Reader_value[2] = ((UWB_Power & 0xFF00) >> 8);
            set_Reader_value[3] = ((UWB_Power & 0xFF));
        }
        if (Interface_name == UWB_Interface1)
            rfid::TCP::RW_TX_POWER(target_ip, TCP_Server_Port, (power_flag - 1), set_Reader_value, 4, Reader_value, Value_flag);
        else
            rfid::Comport::RW_TX_POWER(*serialPort1, (power_flag - 1), set_Reader_value, 4, Reader_value, Value_flag);
        if (Value_flag != 1)
            goto return_error;
        if (read_Parameter_flag != 0)
            UWB_Power = ((unsigned int)Reader_value[0] << 24) + ((unsigned int)Reader_value[1] << 16) + ((unsigned int)Reader_value[2] << 8) + ((unsigned int)Reader_value[3]);
    }
    if (nsd_flag)
    {
        Value_flag = 0;
        memset(Reader_value, 0, sizeof(Reader_value));
        if (nsd_flag == 2)
        {
            for (size_t i = 0; i < 1; i++)
                set_Reader_value[i] = UWB_NSD;
        }
        if (Interface_name == UWB_Interface1)
            rfid::TCP::RW_NSD(target_ip, TCP_Server_Port, (nsd_flag - 1), set_Reader_value, 1, Reader_value, Value_flag);
        else
            rfid::Comport::RW_NSD(*serialPort1, (nsd_flag - 1), set_Reader_value, 1, Reader_value, Value_flag);
        if (Value_flag != 1)
            goto return_error;
        if (read_Parameter_flag != 0)
            UWB_NSD = Reader_value[0];
    }
    if (sfd_timeout_flag)
    {
        Value_flag = 0;
        memset(Reader_value, 0, sizeof(Reader_value));
        if (sfd_timeout_flag == 2)
        {
            set_Reader_value[0] = ((UWB_SFD_timeout & 0xFF00) >> 8);
            set_Reader_value[1] = ((UWB_SFD_timeout & 0xFF));
        }
        if (Interface_name == UWB_Interface1)
            rfid::TCP::RW_SFD_Timeout(target_ip, TCP_Server_Port, (sfd_timeout_flag - 1), set_Reader_value, 2, Reader_value, Value_flag);
        else
            rfid::Comport::RW_SFD_Timeout(*serialPort1, (sfd_timeout_flag - 1), set_Reader_value, 2, Reader_value, Value_flag);
        if (Value_flag != 1)
            goto return_error;
        if (read_Parameter_flag != 0)
            UWB_SFD_timeout = ((unsigned int)Reader_value[0] << 8) + ((unsigned int)Reader_value[1]);
    }
    if (smartpower_flag)
    {
        Value_flag = 0;
        memset(Reader_value, 0, sizeof(Reader_value));
        if (smartpower_flag == 2)
        {
            for (size_t i = 0; i < 1; i++)
                set_Reader_value[i] = UWB_SMARTPOWER;
        }
        if (Interface_name == UWB_Interface1)
            rfid::TCP::RW_SMARTPOWER(target_ip, TCP_Server_Port, (smartpower_flag - 1), set_Reader_value, 1, Reader_value, Value_flag);
        else
            rfid::Comport::RW_SMARTPOWER(*serialPort1, (smartpower_flag - 1), set_Reader_value, 1, Reader_value, Value_flag);
        if (Value_flag != 1)
            goto return_error;
        if (read_Parameter_flag != 0)
            UWB_SMARTPOWER = Reader_value[0];
    }

    if (active_ID_flag)
    {
        int len_temp = 0;
        Value_flag = 0;
        if (UWB_MODE == 1)
            len_temp = 4;
        else
            len_temp = 2;
        memset(Reader_value, 0, sizeof(Reader_value));
        if (active_ID_flag == 2)
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
        if (Interface_name == UWB_Interface1)
            rfid::TCP::RW_active_ID(target_ip, TCP_Server_Port, (active_ID_flag - 1), set_Reader_value, len_temp, Reader_value, Value_flag);
        else
            rfid::Comport::RW_active_ID(*serialPort1, (active_ID_flag - 1), set_Reader_value, len_temp, Reader_value, Value_flag);
        if (Value_flag != 1)
            goto return_error;
        //if ((read_device_flag != 0) || (read_Parameter_flag))
        //{
        if (len_temp == 4)
            active_ID = ((unsigned int)Reader_value[0] << 24) + ((unsigned int)Reader_value[1] << 16) + ((unsigned int)Reader_value[2] << 8) + ((unsigned int)Reader_value[3]);
        else
            active_ID = ((unsigned int)Reader_value[0] << 8) + ((unsigned int)Reader_value[1]);
        //}
        if (active_ID_flag == 2)
            read_device_flag = 0;
    }
    if (transmission_cycle_flag)
    {
        Value_flag = 0;
        memset(Reader_value, 0, sizeof(Reader_value));
        if (transmission_cycle_flag == 2)
        {
            set_Reader_value[0] = (transmission_cycle_time & 0xFF0000) >> 16;
            set_Reader_value[1] = (transmission_cycle_time & 0xFF00) >> 8;
            set_Reader_value[2] = (transmission_cycle_time & 0xFF);
        }
        if (Interface_name == UWB_Interface1)
            rfid::TCP::RW_Transmission_Cycle(target_ip, TCP_Server_Port, (transmission_cycle_flag - 1), set_Reader_value, 3, Reader_value, Value_flag);
        else
            rfid::Comport::RW_Transmission_Cycle(*serialPort1, (transmission_cycle_flag - 1), set_Reader_value, 3, Reader_value, Value_flag);
        if (Value_flag != 1)
            goto return_error;
        if (read_device_flag != 0)
            transmission_cycle_time = (((unsigned int)Reader_value[0] << 16) + ((unsigned int)Reader_value[1] << 8) + ((unsigned int)Reader_value[2]));
    }
    if (NTM_PMULT_flag)
    {
        Value_flag = 0;
        memset(Reader_value, 0, sizeof(Reader_value));
        if (NTM_PMULT_flag == 2)
        {
            set_Reader_value[0] = PMULT_value;
            set_Reader_value[1] = NTM_value;
        }
        if (Interface_name == UWB_Interface1)
            rfid::TCP::RW_NTM_MULT(target_ip, TCP_Server_Port, (NTM_PMULT_flag - 1), set_Reader_value, 2, Reader_value, Value_flag);
        else
            rfid::Comport::RW_NTM_MULT(*serialPort1, (NTM_PMULT_flag - 1), set_Reader_value, 2, Reader_value, Value_flag);
        if (Value_flag != 1)
            goto return_error;
        if (read_Parameter_flag != 0)
        {
            PMULT_value = Reader_value[0];
            NTM_value = Reader_value[1];
        }
    }

    if ((total_count != 1) && (write_Parameter_flag != 0) && (Interface_name == UWB_Interface1) && (Value_flag == 1))
    {
        rfid::TCP::Reset_Chip(target_ip, TCP_Server_Port, Value_flag);
        usleep(100000);
    }

    if (update_flag)
    {
        const char* Filename = fw_name.c_str() ;
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
                            goto return_error;
                        }

                        if (stopvalue == false)
                        {
                            //displaymesgbox(13);
                            //Setbarvalue();
                            break;
                        }
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
                        goto return_error;
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
                    goto return_error;
                }


                if (stopvalue == true)
                {
                    //displaymesgbox(12);
                }
                else if (stopvalue == false)
                {
                    //displaymesgbox(13);
                    //Setbarvalue();
                }
            }
            goto return_ok;
        }
        else
        {
            //displaymesgbox(21);
            goto return_error;
        }
        goto return_ok;
    }

    //if((connect_flag == 1) && (Interface_name == UWB_Interface1))
    //    Connection_only(count_temp);
    //*
    if (Value_flag == 0x01)
    {
        if (connect_flag)
        {
            if (total_count == 1)
            {
                //Connection();
            }
            //displaymesgbox(5);
            connect_flag = 0;
        }
        else if (read_network_flag || read_device_flag)
        {
            if (read_network_flag)
            {
                Set_network_arg();
                read_network_flag = 0;
            }
            if (read_device_flag)
            {
                Set_device_arg();
                read_device_flag = 0;
            }
            //displaymesgbox(28);
        }
        else if (read_Parameter_flag)
        {
            Set_read_arg();
            //displaymesgbox(28);
            read_Parameter_flag = 0;
        }
        else if ((write_device_flag == 1) || (write_network_flag == 1))
        {
            //displaymesgbox(36);
            write_device_flag = 0;
            write_network_flag = 0;
        }
        else if (write_Parameter_flag)
        {
            if (Interface_name == UWB_Interface1)
            {
                if (total_count == 1)
                    rfid::TCP::Reset_Chip(ip_addr, TCP_Server_Port, Value_flag);
            }
            else
                rfid::Comport::Reset_Chip(*serialPort1, Value_flag);

            //displaymesgbox(36);
            write_Parameter_flag = 0;
        }
        goto return_ok;
    }

    //*/






return_error:
    Command_success = 0 ;
    //cout << "EROR" << endl;

return_ok:
    Command_success = 1 ;
    SetMyForm_Lock();
    //cout << "OK" << endl;


}

string main_extern = "YOOOOO" ;
std::string rf_channel          = "" ;
std::string rf_datarate         = "" ;
std::string rf_prf              = "" ;
std::string rf_preambleCode     = "" ;
std::string rf_preambleLength   = "" ;
std::string rf_PAC              = "" ;
std::string rf_PGdelay          = "" ;
std::string rf_Power            = "" ;
std::string rf_NSD              = "" ;
std::string rf_SFD_timeout      = "" ;
std::string rf_SMARTPOWER       = "" ;
std::string rf_MODE             = "" ;
std::string rf_active_ID        = "" ;
std::string rf_NTM_value        = "" ;
std::string rf_PMULT_value      = "" ;
//*/
void Set_read_arg()
{

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


std::string dev_transmission_cycle_time = "" ;
std::string dev_active_ID               = "" ;
void Set_device_arg()
{


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


std::string dev_IP[4]           = {"","","",""};
std::string dev_Mask[4]         = {"","","",""};
std::string dev_GW[4]           = {"","","",""};
std::string dev_Client_IP[4]    = {"","","",""};
void Set_network_arg()
{
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

void Update_FW()
{

    fw_name = "/home/szok/桌面/韌體/ANCHOR 韌體/001.001.bin" ;
    update_flag = 1;
    Command() ;

}



void Read_Network_setting()
{

    ip_flag = 1;
    gw_flag = 1;
    mask_flag = 1;

    client_ip_flag = 1;
    read_network_flag = 1;
    mode_falg = 1;

    Command() ;
    cout << read_network_flag << endl ;
    if (read_network_flag)
    {
        Set_network_arg();
        read_network_flag = 0;
        SetMyForm_Lock();
    }


}

void Write_Network_setting()
{
    try
    {
        ip_flag = 2;
        gw_flag = 2;
        mask_flag = 2;
        client_ip_flag = 2;

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

        write_network_flag = 1;

    }
    catch (exception &e)
    {
        ip_flag = 0;
        gw_flag = 0;
        mask_flag = 0;
        client_ip_flag = 0;
        write_network_flag = 0;
        SetMyForm_Lock();
        return;

    }


    Command() ;

    /*
    try
    {
        unsigned char IPtemp_1 = 0, IPtemp_2 = 0, IPtemp_3 = 0, IPtemp_4 = 0;
        IP_temp[0] = IPtemp_1 = (Convert::ToUInt32(textBox9->Text));
        MASK_temp[0] = IPtemp_1 = (Convert::ToUInt32(textBox20->Text));
        GW_temp[0] = IPtemp_1 = (Convert::ToUInt32(textBox16->Text));
        CLIENT_IP_temp[0] = IPtemp_1 = (Convert::ToUInt32(textBox21->Text));

        write_network_flag = 1;
    }
    catch (Exception ^)
    {
        ip_flag = 0;
        gw_flag = 0;
        mask_flag = 0;
        client_ip_flag = 0;
        write_network_flag = 0;
        SetMyForm_Lock();
        return;
    }
    */



}



extern void Write_Basic_setting()
{
    try
    {
        dev_transmission_cycle_time = g_json_single["dev_transmission_cycle_time"] ;
        dev_active_ID = g_json_single["dev_active_ID"] ;


        if (Interface_name == UWB_Interface1)
        {
            active_ID = stoi(dev_active_ID);
            active_ID_flag = 2;
        }
        else
        {
            transmission_cycle_time = stoi(dev_transmission_cycle_time);
            active_ID = stoi(dev_active_ID);
            transmission_cycle_flag = 2;
            active_ID_flag = 2;
        }
        write_device_flag = 1;

    }
    catch ( exception &e )
    {
        active_ID_flag = 0;
        transmission_cycle_flag = 0;
        write_device_flag = 0;
        SetMyForm_Lock();
        return;

    }



    Command() ;



    /*
    try
    {
        write_device_flag = 1;
        if (Interface_name == UWB_Interface1)
        {
            active_ID = (Convert::ToInt32(textBox26->Text));
            active_ID_flag = 2;
        }
        else
        {
            transmission_cycle_time = (Convert::ToInt32(textBox11->Text));
            active_ID = (Convert::ToInt32(textBox26->Text));
            transmission_cycle_flag = 2;
            active_ID_flag = 2;
        }
    }
    catch (Exception ^)
    {
        active_ID_flag = 0;
        transmission_cycle_flag = 0;
        write_device_flag = 0;
        SetMyForm_Lock();
        return;
    }
    */



}




void Read_Basic_setting()
{

    read_device_flag = 1;
    mode_falg = 1;
    if (Interface_name == UWB_Interface1)
        active_ID_flag = 1;
    else
    {
        transmission_cycle_flag = 1;
        active_ID_flag = 1;
    }
    Command() ;

    if (read_device_flag)
    {
        Set_device_arg();
        read_device_flag = 0;
    }



}

void Write_RF_setting()
{

    try
    {


        version_flag = 1;
        channel_flag = 2;
        datarate_flag = 2;
        prf_flag = 2;
        preamblecode_flag = 2;
        preamblelength_flag = 2;
        pac_flag = 2;
        pgdelay_falg = 2;
        power_flag = 2;
        nsd_flag = 2;
        sfd_timeout_flag = 2;
        smartpower_flag = 2;
        mode_falg = 1;
        NTM_PMULT_flag = 2;
        write_Parameter_flag = 1;


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
        cout << "maybe parse error" << endl ;
        return ;
    }

    Command() ;


}

void Read_RF_setting()
{
    version_flag = 1;
    active_ID_flag = 1;
    channel_flag = 1;
    datarate_flag = 1;
    prf_flag = 1;
    preamblecode_flag = 1;
    preamblelength_flag = 1;
    pac_flag = 1;
    pgdelay_falg = 1;
    power_flag = 1;
    nsd_flag = 1;
    sfd_timeout_flag = 1;
    smartpower_flag = 1;
    mode_falg = 1;
    NTM_PMULT_flag = 1;
    read_Parameter_flag = 1;

    Command() ;
    Set_read_arg();
    read_Parameter_flag = 0;


}








//**********************************************








//char* ip_addr = "192.168.1.202";

//char ip_addr[15]="192.168.1.162";
char* new_ip_addr = "192.168.1.202";
char* new_mask_addr = "255.255.255.0";
char* new_gw_addr = "192.168.1.254" ;
char* ip_adr = "192.168.1.93";


int sockSrv;
int port = 50004;
bool bOpen = false;

char* ip_addr_old = "192.168.1.69";



void TCP_thread_Safe( SOCKET m_socket );
bool init_server()
{
//    sockSrv = socket(AF_INET, SOCK_STREAM, 0);
//	SOCKADDR_IN addrSrv;
//	addrSrv.sin_family = AF_INET;
//	addrSrv.sin_port = htons(port);
//	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
//
//	int retVal = bind(sockSrv, (LPSOCKADDR)&addrSrv, sizeof(SOCKADDR_IN));
//	if (retVal == SOCKET_ERROR)
//	{
//		printf("Failed bind:%d\n", WSAGetLastError());
//		return false;
//	}
//	if (listen(sockSrv, SOMAXCONN) == SOCKET_ERROR)
//	{
//		printf("Listen failed:%d\n", WSAGetLastError());
//		return false;
//	}

    /*
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
    	printf("Failed to load Winsock");
    	return false;
    }
    */
    /*
    sockSrv = socket(AF_INET, SOCK_STREAM, 0);
    SOCKADDR_IN addrSrv;
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(port);
    //addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    addrSrv.sin_addr.s_addr = htonl(INADDR_ANY);
    */

    sockSrv = socket(AF_INET, SOCK_STREAM, 0);
    if( sockSrv < 0)
    {
        printf("Create Socket Failed!");
        exit(1);
    }

    struct sockaddr_in addrSrv,serverInfo;
    bzero(&serverInfo,sizeof(serverInfo));
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(80);
    //addrSrv.sin_addr.s_addr = htonl(INADDR_ANY);
    //addrSrv.sin_addr.s_addr = INADDR_BROADCAST;
    addrSrv.sin_addr.s_addr = inet_addr(ip_adr);;

    int sockClient;
    int server_socket = socket(PF_INET,SOCK_STREAM,0);
//    if( server_socket < 0)
//    {
//        printf("Create Socket Failed!");
//        exit(1);
//    }

    int opt =1;
    //SO_REUSEPORT
    //SO_REUSEADDR
    setsockopt(sockSrv,SOL_SOCKET,SO_REUSEPORT,&opt,sizeof(opt));

    //set timeout
    //struct timeval time_rev= {1,0}; // {sec,ms}
    //setsockopt(sockSrv, SOL_SOCKET, SO_RCVTIMEO, (const void*) &time_rev, sizeof(time_rev));


    int retVal = bind(sockSrv, (struct sockaddr*)&addrSrv, sizeof(SOCKADDR_IN));
    //int retVal = bind(sockSrv, (struct sockaddr*)&serverInfo, sizeof(serverInfo));
    //int retVal = bind(sockSrv,(struct sockaddr *)&serverInfo,sizeof(serverInfo));
    printf("bind failed1:%x\n", retVal);
    if ( retVal == SOCKET_ERROR )
    {
        printf("Failed bind from locus:%d\n", errno);
        return false;
    }
    int flag = listen(sockSrv, 128);
    if (flag == SOCKET_ERROR)
    {
        printf("Listen failed1:%x\n", sockSrv);
        printf("Listen failed:%x\n", errno);
        return false;
    }
    return true;
}

void start_server()
{
    struct SOCKADDR_IN addrtmp;

    //SOCKADDR_IN addrClient;
    int len = sizeof(addrtmp);
    //SOCKET sockConn;
    int sockConn;
    bOpen = true;


    while (bOpen)
    {
        //���ݫȤ�ШD

        sockConn = SOCKET_ERROR;
        sockConn = accept(sockSrv, NULL, NULL );
        //printf("failed:%02d\n", errno);
        if (sockConn == SOCKET_ERROR)
        {
            printf("Accept failed from locus:%02d\n", errno);
            break;
        }

        //windows
        //int time_rev = 2000;

        //linux
        struct timeval time_rev= {1,0}; // {sec,ms}
        int flags = 1;
        //setsockopt(sfd, SO_TCP, TCP_NODELAY, (void *)&flags, sizeof(flags));
        //setsockopt(sockConn, 0xffff, TCP_NODELAY, (char*)&flags, sizeof(flags));//
        setsockopt(sockConn, SOL_SOCKET, SO_SNDTIMEO, (const void*) &time_rev, sizeof(time_rev));
        setsockopt(sockConn, SOL_SOCKET, SO_RCVTIMEO, (const void*) &time_rev, sizeof(time_rev));
        //thread thread_client(&client_process, sockConn);
        thread thread_client(&TCP_thread_Safe, sockConn);
        thread_client.detach();
        usleep(0);
        //Sleep(1);
    }
    //closesocket(sockSrv);
    close(sockSrv);
    //WSACleanup();
}


void Lanuch_Server()
{
    init_server();
    start_server();

}





void SQL_Group_init()
{
    delete[] Init_Group_Main_Anchor_List;
    delete[] Init_Group_Anchor_List;
    Init_Group_Main_Anchor_List = NULL;
    Init_Group_Anchor_List = NULL;
    Init_Group_Main_Anchor_List_count = 0;
    Init_Group_Anchor_List_count = 0;


    SQL_Open();
    string query = "select G.group_id, G.main_anchor_id, G_A.anchor_id from  group_anchors G_A,  group_info G where G_A.group_id = G.group_id ;";
    try
    {
        g_result = g_state->executeQuery(query);

        g_result->last(); //— jump coursor to last
        Init_Group_Anchor_List_count = g_result->getRow(); //— row no.
        g_result->beforeFirst(); //— re jump to very before first
        cout << Init_Group_Anchor_List_count << endl ;

        Init_Group_Main_Anchor_List = new Main_Anchor_Message[Main_Anchor_List_count];
        Init_Group_Anchor_List = new Anchor_Message[Init_Group_Anchor_List_count];

        int init_count = 0;
        while (g_result->next())
        {
            string group_id = g_result->getString("group_id");
            string main_anchor_id = g_result->getString("main_anchor_id");
            string anchor_id = g_result->getString("anchor_id");

            long temp_group = std::atoi(group_id.c_str());
            long temp_main_anchor = std::atoi(main_anchor_id.c_str());
            long temp_anchor = std::atoi(anchor_id.c_str());
            Init_Group_Anchor_List[init_count].item = temp_group;
            Init_Group_Anchor_List[init_count].main_group = temp_main_anchor;
            Init_Group_Anchor_List[init_count].id = temp_anchor;
            for (size_t i = 0; i < Anchor_List_count; i++)
            {
                if (Anchor_List[i].id == Init_Group_Anchor_List[init_count].id)
                {
                    cout << "main an id:" <<Anchor_List[i].id << endl ;
                    Init_Group_Anchor_List[init_count].x = Anchor_List[i].point.x * Map_Scale;
                    Init_Group_Anchor_List[init_count].y = Anchor_List[i].point.y * Map_Scale;
                }
            }
            init_count++;

        }
    }
    catch(sql::SQLException& e)
    {
        std::cout << e.what() << std::endl;
    }

    for (size_t i = 0; i < Main_Anchor_List_count; i++)
    {
        Init_Group_Main_Anchor_List[i].id = Main_Anchor_List[i].id;
        Init_Group_Main_Anchor_List[i].x = Main_Anchor_List[i].point.x * Map_Scale;
        Init_Group_Main_Anchor_List[i].y = Main_Anchor_List[i].point.y * Map_Scale;
        cout << Init_Group_Main_Anchor_List[i].id << "," << Init_Group_Main_Anchor_List[i].x << "," << Init_Group_Main_Anchor_List[i].y<< endl ;
        Init_Group_Main_Anchor_List_count++;
    }


    SQL_Close();
}


volatile bool _SQL_flag = false ;
volatile bool isPreSet = false ;
volatile bool _using_SQL()
{
    std::string line;
    std::ifstream inFile;
    string ini_file = "SQL.ini" ;
    inFile.open( ini_file );
    int line_count = 0 ;
    while (getline(inFile, line))
    {
        if (line == "")
            break;
        line_count++;
    }
    inFile.close();

    int init_count = 0;
    inFile.open( ini_file );

    int ret_val = 0 ;
    while (getline(inFile, line))
    {
        if (line == "")
            break;
        std::string::size_type pos_an = line.find(':');

        std::string f_key = line.substr(0, (pos_an));
        std::string f_value = line.substr(pos_an + 1, line.length());

        ret_val = atoi(f_value.c_str()) ;
        cout << "key :" << f_key << ", f_value :" << f_value << endl ;


        init_count++;
    }
    inFile.close();


    cout << ret_val << endl ;
    if ( ret_val == 1 )
    {
        _SQL_flag = true ;
        return true ;
    }
    else
    {
        _SQL_flag = false ;
        return false ;
    }
}


void Init_Group_List(void)
{
    delete[] Init_Group_Main_Anchor_List;
    delete[] Init_Group_Anchor_List;
    Init_Group_Main_Anchor_List = NULL;
    Init_Group_Anchor_List = NULL;
    Init_Group_Main_Anchor_List_count = 0;
    Init_Group_Anchor_List_count = 0;

    std::string line;
    std::ifstream inFile;
    inFile.open("Anchor Group List.ini");
    while (getline(inFile, line))
    {
        if (line == "")
            break;
        Init_Group_Anchor_List_count++;
    }
    inFile.close();

    Init_Group_Main_Anchor_List = new Main_Anchor_Message[Main_Anchor_List_count];
    Init_Group_Anchor_List = new Anchor_Message[Init_Group_Anchor_List_count];

    int init_count = 0;
    inFile.open("Anchor Group List.ini");
    while (getline(inFile, line))
    {
        if (line == "")
            break;
        std::string::size_type pos_an = line.find(':');
        std::string::size_type pos = line.find(',');
        std::string group = line.substr(0, (pos_an));
        std::string main_anchor = line.substr(pos_an + 1, (pos - pos_an - 1));
        std::string anchor = line.substr(pos + 1, line.length());
        long temp_group = std::atoi(group.c_str());
        long temp_main_anchor = std::atoi(main_anchor.c_str());
        long temp_anchor = std::atoi(anchor.c_str());
        Init_Group_Anchor_List[init_count].item = temp_group;
        Init_Group_Anchor_List[init_count].main_group = temp_main_anchor;
        Init_Group_Anchor_List[init_count].id = temp_anchor;
        for (size_t i = 0; i < Anchor_List_count; i++)
        {
            if (Anchor_List[i].id == Init_Group_Anchor_List[init_count].id)
            {
//                cout << "an id:" <<Anchor_List[i].id << endl ;
                Init_Group_Anchor_List[init_count].x = Anchor_List[i].point.x * Map_Scale;
                Init_Group_Anchor_List[init_count].y = Anchor_List[i].point.y * Map_Scale;
            }
        }

        init_count++;
    }
    inFile.close();


//    cout << "main anchor list :" <<endl ;

    for (size_t i = 0; i < Main_Anchor_List_count; i++)
    {
        Init_Group_Main_Anchor_List[i].id = Main_Anchor_List[i].id;
        Init_Group_Main_Anchor_List[i].x = Main_Anchor_List[i].point.x * Map_Scale;
        Init_Group_Main_Anchor_List[i].y = Main_Anchor_List[i].point.y * Map_Scale;
//        cout << Init_Group_Main_Anchor_List[i].id << endl ;
        Init_Group_Main_Anchor_List_count++;
    }
}


void SQL_Anchors_init()
{
    delete[] Anchor_List;
    delete[] Main_Anchor_List;

    Anchor_List_count = 0;
    Main_Anchor_List_count = 0;
    int init_count = 0;

    SQL_Open();
    string query = "select * from anchor_info where anchor_type = \"main\" ;";
    string query2 = "select * from anchor_info where anchor_type != \"main\" ;";
    try
    {

        // Load main anchor_info
        g_result = g_state->executeQuery(query);

        g_result->last(); //— jump coursor to last
        Main_Anchor_List_count = g_result->getRow(); //— row no.
        g_result->beforeFirst(); //— re jump to very before first

        Main_Anchor_List = new Anchor_info[Main_Anchor_List_count];

        int init_count = 0;
        while (g_result->next())
        {
            string anchor_id = g_result->getString("anchor_id");
            string set_x = g_result->getString("set_x");
            string set_y = g_result->getString("set_y");

            int an = std::atoi(anchor_id.c_str());
            int x = std::atoi(set_x.c_str());
            int y = std::atoi(set_y.c_str());
            Main_Anchor_List[init_count].id = an;
            Main_Anchor_List[init_count].point.x = x;
            Main_Anchor_List[init_count].point.y = y;
            cout << "sql main an :" << an << "," <<  x <<"," << y << endl ;

            init_count++;
        } // while



        // Load anchor_info
        g_result = g_state->executeQuery(query2);

        g_result->last(); //— jump coursor to last
        Anchor_List_count = g_result->getRow(); //— row no.
        g_result->beforeFirst(); //— re jump to very before first
        cout << Anchor_List_count << endl ;

        Anchor_List = new Anchor_info[Anchor_List_count];
        init_count = 0;
        while (g_result->next())
        {
            string anchor_id = g_result->getString("anchor_id");
            string set_x = g_result->getString("set_x");
            string set_y = g_result->getString("set_y");

            int an = std::atoi(anchor_id.c_str());
            int x = std::atoi(set_x.c_str());
            int y = std::atoi(set_y.c_str());
            Anchor_List[init_count].id = an;
            Anchor_List[init_count].point.x = x;
            Anchor_List[init_count].point.y = y;
            cout << "sql an :" << an << "," <<  x <<"," << y << endl ;

            init_count++;
        }


    }
    catch(sql::SQLException& e)
    {
        std::cout << e.what() << std::endl;
    }

    SQL_Close();
}


void init_anchor_list(void)
{
    delete[] Anchor_List;
    delete[] Main_Anchor_List;


    Anchor_List_count = 0;
    Main_Anchor_List_count = 0;
    int init_count = 0;

    //Main Anchor List
    std::string line;
    std::ifstream inFile;
    inFile.open("Main Anchor List.ini");
    while (getline(inFile, line))
    {
        if (line == "")
            break;
        Main_Anchor_List_count++;
    }
    Main_Anchor_List = new Anchor_info[Main_Anchor_List_count];

    inFile.close();
    inFile.open("Main Anchor List.ini");




    while (getline(inFile, line))
    {

        if (line == "")
            break;
        std::string::size_type pos_an = line.find(':');
        std::string::size_type pos = line.find(',');
        std::string anchor = line.substr(0, (pos_an));
        std::string str_x = line.substr(pos_an + 1, (pos - pos_an - 1));
        std::string str_y = line.substr(pos + 1, line.length());
        int an = std::atoi(anchor.c_str());
        int x = std::atoi(str_x.c_str());
        int y = std::atoi(str_y.c_str());
        Main_Anchor_List[init_count].id = an;
        Main_Anchor_List[init_count].point.x = x;
        Main_Anchor_List[init_count].point.y = y;
        cout << "main an :"<< an << "," << x << "," << y << endl ;
        init_count++;
    }
    inFile.close();

    //Anchor List
    init_count = 0;
    inFile.open("Anchor List.ini");
    while (getline(inFile, line))
    {
        if (line == "")
            break;
        Anchor_List_count++;
    }

    Anchor_List = new Anchor_info[Anchor_List_count];

    inFile.close();
    inFile.open("Anchor List.ini");



    while (getline(inFile, line))
    {
        if (line == "")
            break;
        std::string::size_type pos_an = line.find(':');
        std::string::size_type pos = line.find(',');
        std::string anchor = line.substr(0, (pos_an));
        std::string str_x = line.substr(pos_an + 1, (pos - pos_an - 1));
        std::string str_y = line.substr(pos + 1, line.length());
        int an = std::atoi(anchor.c_str());
        int x = std::atoi(str_x.c_str());
        int y = std::atoi(str_y.c_str());
        Anchor_List[init_count].id = an;
        Anchor_List[init_count].point.x = x;
        Anchor_List[init_count].point.y = y;

        cout << "an :" <<an << ":" << x << ":" << y << endl ;

        init_count++;
    }
    inFile.close();
}

string Trans2Standard( string tmp )
{

    // 2019/12/13/18:30:50:54 -> 2019-12-13/18:30:50:54
    for ( int i = 0 ; i <2; i++ )
        tmp = tmp.replace( tmp.find( "/"),1,"-" );

    // 2019-12-13/18:30:50:54 -> 2019-12-13 18:30:50:54
    tmp = tmp.replace( tmp.find( "/"),1," " );

    // 2019-12-13/18:30:50:54 -> 2019-12-13 18:30:50.54
    tmp = tmp.replace( tmp.find_last_of( ":"),1,"." );
    return tmp;

//    cout << tmp << endl ;

}

string TransDate( string tmp )
{

    // 2019/12/13/18:30:50:54 -> 2019-12-13/18:30:50:54
    for ( int i = 0 ; i <2; i++ )
        tmp = tmp.replace( tmp.find( "/"),1,"-" );

    int current = 0;
    int pos = tmp.find_first_of("/", current);

    // cout << tmp.substr(current, pos - current)<<endl;
    string rets = tmp.substr(current, pos - current) ;

    return rets;


}

string TransTime( string tmp )
{
    // 2019/12/13/18:30:50:54 -> 2019-12-13/18:30:50:54
    for ( int i = 0 ; i <2; i++ )
        tmp = tmp.replace( tmp.find( "/"),1,"-" );

    int current = 0;
    int pos = tmp.find_first_of(" /", current) + 1 ;

    tmp = tmp.replace( tmp.find_last_of( ":"),1,"." );
    string rets = tmp.substr(pos, tmp.length() - pos) ;

//    cout << rets << endl ;
    return rets;

//    cout << tmp << endl ;

}

string Get_LastDay_date()
{

    char buf[128]= {0};

    struct tm* ptm = NULL;
    time_t t = time(NULL);
    ptm = localtime(&t);
    strftime(buf,sizeof(buf),"%Y-%m-%d",ptm);
//    cout<<buf<<endl;


    string val_out = "nothing";
//    cout << "before :" << val_out << endl ;
    val_out = string(buf);
    cout << "after :" << val_out  << "<<" << endl ;

    string val_out2 = val_out ; // Today's date
    //val_out2 = Str2Time_BackDate( val_out ) ; // Today's date -> lastday's Date

    return val_out2 ;

}

string Get_Today_date_hour()
{

    char buf[128]= {0};

    struct tm* ptm = NULL;
    time_t t = time(NULL);
    ptm = localtime(&t);
    strftime(buf,sizeof(buf),"%Y-%m-%d %H",ptm);
//    cout<<buf<<endl;


    string val_out = "nothing";
//    cout << "before :" << val_out << endl ;
    val_out = string(buf);
//    cout << "after :" << val_out  << "<<" << endl ;

    string val_out2 = val_out ; // Today's date
    //val_out2 = Str2Time_BackDate( val_out ) ; // Today's date -> lastday's Date

    return val_out2 ;

}

string Get_Today_date_hour_min()
{

    char buf[128]= {0};

    struct tm* ptm = NULL;
    time_t t = time(NULL);
    ptm = localtime(&t);
    strftime(buf,sizeof(buf),"%Y-%m-%d %H:%M",ptm);
//    cout<<buf<<endl;


    string val_out = "nothing";
//    cout << "before :" << val_out << endl ;
    val_out = string(buf);
//    cout << "after :" << val_out  << "<<" << endl ;

    string val_out2 = val_out ; // Today's date
    //val_out2 = Str2Time_BackDate( val_out ) ; // Today's date -> lastday's Date

    return val_out2 ;

}

void check_locus_index()
{
    string date = Get_LastDay_date() ;

    SQL_Update_locus_index(date);

    //usleep(0);
}

void check_locus_index_hour()
{
    string date_hour = Get_Today_date_hour() ;

    SQL_Update_locus_index_hour(date_hour);

    //usleep(0);
}

void check_locus_index_hour_min()
{
    string date_hour = Get_Today_date_hour_min() ;

    SQL_Update_locus_index_hour_min(date_hour);

    //usleep(0);
}

volatile bool Record2SQL = true ;
void Location_Point_display(Tag_record* Tag_record_info,unsigned int coordinate_record_count, Status_record* Tag_Status_record_info, unsigned int status_record_count)
{
    //cout << "point display" << endl;

    if (coordinate_record_count!= 0)
    {
        for (size_t i = 0; i < coordinate_record_count; i++)
        {
            std::string str_temp = Tag_record_info[i].Tag_ID;
            Tag_Map_point[i].Tag_Map_string = str_temp;

            Tag_Map_point[i].point.x = Tag_record_info[i].Tag_info_record[Tag_record_info[i].Info_count - 1].x / Map_Scale;
            Tag_Map_point[i].point.y = Tag_record_info[i].Tag_info_record[Tag_record_info[i].Info_count - 1].y / Map_Scale;
        }
        point_count = coordinate_record_count;


        double temp_scale = (1 / image_scale);


        // Init DB connect START*******
        Connection *con = nullptr;//= connpool.GetConnection();;
        Statement *state = nullptr;
        ResultSet *result = nullptr;
        if ( _SQL_flag )
            SQL_Open_single( con, state, result ) ;
        // Init END*******


        for (size_t i = 0; i < (unsigned)point_count; i++)
        {
            long temp_x = (long)(Tag_Map_point[i].point.x / temp_scale);
            long temp_y = (long)(Tag_Map_point[i].point.y / temp_scale);
            string temp_id = Tag_Map_point[i].Tag_Map_string ;
            string time = Tag_record_info[i].Tag_info_record[Tag_record_info[i].Info_count - 1].System_Time ;

            // cout << time << endl ;

            // Write the Locus into DB START*******
            string temp_date_time = Trans2Standard(time); // Transfer time to standard format.
            if ( Record2SQL && _SQL_flag )
                SQL_AddLocus_combine( state, temp_id, to_string(temp_x), to_string(temp_y), "1",  temp_date_time ) ;
            // write the Locus into DB END*******

//            string temp_date = TransDate(time);
//            string temp_time = TransTime(time);
//            if ( Record2SQL && _SQL_flag )
//                SQL_AddLocus( state, temp_id, to_string(temp_x), to_string(temp_y), "1", temp_date, temp_time ) ;


        }

        // Close connect*******
        if ( _SQL_flag )
            SQL_Close_single( con, state, result );
        // Close END*******

    }



    if (status_record_count!=0)
    {
        // Init DB connect START*******
        Connection *con = nullptr;//= connpool.GetConnection();;
        Statement *state = nullptr;
        ResultSet *result = nullptr;
        if ( _SQL_flag )
            SQL_Open_single( con, state, result ) ;
        // Init DB connect END*******


        for (size_t i = 0; i < status_record_count; i++)
        {
            bool flag = false;
            for (size_t j = 0; j < (unsigned)status_record_count_temp; j++)
            {
                //std::string str_temp = Tag_Status_record_info[i].Tag_ID;
                if ((Tag_Map_Status[j].Tag_ID == Tag_Status_record_info[i].Tag_ID))
                {
                    if (Tag_Status_record_info[i].Status_info_record[Tag_Status_record_info[i].Info_count - 1].Status != No_Status)
                    {
                        if (Tag_Map_Status[j].Status != Tag_Status_record_info[i].Status_info_record[Tag_Status_record_info[i].Info_count - 1].Status)
                        {
                            Tag_Map_Status_temp->Status = Tag_Status_record_info[i].Status_info_record[Tag_Status_record_info[i].Info_count - 1].Status;
                            Tag_Map_Status_temp->System_Time = Tag_Status_record_info[i].Status_info_record[Tag_Status_record_info[i].Info_count - 1].System_Time;
                            Tag_Map_Status_temp->Tag_ID = Tag_Status_record_info[i].Tag_ID;

                            // Write EVENT into Database START*******
                            string temp_time = Tag_Map_Status_temp->System_Time ;
                            string temp_id = Tag_Map_Status_temp->Tag_ID ;
                            string temp_status = to_string(Tag_Map_Status_temp->Status) ;
                            string temp_date_time = Trans2Standard(temp_time);
                            if ( Record2SQL && _SQL_flag )
                                SQL_AddEvent( state, temp_id, temp_status, temp_date_time ) ;
                            // Write EVENT into Database END*******

                            //display_status();
                            Request_Alarm_Status_temp[request_alarm_count].Status = Tag_Map_Status_temp->Status;
                            Request_Alarm_Status_temp[request_alarm_count].System_Time = Tag_Map_Status_temp->System_Time;
                            Request_Alarm_Status_temp[request_alarm_count].Tag_ID = Tag_Map_Status_temp->Tag_ID;
                            request_alarm_count++;
                        }

                    }
                    flag = true;
                    break;
                }
            }
            if ((flag == false)&&(Tag_Status_record_info[i].Status_info_record[Tag_Status_record_info[i].Info_count - 1].Status != No_Status))
            {
                Tag_Map_Status_temp->Status = Tag_Status_record_info[i].Status_info_record[Tag_Status_record_info[i].Info_count - 1].Status;
                Tag_Map_Status_temp->System_Time = Tag_Status_record_info[i].Status_info_record[Tag_Status_record_info[i].Info_count - 1].System_Time;
                Tag_Map_Status_temp->Tag_ID = Tag_Status_record_info[i].Tag_ID;

                // Write EVENT into Database START*******
                string temp_time = Tag_Map_Status_temp->System_Time ;
                string temp_id = Tag_Map_Status_temp->Tag_ID ;
                string temp_status = to_string(Tag_Map_Status_temp->Status) ;
                string temp_date_time = Trans2Standard(temp_time);
                if ( Record2SQL && _SQL_flag )
                    SQL_AddEvent( state, temp_id, temp_status, temp_date_time ) ;
                // Write EVENT into Database END*******


                //display_status();
            }
        }
        for (size_t i = 0; i < status_record_count; i++)
        {
            Tag_Map_Status[i].Tag_ID = Tag_Status_record_info[i].Tag_ID;
            Tag_Map_Status[i].Status = Tag_Status_record_info[i].Status_info_record[Tag_Status_record_info[i].Info_count - 1].Status;
            Tag_Map_Status[i].System_Time = Tag_Status_record_info[i].Status_info_record[Tag_Status_record_info[i].Info_count - 1].System_Time;
        }
        status_record_count_temp = status_record_count;


        // Close connect*******
        if ( _SQL_flag )
            SQL_Close_single( con, state, result );
        // Close END*******
    }



}





typedef void (*lanuch_t)();
void loc_run2();
void *g_handle;
int load_DLL()
{
    void *handle;
    cout << "C++ dlopen" << endl;

    // 打开库文件
    cout << "Opening *.so..." << endl;
    //动态库 libhello.so 的绝对路径
    handle = dlopen(LIB_CACULATE_PATH, RTLD_NOW);

    if (!handle)
    {
        cerr << "Cannot open library: " << endl << dlerror() << endl;
        return 1;
    }

    // 加载符号表
    cout << "Loading symbol caculate..." << endl;
    typedef void (*lanuch_t)();

    // 错误
    dlerror();

//
//    lanuch_t hi = (lanuch_t) dlsym(handle, "_ZN8Location10set_AnchorEP19Main_Anchor_MessagejP14Anchor_Messagej");
//    const char *dlsym_error = dlerror();
//    if (dlsym_error)
//    {
//        cerr << "Cannot load symbol : " << dlsym_error << endl;
//        dlclose(handle);
//        return 1;
//    }

    /*
    cout << "Calling hi()..." << endl;
    hi();

    // 加载符号表
    cout << "Loading symbol add..." << endl;
    typedef int (*add_t)(int, int);

    // 错误
    dlerror();
    add_t add = (add_t) dlsym(handle, "add");
    if (dlsym_error) {
        cerr << "Cannot load symbol 'add': " << dlsym_error << endl;

        dlclose(handle);
        return 1;
    }

    cout << "Calling the add()..."<< endl;
    cout << add(2, 3) << " is the result"<< endl;
    */

    // 关闭库文件
    cout << "Closing library..."<< endl;
//    dlclose(handle);
    return 0 ;

}








//volatile int tep = 0 ;

volatile bool debug_mode = false;
void Pre_Setting_init();
volatile bool server_flag = false;
//const char*  Filename;

void Stop();
void TCP_thread_Safe( SOCKET m_socket )
{
    if ( debug_mode )
        cout << "TCP thread" << endl ;

    int buf_len = 200000 ;

    unsigned char testbuff[buf_len] = { 0 };
    int timeout_count = 0;
    memset(testbuff, 0, sizeof(testbuff));
    int bytesSent;
    int bytesRecv = SOCKET_ERROR;
    int temp = 0, count = 0, timeoutcount = 10000;
    char sendbuf[] = "ACK";

    SOCKET SOCKET_temp = (SOCKET)m_socket;
    int flag = 0;
    SOCKET handler = NULL;

    //int tep = 0 ;

    while ( 1 )
    {
        //cout << "m_socket :" << m_socket << endl ;
        if ( debug_mode )
            cout << "thread_tcp" << endl ;
        memset(testbuff, 0, sizeof(testbuff));

        // Original : if data too large that single recv can't receive, using next while to get ( temp = temp + ByteRecv ).
        // bytesRecv = recv(SOCKET_temp, (char*)testbuff + temp, 0xFFFFFF, flag);

        // Modify : 2019/04/30
        // using do while loop to get total data, by one time in "while( 1 )".
        int content_len = 0 ;
        do
        {
            bytesRecv = recv(SOCKET_temp, (char*)testbuff + temp, 0xFFFFFF, flag);
            if ( strstr((char*)testbuff, "Content-Length:" ) != 0 )
            {
                string str = "" ;
                char* deli_str_ = "Content-Length:" ;
                unsigned char deli_arg_[buf_len] = { 0 };
                std::string str_temp = strstr((char*)testbuff, deli_str_);
//                cout << "str_temp :" << str_temp << endl ;
                int buff_len = strlen(strstr((char*)testbuff,  deli_str_));
//                cout << "buff_len :" << buff_len << endl ;

                int start_loc = strcspn((char*)testbuff, deli_str_);
                int len = buff_len - strlen(strstr((char*)testbuff, "\r\n"));
                //cout << "strlen :" << strlen(strstr((char*)testbuff, "\r\n")) << endl ;
                str = str_temp.substr(strlen(deli_str_)+1, len - strlen(deli_str_));
//                cout << "str :" << str << endl ;


                int w_count = 0 ;
                int w_index = 0 ;
                unsigned char tmp_ret[10] = { 0 };
                unsigned char tmp_buf[10] = { 0 };
                strcpy( (char*)tmp_buf, str.c_str() );

                for ( int i = 0 ; i < sizeof(tmp_buf) ; i++ )
                    if ( tmp_buf[i] == 13 && tmp_buf[i+1] == 10 ) {
                        w_index = i ;
                        tmp_ret[i] = '\0' ;
                        break;
                    }
                    else {
                        // cout << "???>>>" << i << endl ;
                        tmp_ret[i] = tmp_buf[i] ;
                    }

                int int_index = atoi( (char*)tmp_ret) ;
                // cout << int_index << endl ;
                content_len = int_index ;


            }
            temp = temp + bytesRecv;
            // cout << "temp :" << temp << endl ;

        }
        while ( temp < content_len ) ;
        // END : using do while loop to get total data, by one time in "while( 1 )".



        // cout << "temp :" << temp << endl ;
        /*
                if ( tep == 0 )
                    tep = m_socket ;
                else if ( tep == m_socket )
                    cout << bytesRecv << endl ;
                //cout << "Recv:" << bytesRecv << endl ;
                */
        cout << "byteRecv :" << bytesRecv << endl ;
        if (bytesRecv == -1)
            break;
        else
            temp = temp + bytesRecv;
        if (strstr((char*)testbuff, "KEEP CONNECTED") != 0)
        {
            timeout_count = 0;
            temp = 0;
        }
        else if ( temp > 0 )
        {

            char binch[200000] = { 0 };
            int u = 0;
            int n_h = 0, n_l = 0, n = 0;
            long s = 0;
            std::fstream file;
            char ch;
            const char* html_temp;
            const char* binch2;


            Filename = "/var/www/html/Location System/html/index.html";
            std::string html_head = "/var/www/html/Location System/html/";
            std::string html_root = "/var/www/html/Location System/";
            std::string html_str;

            if ( debug_mode )
                cout <<testbuff<< endl  ;

            unsigned char delibuff[buf_len] = { 0 };
            memset(delibuff, 0, sizeof(delibuff));
            unsigned char deli_arg[buf_len] = { 0 };
            memset(deli_arg, 0, sizeof(deli_arg));

//            cout << "Original :" << endl <<testbuff << ""<< endl ;
            /*
            for ( int i = 0 ; i < strlen((char*)testbuff) ; i++ )
                printf( "%d ", testbuff[i] ) ;
            //*/
            // notice the end of char array set by 0 ~~~


            // get the last line ( parameter )
            int ter_ind = 0 ;
            int wrap_count = 0 ;
            int wrap_index = 0 ;
            for ( int i = 0 ; i < sizeof(testbuff) - 1 ; i++ )
                if ( testbuff[i] == '\r' && testbuff[i+1] == '\n' ) // 0x0D , 0x0A!!
                {
                    wrap_count++ ;
                    wrap_index = i ; // last 0d0a index
                    if ( wrap_count == 1 ) // get first line to
                        strncpy( (char*)delibuff, (char*)testbuff, i+1 );

                }

            /*
            cout << "strlen :" <<strlen((char*)testbuff) << endl ;
            cout << "CRLF counting :" << wrap_count << endl ;
            cout << "last crlf :" << wrap_index << endl ;
            //*/

            strncpy( (char*)deli_arg, (char*)testbuff+wrap_index+2, strlen((char*)testbuff) -  (wrap_index+2) );
            /*
            cout << ">>" << deli_arg << "<<" <<endl;
            cout <<"deli len :"<< strlen((char*)deli_arg) << endl;
            //*/
            /*
            for ( int i = 0 ; i < strlen((char*)deli_arg) ; i++ )
                printf( "%hu", deli_arg[i] );
            cout << "<<"<< endl ;
            //*/




            for ( int i = 0 ; i < buf_len ; i++ )
                testbuff[i] = delibuff[i] ;

            if (strstr((char*)testbuff, "GET / HTTP/1.1") != 0 || strstr((char*)testbuff, "GET /dashboard/ HTTP/1.1") != 0)
            {
                cout << "index" << endl ;
                html_str = html_head + "index.html";
                html_temp = html_str.c_str();
                //html_temp = Filename;
                //ifstream fin("C:\\Users\\john.zhang\\Documents\\§Úªººô¯ž\\CTL.html", ios::in);
                std::ifstream fin(html_temp, std::ios::in);
                //ifstream fin(html_temp, ios::in | ios::binary);
                //Filename
                while (fin.get(ch))
                {
                    //fin.get(ch); // wrong method!!
                    binch[u] = ch;
                    u++;
                }
                fin.close();
                //binch[u] = '\r';
                //binch[u++] = '\n';
                //file.close();
                //int temp_len = strlen(binch);
                bytesSent = send(SOCKET_temp, (const char*)binch, u, 0);

            }


            else if (strstr((char*)testbuff, "POST /request2 HTTP/1.1") != 0 || strstr((char*)testbuff, "POST /dashboard/request2 HTTP/1.1") != 0)
            {

                if (point_count != 0)
                {
                    std::string tags_id, tags_name, response_text;
                    //String^ Tag_ID = gcnew String(Tag_Map_Status[i].Tag_ID.c_str());
                    //unsigned __int64 ID_int = Convert::ToUInt64(Tag_ID, 16);
                    for (size_t i = 0; i < point_count - 1; i++)
                    {
                        tags_id += "\"" + Tag_Map_point[i].Tag_Map_string + "\",";
                        tags_name += "\" \",";
                    }
                    tags_id += "\"" + Tag_Map_point[point_count - 1].Tag_Map_string + "\"";
                    tags_name += "\" \"";
                    response_text = "{\"name\":[" + tags_name + "],\"tag_list\":[" + tags_id + "]}";
                    binch2 = response_text.c_str();
                    //binch2 = "{\"items\":[\"1\",\"2\",\"3\"],\"display_id\":["true","true","true"],\"name\":[\"A\",\"B\",\"C\"],\"tag_list\":[\"7\",\"8\",\"9\"]}";
                    bytesSent = send(SOCKET_temp, (const char*)binch2, strlen(binch2), 0);
                }
            }


            else if (strstr((char*)testbuff, "POST /requestTagList HTTP/1.1") != 0 || strstr((char*)testbuff, "POST /dashboard/requestTagList HTTP/1.1") != 0)
            {

                if (point_count != 0)
                {
                    std::string tags_id, tags_x, tags_y, tags_systemTime, response_text;
                    for (size_t i = 0; i < point_count-1; i++)
                    {
                        tags_id += "\"" + Tag_Map_point[i].Tag_Map_string + "\",";
                        tags_x += to_string(Tag_Map_point[i].point.x) + ",";
                        tags_y += to_string(Tag_Map_point[i].point.y) + ",";
                        tags_systemTime += "\"2019-01-27 00:00:00:00\",";
                    }
                    tags_id += "\"" + Tag_Map_point[point_count - 1].Tag_Map_string + "\"";
                    tags_x += to_string(Tag_Map_point[point_count - 1].point.x);
                    tags_y += to_string(Tag_Map_point[point_count - 1].point.y);
                    tags_systemTime += "\"2019-01-28 00:00:00:00\"";
                    response_text = "{\"tag_list\":[" + tags_id + "], \"x\":[" + tags_x + "], \"y\":[" + tags_y + "], \"system_time\":[" + tags_systemTime + "]}";
                    binch2 = response_text.c_str();
                    //char binch2[] = "{\"x\":[100,200,300],\"y\":[100,200,300],\"color\":[\"#F30\",\"#09F\",\"#6C0\"]}";
                    bytesSent = send(SOCKET_temp, (const char*)binch2, strlen(binch2), 0);
                }
            }


            else if (strstr((char*)testbuff, "POST /requestImage HTTP/1.1") != 0 || strstr((char*)testbuff, "POST /dashboard/requestImage HTTP/1.1") != 0)
            {
                string response_html = html_root + "/image/map4 - 1_3.png";

                html_temp = response_html.c_str() ;
                //html_temp = Filename;
                std::ifstream fin(html_temp, std::ios::in | std::ios::binary);
                //Filename
                while (!fin.eof())
                {
                    fin.get(ch);
                    binch[u] = ch;
                    u++;
                }
                fin.close();
                //int temp_len = strlen(binch);
                bytesSent = send(SOCKET_temp, (const char*)binch, u, 0);
                //bytesSent = send(SOCKET_temp, (const char*)binch2, strlen(binch2), 0);
            }


            else if (strstr((char*)testbuff, "POST /requestMainAnchorPosition HTTP/1.1") != 0 || strstr((char*)testbuff, "POST /dashboard/requestMainAnchorPosition HTTP/1.1") != 0)
            {
                if (Main_Anchor_List_count != 0)
                {
                    std::string main_anchors_id, main_anchors_x, main_anchors_y, response_text;
                    for (size_t i = 0; i < Main_Anchor_List_count; i++)
                    {
                        main_anchors_id += to_string(Init_Group_Main_Anchor_List[i].id) + ",";
                        main_anchors_x += to_string(Init_Group_Main_Anchor_List[i].x) + ",";
                        main_anchors_y += to_string(Init_Group_Main_Anchor_List[i].y) + ",";
                        cout << Init_Group_Main_Anchor_List[i].id << "," << Init_Group_Main_Anchor_List[i].x << "," << Init_Group_Main_Anchor_List[i].y << endl ;
                    }
                    main_anchors_id += to_string(Init_Group_Main_Anchor_List[Main_Anchor_List_count - 1].id);
                    main_anchors_x += to_string(Init_Group_Main_Anchor_List[Main_Anchor_List_count - 1].x);
                    main_anchors_y += to_string(Init_Group_Main_Anchor_List[Main_Anchor_List_count - 1].y);
                    response_text = "{\"main_id\":[" + main_anchors_id + "], \"main_x\":[" + main_anchors_x + "], \"main_y\":[" + main_anchors_y + "]}";
                    binch2 = response_text.c_str();
                    //char binch2[] = "{\"id\":[111,112,113],\"x\":[100,120,560],\"y\":[555,322,210]}";
                    bytesSent = send(SOCKET_temp, (const char*)binch2, strlen(binch2), 0);
                }
            }


            else if (strstr((char*)testbuff, "POST /requestAnchorPosition HTTP/1.1") != 0 || strstr((char*)testbuff, "POST /dashboard/requestAnchorPosition HTTP/1.1") != 0)
            {
                if (Anchor_List_count != 0)
                {
                    std::string anchors_id, anchors_x, anchors_y, response_text;
                    for (size_t i = 0; i < Anchor_List_count - 1; i++)
                    {
                        anchors_id += to_string(Init_Group_Anchor_List[i].id) + ",";
                        anchors_x += to_string(Init_Group_Anchor_List[i].x) + ",";
                        anchors_y += to_string(Init_Group_Anchor_List[i].y) + ",";
                    }
                    anchors_id += to_string(Init_Group_Anchor_List[Anchor_List_count - 1].id);
                    anchors_x += to_string(Init_Group_Anchor_List[Anchor_List_count - 1].x);
                    anchors_y += to_string(Init_Group_Anchor_List[Anchor_List_count - 1].y);
                    response_text = "{\"id\":[" + anchors_id + "], \"x\":[" + anchors_x + "], \"y\":[" + anchors_y + "]}";
                    binch2 = response_text.c_str();
                    //char binch2[] = "{\"main_id\":[123,124,125],\"main_x\":[500,200,300],\"main_y\":[100,300,200]}";
                    bytesSent = send(SOCKET_temp, (const char*)binch2, strlen(binch2), 0);
                }
            }




            /***********

            get html page

            //*********/
            else if (strstr((char*)testbuff, "html") != 0 || strstr((char*)testbuff, "GET /dashboard/html/") != 0)
            {

                std::string str, response_html;
                char* deli_str = "/" ;
                std::string str_temp = strstr((char*)testbuff, deli_str);
                int buff_len = strlen(strstr((char*)testbuff,  deli_str));
                int len = buff_len - strlen(strstr((char*)testbuff, " HTTP/1.1"));

                str = str_temp.substr(strlen(deli_str), len - strlen(deli_str));
                response_html = html_root + "html/" + str;
                html_temp = response_html.c_str();//StringToChar(html_str);

                if ( debug_mode )
                    cout << "html :" << html_temp << endl ;

                std::ifstream fin(html_temp, std::ios::in);
                while (fin.get(ch))
                {
                    //fin.get(ch); // wrong method!!
                    binch[u] = ch;
                    u++;
                }
                fin.close();
                bytesSent = send(SOCKET_temp, (const char*)binch, u, 0);

            }


            /***********

            get properties page

            2019/04/18:
            /properties/i18n/zh-CN/common.properties?_=1555579054345 HTTP/1.1

            //*********/
            else if (strstr((char*)testbuff, "properties/i18n") != 0 )
            {

                std::string str, response_html;
                char* deli_str = "/" ;
                std::string str_temp = strstr((char*)testbuff, deli_str);
//                cout << str_temp << endl ;
                int buff_len = strlen(strstr((char*)testbuff,  deli_str));
//                cout << buff_len << endl ;
                int len = buff_len - strlen(strstr((char*)testbuff, "properties?"));
//                cout << len << endl ;

                str = str_temp.substr(strlen(deli_str), len - strlen(deli_str));
//                cout << str << endl ;
                response_html = html_root + "/" + str + "properties" ;
                html_temp = response_html.c_str();//StringToChar(html_str);

                if ( debug_mode )
                    cout << "properties :" << html_temp << endl ;

                std::ifstream fin(html_temp, std::ios::in);
                while (fin.get(ch))
                {
                    //fin.get(ch); // wrong method!!
                    binch[u] = ch;
                    u++;
                }
                fin.close();
                bytesSent = send(SOCKET_temp, (const char*)binch, u, 0);

            }


            /************************************************************
            Function condition

            Request function status:

            date        2019/04/16
            /Command    : Work, command for "device" ,but deprecated.
            /updateFW   : Work, testing.
            /test       : Work, useless ,just practice to send.
            /test2      : Work, do the same thing like /Command, but using the method "Callback" to call function.
            /sql        : Work, any action about database, still adding the new SQL command.



            //************************************************************/

            else if (strstr((char*)testbuff, "POST /Command HTTP/1.1") != 0 )
            {
                //{"Command_Type":["Read"],"Command_Name":["Connect"],"Value":{"IP_address":["192.168.1.38","192.168.1.90"]}}
                //{"Command_Type":["Read"],"Command_Name":["RF"],"Value":{"IP_address":["192.168.1.38"]}, "call_func :["ip","gw","msk","cip"]}
                //{"Command_Type":["Read"],"Command_Name":["Search"],"Value":{"net_interface_id":["enp0s31f6"],"ip":["192.168.1.139"]}}
                //{"Command_Type":["Write"],"Command_Name":["Basic"],"Value":{"IP_address":["192.168.1.38","192.168.1.90"],"dev_active_ID": "65513","dev_transmission_cycle_time":""}}
                //{"Command_Type":["Read"],"Command_Name":["Basic"],"Value":{"IP_address":["192.168.1.38","192.168.1.90"]}}
                //{"Command_Type":["Write"],"Command_Name":["RF"],"Value":{"rf_MODE": "Anchor", "rf_NSD": "1", "rf_NTM_value": "0", "rf_PAC": "8", "rf_PGdelay": "CH3", "rf_PMULT_value": "0", "rf_Power": "1869573999", "rf_SFD_timeout": "137","rf_SMARTPOWER": "0","rf_channel": "CH3 (4.5GHz)","rf_datarate": "6.8Mbps","rf_preambleCode": "6","rf_preambleLength": "128","rf_prf": "16M","Connected_IP":["192","168","1","37"]}}
                //{"Command_Type":["Read"],"Command_Name":["Search_net"]}
                // implement


                string target = "" ;
                string action = "" ;
                string command_name = "" ;
                json j_response;
                try
                {
                    stringstream json_part ;
                    json_part << deli_arg ; // char* to stringstream
                    cout << "stream:"<< json_part.str() << endl ; // stringstream to string
                    auto arg_from_web = json::parse(json_part.str()); // string to json parser
                    cout << "get_arg from web :" << arg_from_web << endl ;

                    action = arg_from_web["Command_Type"][0].get<std::string>() ;
                    command_name = arg_from_web["Command_Name"][0].get<std::string>() ;



                    if ( command_name == "Search" )
                    {

                        str_inferface_ip = "" ;
                        str_inferface_ip = arg_from_web["Value"]["net_interface_id"][0].get<std::string>();

                        dev_count = 0 ;
                        if ( str_inferface_ip != "" )
                            dev_count = Update_search_dev( str_inferface_ip ) ;
                        if (dev_count != 0)
                        {
                            j_response = g_json_multi ;
                            g_json_multi.clear() ;
                        }



                    }

                    else if ( command_name == "RF" )
                    {
                        /* ip separate to 4 parts
                        for ( int i = 0 ; i < 4 ; i++)
                        {
                            target += arg_from_web["Value"]["IP_address"][i].get<std::string>() ;
                            if ( i < 3 )
                                target += ".";
                        }
                        //*/
                        target = arg_from_web["Value"]["IP_address"][0].get<std::string>() ;

                        target_ip = (char*)target.c_str() ;
                        cout << "target IP :"<<target_ip <<endl ;
                        cout << "action :" << action << endl ;

                        if ( action == "Read" )
                            Read_RF_setting();
                        if ( action == "Write" )
                        {
                            g_json_single = arg_from_web["Value"] ;
                            cout << g_json_single.dump(2) << endl ;
                            Write_RF_setting();
                            g_json_single["Command_status"] = Command_success ;

                        }

                        j_response.push_back(g_json_single);
                        g_json_single.clear() ;

                    }

                    else if ( command_name == "Network" || command_name == "Basic" )
                    {
                        int dev_amount = arg_from_web["Value"]["IP_address"].size() ;
                        for ( int i = 0 ; i < dev_amount ; i++)
                        {
                            target = arg_from_web["Value"]["IP_address"][i].get<std::string>() ;
                            target_ip = (char*)target.c_str() ;
                            cout << target_ip << endl ;

                            if ( action == "Read" )
                            {
                                if (command_name == "Network")
                                    Read_Network_setting();
                                else if (command_name == "Basic")
                                    Read_Basic_setting();
                            }
                            else if ( action == "Write" )
                            {
                                g_json_single = arg_from_web["Value"] ;
                                cout << g_json_single.dump(2) << endl ;
                                if (command_name == "Network")
                                {
                                    Write_Network_setting();
                                }
                                else if (command_name == "Basic")
                                    Write_Basic_setting();

                                g_json_single["Command_status"] = Command_success ;

                            }

                            g_json_multi.push_back(g_json_single);
                            g_json_single.clear();

                        }
                        j_response = g_json_multi ;
                        g_json_multi.clear();

                    }



                    else if ( command_name == "Connect")
                    {
                        int dev_amount = arg_from_web["Value"]["IP_address"].size() ;
                        for ( int i = 0 ; i < dev_amount ; i++)
                        {
                            target = arg_from_web["Value"]["IP_address"][i].get<std::string>() ;
                            target_ip = (char*)target.c_str() ;
                            cout << target_ip << endl ;

                            //Read_Network_setting();
                            g_json_single["dev_ip"] = target_ip ;
                            Read_Basic_setting();
                            //g_json_single.erase("dev_transmission_cycle_time");

                            g_json_multi.push_back(g_json_single);

                            g_json_single.clear();
                        }
                        j_response = g_json_multi ;
                        g_json_multi.clear();
                    }


                    else if ( command_name == "Search_net" )
                    {
                        Update_net_interface() ;
                        for (size_t i = 0; i < net_len ; i++)
                        {
                            g_json_single["net_interface_id"] = std::string(Info[i].Network_Interface_ID) ;
                            g_json_single["ip"] = std::string(Info[i].IP_address) ;

                            j_response.push_back(g_json_single) ;
                            g_json_single.clear() ;
                        }

                    }




                }
                catch(json::parse_error)
                {
                    cout << "parse_error" << endl ;
                }
                catch(json::type_error)
                {
                    cout << "type_error" << endl ;
                }
                catch( exception &e )
                {
                    cout << "other error" << endl ;
                }

                std::string response_text = j_response.dump();
                binch2 = response_text.c_str();
                bytesSent = send(SOCKET_temp, (const char*)binch2, strlen(binch2), 0);

            }



            else if (strstr((char*)testbuff, "POST /Update_fw HTTP/1.1") != 0 )
            {
                Update_FW();
                std::string ret_val = "" ;
                if ( Command_success )  // update successfully.
                    ret_val = "1" ;
                else                    // update failed.
                    ret_val = "0" ;

                std::string json_value = "\"" ;
                json_value  += ret_val + "\"" ;


                std::string response_text;
                response_text = "{\"Update result\":[" + json_value + "]}";
                binch2 = response_text.c_str();
                //char binch2[] = "{\"main_id\":[123,124,125],\"main_x\":[500,200,300],\"main_y\":[100,300,200]}";
                bytesSent = send(SOCKET_temp, (const char*)binch2, strlen(binch2), 0);


            }

            else if (strstr((char*)testbuff, "POST /test HTTP/1.1") != 0 || strstr((char*)testbuff, "POST /dashboard/test HTTP/1.1") != 0)
            {

                std::string response_text;
                //cout << "request :"<<testbuff << endl ;

                //response_text = "{\"Update result\":[" + json_value + "]}";
                //response_text = "[\"str\",123]";

                response_text = "{\"dev_IP\":[\"192\",\"168\",\"1\",\"65\"], \"dev_Mask\":[\"255\",\"255\",\"255\",\"0\"]}" ;
                //response_text = "{\"rf_channel\":[" + rf_active_ID + "], \"rf_NTM_value\":[" + rf_NTM_value + "], \"rf_PMULT_value\":[" + rf_PMULT_value + "]}";

                binch2 = response_text.c_str();
                //char binch2[] = "{\"main_id\":[123,124,125],\"main_x\":[500,200,300],\"main_y\":[100,300,200]}";
                bytesSent = send(SOCKET_temp, (const char*)binch2, strlen(binch2), 0);


            }

            else if (strstr((char*)testbuff, "POST /test2 HTTP/1.1") != 0 )
            {

                string target = "" ;
                string action = "" ;
                string command_name = "" ;
                int dev_amount = 0, function_amount = 0, rw_flag = 0 ;
                json j_response;
                try
                {
                    stringstream json_part ;
                    json_part << deli_arg ; // char* to stringstream
                    cout << "stream:"<< json_part.str() << endl ; // stringstream to string
                    auto arg_from_web = json::parse(json_part.str()); // string to json parser
                    cout << "get_arg from web :" << arg_from_web << endl ;

                    action = arg_from_web["Command_Type"][0].get<std::string>() ;
                    command_name = arg_from_web["Command_Name"][0].get<std::string>() ;


                    if ( action == "Write" )
                        rw_flag = 2;
                    else
                        rw_flag = 1 ;


                    cout << "command_name:"<< command_name << endl ;


                    if ( command_name == "Search" )
                    {
                        str_inferface_ip = "" ;
                        str_inferface_ip = arg_from_web["Value"]["net_interface_id"][0].get<std::string>();

                        dev_count = 0 ;
                        if ( str_inferface_ip != "" )
                            dev_count = Update_search_dev( str_inferface_ip ) ;
                        if (dev_count != 0)
                        {
                            j_response = g_json_multi ;
                            g_json_multi.clear() ;
                        }

                    }

                    else if ( command_name == "Launch" )
                    {
                        if ( arg_from_web["Value"].get<std::string>() == "Start" )
                        {
                            cout << ">>>>>>>>>>>>>>>>>>>>>>>>GET Launch"<< endl ;
                            if ( !isPreSet )
                                Pre_Setting_init();
                            openserver_flag = true ;

                            j_response["Status"] = "Start" ;
                        }
                        else if ( arg_from_web["Value"].get<std::string>() == "Stop" )
                        {
                            cout << ">>>>>>>>>>>>>>>>>>>>>>>>GET Stop"<< endl ;
                            Stop();
                            j_response["Status"] = "Stop" ;
                        }
                    }

                    else
                    {
                        function_amount = arg_from_web["Value"]["function"].size() ;
                        dev_amount = arg_from_web["Value"]["IP_address"].size() ;

                        if ( function_amount != 0 )
                        {

                            for ( int j = 0 ; j < dev_amount ; j++ )
                            {
                                target = arg_from_web["Value"]["IP_address"][j].get<std::string>() ;
                                target_ip = (char*)target.c_str() ;
                                cout << endl << target_ip << endl ;


                                if ( rw_flag == 2 )   // write
                                {
                                    g_json_single = arg_from_web["Value"] ;
                                    // get package data for json
                                    g_RW_json_package[action+"_"+command_name]();
//                                            g_function_7_arg_map[launch_cmd].RW_arg( rw_flag, set_Reader_value, Reader_value ) ; // set wrote value
                                }


                                for ( int i = 0 ; i < function_amount ; i++ )
                                {
                                    string launch_cmd = arg_from_web["Value"]["function"][i].get<std::string>();
                                    Command_success = 0 ;


                                    int Value_flag = 0;
                                    unsigned char Reader_value[2048] = { 0 };
                                    unsigned char set_Reader_value[2048] = { 0 };
                                    memset(Reader_value, 0, sizeof(Reader_value));


                                    // found the command in g_function_7_arg_map ;
                                    if ( g_function_7_arg_map.count(launch_cmd) != 0 )
                                    {
                                        cout << "func 7" << endl ;

                                        if ( rw_flag == 2 )   // write
                                        {
                                            cout << rw_flag << endl ;
//                                            g_json_single = arg_from_web["Value"] ;
//                                            // get package data for json
//                                            g_RW_json_package[action+"_"+command_name]();
                                            g_function_7_arg_map[launch_cmd].RW_arg( rw_flag, set_Reader_value, Reader_value ) ; // set wrote value
                                        }

                                        int set_length = g_function_7_arg_map[launch_cmd].set_length;
                                        g_function_7_arg_map[launch_cmd].callback(target_ip, TCP_Server_Port, (rw_flag - 1), set_Reader_value, set_length, Reader_value, Value_flag);

                                        if (Value_flag != 1) // sent command failed!
                                        {
                                            cout << "error from:" << launch_cmd << endl ;
                                            goto return_error;
                                        }
                                        else if ( Value_flag && rw_flag == 1 )
                                        {
                                            g_function_7_arg_map[launch_cmd].RW_arg( rw_flag, Reader_value, Reader_value) ; // read returned value
//                                            // set package data for json
//                                            g_RW_json_package[action+"_"+command_name]();
                                        }

                                        usleep(2000);

                                    }

//                                    if (client_ip_flag)
//                                    {
//                                        Value_flag = 0;
//                                        memset(Reader_value, 0, sizeof(Reader_value));
//                                        if (client_ip_flag == 2)
//                                        {
//                                            for (size_t i = 0; i < 4; i++)
//                                                set_Reader_value[i] = CLIENT_IP_temp[i];
//                                        }
//                                        if (Interface_name == UWB_Interface1)
//                                            rfid::TCP::RW_ClientIP(target_ip, TCP_Server_Port, (client_ip_flag - 1), set_Reader_value, 4, Reader_value, Value_flag);
//                                        client_ip_flag = 0;
//                                        if (Value_flag != 1)
//                                            goto return_error;
//                                        if (read_network_flag != 0)
//                                        {
//                                            for (size_t i = 0; i < 4; i++)
//                                                CLIENT_IP_temp[i] = Reader_value[i];
//                                        }
//                                        sleep(20);
//                                        usleep(2000);
//                                    }
//


                                    // found the command in g_function_52_arg_map ;
                                    else if ( g_function_52_arg_map.count(launch_cmd) != 0 ) // update FW
                                    {
                                        cout << "func 52" << endl ;

                                        string fw_path = "/home/szok/桌面/韌體/ANCHOR 韌體/001.001.bin" ;

                                        g_function_52_arg_map[launch_cmd].RW_arg( target_ip, fw_path, Value_flag );

                                        if (Value_flag != 1) // sent command failed!
                                        {
                                            cout << "update failed" << endl ;
                                            goto return_error;
                                        }

                                        cout << "update success" << endl ;
                                        goto return_ok;


                                        usleep(2000);
                                    }



                                    // found the command in g_function_4_arg_map ;
                                    else if ( g_function_4_arg_map.count(launch_cmd) != 0 )
                                    {
                                        cout << "func 4" << endl ;

                                        if ( rw_flag == 2 )   // write
                                            g_function_4_arg_map[launch_cmd].RW_arg( rw_flag, set_Reader_value, Reader_value ) ; // set wrote value


                                        g_function_4_arg_map[launch_cmd].callback(target_ip, TCP_Server_Port, Reader_value, Value_flag);

                                        if (Value_flag != 1) // sent command failed!
                                        {
                                            cout << "error from:" << launch_cmd << endl ;
                                            goto return_error;
                                        }
                                        else if ( Value_flag && rw_flag == 1 )
                                            g_function_4_arg_map[launch_cmd].RW_arg( rw_flag, Reader_value, Reader_value) ; // read returned value

                                        usleep(2000);
                                    }


                                    else
                                    {
                                        cout << "Not found cmd :" <<  launch_cmd << endl ;
                                        goto return_error;
                                    }



                                } // send to one device all cmd successfully

                                if ( rw_flag == 1 )
                                {
                                    // set package data for json
                                    g_RW_json_package[action+"_"+command_name]();
                                }
                                goto return_ok;

return_error:
                                {
                                    Command_success = 0 ;
                                    g_json_single["Command_status"] = Command_success ;
                                    g_json_single["error at"] = target_ip ;
                                    cout << "return error" << endl ;
                                    cout << "return from :" << target_ip << endl ;
                                    g_json_single.clear() ;
                                    break;

                                }


return_ok:
                                {
                                    Command_success = 1 ;
                                    cout << "return ok" << endl ;

                                }



                                // one device ran out all command

                                //cout << "after goto" << endl ;
                                g_json_single["Command_status"] = Command_success ;
                                g_json_multi.push_back(g_json_single);
                                g_json_single.clear() ;


                            }

                            cout << "sent to all device"<< endl ;
                            //cout << g_json_multi.dump(2) << endl ;


                            j_response = g_json_multi ;
                            //j_response.push_back(g_json_multi);
                            g_json_multi.clear() ;


                        }
                    }




                }
                catch(json::parse_error)
                {
                    cout << "parse_error" << endl ;
                }
                catch(json::type_error)
                {
                    cout << "type_error" << endl ;
                }
                catch( exception &e )
                {
                    cout << "other error" << endl ;
                }

                std::string response_text = j_response.dump();
                binch2 = response_text.c_str();
                bytesSent = send(SOCKET_temp, (const char*)binch2, strlen(binch2), 0);


            }

//            "Command_Type": ["Read"],
//            "Command_Name": ["RF"],
//            "Value": {
//                "IP_address": [connect_ip_array[ip_arr_len - 1]],
//                "function": ["Model_Name", "Version_Name", "rf_MODE", "rf_active_ID", "rf_channel",
//                    "rf_Datarate", "rf_PRF", "rf_PreambleCode", "rf_PreambleLength", "rf_PAC",
//                    "rf_TX_PGdelay", "rf_TX_Power", "rf_NSD", "rf_SDF_timeoutr", "rf_SMARTPOWER",
//                    "rf_NTM", "rf_MULT"
//

            else if (strstr((char*)testbuff, "POST /sql HTTP/1.1") != 0 )
            {

                string target = "" ;
                string action = "" ;
                string command_name = "" ;
                int dev_amount = 0, function_amount = 0, rw_flag = 0 ;
                json j_response;
                try
                {
                    stringstream json_part ;
                    json_part << deli_arg ; // char* to stringstream
//                    cout << testbuff << endl ;
//                    cout << "stream:"<< json_part.str() << endl ; // stringstream to string
//                    cout << ":::::" <<endl ;
                    auto arg_from_web = json::parse(json_part.str()); // string to json parser
//                    cout << "????" << endl ;
//                    cout << "get_arg from web :" << arg_from_web << endl ;

                    //action = arg_from_web["Command_Type"][0].get<std::string>() ;
                    //command_name = arg_from_web["Command_Name"][0].get<std::string>() ;
                    //function_amount = arg_from_web["Value"]["function"].size() ;
                    //dev_amount = arg_from_web["Value"]["IP_address"].size() ;
                    function_amount = arg_from_web["Command_Name"].size() ; // get the amount of action.

                    if ( action == "Write" )
                        rw_flag = 2;
                    else
                        rw_flag = 1 ;


//                    SQL_Open();
//                    vector<vector<string>> foo = SQL_GetAnchors_info();
//                    SQL_Close();
//                    for (int i = 0 ; i < foo.size() ; i++ )
//                    {
//                        for ( int j = 0 ; j < foo[i].size() ; j++ )
//                            cout << foo[i][j] << " " ;
//                        cout << endl ;
//                    }


//                    SQL_Open();
//                    j_response = json_SQL_GetAnchors_info();

                    json j_arg = arg_from_web["Value"] ; // get the parameters for database.


                    for ( int i = 0 ; i < function_amount ; i++ )
                    {
                        command_name = arg_from_web["Command_Name"][i].get<std::string>() ;
                        if ( _SQL_flag )
                        {
                            j_response = Call_SQL_func( command_name, j_arg );
                        }
//                    SQL_Close();
                    }



                }
                catch(json::parse_error)
                {
                    cout << "parse_error_sql" << endl ;

                }
                catch(json::type_error)
                {
                    cout << "type_error" << endl ;

                }
                catch( exception &e )
                {
                    cout << "other error" << endl ;
                    std::cout << e.what() << std::endl;
                }

                std::string response_text = j_response.dump();
                j_response.clear();
                binch2 = response_text.c_str();
                bytesSent = send(SOCKET_temp, (const char*)binch2, strlen(binch2), 0);


            }




            /***********
            dir:

            Part of get the web resource request and return resource file.
            like :
            /js/*.* & /css/*.* & /image/*.*

            /**********/
            else if (strstr((char*)testbuff, "/" ) != 0 )
            {
                // get text between two slash
                // ex. GET /js/xxxx.js
                int slash_index = 0, slash_cnt = 0 ;
                int slash_index2 = 0 ;
                for ( int i = 0 ; i < strlen((char*)delibuff) ; i++ )
                    if ( delibuff[i] == '/' )
                    {
                        slash_cnt++ ;
                        if ( slash_cnt == 1)
                            slash_index = i ;
                        else if ( slash_cnt == 2 )
                            slash_index2 = i ;
                    }

                unsigned char folder[20] = { 0 };
                memset(folder, 0, sizeof(folder));
                strncpy( (char*)folder, (char*)delibuff+slash_index+1, slash_index2 - slash_index -1 );
                //cout << "folder:" << folder << endl ;
                stringstream stream;
                stream << folder ;
                //cout << "stream:"<< stream.str() << endl ;
                //************** not yet to use**************



                std::string str, response_html;
                char* deli_str = "/" ;
                std::string str_temp = strstr((char*)testbuff, deli_str);

                int buff_len = strlen(strstr((char*)testbuff,  deli_str));
                int len = buff_len - strlen(strstr((char*)testbuff, " HTTP/1.1"));

                str = str_temp.substr(strlen(deli_str), len - strlen(deli_str));
                response_html = html_root + str;
                html_temp = response_html.c_str();//StringToChar(html_str);

                if (debug_mode)
                    cout << "html :" << html_temp << endl ;

                std::ifstream fin(html_temp, std::ios::in);
                while (fin.get(ch))
                {
                    //fin.get(ch); // wrong method!!
                    binch[u] = ch;
                    u++;
                }
                fin.close();
                bytesSent = send(SOCKET_temp, (const char*)binch, u, 0);



            }






















            // force to terminate while loop in each time, not to reuse m_socket.
            break;



            temp = 0 ;
        }
    }

//    bytesSent = send(SOCKET_temp, (const char*)testbuff, 42903, 0);
//    usleep(100000);
    close( SOCKET_temp );// << endl ;



}


void Pre_Setting_init()
{
    if ( _SQL_flag )
    {
        cout << "SQL_FLAG" << endl ;
        SQL_Anchors_init();
        SQL_Group_init();
    }
    else
    {
        init_anchor_list();
        Init_Group_List();
    }
    isPreSet = true ;
}


//void loc_run()
//{
//
//    Pre_Setting_init();
//
//    int ret = load_DLL() ;
//    cout << "result :" << ret << endl;
//
//    //lanuch_t run = (lanuch_t) dlsym(handle, "Location_Set_Anchor");
//    Init_Anchor = (Location_Set_Anchor_fun) dlsym(handle, Location_Set_Anchor );
//    if (Init_Anchor)
//    {
//        Init_Anchor(Init_Group_Main_Anchor_List, Init_Group_Main_Anchor_List_count, Init_Group_Anchor_List, Init_Group_Anchor_List_count);
////        str.Printf( wxT("init_anchor_successfully") );
////        this->StatusBar1->SetStatusText( str,1 );
//        cout << "init_anchor_success" << endl ;
////        usleep(1000000);
//    }
//
//
//    //Location_Init = (Location_Init_fun)GetProcAddress(CallLibrary, "Location_Init");
//    Location_Init = (Location_Init_fun) dlsym(handle, Location_init);
//    if (Location_Init)
//    {
//        bool bResault = Location_Init();
//        if (bResault)
//        {
////            str.Printf( wxT("location_init") );
////            this->StatusBar1->SetStatusText( str,1 );
//            cout << "location_init" << endl ;
//
//            //Load_Location_coordinate = (Load_Location_Coordinate)GetProcAddress(CallLibrary, "Load_Location_coordinate_record");
//            //Load_Location_status = (Load_Location_Status)GetProcAddress(CallLibrary, "Load_Location_status_record");
//            Load_Location_coordinate = (Load_Location_Coordinate) dlsym(handle, Load_Location_coordinate_record);
//            Load_Location_status = (Load_Location_Status) dlsym(handle, Load_Location_status_record );
//            //Sleep(1000);
////            thread server_thread( Lanuch_Server ) ;
////            server_thread.detach();
//
//            //*
//            while (openserver_flag)
//            {
//                Tag_record* Tag_record_info = NULL;
//                Status_record* Tag_Status_record_info = NULL;
//                unsigned int coordinate_record_count = 0, status_record_count = 0;
//
//                //cout << Load_Location_coordinate << endl ;
//                if (Load_Location_coordinate)
//                    Tag_record_info = Load_Location_coordinate(coordinate_record_count);
//                if (Load_Location_status)
//                    Tag_Status_record_info = Load_Location_status(status_record_count);
//
//                //cout << "record count :"<<coordinate_record_count << endl;
//                Location_Point_display(Tag_record_info, coordinate_record_count, Tag_Status_record_info, status_record_count);
//
//                usleep(100*1000);
//
//            }
//            //*/
//            //Device_signal_mode = (Device_Signal_Mode)GetProcAddress(CallLibrary, "Device_Signal_Mode");
//
////            if (Device_signal_mode)
////            {
////                Device_signal_mode(false, "", "");
////                Thread^ UI_Thread;
////                UI_Thread = gcnew Thread(gcnew ThreadStart(this, &MyForm::start_UI));
////                UI_Thread->IsBackground = true;
////                UI_Thread->Start();
////            }
////            dlclose(handle);
////            handle = nullptr ;
//
//            cout << "END" << endl ;
//
//        }
//    }
//
//}

void Stop()
{
    openserver_flag = false;
    isPreSet = false ;
//    void *handle = g_handle;
//    Location_cleanup = ( Cleanup ) dlsym(handle, Location_Cleanup );
//    if ( Location_cleanup)
//        Location_cleanup() ;


}



void pre_loc2()
{
    int ret = load_DLL() ;
    cout << "result :" << ret << endl;


}


void loc_run2()
{

    // Load .so ( UPOS Library ) *******
    void *handle = nullptr;
    cout << "C++ dlopen" << endl;
    // 打开库文件
    cout << "Opening *.so..." << endl;
    //动态库 libhello.so 的绝对路径
    handle = dlopen(LIB_CACULATE_PATH, RTLD_NOW);

    if (!handle)
    {
        cerr << "Cannot open library: " << endl << dlerror() << endl;
        return ;
    }
    // 加载符号表
    cout << "Loading symbol caculate..." << endl;
    // Load .so END *******



    Pre_Setting_init();
    Location_Init = (Location_Init_fun) dlsym(handle, Location_init);

    Init_Anchor = (Location_Set_Anchor_fun) dlsym(handle, Location_Set_Anchor );
    if (Init_Anchor)
    {
        Init_Anchor(Init_Group_Main_Anchor_List, Init_Group_Main_Anchor_List_count, Init_Group_Anchor_List, Init_Group_Anchor_List_count);
        cout << "init_anchor_success" << endl ;
    }


    if (Location_Init)
    {
        bool bResault = Location_Init();
        if (bResault)
        {
            cout << "location_init" << endl ;

            Load_Location_coordinate = (Load_Location_Coordinate) dlsym(handle, Load_Location_coordinate_record);
            Load_Location_status = (Load_Location_Status) dlsym(handle, Load_Location_status_record );

            //*
            while (openserver_flag)
            {
                Tag_record* Tag_record_info = NULL;
                Status_record* Tag_Status_record_info = NULL;
                unsigned int coordinate_record_count = 0, status_record_count = 0;

                //cout << Load_Location_coordinate << endl ;
                if (Load_Location_coordinate)
                    Tag_record_info = Load_Location_coordinate(coordinate_record_count);
                if (Load_Location_status)
                    Tag_Status_record_info = Load_Location_status(status_record_count);
//
//                //cout << "record count :"<<coordinate_record_count << endl;
                Location_Point_display(Tag_record_info, coordinate_record_count, Tag_Status_record_info, status_record_count);



                // create index for locus record *******
                // check_locus_index();
                // each hour , get id of the first record in each hour, and use the id to create index.
                check_locus_index_hour();

                // each min , get id of the first record in each minute, and use the id to create index.
                check_locus_index_hour_min();

                // Because still not determining which method to use, so reserving above ( hour / min ).
                // create index END *******


                usleep(100000);


            }

            cout << "END" << endl ;

        }
    }

    Location_cleanup = ( Cleanup ) dlsym(handle, Location_Cleanup );
    if ( Location_cleanup)
        Location_cleanup() ;

    cout << "before close" << endl ;
//    cout << "close value :" << dlclose(handle) << endl ;
    cout << "after close" << endl ;



}



void List_port2()
{

    string port;
    int fd;
    //vector<string>  list;
    for(int i = 0; i < 256; ++i)
    {
        port.clear();
        port.append("/dev/ttyUSB");
        port.append(to_string(i));

        fd = open(port.c_str(), O_RDWR | O_NOCTTY ); // | O_NDELAY
        if(fd < 0 )
        {
            cout << "Error " << errno << " opening " << port << "\t: " << strerror (errno) << endl;

        }
        else
        {
            port_list.push_back(port);
        }

    }

    cout << endl << "ok port : " << endl ;
    for ( int i = 0 ; i < port_list.size() ; i++)
        cout  << port_list[i] << endl ;



}



void Setting_Server_IP()
{

    cout << "Type the IP :" << endl ;
    char input_ip[16] = {0} ;
    cin.getline(input_ip,16); //呼叫函數 ,10代表最大能讀入的字串長度
    cout << ">>" << input_ip << "<<" << endl ;
    if ( strlen(input_ip) == 15 )
        ip_adr = (char*)input_ip;
//    strcpy( ip_adr, (char*)input_ip ) ;
//    *ip_adr = *input_ip;
    cout << ">>" << ip_adr << "<<" << endl ;

}



string test_date_part( string date_with_hour )
{

    tm tm_;
    time_t t_;
    char buf[128]= {0};

    //strcpy(buf, "2012-01-30");
    string in = date_with_hour + ":00:00" ;
//    cout << in << endl ;


    strcpy (buf, in.c_str());

    strptime(buf, "%Y-%m-%d %H:00:00", &tm_); //将字符串转换为tm时间
    tm_.tm_isdst = -1;
    t_  = mktime(&tm_); //将tm时间转换为秒时间
    //t_ += 3600;  //秒数加3600
//    t_ += 3600;

    tm_ = *localtime(&t_);//输出时间
    strftime(buf, 64, "%Y-%m-%d", &tm_);
//    cout << buf << endl;

    string val_out = "nothing";
    val_out = string(buf);
    cout << "date part :" << val_out << endl ;
    return val_out ;
}

string test_time_part ( string date_with_hour )
{
    tm tm_;
    time_t t_;
    char buf[128]= {0};

    //strcpy(buf, "2012-01-30");
    string in = date_with_hour + ":00:00" ;
//    cout << in << endl ;


    strcpy (buf, in.c_str());

    strptime(buf, "%Y-%m-%d %H:00:00", &tm_); //将字符串转换为tm时间
    tm_.tm_isdst = -1;
    t_  = mktime(&tm_); //将tm时间转换为秒时间
    //t_ += 3600;  //秒数加3600
//    t_ += 3600;

    tm_ = *localtime(&t_);//输出时间
    strftime(buf, 64, "%H:%M:%S", &tm_);
//    cout << buf << endl;

    string val_out = "nothing";
    val_out = string(buf);
    cout << "time part :" << val_out << endl ;
    return val_out ;
}

string testStr2Time_Hour( string date, string time )
{

    tm tm_;
    time_t t_;
    char buf[128]= {0};

    //strcpy(buf, "2012-01-30");
    string in = date + time ;
//    cout << in << endl ;


    strcpy (buf, in.c_str());

    strptime(buf, "%Y-%m-%d %H:00:00", &tm_); //将字符串转换为tm时间
    tm_.tm_isdst = -1;
    t_  = mktime(&tm_); //将tm时间转换为秒时间
    //t_ += 3600;  //秒数加3600
//    t_ += 3600;

    tm_ = *localtime(&t_);//输出时间
    strftime(buf, 64, "%Y-%m-%d %H", &tm_);
//    cout << buf << endl;

    string val_out = "nothing";
//    cout << "before :" << val_out << endl ;
    val_out = string(buf);
    cout << "after :" << val_out  << "<<" << endl ;


    return val_out ;

}

int main()
{


//    Get_LastDay_date() ;
//    Get_Today_date_hour();
    cout << Get_Today_date_hour_min() << endl ;
//    string datetest = "2012-01-30 21";
//"2019-03-29", "start_time": "00:30:32" ,
//    testStr2Time_Hour( "2019-03-29", "00:30:32" ) ;
//    test_date_part( datetest );
//    test_time_part( datetest );
//    debug_mode = false ;

    cout << "net inferface" << endl ;
    //Update_net_interface() ;


    cout << "search dev"  << endl ;
    //if ( str_inferface_ip.length() != 0 )
    //    Update_search_dev(str_inferface_ip) ;


    //Read_RF_setting();

    //Update_FW() ;

    /*
    cout << "Comport list" << endl ;
    List_port2();
    serialPort1->Set_port_name(list[0]);
    serialPort1->Open_port();
    Read_Basic_setting() ;
    //serialPort1->
    //*/



//    Setting_Server_IP();

    construct_func_map() ;
    construct_RW_json_map();

    thread server_thread( Lanuch_Server ) ;
    server_thread.detach();



    if ( _using_SQL() )
    {
        SQL_Init();
        if ( Construct_sql_cmd() ) // create DB table
            _SQL_flag = true ;
        else
        {
            cout << "Construct DB Failed" << endl ;
            return 0;
        }
    }


    while (1)
    {
        while ( openserver_flag )
        {
            if ( _SQL_flag )
                cout << "====== SQL Mode ======" << endl ;

            else
                cout << "====== Without SQL Mode ======" << endl ;


            loc_run2();
//            cout << "close :" << dlclose(handle) << endl ;
//            cout << "dl error :" << dlerror() << endl ;
        }
//        cout << "Openserver OFF"<< endl ;

        usleep(1000000);

    } // while


}
