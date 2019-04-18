

using namespace std ;

typedef void(*Callback_Fun0)() ;


// int RW, unsigned char* value
typedef void(*Callback_Fun)( int, unsigned char*,unsigned char* );

//( string fw_name, int &flag )
typedef void(*Callback_FW)( char*, string, int & );

// void RW_IP(char* ip_addr, int ip_port, int RW, unsigned char* Set_data, int set_length, unsigned char* buff, int &flag);
//typedef void(*Callback_with_arg_7[])( char*, int, int, unsigned char*, int, unsigned char*, int &);
typedef void(*Callback_with_arg_7)( char*, int, int, unsigned char*, int, unsigned char*, int &);


//static  void TCP_sendpackage(char* ip_addr, int ip_port, int net_str_length, int eoco_length, char* net_str, char* buff);
typedef void(*Callback_with_arg_6)(char* , int , int , int , char* , char* );

//void send_cmd(char* ip_addr, int ip_port, unsigned char* buff_temp, unsigned int length, unsigned char* return_buff_temp);
typedef void(*Callback_with_arg_5_1)( char*, int, unsigned char*, unsigned int ,unsigned char* );

//void update_data(char* ip_addr, int ip_port, unsigned char* binch, int length, int &flag);
typedef void(*Callback_with_arg_5_2)(char* , int, unsigned char*, int, int &);

//static  void Read_MODE(char* ip_addr, int ip_port, unsigned char* buff, int &flag);
typedef void(*Callback_with_arg_4)( char*, int, unsigned char*, int & );

//void Reset_Chip(char* ip_addr, int ip_port, int &flag);
typedef void(*Callback_with_arg_3_1)( char*, int, int & );

//static	 void crc16(const unsigned char* buffer, int size, int &crc_value);
typedef void(*Callback_with_arg_3_2)(const unsigned char* , int , int &);




//enum op_type { ADD, SUB, MUL, DIV };

typedef struct {
    string func_name;
    string rw;
    //string input_arg ;
    int set_length;

    Callback_with_arg_7 callback ;
    Callback_Fun RW_arg;

} func_cmd_detail_7_arg;

typedef struct {
    string func_name;
    string rw;
    //string input_arg ;
    int set_length;

    Callback_with_arg_6 callback ;
    Callback_Fun RW_arg;

} func_cmd_detail_6_arg;



typedef struct {
    string func_name;
    string rw;
    //string input_arg ;
    int set_length;

    Callback_with_arg_5_1 callback ;
    Callback_Fun RW_arg;

} func_cmd_detail_5_1_arg;

typedef struct {
    string func_name;
    string rw;
    //string input_arg ;
    int set_length;

    Callback_with_arg_5_2 callback ;
    Callback_FW RW_arg;

} func_cmd_detail_5_2_arg;



typedef struct {
    string func_name;
    string rw;
    //string input_arg ;
    int set_length;

    Callback_with_arg_4 callback ;
    Callback_Fun RW_arg;

} func_cmd_detail_4_arg;



typedef struct {
    string func_name;
    string rw;
    //string input_arg ;
    int set_length;

    Callback_with_arg_3_1 callback ;
    Callback_Fun RW_arg;

} func_cmd_detail_3_1_arg;

typedef struct {
    string func_name;
    string rw;
    //string input_arg ;
    int set_length;

    Callback_with_arg_3_2 callback ;
    Callback_Fun RW_arg;

} func_cmd_detail_3_2_arg;


extern map<string, func_cmd_detail_7_arg> g_function_7_arg_map;
extern map<string, func_cmd_detail_6_arg> g_function_6_arg_map;
extern map<string, func_cmd_detail_5_1_arg> g_function_51_arg_map;
extern map<string, func_cmd_detail_5_2_arg> g_function_52_arg_map;
extern map<string, func_cmd_detail_4_arg> g_function_4_arg_map;
extern map<string, func_cmd_detail_3_1_arg> g_function_31_arg_map;
extern map<string, func_cmd_detail_3_2_arg> g_function_32_arg_map;


void construct_func_map();

void construct_RW_json_map();



extern map<string, Callback_Fun0> g_RW_json_package;













