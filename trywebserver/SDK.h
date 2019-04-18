#pragma once
#include <map>
#define TAG_LEN 16
#define Time_LEN 23
//using namespace std;
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
	char Tag_ID[TAG_LEN+1] = {0};
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
	char Tag_ID[TAG_LEN + 1] = { 0 };
	Status_info Status_info_record[20];
	unsigned int Info_count = 0;
};
