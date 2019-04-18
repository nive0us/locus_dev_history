# include <ser.h>
#include <string>
#include <iostream>
#include <SerialPort.h>
using namespace std;

#define baudrate B115200



int SerialPort::Open_port()
{
    int USB = open( PortName.c_str(), O_RDWR| O_NOCTTY );
    struct termios tty;
    struct termios tty_old;
    memset (&tty, 0, sizeof tty);

    /* Error Handling */
    if ( tcgetattr ( USB, &tty ) != 0 )
    {
        std::cout << "Error " << errno << " from tcgetattr: " << strerror(errno) << std::endl;
        return -1 ;
    }

    /* Save old tty parameters */
    tty_old = tty;

    /* Set Baud Rate */
    cfsetospeed (&tty, (speed_t)baudrate);
    cfsetispeed (&tty, (speed_t)baudrate);

    /* Setting other Port Stuff */
    tty.c_cflag     &=  ~PARENB;            // Make 8n1
    tty.c_cflag     &=  ~CSTOPB;
    tty.c_cflag     &=  ~CSIZE;
    tty.c_cflag     |=  CS8;

    tty.c_cflag     &=  ~CRTSCTS;           // no flow control
    tty.c_cc[VMIN]   =  1;                  // read doesn't block
    //tty.c_cc[VTIME]  =  5;                  // 0.5 seconds read timeout
    tty.c_cc[VTIME]  =  1 ;
    tty.c_cflag     |=  CREAD | CLOCAL;     // turn on READ & ignore ctrl lines

    /* Make raw */
    cfmakeraw(&tty);

    /* Flush Port, then applies attributes */
    tcflush( USB, TCIFLUSH );
    if ( tcsetattr ( USB, TCSANOW, &tty ) != 0)
    {
        std::cout << "Error " << errno << " from tcsetattr" << std::endl;
        return -1 ;
    }

    PortNum = USB ;
}



void SerialPort::Set_port_name( string target )
{
    PortName = "" ;
    PortName = target ;
}


void SerialPort::Port_Read(array<Byte,2048> read_back2, int offset )
{
    int n = 0,
        spot = offset;
    char buf = '\0';

    unsigned char read_back = {0};
    /* Whole response*/
    char response[1024];
    memset(response, '\0', sizeof response);

    //cout << "111" << endl ;


    n = read( PortNum, &buf, 1 );
    // cout << "222" << endl ;
    sprintf( &response[spot], "%c", buf );
    printf( "%hhu\n", buf ) ;
    read_back = buf ;
    read_back2[spot] = (unsigned char)buf ;
    spot += n;



    if (n < 0)
    {
        cout << "Error reading: " << strerror(errno) << endl;
    }
    else if (n == 0)
    {
        std::cout << "Read nothing!" << endl;
    }
    else
    {
        cout << "Response: " << response << endl;
    }
    //return spot ;

}


void SerialPort::Port_Read_original(array<Byte,2048> read_back2)
{
    int n = 0,
        spot = 0;
    char buf = '\0';

    unsigned char read_back[1024] = {0};
    /* Whole response*/
    char response[1024];
    memset(response, '\0', sizeof response);

    do
    {
        n = read( PortNum, &buf, 1 );
        sprintf( &response[spot], "%c", buf );
        read_back[spot] = buf ;
        spot += n;
    }
    while( buf != '\r' && n > 0);

    if (n < 0)
    {
        cout << "Error reading: " << strerror(errno) << endl;
    }
    else if (n == 0)
    {
        std::cout << "Read nothing!" << endl;
    }
    else
    {
        cout << "Response: " << response << endl;
    }
    //eturn spot ;

}


void SerialPort::Port_Write(unsigned char cmd[2048], int writen_length)
{
    //unsigned char cmd[] = "INIT \r";
    int n_written = 0,
        spot = 0;

    /*
    do
    {
    n_written = write( PortNum, &cmd[spot], 1 );
    spot += n_written;
    }
    while (cmd[spot-1] != '\r' && n_written > 0);
    */
    //n_written = write( PortNum, cmd, sizeof(cmd) -1) ;
    n_written = write( PortNum, cmd, writen_length) ;
    printf ( "n_written : %d\n", n_written ) ;

}







