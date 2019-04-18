#include <string>
#include <iostream>
#include <array>

typedef unsigned char Byte;
using namespace std;

class SerialPort
{

private:


    string PortName;
    int PortNum;

public:
    int ReadTimeout;
    int Open_port();


    void Set_port_name( string target ) ;


    void Port_Read(array<Byte,2048> read_back2, int offset );

    void Port_Read_original(array<Byte,2048> read_back2);


    void Port_Write(unsigned char cmd[], int writen_length);


};

