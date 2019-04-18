#pragma once
#include <map>
//using namespace std;

#define TAG_LEN 16
#define Time_LEN 23
struct Anchor_Message
{
	int item = 0;
	int main_group = 0;
	int id = 0;
	int x = 0;
	int y = 0;
	//int distance = 0;
};
struct Main_Anchor_Message
{
	int id = 0;
	int x = 0;
	int y = 0;
	//int distance = 0;
};
struct Tag_info
{
	int x = 0;
	int y = 0;
	//int Status = 0;
	//std::string System_Time = "";
	char System_Time[Time_LEN + 1] = {0};
};
struct Tag_record
{
	//std::string Tag_ID = "";
	char Tag_ID[TAG_LEN + 1] = { 0 };
	Tag_info Tag_info_record[20];
	unsigned int Info_count = 0;
};
struct Status_info
{
	int Status = 0;
	//std::string System_Time = "";
	char System_Time[Time_LEN + 1] = { 0 };
};
struct Status_record
{
	//std::string Tag_ID = "";
	char Tag_ID[TAG_LEN + 1] = { 0 };
	Status_info Status_info_record[20];
	unsigned int Info_count = 0;
};
// µ²ºc

//SYSTEMTIME st;

//GetLocalTime(&st);
//class Location_Record
//{
//	Location_Record();
//	public:
//		map<string, map<SYSTEMTIME, Tag_info>> Map_Location_Record;
//};
//typedef void(*LocationCallBack)(int x, int y, std::string tag_id, unsigned long pParam);
//typedef void(*LocationCallBack_Status)(std::string tag_id, int Status, unsigned long pParam);

bool Location_Init(/*LocationCallBack mLocationcallback, LocationCallBack_Status mLocationCallBack_Status, unsigned long pParam*/);

void Location_Cleanup();

void Location_Set_Anchor(Main_Anchor_Message* achor_main, int len_main, Anchor_Message* anchor_child, int len_child);

Tag_record* Load_Location_coordinate_record(unsigned int &Tag_count);
Status_record* Load_Location_status_record(unsigned int &Tag_count);
//void Load_Location_Status(std::map<std::string, std::map<std::string, Status_info>> map_Location_Status_Record);
