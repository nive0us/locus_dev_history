

#include <sys/socket.h>

#include <netinet/in.h>
//#include "netinet/in.h"
#include <sys/types.h>

#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <map>
#include <unistd.h>

#include <stdio.h>
#include <ifaddrs.h>

//***********************************************************************
#include <stdio.h>      // standard input / output functions
#include <stdlib.h>
#include <string.h>     // string function definitions
#include <unistd.h>     // UNIX standard function definitions
#include <fcntl.h>      // File control definitions
#include <errno.h>      // Error number definitions
#include <termios.h>    // POSIX terminal control definitions

#include<vector>




//***********************************************************************
typedef unsigned short      WORD;
typedef char CHAR;
typedef unsigned short USHORT;
typedef  unsigned int SOCKET;
#define WSADESCRIPTION_LEN      256
#define WSASYS_STATUS_LEN       128
#define far
#define FAR                 far


#ifndef BASETYPES
#define BASETYPES
typedef unsigned long ULONG;
typedef ULONG *PULONG;
typedef unsigned short USHORT;
typedef USHORT *PUSHORT;
typedef unsigned char UCHAR;
typedef UCHAR *PUCHAR;

typedef  unsigned int UINT_PTR, *PUINT_PTR;
typedef UINT_PTR        SOCKET;


typedef unsigned long ULONG_PTR, *PULONG_PTR;
typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
#define Byte BYTE
typedef unsigned short      WORD;
typedef float               FLOAT;
typedef ULONG_PTR DWORD_PTR, *PDWORD_PTR;


//typedef _Null_terminated_ char *PSZ;
#endif  /* !BASETYPES */





#define AF_INET         2               // internetwork: UDP, TCP, etc.
#define SOCKET_ERROR  (-1)



/*

typedef struct WSAData {
        WORD                    wVersion;
        WORD                    wHighVersion;
#ifdef _WIN64
        unsigned short          iMaxSockets;
        unsigned short          iMaxUdpDg;
        char FAR *              lpVendorInfo;
        char                    szDescription[WSADESCRIPTION_LEN+1];
        char                    szSystemStatus[WSASYS_STATUS_LEN+1];
#else
        char                    szDescription[WSADESCRIPTION_LEN+1];
        char                    szSystemStatus[WSASYS_STATUS_LEN+1];
        unsigned short          iMaxSockets;
        unsigned short          iMaxUdpDg;
        char FAR *              lpVendorInfo;
#endif
}  WSADATA, FAR * LPWSADATA;



*/

typedef struct _SYSTEMTIME {
    WORD wYear;
    WORD wMonth;
    WORD wDayOfWeek;
    WORD wDay;
    WORD wHour;
    WORD wMinute;
    WORD wSecond;
    WORD wMilliseconds;
} SYSTEMTIME, *PSYSTEMTIME, *LPSYSTEMTIME;


//***********************************************************************


#define _BSD_SOURCE

#define NO_ERROR 0L                                                 // dderror
#define SEC_E_OK                         ((HRESULT)0x00000000L)


#define SOCKADDR_IN	sockaddr_in
#define SOCKADDR	sockaddr

#ifndef FALSE
#define FALSE               0
#endif

#ifndef TRUE
#define TRUE                1
#endif

//#define MAKEWORD(a,b)   ((WORD)(((BYTE)(a))|(((WORD)((BYTE)(b)))<<8)))

//#define MAKEWORD(a, b)      ((WORD)(((BYTE)(((DWORD_PTR)(a)) & 0xff)) | ((WORD)((BYTE)(((DWORD_PTR)(b)) & 0xff))) << 8))



WORD MAKEWORD(
  BYTE bLow,
  BYTE bHigh
);

//****************************************************************************
#define DF_UDP_PORT 50001
#define DF_TCP_PORT 80
#define DF_TCP_CLIENT_PORT 50004
#define baudrate  115200

#define CH1_freq "CH1 (3.5GHz)"
#define CH2_freq "CH2 (4.0GHz)"
#define CH3_freq "CH3 (4.5GHz)"
#define CH4_freq "CH4 (4.5GHz WBW)"
#define CH5_freq "CH5 (6.5GHz)"
#define CH7_freq "CH7 (6.5GHz WBW)"

#define Dararate1 "110Kbps"
#define Dararate2 "850Kbps"
#define Dararate3 "6.8Mbps"

#define PRF16M "16M"
#define PRF64M "64M"

#define CH1_PGDELAY  "CH1"
#define CH2_PGDELAY  "CH2"
#define CH3_PGDELAY  "CH3"
#define CH4_PGDELAY  "CH4"
#define CH5_PGDELAY  "CH5"
#define CH7_PGDELAY  "CH7"

#define CH1_NOSMART_16M_MAX "CH1_NOSMART_16M"
#define CH2_NOSMART_16M_MAX "CH2_NOSMART_16M"
#define CH3_NOSMART_16M_MAX "CH3_NOSMART_16M"
#define CH4_NOSMART_16M_MAX "CH4_NOSMART_16M"
#define CH5_NOSMART_16M_MAX "CH5_NOSMART_16M"
#define CH7_NOSMART_16M_MAX "CH7_NOSMART_16M"
#define CH1_NOSMART_64M_MAX "CH1_NOSMART_64M"
#define CH2_NOSMART_64M_MAX "CH2_NOSMART_64M"
#define CH3_NOSMART_64M_MAX "CH3_NOSMART_64M"
#define CH4_NOSMART_64M_MAX "CH4_NOSMART_64M"
#define CH5_NOSMART_64M_MAX "CH5_NOSMART_64M"
#define CH7_NOSMART_64M_MAX "CH7_NOSMART_64M"
#define CH1_SMART_16M_MAX "CH1_SMART_16M"
#define CH2_SMART_16M_MAX "CH2_SMART_16M"
#define CH3_SMART_16M_MAX "CH3_SMART_16M"
#define CH4_SMART_16M_MAX "CH4_SMART_16M"
#define CH5_SMART_16M_MAX "CH5_SMART_16M"
#define CH7_SMART_16M_MAX "CH7_SMART_16M"
#define CH1_SMART_64M_MAX "CH1_SMART_64M"
#define CH2_SMART_64M_MAX "CH2_SMART_64M"
#define CH3_SMART_64M_MAX "CH3_SMART_64M"
#define CH4_SMART_64M_MAX "CH4_SMART_64M"
#define CH5_SMART_64M_MAX "CH5_SMART_64M"
#define CH7_SMART_64M_MAX "CH7_SMART_64M"

#define UWB_preambleLength64 "64"
#define UWB_preambleLength128 "128"
#define UWB_preambleLength256 "256"
#define UWB_preambleLength512 "512"
#define UWB_preambleLength1024 "1024"
#define UWB_preambleLength1536 "1536"
#define UWB_preambleLength2048 "2048"
#define UWB_preambleLength4096 "4096"

#define UWB_PAC8 "8"
#define UWB_PAC16 "16"
#define UWB_PAC32 "32"
#define UWB_PAC64 "64"

#define UWB_NSD0 "0"
#define UWB_NSD1 "1"

#define UWB_SMARTPOWER0 "0"
#define UWB_SMARTPOWER1 "1"

#define UWB_ANCHOR "Anchor"
#define UWB_TAG "Tag"
#define UWB_Gateway "Gateway"

#define UWB_Interface1 "Ethernet"
#define UWB_Interface2 "Comport"

#define Max_Tag_Count 5000
//using namespace std;

struct Point_info
{
	long x = 0;
	long y = 0;
};
//struct Status_info
//{
//	int Status = 0;
//	std::string System_Time = "";
//};
//struct Status_record
//{
//	string Tag_ID = "";
//	Status_info Status_info_record[20];
//	unsigned int Info_count = 0;
//};
//struct Anchor_Message
//{
//	int item = 0;
//	int main_group = 0;
//	int id = 0;
//	int x = 0;
//	int y = 0;
//};
//struct Tag_info
//{
//	int x = 0;
//	int y = 0;
//	std::string System_Time = "";
//};
//struct Tag_record
//{
//	std::string Tag_ID = "";
//	Tag_info Tag_info_record[20];
//	unsigned int Info_count = 0;
//};
struct Anchor_info
{
	int id = 0;
	Point_info point;
};
struct tag_info_point
{
	Point_info point;
	std::string Tag_Map_string;
	std::string Tag_picture_path;
};

//
///
//
//
//
//
///

#define Max_Tag_Count 5000
#define Max_Tag_Record_Count 20
#define pictureBox_size 15
#define pictureBox_max_size 40


//struct Status_info
//{
//	int Status = 0;
//	std::string System_Time = "";
//};
//struct Status_record
//{
//	string Tag_ID = "";
//	Status_info Status_info_record[20];
//	unsigned int Info_count = 0;
//};
//struct Anchor_Message
//{
//	int item = 0;
//	int main_group = 0;
//	int id = 0;
//	int x = 0;
//	int y = 0;
//};
//struct Tag_info
//{
//	int x = 0;
//	int y = 0;
//	std::string System_Time = "";
//};
//struct Tag_record
//{
//	std::string Tag_ID = "";
//	Tag_info Tag_info_record[20];
//	unsigned int Info_count = 0;
//};

struct tagid_info
{
	std::string Tag_Map_string;
	bool display_id_flag = true;
};
//struct Main_Anchor_Message
//{
//	int id = 0;
//	int x = 0;
//	int y = 0;
//};
#define No_Status 0
#define Lowpower_Status 1
#define Help_Status 2
#define Still_Status 3
#define Active_Status 4
#define Image_Height 40
#define DF_UDP_PORT 50001
#define DF_TCP_PORT 80
#define DF_TCP_CLIENT_PORT 50004
#define baudrate  115200



