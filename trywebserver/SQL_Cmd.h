#include <string>
#include <string.h>
#include <iostream>
#include <map>

#include <fstream>
#include <bitset>
#include "base64.h"
#include "DBPool.h"
//#include "Alarm.h"
#include <stdio.h>
#include <locale.h>
#include <wchar.h>

#include <vector>
#include "json.hpp"
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

using json = nlohmann::json;
using namespace std;


extern DBPool  g_connpool ;
extern Connection *g_con ;//= connpool.GetConnection();;
extern Statement *g_state;
extern ResultSet *g_result;

extern string sql_cmd_list[];

extern string sql_create_database  ;

extern string sql_create_table  ;
extern string sql_create_locus  ;
extern string sql_create_map    ;
extern string sql_create_group  ;
extern string sql_create_anchor_info    ;
extern string sql_create_group_anchor   ;


bool Construct_sql_cmd() ;
bool SQL_Open();
void SQL_Close();
int SQL_ExecuteUpdate( string in ) ;
void SQL_Init();

bool SQL_Open_single( Connection *&c, Statement *&s, ResultSet *&r );
void SQL_Close_single( Connection *&c, Statement *&s, ResultSet *&r );
int SQL_ExecuteUpdate_single( Statement *&state, string input );



json Call_SQL_func( string func_name, json func_arg );

int SQL_AddAnchor( Statement *&state, string id, string x, string y, string type );
int SQL_EditAnchor_Info( Statement *&state, json func_arg );

int SQL_AddGroup_Info( Statement *&state, string group_id, string group_name, string main_anchor_id, string mode, string mode_value, string fence );
int SQL_EditGroup_Info( Statement *&state, json func_arg );


int SQL_AddMap( Statement *&state, string map_name, string map_file, string map_scale, string map_file_ext ) ;
int SQL_EditMap( Statement *&state, json func_arg ) ;
int SQL_DeleteMap( Statement *&state, string id );

int SQL_AddGroup_Anchor( Statement *&state, string group_id, string main_anchor_id ) ;
int SQL_AddMap_Group( Statement *&state, string map_id, string group_id ) ;
int SQL_DeleteMap_Group_by_one_id( Statement *&state, string m_id ) ;
int SQL_DeleteMap_Group_by_duo_id( Statement *&state, string m_id, string g_id ) ;



int SQL_AddLocus( Statement *&state, string tag_id, string x, string y, string group_id, string date, string time ) ;
int SQL_AddLocus_combine( Statement *&state, string tag_id, string x, string y, string group_id,  string time ) ;
int SQL_AddEvent( Statement *&state, string tag_id, string alarm_type, string status, string time ) ;

json update_staff_list( json from_sql_latest_list ) ; // only for server cache ( for match alarm list ), not web request.

int SQL_AddStaff( Statement *&state, json func_arg ) ;
int SQL_EditStaff( Statement *&state, json func_arg ) ;
int SQL_DeleteStaff( Statement *&state, string number ) ;


int SQL_AddDepartment( Statement *&state, json func_arg ) ;
int SQL_EditDepartment( Statement *&state, json func_arg ) ;
int SQL_DeleteDepartment( Statement *&state, string c_id ) ;

int SQL_AddJobTitle( Statement *&state, json func_arg ) ;
int SQL_EditJobTitle( Statement *&state, json func_arg ) ;
int SQL_DeleteJobTitle( Statement *&state, string c_id ) ;


int SQL_AddUserType( Statement *&state, json func_arg ) ;
int SQL_EditUserType( Statement *&state, json func_arg ) ;
int SQL_DeleteUserType( Statement *&state, string type ) ;


//** Time HEAD
int SQL_AddTime_Slot( Statement *&state, string time_slot_name, string Mon_start, string Mon_end, string Tue_start, string Tue_end,
                      string Wed_start, string Wed_end, string Thu_start, string Thu_end, string Fir_start, string Fir_end,
                      string Sat_start, string Sat_end, string Sun_start, string Sun_end );
int SQL_EditTime_Slot( Statement *&state, json func_arg );
int SQL_DeleteTime_Slot( Statement *&state, string id );

int SQL_AddTimeSlot_Group( Statement *&state, string time_group_id, string time_slot_id );
int SQL_DeleteTime_Slot_Group( Statement *&state, string time_group_id );

int SQL_AddTime_Group( Statement *&state, string time_group_name );
int SQL_DeleteTime_Group( Statement *&state, string time_group_id );
int SQL_EditTime_Group( Statement *&state, json func_arg );
//** Time TAIL ******************/


//** Alarm HEAD ***************
int SQL_AddAlarm_Info( Statement *&state, string alarm_name, string alarm_switch, string alarm_value, string alarm_group_id );
int SQL_EditAlarmInfo( Statement *&state, json func_arg );
int SQL_DeleteAlarm_Info( Statement *&state, string id );

int SQL_AddAlarm_Group_Info( Statement *&state, string alarm_group_name, string time_group_id );
int SQL_EditAlarmGroupInfo( Statement *&state, json func_arg );
int SQL_DeleteAlarm_Group_Info( Statement *&state, string id );
//** Alarm TAIL *******************/



int SQL_multiEdit_StaffDepartment( Statement *&state, string number, string department_id ) ;
int SQL_multiEdit_StaffType( Statement *&state, string number, string type ) ;
int SQL_multiEdit_StaffJobTitle( Statement *&state, string number, string jobTitle_id ) ;
int SQL_multiEdit_StaffSetColor( Statement *&state, string number, string color_type ) ;




int SQL_OFF_SafeUpdate( Statement *&state );
int SQL_DeleteAnchor_Info( Statement *&state, string id );

int SQL_DeleteGroup_Info( Statement *&state, string id );
int SQL_DeleteGroup_Anchor_by_one_id( Statement *&state, string gid );
int SQL_DeleteGroup_Anchor_by_duo_id( Statement *&state, string gid, string anid );

int SQL_DeleteTag( Statement *&state, string id );
int SQL_TruncateTable( Statement *&state, string id ) ;


json json_SQL_GetAnchors_info( Statement *&state, ResultSet *&result );
json json_SQL_GetGroups_info( Statement *&state, ResultSet *&result );
json json_SQL_GetMaps( Statement *&state, ResultSet *&result );

json json_SQL_GetOneStaffPhoto( Statement *&state, ResultSet *&result, json func_arg );
json json_SQL_GetAnchorsInMap( Statement *&state, ResultSet *&result, json func_arg );


json json_SQL_Get_One_Staff( Statement *&state, ResultSet *&result, json func_arg );
json json_SQL_GetStaffs( Statement *&state, ResultSet *&result );
json json_SQL_GetDepartment_relation( Statement *&state, ResultSet *&result );
json json_SQL_GetJobTitle_relation( Statement *&state, ResultSet *&result );
json json_SQL_GetDepartment_relation_list( Statement *&state, ResultSet *&result );
json json_SQL_GetJobTitle_relation_list( Statement *&state, ResultSet *&result );
json json_SQL_GetUserTypes( Statement *&state, ResultSet *&result );

// Alarm START
json json_alarm_GroupBy_id( json group, json single ) ;
////json json_SQL_GetAlarmTypes( Statement *&state, ResultSet *&result );
json json_SQL_GetAlarmInfo_list( Statement *&state, ResultSet *&result );
json json_SQL_GetAlarmGroup_list( Statement *&state, ResultSet *&result );
// Alarm END


json json_time_GroupBy_id( json group, json group_single, json single );

json json_SQL_GetTimeSlot_list( Statement *&state, ResultSet *&result );
json json_SQL_GetTimeGroup_list( Statement *&state, ResultSet *&result );
json json_SQL_GetTimeSlot_group( Statement *&state, ResultSet *&result );



json json_SQL_Return_inserted_dept_id( Statement *&state, ResultSet *&result );
json json_SQL_Return_inserted_job_id( Statement *&state, ResultSet *&result );
json json_SQL_Return_alarm_gid( Statement *&state, ResultSet *&result );
json json_SQL_Return_inserted_map_id( Statement *&state, ResultSet *&result );

json json_SQL_GetGroup_Anchors( Statement *&state, ResultSet *&result );
json json_SQL_GetMap_Groups( Statement *&state, ResultSet *&result );

json json_SQL_GetTags_info( Statement *&state, ResultSet *&result );
json json_SQL_GetSingleLocus( Statement *&state, string tag_id, string start_date, string start_time, string end_date, string end_time, ResultSet *&result ) ;
json json_SQL_GetSingleLocus_combine( Statement *&state, string tag_id, string start_date, string start_time, string end_date, string end_time, ResultSet *&result ) ;
json json_SQL_GetSingleLocus_combine_hour( Statement *&state, string tag_id, string start_date, string start_time, string end_date, string end_time, ResultSet *&result ) ;
json json_SQL_GetSingleLocus_combine_min( Statement *&state, string tag_id, string start_date, string start_time, string end_date, string end_time, ResultSet *&result ) ;

void Request_Add2AlarmList( string temp_id, string temp_status, string temp_date_time ) ;
json Request_GetAlarmList() ;


void SQL_Update_locus_index( string date );
void SQL_Update_locus_index_hour( string datetime );
void SQL_Update_locus_index_hour_min( string datetime ) ;


string Str2Time_BackDate( string date );
string Str2Time_ShiftDate( string date );
string Str2Time_ShiftHour( string date ) ;
string Str2Time_Hour( string date, string time );
string Str2Time_ShiftMin( string date ) ;
string Str2Time_Min( string date, string time );

string date_part( string date );
string time_part( string date );

string Only_get_Time( string tmp );
string Only_get_Date( string tmp );

string SQL_Get_indexOf_locus_index_by_date( string date );
string SQL_Get_date_by_indexOf_locus_index( string rownum );
string SQL_Get_indexOf_locus_index_by_hour( string date_hour );
string SQL_Get_indexOf_locus_index_by_next_hour( string rownum );
string SQL_Get_indexOf_locus_index_by_min( string date_hour ) ;
string SQL_Get_indexOf_locus_index_by_next_min( string rownum );



json Find_staff_byTag( string tag_id ) ;
json Find_alarm_group_byStaff( json aStaff ) ;
json Find_single_alarm_byAlarmName( json the_alarm_group, string alarm_name ) ;
json Find_time_group_byTime_gid( string time_group_id ) ;
bool Walk_single_time_group_byWeekDay( json target_time_slot, int WeekDay, string tag_time );




bool Time_In_Interval( string input, string starting, string ending) ;
json package2json( string coordinate_x, string coordinate_y, string map_id, string time ) ;



class Alarm
{
private:


public :
    static json visible_list ; // last next tag_list
    static json invisible_list ;
    static json alarm_status_list ;
    static json alarm_top50_list ;

    json Call_Alarm_func( string func_name, json func_arg ) ;


    bool remove_from_invisible_list( string target_tag ) ;
    bool search_visible_list( string target_tag ) ;
    bool remove_from_status_list( string target_tag ) ;
    json add_to_alarm_top50_list( json j_list, json input ) ;
    json combine_staff_info_to_alarm_list( json staff, json alarm ) ;



    static int bar;

};
