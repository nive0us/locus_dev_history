#pragma once
//#include "stdafx.h"
//#include "wx/wx.h"
#include "TDOA.h"
#include <mutex>
#include <cstring>
#include <unistd.h>

std::mutex thread_lock; //mike
#define No_Status 0
#define Lowpower_Status 1
#define Help_Status 2

//***************
#include"Loc_def.h"

//****************
using namespace std;
class Location
{
public:
	Location();
	void cal(unsigned char* msg, int recvSize);
	void GetLocalTime(SYSTEMTIME *st);
	void setLocationCallBack(map<string, map<string, Tag_info>> map_record, map<string, map<string, Status_info>> map_status/*,LocationCallBack mLocationcallback, LocationCallBack_Status mLocationCallBack_Status, unsigned long pParam*/);
	Tag_record*  Load_Location_point(unsigned int &Tag_count);
	Status_record* Load_Location_status(unsigned int &Tag_count);
	void set_Anchor(Main_Anchor_Message* achor_main, unsigned int len_main, Anchor_Message* anchor_child, unsigned int len_child);
	map<string, map<string, Status_info>> Map_Location_Status_Record;
	TDOA _tdoa;
	Status_record* Tag_Status_record_temp = NULL;
private:
	unsigned long view_temp;
	//LocationCallBack_Status Locationcallback_Status_temp;
};

Location::Location()
{
	//int offset_x = 89;
	//int offset_y = 89;

	//map<int, Anchor_Message2> anchor_map_ffff;
	//anchor_map_ffff[65525] = { 0 + offset_x, 0 + offset_y, 2262 };
	//anchor_map_ffff[65526] = { 1717 + offset_x, 30 + offset_y, 757 };
	//anchor_map_ffff[65527] = { 1725 + offset_x, 681 + offset_y, 449 };
	//anchor_map_ffff[65528] = { 0 + offset_x, 939 + offset_y, 2193 };
	//anchor_map_ffff[65529] = { 1066 + offset_x, 0 + offset_y, 1272 };
	//anchor_map_ffff[65530] = { 3074 + offset_x, 53 + offset_y, 1074 };
	//anchor_map_ffff[65531] = { 1206 + offset_x, 645 + offset_y, 966 };
	//anchor_map_ffff[65532] = { 2677 + offset_x, 0 + offset_y, 811 };
	//anchor_map_ffff[65533] = { 406 + offset_x, 0 + offset_y, 1876 };
	//anchor_map_ffff[65534] = { 3076 + offset_x, 564 + offset_y, 905 };

	//map<int, Anchor_Message2> anchor_map_f000;
	//anchor_map_f000[65525] = { 0 + offset_x, 0 + offset_y, 1522 };
	//anchor_map_f000[65526] = { 1717 + offset_x, 30 + offset_y, 700 };
	//anchor_map_f000[65527] = { 1725 + offset_x, 681 + offset_y, 348 };
	//anchor_map_f000[65528] = { 0 + offset_x, 939 + offset_y, 1410 };
	//anchor_map_f000[65529] = { 1066 + offset_x, 0 + offset_y, 713 };
	//anchor_map_f000[65530] = { 3074 + offset_x, 53 + offset_y, 1797 };
	//anchor_map_f000[65531] = { 1206 + offset_x, 645 + offset_y, 174 };
	//anchor_map_f000[65532] = { 2677 + offset_x, 0 + offset_y, 1450 };
	//anchor_map_f000[65533] = { 406 + offset_x, 0 + offset_y, 1168 };
	//anchor_map_f000[65534] = { 3076 + offset_x, 564 + offset_y, 1697 };

	//map<int, Anchor_Message2> anchor_map_fff4;
	//anchor_map_fff4[65525] = { 0 + offset_x, 0 + offset_y, 677 };
	//anchor_map_fff4[65526] = { 1717 + offset_x, 30 + offset_y, 1584 };
	//anchor_map_fff4[65527] = { 1725 + offset_x, 681 + offset_y, 1478 };
	//anchor_map_fff4[65528] = { 0 + offset_x, 939 + offset_y, 396 };
	//anchor_map_fff4[65529] = { 1066 + offset_x, 0 + offset_y, 1030 };
	//anchor_map_fff4[65530] = { 3074 + offset_x, 53 + offset_y, 2886 };
	//anchor_map_fff4[65531] = { 1206 + offset_x, 645 + offset_y, 958 };
	//anchor_map_fff4[65532] = { 2677 + offset_x, 0 + offset_y, 2510 };
	//anchor_map_fff4[65533] = { 406 + offset_x, 0 + offset_y, 651 };
	//anchor_map_fff4[65534] = { 3076 + offset_x, 564 + offset_y, 2827 };

	//map<string, map<int, Anchor_Message2>> map_anchor_msg;
	////map_anchor_msg["FFFF"] = anchor_map_ffff;
	//map_anchor_msg["F000"] = anchor_map_f000;
	//map_anchor_msg["FFF4"] = anchor_map_fff4;

	//TDOA tdoa(map_anchor_msg);
	//_tdoa = tdoa;
}

constexpr char hexmap[] = { '0', '1', '2', '3', '4', '5', '6', '7',
'8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

std::string hexStr(unsigned char *data, int len)
{
	std::string s(len * 2, ' ');
	for (int i = 0; i < len; ++i) {
		s[2 * i] = hexmap[(data[i] & 0xF0) >> 4];
		s[2 * i + 1] = hexmap[data[i] & 0x0F];
	}
	return s;
}

using std::map;


void Location::GetLocalTime(SYSTEMTIME *st)
{
if(st){
struct tm *pst = NULL;
time_t t = time(NULL);
pst = localtime(&t);
memcpy(st,pst,sizeof(SYSTEMTIME));
st->wYear += 1900;
}
}

void Location::cal(unsigned char* msg, int msg_size)
{
	std::string msg_hex = hexStr(msg, msg_size);
	//printf("DATA:%s\n", msg_hex.c_str());
	unsigned __int64 time = (unsigned __int64)((((unsigned __int64)msg[1] << 32) & 0xFF00000000) + (((unsigned __int64)(msg[2] << 24)) & 0xFF000000) + (((unsigned __int64)(msg[3] << 16)) & 0xFF0000) + (((unsigned __int64)(msg[4] << 8)) & 0xFF00) + (((unsigned __int64)(msg[5])) & 0xFF));
	int msg_type = msg[0];
	std::string broadcast = "";
	int antenna = 0;
	int Threshold = 0;
	int count = 0;
	int Status_warning = msg[16];
	if (msg_type == 2)// �DAnchor�H��
	{
		broadcast = broadcast.append(msg_hex, 12, 4);
		antenna = msg[14] * 256 + msg[15];
		count = msg[17] * 256 + msg[18];
		Threshold = msg[19] * 256 + msg[20];
	}
	else if (msg_type == 1)//Tag�H��
	{
		broadcast = broadcast.append(msg_hex, 12, 16);
		antenna = msg[14] * 256 + msg[15];
		count = msg[17] * 256 + msg[18];
		Threshold = msg[19] * 256 + msg[20];

		//if (Status_warning == Lowpower_Status)
		//{
		//	//Locationcallback_Status_temp(broadcast, Status_warning, view_temp);
		//	TRACE(_T("LowPower\n"));
		//}
		//else if (Status_warning == Help_Status)
		//{
		//	//Locationcallback_Status_temp(broadcast, Status_warning, view_temp);
		//	TRACE(_T("Help\n"));
		//}
		//Location_Record::Map_Location_Record[broadcast] = Status_warning;

		if (Map_Location_Status_Record.find(broadcast) != Map_Location_Status_Record.end())
		{
			map<string, Status_info>::iterator first = Map_Location_Status_Record[broadcast].end();
			first--;
			if (first->second.Status != Status_warning)
			{
				SYSTEMTIME st;
				GetLocalTime(&st);
				//string strDate_time;
				char * strDate_time = new char[50];
				char str_key_temp[100] = { 0 };
				string str_key;
				//strDate_time.Format(_T("%4d/%2d/%2d/%2d:%2d:%2d"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
				sprintf( strDate_time, "%4d/%2d/%2d/%2d:%2d:%2d",st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
				for (size_t i = 0; i < sizeof(strDate_time) ; i++)
					str_key_temp[i] = (char)strDate_time[i];
				str_key = str_key_temp;
				thread_lock.lock(); //mike
				Map_Location_Status_Record[broadcast][str_key].Status = Status_warning;
				thread_lock.unlock(); //mike
									  //				Map_Location_Status_Record[broadcast][str_key].update = "true";
				if (Map_Location_Status_Record[broadcast].size()>20)
				{
					thread_lock.lock(); //mike
					map<string, Status_info>::iterator erase_first = Map_Location_Status_Record[broadcast].begin();
					Map_Location_Status_Record[broadcast].erase(erase_first);
					thread_lock.unlock(); //mike
				}
			}
		}
		else
		{
			thread_lock.lock(); //mike
			SYSTEMTIME st;
			GetLocalTime(&st);
			//string strDate_time;
			char * strDate_time = new char[50];
			char str_key_temp[100] = { 0 };
			string str_key;
			//strDate_time.Format(_T("%4d/%2d/%2d/%2d:%2d:%2d"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
			sprintf( strDate_time, "%4d/%2d/%2d/%2d:%2d:%2d",st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
			for (size_t i = 0; i < sizeof(strDate_time) ; i++)
				str_key_temp[i] = (char)strDate_time[i];
			str_key = str_key_temp;
			Map_Location_Status_Record[broadcast][str_key].Status = Status_warning;
			//			Map_Location_Status_Record[broadcast][str_key].update = "true";
			thread_lock.unlock(); //mike
		}
		//SYSTEMTIME st;
		//GetLocalTime(&st);
		//CString strDate_time;
		//char str_key_temp[100] = { 0 };
		//string str_key;
		//strDate_time.Format(_T("%4d/%2d/%2d/%2d:%2d:%2d"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
		//for (size_t i = 0; i < strDate_time.GetLength(); i++)		
		//	str_key_temp[i] = strDate_time[i];
		//str_key = str_key_temp;
		//
		//Map_Location_Status_Record[broadcast][str_key].Status = Status_warning;
		//Map_Location_Status_Record[broadcast][str_key].update = "true";
		//if (Map_Location_Status_Record[broadcast].size()>20)
		//{
		//	map<string, Status_info>::iterator first = Map_Location_Status_Record[broadcast].begin();
		//	Map_Location_Status_Record[broadcast].erase(first);
		//}

		//if(Status_warning!=)
		//str_key = strDate_time.GetString;
		//char* s_char = W2A(strDate_time);
		//strTime.Format(_T("%2d:%2d:%2d"), st.wHour, st.wMinute, st.wSecond);
		//st.Format(" %d-%d-%d", st.wYear, st.wMonth, st.wDay);
		//TDOA::Map_Location_Record[broadcast][0].Status = Status_warning;
		//Locationcallback_Status_temp(broadcast, Status_warning, view_temp);
		//TRACE(_T("Status_warning%d\n"), Status_warning);
	}
	else
		return;


	_tdoa.get5(time, broadcast, antenna, count, Threshold);
}

void Location::setLocationCallBack(map<string, map<string, Tag_info>> map_record, map<string, map<string, Status_info>> map_status/*,LocationCallBack mLocationcallback, LocationCallBack_Status mLocationCallBack_Status, unsigned long pParam*/)
{
	_tdoa.setLocationCallBack(map_record, map_status/*,mLocationcallback, mLocationCallBack_Status, pParam*/);
	//Locationcallback_Status_temp = mLocationCallBack_Status;
	//view_temp = pParam;
}
Tag_record*  Location::Load_Location_point(unsigned int &Tag_count)
{
	return _tdoa.Load_Location_point(Tag_count);
}
Status_record* Location::Load_Location_status(unsigned int &Tag_count)
{
	thread_lock.lock(); //mike
	delete[] Tag_Status_record_temp;
	map<string, map<string, Status_info>> Map_Location_Status_Record_temp = Map_Location_Status_Record;
	Tag_Status_record_temp = new Status_record[Map_Location_Status_Record_temp.size()];
	int count = 0;
	for (map<string, map<string, Status_info>>::iterator it = Map_Location_Status_Record_temp.begin(); it != Map_Location_Status_Record_temp.end(); it++)
	{
		Tag_Status_record_temp[count].Tag_ID = it->first;
		Tag_Status_record_temp[count].Info_count = 0;
		for (map<string, Status_info>::iterator it1 = Map_Location_Status_Record_temp[it->first].begin(); it1 != Map_Location_Status_Record_temp[it->first].end(); it1++)
		{
			if (Tag_Status_record_temp[count].Info_count >= 20)
				break;
			Tag_Status_record_temp[count].Status_info_record[Tag_Status_record_temp[count].Info_count].System_Time = it1->first;
			Tag_Status_record_temp[count].Status_info_record[Tag_Status_record_temp[count].Info_count].Status = it1->second.Status;
			Tag_Status_record_temp[count].Info_count++;
		}
		count++;
	}
	Tag_count = count;
	thread_lock.unlock(); //mike
	return Tag_Status_record_temp;
}
void Location::set_Anchor(Main_Anchor_Message* achor_main, unsigned int len_main, Anchor_Message* anchor_child, unsigned int len_child)
{
	map<string, map<int, Anchor_Message2>> map_anchor_msg;
	map<string, map < int, map<int, Anchor_Message2>>> map_group_anchor_msg;
	for (size_t i = 0; i < len_main; i++)
	{
		int x_main = achor_main[i].x;
		int y_main = achor_main[i].y;
		int id_main = achor_main[i].id;
		std::string str_id_main(4, ' ');
		str_id_main[0] = hexmap[(id_main & 0xF000) >> 12];
		str_id_main[1] = hexmap[(id_main & 0x0F00) >> 8];
		str_id_main[2] = hexmap[(id_main & 0x00F0) >> 4];
		str_id_main[3] = hexmap[(id_main & 0x000F)];

		//_tdoa.mainAnchor_msg[str_id_main] = { 0,0, id_main, x_main, y_main };
		/*
		int item = 0;
		int main_group = 0;
		int id = 0;
		int x = 0;
		int y = 0;
		*/
		//int distance = 0;
		_tdoa.mainAnchor_msg[str_id_main].item = 0 ;
		_tdoa.mainAnchor_msg[str_id_main].main_group = 0 ;
		_tdoa.mainAnchor_msg[str_id_main].id = id_main ;
		_tdoa.mainAnchor_msg[str_id_main].x = x_main ;
		_tdoa.mainAnchor_msg[str_id_main].y = y_main ;

		map<int, Anchor_Message2> anchor_map;
		for (size_t j = 0; j < len_child; j++)
		{
			anchor_map.clear();
			int item1 = anchor_child[j].item;
			for (size_t k = 0; k < len_child; k++)
			{
				int item = anchor_child[k].item;
				if ((item1 != item))
					continue;
				if ((anchor_child[k].main_group != id_main))
					continue;
				int x = anchor_child[k].x;
				int y = anchor_child[k].y;
				int distance = (int)abs(sqrt(pow((x - x_main), 2) + pow((y - y_main), 2)));
				//anchor_map[anchor_child[k].id] = { x, y, distance };
				anchor_map[anchor_child[k].id].x =x ;// = (Anchor_Message2){ .x=x, .y=y, .distance=distance };
				anchor_map[anchor_child[k].id].y =y ;
				anchor_map[anchor_child[k].id].distance = distance ;
			}
			if (anchor_map.size()>0)
				map_group_anchor_msg[str_id_main][item1] = anchor_map;
		}
		map_anchor_msg[str_id_main] = anchor_map;

	}
	_tdoa.setAnchor(map_anchor_msg, map_group_anchor_msg);
}
