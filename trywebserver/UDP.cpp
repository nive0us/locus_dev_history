//#include "stdafx.h"
#include "UDP.h"
//#include <WS2tcpip.h>
//#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//#include <iphlpapi.h>
#include <vector>
//#include <windows.h>

//*******************************************
#include "ser.h"

#include <iostream>
#include <stdio.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <cstring>
#include <sstream>


#include <string.h>
#include <errno.h>
using namespace std;





//*******************************************
#include"TCP.h"
//#include "map"
#define R 1000
#define C 200
//#pragma comment(lib, "ws2_32.lib")
//#pragma comment(lib, "IPHLPAPI.lib")
#pragma once
//using namespace std;
namespace rfid
{
Network_Interface_Info* Info = NULL;
Device_Info* device_info = NULL;
rfid::Device_Info* rfid::UDP::Search_ip(int ip_port, char* ipaddr,int &count)
{
    delete[] device_info;
    device_info = NULL;
    //int MAC_len = 17, Machine_Number_len = 8, Ip_len = 4, GW_len = 4, Mask_len = 4, cleienIP_len = 4,
    //TCP_server_port_len = 2, UDP_server_port_len = 2, TCP_client_src_port_len = 2, TCP_client_des_port_len = 2, model_len = 8;
    int count_temp = 0;
    unsigned int port_temp = 0;
    std::string temp1, temp2;
    count = 0;
    std::map<int, Device_Info> Search_temp;




    /*
    WSACleanup();
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    	return device_info;
    */


    /*
    int thisSocket;


    destination.sin_family = AF_INET;
    thisSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (thisSocket < 0)
    {
        printf("\nSocket Creation FAILED!");
        return 0;
    }
    */


    char m_strData[] = "SF-TEK-Ethernet RFID Reader";

    SOCKET m_socket = socket(AF_INET, SOCK_DGRAM, 0);//UPD¤è¦¡
    //int m_socket = socket(AF_INET, SOCK_DGRAM, 0);
    //fcntl(m_socket, F_SETFL, O_NONBLOCK);

    if (m_socket < 0)
    {
        printf("\nSocket Creation FAILED!");
        return 0;
    }

    BOOL bBroadcast = TRUE;

    if ( setsockopt(m_socket, SOL_SOCKET, SO_BROADCAST | SO_REUSEADDR, (const char*)&bBroadcast, sizeof(BOOL)) == -1 )
    {
        cout << "setsockopt failed!" << endl ;
        return 0 ;
    }


    //
    if ( setsockopt(m_socket, SOL_SOCKET,  SO_BINDTODEVICE , ipaddr, strlen(ipaddr)) == -1 )
    {
        cout << "setsockopt2 failed!" << endl ;
        return 0 ;
    }

    //struct sockaddr_in addr_local;
    sockaddr_in addr_local, addr_sendto;
    memset(&addr_local, 0x00, sizeof(addr_local));
    memset(&addr_sendto, 0x00, sizeof(addr_sendto));

    cout << "net interface : "<< ipaddr << endl ;

    /*
    addr_local.sin_family = AF_INET;
    addr_local.sin_port = htons(0);
    addr_local.sin_addr.s_addr = htonl(INADDR_ANY) ;

    //addr_local.sin_addr.s_addr = inet_aton(ipaddr,&addr_local.sin_addr);
    //addr_local.sin_addr.s_addr = htonl(0xffffffff) ;
    //addr_local.sin_addr.s_addr = inet_addr("192.168.1.132");
    //addr_local.sin_addr.s_addr = inet_addr(ipaddr);



    //setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, &addr_local, sizeof(addr_local)); // reuse addr
    //int optval = 1;//这个值一定要设置，否则可能导致sendto()失败
    //setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEADDR, &optval, sizeof(addr_local)); // reuse addr


    if (bind(m_socket, (struct sockaddr*)&addr_local, sizeof(addr_local)) == SOCKET_ERROR)
    {
        printf("Failed bind:%d\n", errno);
        return FALSE;
    }
    //*/




    addr_sendto.sin_family = AF_INET;
    addr_sendto.sin_port = htons(ip_port);
    //addr_sendto.sin_addr.s_addr = htonl(INADDR_ANY);
    addr_sendto.sin_addr.s_addr = htonl(INADDR_BROADCAST);
//    addr_sendto.sin_addr.s_addr = inet_addr("192.168.1.255");




    // windows
    //int nlen = sizeof(SOCKADDR);

    // linux
    socklen_t nlen = sizeof( sockaddr_in );
    cout << "nlen :" << nlen << endl ;
    //socklen_t nlen = sizeof(struct sockaddr_storage);

    //char test[1024] = {0};
    //socklen_t nlen = sizeof(test);

    int nSenlen = strlen(m_strData);
    int nNetTimeout = 500;

    struct timeval timeout= {0,nNetTimeout}; // {sec,ms}

    /*/ windows
    setsockopt(m_socket,SOL_SOCKET, SO_SNDTIMEO, (char *)&nNetTimeout, sizeof(nNetTimeout));
    setsockopt(m_socket,SOL_SOCKET, SO_RCVTIMEO, (char *)&nNetTimeout, sizeof(nNetTimeout));
    //*/

    //*/ linux
    int sndto = setsockopt(m_socket,SOL_SOCKET, SO_SNDTIMEO,(const void*) &timeout, sizeof(timeout));
    int rcvto = setsockopt(m_socket,SOL_SOCKET, SO_RCVTIMEO,(const void*) &timeout, sizeof(timeout));
    if ( sndto != 0 || rcvto != 0 )
        cout << "time eor" << endl ;
    //*/

    if ( sendto(m_socket, m_strData, nSenlen, 0, (struct SOCKADDR *)&addr_sendto, nlen) < 0 )
        cout << "send err" << endl ;
    int nrecv = 0;
    char szrecvbuf[2048] = {0};

    SOCKADDR_IN sockRecv;

    while (1)
    {
        char temp[1024] = { 0 };
        nrecv = 0 ;

        memset(szrecvbuf, 0, sizeof(szrecvbuf));

        nrecv = recvfrom(m_socket, szrecvbuf, sizeof(szrecvbuf), 0, (struct sockaddr*)&sockRecv, &nlen);
//        nrecv = recvms(m_socket, szrecvbuf, sizeof(szrecvbuf));


        if (nrecv < 0)
        {
            printf ("nrecv equal %d\n", nrecv );
            if (errno == EINTR)
            {
                fprintf(stderr, "recvfrom() interrupted.\n");
            }
            else
            {
                fprintf(stderr, "Error from recvfrom() - %s (%d)\n", strerror(errno), errno);
            }
            break;
        }

        cout << "for check" << endl ;


        /*
        for ( size_t z = 0 ; z <  (unsigned int)sizeof(szrecvbuf) ; z++ )
            printf ("%hhu",szrecvbuf[z] );
        */


        for (size_t j = 0; j < (unsigned int)MAC_len; j++)
        {
            temp[j] = szrecvbuf[j];
            temp[j + 1] = 0;
        }
        //Search_temp[count].MAC_address = temp;
        strcpy( Search_temp[count].MAC_address, temp ) ;
        cout << "tmp MAC :"<< temp << endl ;

        for (size_t j = 0; j < (unsigned int)Machine_Number_len; j++)
        {
            temp[j] = szrecvbuf[j + MAC_len];
            temp[j + 1] = 0;
        }
        //Search_temp[count].Machine_Number = temp;
        strcpy( Search_temp[count].Machine_Number, temp ) ;
        temp2 = "";
        for (size_t j = 0; j < (unsigned int)Ip_len; j++)
        {
            temp1 = std::to_string((unsigned char)szrecvbuf[j + MAC_len + Machine_Number_len]);
            if (j < (unsigned int)(Ip_len-1))
                temp1 = temp1 + ".";
            temp2 = temp2 + temp1;
        }
        //Search_temp[count].IP_address = temp2;
        strcpy( Search_temp[count].IP_address, temp2.c_str() ) ;
        cout << "tmp IP :" << temp2 << endl ;

        temp2 = "";
        for (size_t j = 0; j < (unsigned int)GW_len; j++)
        {
            temp1 = std::to_string((unsigned char)szrecvbuf[j + MAC_len + Machine_Number_len + Ip_len]);
            if (j < (unsigned int)(GW_len - 1))
                temp1 = temp1 + ".";
            temp2 = temp2 + temp1;
        }
        //Search_temp[count].Gateway_address = temp2;
        strcpy( Search_temp[count].Gateway_address, temp2.c_str() ) ;
        temp2 = "";
        for (size_t j = 0; j < (unsigned int)Mask_len; j++)
        {
            temp1 = std::to_string((unsigned char)szrecvbuf[j + MAC_len + Machine_Number_len + Ip_len + GW_len]);
            if (j < (unsigned int)(Mask_len - 1))
                temp1 = temp1 + ".";
            temp2 = temp2 + temp1;
        }
        //Search_temp[count].Mask_address = temp2;
        strcpy( Search_temp[count].Mask_address, temp2.c_str() ) ;
        temp2 = "";
        for (size_t j = 0; j < (unsigned int)cleienIP_len; j++)
        {
            temp1 = std::to_string((unsigned char)szrecvbuf[j + MAC_len + Machine_Number_len + Ip_len + GW_len + Mask_len]);
            if (j < (unsigned int)(cleienIP_len - 1))
                temp1 = temp1 + ".";
            temp2 = temp2 + temp1;
        }
        //Search_temp[count].Client_ip_addr = temp2;
        strcpy( Search_temp[count].Client_ip_addr, temp2.c_str() ) ;
        temp2 = "";

        port_temp = (unsigned int)((unsigned char)szrecvbuf[ MAC_len + Machine_Number_len + Ip_len + GW_len + Mask_len + cleienIP_len] * 256 + (unsigned char)szrecvbuf[MAC_len + Machine_Number_len + Ip_len + GW_len + Mask_len + cleienIP_len + 1]);
        temp1 = std::to_string((unsigned int)port_temp);
        //Search_temp[count].TCP_Serve_Port = temp1;
        strcpy( Search_temp[count].TCP_Serve_Port, temp1.c_str() ) ;

        port_temp = (unsigned int)((unsigned char)szrecvbuf[MAC_len + Machine_Number_len + Ip_len + GW_len + Mask_len + cleienIP_len + TCP_server_port_len] * 256 + (unsigned char)szrecvbuf[MAC_len + Machine_Number_len + Ip_len + GW_len + Mask_len + cleienIP_len + TCP_server_port_len + 1]);
        temp1 = std::to_string((unsigned int)port_temp);
        //Search_temp[count].UDP_Serve_Port = temp1;
        strcpy( Search_temp[count].UDP_Serve_Port, temp1.c_str() ) ;

        port_temp = (unsigned int)((unsigned char)szrecvbuf[ MAC_len + Machine_Number_len + Ip_len + GW_len + Mask_len + cleienIP_len + TCP_server_port_len + UDP_server_port_len]*256 + (unsigned char)szrecvbuf[MAC_len + Machine_Number_len + Ip_len + GW_len + Mask_len + cleienIP_len + TCP_server_port_len + UDP_server_port_len + 1]);
        temp1 = std::to_string((unsigned int)port_temp);
        //Search_temp[count].TCP_Client_Src_Port = temp1;
        strcpy( Search_temp[count].TCP_Client_Src_Port, temp1.c_str() ) ;

        port_temp = (unsigned int)((unsigned char)szrecvbuf[MAC_len + Machine_Number_len + Ip_len + GW_len + Mask_len + cleienIP_len + TCP_server_port_len + UDP_server_port_len + TCP_client_src_port_len]*256+ (unsigned char)szrecvbuf[MAC_len + Machine_Number_len + Ip_len + GW_len + Mask_len + cleienIP_len + TCP_server_port_len + UDP_server_port_len + TCP_client_src_port_len + 1]);
        temp1 = std::to_string((unsigned int)port_temp);
        //Search_temp[count].TCP_Client_Des_Port = temp1;
        strcpy( Search_temp[count].TCP_Client_Des_Port, temp1.c_str() ) ;


        for (size_t j = 0; j < (unsigned int)model_len; j++)
        {
            temp[j] = szrecvbuf[j + MAC_len + Machine_Number_len + Ip_len + GW_len + Mask_len + cleienIP_len + TCP_server_port_len + UDP_server_port_len + TCP_client_src_port_len + TCP_client_des_port_len];
            temp[j + 1] = 0;
        }
        //Search_temp[count].Model = temp;
        strcpy( Search_temp[count].Model, temp ) ;
        cout << "tmp model :" << temp << endl ;


        //if ( Search_temp[count].Model == "UPOS" )
        if ( strcmp ( Search_temp[count].Model,"UPOS") == 0 )
        {
            cout << "IP adr :" <<Search_temp[count].IP_address << endl ;
            cout << "machine :"<<Search_temp[count].Machine_Number << endl ;
            cout << "mac adr :" <<Search_temp[count].MAC_address << endl ;
            cout << Search_temp[count].Model << endl ;
            cout << Search_temp[count].Mask_address << endl ;



            count++;
        }


        else
            Search_temp.erase(count);


    }



    if(count > 0)
        device_info = new Device_Info[count];
    for (size_t i = 0; i < (unsigned int)count; i++)
    {
        /*
        device_info[i].Client_ip_addr = Search_temp[i].Client_ip_addr;
        device_info[i].Gateway_address = Search_temp[i].Gateway_address;
        device_info[i].IP_address = Search_temp[i].IP_address;
        device_info[i].Machine_Number = Search_temp[i].Machine_Number;
        device_info[i].MAC_address = Search_temp[i].MAC_address;
        device_info[i].Mask_address = Search_temp[i].Mask_address;
        device_info[i].Model = Search_temp[i].Model;
        device_info[i].TCP_Client_Des_Port = Search_temp[i].TCP_Client_Des_Port;
        device_info[i].TCP_Client_Src_Port = Search_temp[i].TCP_Client_Src_Port;
        device_info[i].TCP_Serve_Port = Search_temp[i].TCP_Serve_Port;
        device_info[i].UDP_Serve_Port = Search_temp[i].UDP_Serve_Port;
        */

        strcpy( device_info[i].Client_ip_addr, Search_temp[i].Client_ip_addr );
        strcpy( device_info[i].Gateway_address, Search_temp[i].Gateway_address);
        strcpy( device_info[i].IP_address, Search_temp[i].IP_address);
        strcpy( device_info[i].Machine_Number, Search_temp[i].Machine_Number);
        strcpy( device_info[i].MAC_address, Search_temp[i].MAC_address);
        strcpy( device_info[i].Mask_address, Search_temp[i].Mask_address);
        strcpy( device_info[i].Model, Search_temp[i].Model);
        strcpy( device_info[i].TCP_Client_Des_Port, Search_temp[i].TCP_Client_Des_Port);
        strcpy( device_info[i].TCP_Client_Src_Port, Search_temp[i].TCP_Client_Src_Port);
        strcpy( device_info[i].TCP_Serve_Port, Search_temp[i].TCP_Serve_Port);
        strcpy( device_info[i].UDP_Serve_Port, Search_temp[i].UDP_Serve_Port);

        cout << device_info[i].IP_address << endl ;
    }
    close(m_socket);
    //WSACleanup();
    return device_info;


}


Network_Interface_Info* UDP::Get_ipaddr(int &count)
{

    delete[] Info;
    Info = NULL;
    count = 0;
    /*
    int count_temp = 0;
    int first_flag = 0;
    while (1)
    {
    	if (first_flag != 0)
    		Info = new Network_Interface_Info[count];
    	PIP_ADAPTER_ADDRESSES pAddresses = NULL;
    	ULONG outBufLen = 0;
    	GetAdaptersAddresses(AF_UNSPEC, 0, NULL, pAddresses, &outBufLen);
    	pAddresses = (IP_ADAPTER_ADDRESSES*)malloc(outBufLen);
    	if (GetAdaptersAddresses(AF_UNSPEC, GAA_FLAG_SKIP_ANYCAST, NULL, pAddresses, &outBufLen) != NO_ERROR)
    		std::free(pAddresses);
    	char buff[200];
    	DWORD bufflen = 200;
    	PIP_ADAPTER_ADDRESSES pCurrAddresses = NULL;
    	PIP_ADAPTER_UNICAST_ADDRESS pUnicast = NULL;
    	LPSOCKADDR addr = NULL;
    	pCurrAddresses = pAddresses;
    	//int i = 0, j = 0;
    	while (pCurrAddresses)
    	{
    		pUnicast = pCurrAddresses->FirstUnicastAddress;
    		while (pUnicast)
    		{
    			addr = pUnicast->Address.lpSockaddr;
    			ZeroMemory(buff, bufflen);
    			if (addr->sa_family != AF_INET6)
    			{
    				sockaddr_in  *sa_in = (sockaddr_in *)addr;
    				inet_ntop(AF_INET, &(sa_in->sin_addr), buff, bufflen);
                    //InetNtopA(AF_INET, &(sa_in->sin_addr), buff, bufflen);

    				pUnicast = pUnicast->Next;
    				if (first_flag != 0)
    				{
    					for (size_t i = 0; i < 4; i++)
    						Info[count_temp].IP_address[i] = addr->sa_data[i + 2];
    					if (pCurrAddresses->Description[0] == 0)
    						break;
    					char temp[200] = { 0 };
    					for (size_t i = 0; i < wcslen(pCurrAddresses->Description); i++)
    						temp[i] = (char)pCurrAddresses->Description[i];
    					Info[count_temp].Network_Interface_ID = temp;
    				}
    				if (first_flag == 0)
    					count++;
    				else
    					count_temp++;
    			}
    			else
    			{
    				sockaddr_in6 *sa_in6 = (sockaddr_in6 *)addr;
    				pUnicast = pUnicast->Next;
    			}
    		}
    		pCurrAddresses = pCurrAddresses->Next;
    	}

    	std::free(pAddresses);
    	if (first_flag != 0)
    		break;
    	first_flag = 1;
    }
    return 	Info;
    }

    */
    struct sockaddr_in *sin = NULL;
    struct ifaddrs *ifa = NULL, *ifList;

    if (getifaddrs(&ifList) < 0)
    {
        return Info;
    }

    for (ifa = ifList; ifa != NULL; ifa = ifa->ifa_next)
    {
        if(ifa->ifa_addr->sa_family == AF_INET)
        {
            count++;

            printf("n>>> interfaceName: %sn", ifa->ifa_name);
            //Info->Network_Interface_ID = ifa->ifa_name ;
            strcpy(Info->Network_Interface_ID, ifa->ifa_name );

            sin = (struct sockaddr_in *)ifa->ifa_addr;
            printf(">>> ipAddress: %sn", inet_ntoa(sin->sin_addr));
            //Info->IP_address  =  inet_ntoa(sin->sin_addr) ;

            sin = (struct sockaddr_in *)ifa->ifa_dstaddr;
            printf(">>> broadcast: %sn", inet_ntoa(sin->sin_addr));

            sin = (struct sockaddr_in *)ifa->ifa_netmask;
            printf(">>> subnetMask: %sn", inet_ntoa(sin->sin_addr));
        }
    }

    freeifaddrs(ifList);

    return Info;


}


}


