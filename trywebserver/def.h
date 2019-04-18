
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
/*
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

*/
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



#define DF_UDP_PORT 50001
#define DF_TCP_PORT 80
#define DF_TCP_CLIENT_PORT 50004
#define baudrate  115200



