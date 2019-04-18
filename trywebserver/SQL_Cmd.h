#include <string>
#include <string.h>
#include <iostream>
#include <map>

#include "DBPool.h"
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

int SQL_AddAnchor( Statement *&state, string id, string x, string y, string type ) ;
int SQL_AddGroup( Statement *&state, string group_id, string main_anchor_id, string mode, string mode_value, string fence ) ;
int SQL_AddMap( Statement *&state, string map_id, string map_name, string map_path ) ;

int SQL_AddGroup_Anchor( Statement *&state, string group_id, string main_anchor_id ) ;
int SQL_AddMap_Group( Statement *&state, string map_id, string group_id ) ;

int SQL_AddLocus( Statement *&state, string tag_id, string x, string y, string group_id, string date, string time ) ;
int SQL_AddLocus_combine( Statement *&state, string tag_id, string x, string y, string group_id,  string time ) ;
int SQL_AddEvent( Statement *&state, string tag_id, string status, string time ) ;

int SQL_AddStaff( Statement *&state, json func_arg ) ;
int SQL_AddDepartment( Statement *&state, json func_arg ) ;
int SQL_EditDepartment( Statement *&state, json func_arg ) ;
int SQL_DeleteDepartment( Statement *&state, string c_id ) ;



int SQL_OFF_SafeUpdate( Statement *&state );
int SQL_DeleteAnchor( Statement *&state, string id );
int SQL_DeleteMap( Statement *&state, string id );
int SQL_DeleteGroup( Statement *&state, string id );
int SQL_DeleteGroup_Anchor( Statement *&state, string gid, string anid );
int SQL_DeleteTag( Statement *&state, string id );
int SQL_TruncateTable( Statement *&state, string id ) ;


json json_SQL_GetAnchors_info( Statement *&state, ResultSet *&result );
json json_SQL_GetGroups_info( Statement *&state, ResultSet *&result );
json json_SQL_GetMaps( Statement *&state, ResultSet *&result );

json json_SQL_GetStaffs( Statement *&state, ResultSet *&result );
json json_SQL_GetDepartment_relation( Statement *&state, ResultSet *&result );
json json_SQL_Return_inserted_id( Statement *&state, ResultSet *&result );


json json_SQL_GetGroup_Anchors( Statement *&state, ResultSet *&result );
json json_SQL_GetMap_Groups( Statement *&state, ResultSet *&result );

json json_SQL_GetTags_info( Statement *&state, ResultSet *&result );
json json_SQL_GetSingleLocus( Statement *&state, string tag_id, string start_date, string start_time, string end_date, string end_time, ResultSet *&result ) ;
json json_SQL_GetSingleLocus_combine( Statement *&state, string tag_id, string start_date, string start_time, string end_date, string end_time, ResultSet *&result ) ;
json json_SQL_GetSingleLocus_combine_hour( Statement *&state, string tag_id, string start_date, string start_time, string end_date, string end_time, ResultSet *&result ) ;
json json_SQL_GetSingleLocus_combine_min( Statement *&state, string tag_id, string start_date, string start_time, string end_date, string end_time, ResultSet *&result ) ;



void SQL_Update_locus_index( string date );
void SQL_Update_locus_index_hour( string datetime );
void SQL_Update_locus_index_hour_min( string datetime ) ;


string Str2Time_BackDate( string date );
string Str2Time_ShiftDate( string date );
string Str2Time_ShiftHour( string date ) ;
string Str2Time_Hour( string date , string time );
string Str2Time_ShiftMin( string date ) ;
string Str2Time_Min( string date , string time );

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



bool Time_In_Interval( string input, string starting, string ending) ;
json package2json( string coordinate_x, string coordinate_y, string map_id, string time ) ;
