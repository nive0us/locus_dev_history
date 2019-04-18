
#include <string>

#define MAC_len 17
#define Machine_Number_len 8
#define Ip_len 4
#define GW_len 4
#define Mask_len 4
#define cleienIP_len 4
#define TCP_server_port_len 2
#define UDP_server_port_len 2
#define TCP_client_src_port_len 2
#define TCP_client_des_port_len 2
#define model_len 8
#define Interface_ID_Max_len 300
#define Ip_str_len 15
#define GW_str_len 15
#define Mask_str_len 15
#define cleienIP_str_len 15
#define TCP_server_port_str_len 5
#define UDP_server_port_str_len 5
#define TCP_client_src_port_str_len 5
#define TCP_client_des_port_str_len 5






namespace rfid
{
/*
rfid::Network_Interface_Info* Info = NULL;
rfid::Device_Info* device_info = NULL;
*/
struct Network_Interface_Info
{
    /*
    std::string Network_Interface_ID = "";
    unsigned char IP_address[4] = {0};
    */
    char Network_Interface_ID[Interface_ID_Max_len + 1] = { 0 };
	char IP_address[Ip_str_len + 1] = { 0 };
};
struct Device_Info
{
    /*
    std::string Machine_Number = "";
    std::string Model = "";
    std::string IP_address = "";
    std::string Mask_address = "";
    std::string Gateway_address = "";
    std::string Client_ip_addr = "";
    std::string MAC_address = "";
    std::string TCP_Serve_Port = "";
    std::string UDP_Serve_Port = "";
    std::string TCP_Client_Src_Port = "";
    std::string TCP_Client_Des_Port= "";
    */
    char Machine_Number[Machine_Number_len + 1] = { 0 };
    char Model[model_len + 1] = { 0 };
    char IP_address[Ip_str_len + 1] = { 0 };
    char Mask_address[Mask_str_len + 1] = { 0 };
    char Gateway_address[GW_str_len + 1] = { 0 };
    char Client_ip_addr[cleienIP_str_len + 1] = { 0 };
    char MAC_address[MAC_len + 1] = { 0 };
    char TCP_Serve_Port[TCP_server_port_str_len + 1] = { 0 };
    char UDP_Serve_Port[UDP_server_port_str_len + 1] = { 0 };
    char TCP_Client_Src_Port[TCP_client_src_port_str_len + 1] = { 0 };
    char TCP_Client_Des_Port[TCP_client_des_port_str_len + 1] = { 0 };
};
//using namespace system;
class UDP
{
public:
    static  Device_Info* Search_ip(int ip_port, char* ipaddr,int &count);
public:
    static  Network_Interface_Info* Get_ipaddr(int &count);
};
}
