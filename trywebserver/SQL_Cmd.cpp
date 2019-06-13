#include "SQL_Cmd.h"

DBPool  g_connpool = DBPool::GetInstance();

Connection *g_con = nullptr;//= connpool.GetConnection();;
Statement *g_state = nullptr;
ResultSet *g_result = nullptr;

//Connection *g_con2 = nullptr;//= connpool.GetConnection();;
//Statement *g_state2 = nullptr;
//ResultSet *g_result2 = nullptr;

json j_response ;
json j_staff_list;
json j_alarm_list;
json j_time_list;


string sql_create_database  = "create database IF NOT EXISTS `PositioningSystem` character set utf8" ;


string sql_create_table     = "CREATE TABLE IF NOT EXISTS  " ;


string sql_create_locus1    = "locus ( id INT UNSIGNED NOT NULL AUTO_INCREMENT, PRIMARY KEY (id), tag_id VARCHAR(16), " ;
string sql_create_locus2    = "coordinate_x INT UNSIGNED, coordinate_y INT UNSIGNED, group_id SMALLINT UNSIGNED, `date` date,`time`time(2) )";
string sql_create_locus     = sql_create_table + sql_create_locus1 + sql_create_locus2 ; // date and time separated store.


string sql_create_map1      = "map_info ( map_id INT UNSIGNED NOT NULL AUTO_INCREMENT, PRIMARY KEY (map_id), map_name VARCHAR(16), " ;
string sql_create_map2      = "map_file MEDIUMBLOB, map_scale VARCHAR(10), map_file_ext VARCHAR(5) )";
string sql_create_map_info  = sql_create_table + sql_create_map1 + sql_create_map2 ;


string sql_create_group1        = "group_info ( group_id SMALLINT UNSIGNED NOT NULL AUTO_INCREMENT, PRIMARY KEY (group_id), group_name VARCHAR(16), " ;
string sql_create_group2        = "main_anchor_id VARCHAR(16), mode VARCHAR(8), mode_value VARCHAR(8), fence VARCHAR(8) )";
string sql_create_group_info    = sql_create_table + sql_create_group1 + sql_create_group2 ;

string sql_create_anchor1       = "anchor_info ( anchor_id SMALLINT UNSIGNED NOT NULL AUTO_INCREMENT, PRIMARY KEY (anchor_id), " ;
string sql_create_anchor2       = "set_x INT UNSIGNED, set_y INT UNSIGNED, anchor_type VARCHAR(16) )";
string sql_create_anchor_info   = sql_create_table + sql_create_anchor1 + sql_create_anchor2 ;

string sql_create_group_anchor1 = "group_anchors ( id INT UNSIGNED NOT NULL AUTO_INCREMENT, PRIMARY KEY (id), group_id SMALLINT UNSIGNED, " ;
string sql_create_group_anchor2 = "anchor_id SMALLINT UNSIGNED )";
string sql_create_group_anchor  = sql_create_table + sql_create_group_anchor1 + sql_create_group_anchor2 ;

string sql_create_map_group1    = "map_groups ( id INT UNSIGNED NOT NULL AUTO_INCREMENT, PRIMARY KEY (id), map_id INT UNSIGNED, " ;
string sql_create_map_group2    = "group_id SMALLINT UNSIGNED )";
string sql_create_map_group     = sql_create_table + sql_create_map_group1 + sql_create_map_group2 ;




string sql_create_tag1  = "tag_info ( tag_id VARCHAR(16) NOT NULL, PRIMARY KEY (tag_id), tag_name VARCHAR(16), " ;
string sql_create_tag2  = "pic_path VARCHAR(128) )";
string sql_create_tag   = sql_create_table + sql_create_tag1 + sql_create_tag2 ;




string sql_create_locus_combine1    = "locus_combine ( id INT UNSIGNED NOT NULL AUTO_INCREMENT, PRIMARY KEY (id), tag_id VARCHAR(16), " ;
string sql_create_locus_combine2    = "coordinate_x INT UNSIGNED, coordinate_y INT UNSIGNED, group_id SMALLINT UNSIGNED, `time`datetime(2) )";
string sql_create_locus_combine     = sql_create_table + sql_create_locus_combine1 + sql_create_locus_combine2 ; // date and time combined store.





string sql_create_locus_index1  = "locus_index ( `date`date NOT NULL , PRIMARY KEY (date), " ;
string sql_create_locus_index2  = "index_id INT UNSIGNED  )";
string sql_create_locus_index   = sql_create_table + sql_create_locus_index1 + sql_create_locus_index2 ;


string sql_create_locus_index_hour1  = "locus_index_hour ( id INT UNSIGNED NOT NULL AUTO_INCREMENT, PRIMARY KEY (id), `datetime`datetime(2), INDEX index_datetime(`datetime`), " ;
string sql_create_locus_index_hour2  = "index_id INT UNSIGNED  )";
string sql_create_locus_index_hour   = sql_create_table + sql_create_locus_index_hour1 + sql_create_locus_index_hour2 ;


string sql_create_locus_index_min1  = "locus_index_min ( id INT UNSIGNED NOT NULL AUTO_INCREMENT, PRIMARY KEY (id), `datetime`datetime(2), INDEX index_datetime(`datetime`), " ;
string sql_create_locus_index_min2  = "index_id INT UNSIGNED  )";
string sql_create_locus_index_min   = sql_create_table + sql_create_locus_index_min1 + sql_create_locus_index_min2 ;


string sql_create_event1    = "event ( id INT UNSIGNED NOT NULL AUTO_INCREMENT, PRIMARY KEY (id), tag_id VARCHAR(16), " ;
string sql_create_event2    = "alarm_type VARCHAR(10), status VARCHAR(10), `time`datetime(2) )";
string sql_create_event     = sql_create_table + sql_create_event1 + sql_create_event2 ;




string sql_create_staff1    = "staff ( id INT UNSIGNED NOT NULL AUTO_INCREMENT, PRIMARY KEY (id), number VARCHAR(40) NOT NULL, UNIQUE (number), INDEX index_staff(number), " ;
string sql_create_staff2    = string("") + "tag_id VARCHAR(16), INDEX index_tag_id( tag_id ), Name VARCHAR(40)" + ",lastName VARCHAR(40)" + ", firstName VARCHAR(40)" + ",EnglishName VARCHAR(40) ," ;
string sql_create_staff3    = string("") + "gender VARCHAR(10)," + "card_id VARCHAR(40)," + "status VARCHAR(40)," + "color_type VARCHAR(10)," + "color VARCHAR(10)," + "department_id INT UNSIGNED," + "jobTitle_id INT UNSIGNED," +  "type VARCHAR(40),";
string sql_create_staff4    = string("") + "birthday VARCHAR(10)," + "dateEntry VARCHAR(10)" + ", dateLeave VARCHAR(10)" + ", school VARCHAR(40)" + ", education VARCHAR(10)"
                              + ", phoneJob VARCHAR(20)" + ", phoneSelf VARCHAR(20)" + ", mail VARCHAR(60)" + ", address TEXT" + ", note TEXT" + ", photo MEDIUMBLOB" + ", exist INT"
                              + ", grade VARCHAR(20)"  +  ", tech_grade VARCHAR(20)" +  ", file_ext VARCHAR(5)" + ", alarm_group_id INT UNSIGNED" + ")";
string sql_create_staff     = sql_create_table + sql_create_staff1 + sql_create_staff2 + sql_create_staff3 + sql_create_staff4 ;



string sql_create_card_correspond1  = "card_correspond ( id INT UNSIGNED NOT NULL AUTO_INCREMENT, PRIMARY KEY (id), card VARCHAR(24) NOT NULL, INDEX index_card( card ), UNIQUE (card)," ;
string sql_create_card_correspond2  = "number VARCHAR(40) , status TINYINT, `time`datetime(2) )";
string sql_create_card_correspond   = sql_create_table + sql_create_card_correspond1 + sql_create_card_correspond2 ;

string sql_create_department_relation1  = "department_relation ( id INT UNSIGNED NOT NULL AUTO_INCREMENT, PRIMARY KEY (id), " ;
string sql_create_department_relation2  = "parent VARCHAR(40), p_id INT UNSIGNED, children VARCHAR(40), c_id INT UNSIGNED, color VARCHAR(10) )";
string sql_create_department_relation   = sql_create_table + sql_create_department_relation1 + sql_create_department_relation2 ;


string sql_create_jobTitle_relation1  = "jobTitle_relation ( id INT UNSIGNED NOT NULL AUTO_INCREMENT, PRIMARY KEY (id), " ;
string sql_create_jobTitle_relation2  = "parent VARCHAR(40), p_id INT UNSIGNED, children VARCHAR(40), c_id INT UNSIGNED, color VARCHAR(10) )";
string sql_create_jobTitle_relation   = sql_create_table + sql_create_jobTitle_relation1 + sql_create_jobTitle_relation2 ;


string sql_create_user_type1  = "user_type (  type VARCHAR(40), PRIMARY KEY (type), " ;
string sql_create_user_type2  = " color VARCHAR(10) )";
string sql_create_user_type   = sql_create_table + sql_create_user_type1 + sql_create_user_type2 ;


//********************
//*
string sql_create_time_group_info1  = "time_group_info ( id INT UNSIGNED NOT NULL AUTO_INCREMENT, PRIMARY KEY (id), " ;
string sql_create_time_group_info2  = " time_group_name VARCHAR(10) )";
string sql_create_time_group_info   = sql_create_table + sql_create_time_group_info1 + sql_create_time_group_info2 ;
// ex. this is a one time_group info : 12,time_group_name
//*/

string sql_create_time_slot_info1  = "time_slot_info (  id INT UNSIGNED NOT NULL AUTO_INCREMENT, PRIMARY KEY (id), " ;
string sql_create_time_slot_info2  = " time_slot_name VARCHAR(10), Mon_start VARCHAR(10), Mon_end VARCHAR(10), Tue_start VARCHAR(10), Tue_end VARCHAR(10), " ;
string sql_create_time_slot_info3  = " Wed_start VARCHAR(10), Wed_end VARCHAR(10), Thu_start VARCHAR(10), Thu_end VARCHAR(10), Fri_start VARCHAR(10), Fri_end VARCHAR(10), " ;
string sql_create_time_slot_info4  = " Sat_start VARCHAR(10), Sat_end VARCHAR(10), Sun_start VARCHAR(10), Sun_end VARCHAR(10) )";
string sql_create_time_slot_info   = sql_create_table + sql_create_time_slot_info1 + sql_create_time_slot_info2 + sql_create_time_slot_info3 + sql_create_time_slot_info4 ;
// ex. this is a one time_slot_info : 54,time_A, 13:25:55, 18:28:65
// ex. this is a one time_slot_info : 55,time_C, 13:25:55, 18:28:65

//*
string sql_create_time_slot_group1  = "time_slot_group (  id INT UNSIGNED NOT NULL AUTO_INCREMENT, PRIMARY KEY (id), " ;
string sql_create_time_slot_group2  = " time_group_id INT UNSIGNED , time_slot_id INT UNSIGNED )";
string sql_create_time_slot_group   = sql_create_table + sql_create_time_slot_group1 + sql_create_time_slot_group2 ;
// ex. this is a one time_slot_group (correspond) : 10, 12(time_group_id), 54(single time_slot_info_id).
// ex. this is a one time_slot_group (correspond) : 11, 12(time_group_id), 55(single time_slot_info_id).
//****************************/


string sql_create_alarm_info1  = "alarm_info (  id INT UNSIGNED NOT NULL AUTO_INCREMENT, PRIMARY KEY (id), " ;
string sql_create_alarm_info2  = " alarm_name VARCHAR(10), alarm_switch VARCHAR(5), alarm_value INT, alarm_group_id INT UNSIGNED )";
string sql_create_alarm_info   = sql_create_table + sql_create_alarm_info1 + sql_create_alarm_info2 ;

//string sql_create_alarm_group1  = "alarm_group (  id INT UNSIGNED NOT NULL AUTO_INCREMENT, PRIMARY KEY (id), " ;
//string sql_create_alarm_group2  = " alarm_group_info_id INT UNSIGNED , alarm_info_id INT UNSIGNED )";
//string sql_create_alarm_group   = sql_create_table + sql_create_alarm_group1 + sql_create_alarm_group2 ;


string sql_create_alarm_group_info1  = "alarm_group_info ( id INT UNSIGNED NOT NULL AUTO_INCREMENT, PRIMARY KEY (id), " ;
string sql_create_alarm_group_info2  = " alarm_group_name VARCHAR(20), time_group_id INT UNSIGNED  )";
string sql_create_alarm_group_info   = sql_create_table + sql_create_alarm_group_info1 + sql_create_alarm_group_info2 ;


// ******************** fence *****************
string sql_create_fence_point1  = "fence_point (  id INT UNSIGNED NOT NULL AUTO_INCREMENT, PRIMARY KEY (id), " ;
string sql_create_fence_point2  = " point_x INT UNSIGNED , point_y INT UNSIGNED, fence_id INT UNSIGNED, point_order TINYINT )";
string sql_create_fence_point   = sql_create_table + sql_create_fence_point1 + sql_create_fence_point2 ;

string sql_create_fence_info1  = "fence_info (  fence_id INT UNSIGNED NOT NULL AUTO_INCREMENT, PRIMARY KEY (fence_id), " ;
string sql_create_fence_info2  = " fence_name VARCHAR(10), map_id INT UNSIGNED, list_type VARCHAR(10) )";
string sql_create_fence_info   = sql_create_table + sql_create_fence_info1 + sql_create_fence_info2 ;

string sql_create_fence_group1  = "fence_group (  id INT UNSIGNED NOT NULL AUTO_INCREMENT, PRIMARY KEY (id), " ;
string sql_create_fence_group2  = " fence_id INT UNSIGNED, group_id INT UNSIGNED )";
string sql_create_fence_group   = sql_create_table + sql_create_fence_group1 + sql_create_fence_group2 ;

string sql_create_restricted_list1  = "restricted_list (  id INT UNSIGNED NOT NULL AUTO_INCREMENT, PRIMARY KEY (id), " ;
string sql_create_restricted_list2  = " fence_id INT UNSIGNED, staff_number VARCHAR(40) )";
string sql_create_restricted_list   = sql_create_table + sql_create_restricted_list1 + sql_create_restricted_list2 ;
// ******************** fence  END *****************

int list_size = 5 ;
//string sql_cmd_list[list_size];
bool Construct_sql_cmd()
{

    try
    {
        SQL_Open();

        SQL_ExecuteUpdate( sql_create_database );


        SQL_ExecuteUpdate( sql_create_map_info ) ;
        SQL_ExecuteUpdate( sql_create_group_info ) ;
        SQL_ExecuteUpdate( sql_create_anchor_info ) ;

        SQL_ExecuteUpdate( sql_create_group_anchor ) ;
        SQL_ExecuteUpdate( sql_create_map_group ) ;


        SQL_ExecuteUpdate( sql_create_locus ) ;
        SQL_ExecuteUpdate( sql_create_tag ) ;
        SQL_ExecuteUpdate (sql_create_locus_combine );

        SQL_ExecuteUpdate( sql_create_locus_index ) ;

        SQL_ExecuteUpdate( sql_create_locus_index_hour ) ;
        SQL_ExecuteUpdate( sql_create_locus_index_min ) ;
        SQL_ExecuteUpdate( sql_create_event ) ;

        SQL_ExecuteUpdate( sql_create_staff ) ;
        SQL_ExecuteUpdate( sql_create_department_relation ) ;
        SQL_ExecuteUpdate( sql_create_jobTitle_relation ) ;
        SQL_ExecuteUpdate( sql_create_user_type ) ;
//        SQL_ExecuteUpdate( sql_create_card_correspond ) ;

        SQL_ExecuteUpdate( sql_create_time_group_info ) ;
        SQL_ExecuteUpdate( sql_create_time_slot_info ) ;
        SQL_ExecuteUpdate( sql_create_time_slot_group ) ;

        SQL_ExecuteUpdate( sql_create_alarm_group_info ) ;
        SQL_ExecuteUpdate( sql_create_alarm_info ) ;
//        SQL_ExecuteUpdate( sql_create_alarm_group ) ;

        SQL_ExecuteUpdate( sql_create_fence_point ) ;
        SQL_ExecuteUpdate( sql_create_fence_info ) ;
        SQL_ExecuteUpdate( sql_create_restricted_list ) ;
        SQL_ExecuteUpdate( sql_create_fence_group ) ;


        SQL_Close();
    }
    catch ( exception &e )
    {
        cout << "Database table init error" << endl ;
        return false ;
    }
    return true ;
}

void SQL_Init()
{
    char* pwd = "1234";
    char* usr = "root";
    char* hostname = "tcp://127.0.0.1:3306";

    g_connpool.initPool( hostname, usr, pwd, 100);
}


bool SQL_Open()
{
    try
    {
        g_con = nullptr;
        g_state = nullptr;
        g_result = nullptr ;
        g_con = g_connpool.GetConnection();//get a db conn

        ios::sync_with_stdio(false);    // Linux gcc.
        locale::global(locale(""));
        setlocale(LC_CTYPE, "en_US.UTF-8");    // MinGW gcc.
        wcout.imbue(locale(""));


        g_state = g_con->createStatement();
        g_state->execute("set names utf8");
        //state->executeUpdate(sql_create_database);
        g_state->execute("use PositioningSystem");

    }
    catch ( exception &e )
    {
        cout << "SQL opening error"<< endl ;
        return false ;
    }

    return true ;
}

bool SQL_Open_single( Connection *&con, Statement *&state, ResultSet *&result )
{
    try
    {

//        Connection *con = nullptr;//= connpool.GetConnection();;
//        Statement *state = nullptr;
//        ResultSet *result = nullptr;
//        con = nullptr;
//        state = nullptr;
//        result = nullptr ;
        con = g_connpool.GetConnection();//get a db conn

        ios::sync_with_stdio(false);    // Linux gcc.
        locale::global(locale(""));
        setlocale(LC_CTYPE, "en_US.UTF-8");    // MinGW gcc.
        wcout.imbue(locale(""));


        state = con->createStatement();
        state->execute("set names utf8");
        //state->executeUpdate(sql_create_database);
        state->execute("use PositioningSystem");

    }
    catch ( exception &e )
    {
        cout << "SQL opening error"<< endl ;
        return false ;
    }

    return true ;
}

int SQL_ExecuteUpdate_single( Statement *&state, string input )
{

    try
    {
        state->executeUpdate(input);
    }
    catch ( sql::SQLException&e )
    {
        cout << "SQL:" << e.what() << endl ;
        return 0 ;
    }
    catch (exception &e)
    {
        cout << e.what() << endl ;
        return -1 ;

    }

    return 1 ;
}

int SQL_ExecuteUpdate( string input )
{

    try
    {
        g_state->executeUpdate(input);
    }
    catch ( sql::SQLException&e )
    {
        cout << "SQL:" << e.what() << endl ;
        return 0 ;
    }
    catch (exception &e)
    {
        cout << e.what() << endl ;
        return -1 ;

    }

    return 1 ;
}



void SQL_Close()
{
    if ( g_result != nullptr )
        delete g_result;
    if ( g_state != nullptr )
        delete g_state;
    if ( g_con != nullptr )
        g_connpool.ReleaseConnection(g_con);
}

void SQL_Close_single( Connection *&c, Statement *&s, ResultSet *&r )
{
    if ( r != nullptr )
        delete r;
    if ( s != nullptr )
        delete s;
    if ( c != nullptr )
        g_connpool.ReleaseConnection(c);
}

json Call_SQL_func( string func_name, json func_arg )
{

    json ret ;
    int success = 0 ;

    Connection *con = nullptr;//= connpool.GetConnection();;
    Statement *state = nullptr;
    ResultSet *result = nullptr;

    bool do_update_alarm_list = false ;
    bool do_update_time_list = false ;

    try
    {
//        SQL_Open();
        SQL_Open_single( con, state, result ) ;
        for ( int i = 0 ; i < func_arg.size() ; i++ )
        {
            if ( func_name == "AddListAnchor" )
                success += SQL_AddAnchor( state, func_arg[i]["anchor_id"].get<std::string>(), func_arg[i]["set_x"].get<std::string>(), func_arg[i]["set_y"].get<std::string>(),
                                          func_arg[i]["anchor_type"].get<std::string>() ) ;

            else if ( func_name == "AddListGroup" )
                success += SQL_AddGroup_Info( state, func_arg[i]["group_id"].get<std::string>(),func_arg[i]["group_name"].get<std::string>(),func_arg[i]["main_anchor_id"].get<std::string>(),
                                              func_arg[i]["mode"].get<std::string>(), func_arg[i]["mode_value"].get<std::string>(), func_arg[i]["fence"].get<std::string>() ) ;

            else if ( func_name == "AddListMap" )
            {
                success += SQL_AddMap( state, func_arg[i]["map_name"].get<std::string>(), func_arg[i]["map_file"].get<std::string>(), func_arg[i]["map_scale"].get<std::string>(), func_arg[i]["map_file_ext"].get<std::string>() ) ;
            }


            else if ( func_name == "AddListGroup_Anchor" )
                success += SQL_AddGroup_Anchor( state, func_arg[i]["group_id"].get<std::string>(), func_arg[i]["anchor_id"].get<std::string>() );

            else if ( func_name == "AddListMap_Group" )
                success += SQL_AddMap_Group( state, func_arg[i]["map_id"].get<std::string>(), func_arg[i]["group_id"].get<std::string>() );

            else if ( func_name == "AddAlarmInfo" )
            {
                success += SQL_AddAlarm_Info( state, func_arg[i]["alarm_name"].get<std::string>(), func_arg[i]["alarm_switch"].get<std::string>(), func_arg[i]["alarm_value"].get<std::string>(), func_arg[i]["alarm_group_id"].get<std::string>() );
                do_update_alarm_list = true ;
            }

//            else if ( func_name == "AddAlarmGroup")
//            {
//                success += SQL_AddAlarm_Group_Info( state, func_arg[i]["alarm_group_name"].get<std::string>(), func_arg[i]["time_group_id"].get<std::string>() );
//                ret = json_SQL_Return_alarm_gid( state, result );
//            }

            else if ( func_name == "AddTimeSlot")
            {
                // id, time_slot_name, Mon_start, Mon_end, Tue_start, Tue_end, Wed_start, Wed_end, Thu_start, Thu_end, Fri_start, Fri_end, Sat_start, Sat_end, Sun_start, Sun_end
                success += SQL_AddTime_Slot( state, func_arg[i]["time_slot_name"].get<std::string>(),
                                             func_arg[i]["Mon_start"].get<std::string>(), func_arg[i]["Mon_end"].get<std::string>(),
                                             func_arg[i]["Tue_start"].get<std::string>(), func_arg[i]["Tue_end"].get<std::string>(),
                                             func_arg[i]["Wed_start"].get<std::string>(), func_arg[i]["Wed_end"].get<std::string>(),
                                             func_arg[i]["Thu_start"].get<std::string>(), func_arg[i]["Thu_end"].get<std::string>(),
                                             func_arg[i]["Fri_start"].get<std::string>(), func_arg[i]["Fri_end"].get<std::string>(),
                                             func_arg[i]["Sat_start"].get<std::string>(), func_arg[i]["Sat_end"].get<std::string>(),
                                             func_arg[i]["Sun_start"].get<std::string>(), func_arg[i]["Sun_end"].get<std::string>() );
                do_update_time_list = true ;
            }




            else if ( func_name == "AddStaff" )
            {
                success += SQL_AddStaff( state, func_arg[i] ) ;

                // When update a staff_info, updating the staff_list which in the ram .
                json tmp_list = json_SQL_GetStaffs( state, result );
                cout << tmp_list.dump(2) << endl ;
                j_staff_list.clear() ;
                j_staff_list = update_staff_list( tmp_list ) ;
            }

            else if ( func_name == "EditStaff" )
            {
                success += SQL_EditStaff( state, func_arg[i] ) ;

                // When update a staff_info, updating the staff_list which in the ram .
                json tmp_list = json_SQL_GetStaffs( state, result );
                cout << tmp_list.dump(2) << endl ;
                j_staff_list.clear() ;
                j_staff_list = update_staff_list( tmp_list ) ;
            }

            else if ( func_name == "EditAlarmInfo" )
            {
                success += SQL_EditAlarmInfo( state, func_arg[i] ) ;
                do_update_alarm_list = true ;
            }

            else if ( func_name == "AddDepartment" )
            {
                success += SQL_AddDepartment( state, func_arg[i] ) ;
                ret = json_SQL_Return_inserted_dept_id( state, result );
            }
            else if ( func_name == "AddJobTitle" )
            {
                success += SQL_AddJobTitle( state, func_arg[i] ) ;
                ret = json_SQL_Return_inserted_job_id( state, result );
            }
            else if ( func_name == "AddUserType" )
            {
                success += SQL_AddUserType( state, func_arg[i] ) ;
//                ret = json_SQL_Return_inserted_job_id( state, result );
            }

            else if ( func_name == "AddFencePoint" )
            {
                success += SQL_AddFence_point( state, func_arg[i] ) ;
//                ret = json_SQL_Return_inserted_job_id( state, result );
            }
            else if ( func_name == "AddFenceInfo" )
            {
                success += SQL_AddFence_info( state, func_arg[i] ) ;
                ret = json_SQL_Return_inserted_fence_id( state, result );
            }
            else if ( func_name == "AddFenceGroup" )
            {
                success += SQL_AddFence_group( state, func_arg[i] ) ;
//                ret = json_SQL_Return_inserted_job_id( state, result );
            }


            else if ( func_name == "DeleteAnchor_Info" )
                success += SQL_DeleteAnchor_Info( state, func_arg[i]["anchor_id"] );

            else if ( func_name == "DeleteGroup_Info" )
                success += SQL_DeleteGroup_Info( state, func_arg[i]["group_id"] );

            else if ( func_name == "DeleteGroup_Anchor" )
            {
                if ( func_arg[i]["anchor_id"].empty() )
                {
                    success += SQL_DeleteGroup_Anchor_by_one_id( state, func_arg[i]["group_id"] );
                } // if
                else
                {
                    success += SQL_DeleteGroup_Anchor_by_duo_id( state, func_arg[i]["group_id"], func_arg[i]["anchor_id"] );
                } // else
            }

            else if ( func_name == "DeleteMap_Group" )
            {
                if ( func_arg[i]["map_id"].empty() )
                {
                    success += SQL_DeleteMap_Group_by_one_id( state, func_arg[i]["map_id"] );
                } // if
                else
                {
                    success += SQL_DeleteMap_Group_by_duo_id( state, func_arg[i]["map_id"], func_arg[i]["group_id"] );
                } // else

            }

            else if ( func_name == "DeleteMap" )
            {
                success += SQL_DeleteMap( state, func_arg[i]["map_id"] );
            }







            else if ( func_name == "DeleteDepartment" )
                success += SQL_DeleteDepartment( state, func_arg[i]["c_id"].get<std::string>() ) ;
            else if ( func_name == "DeleteJobTitle" )
                success += SQL_DeleteJobTitle( state, func_arg[i]["c_id"].get<std::string>() ) ;
            else if ( func_name == "DeleteUserType" )
                success += SQL_DeleteUserType( state, func_arg[i]["type"].get<std::string>() ) ;

            else if ( func_name == "DeleteStaff" )
            {
                success += SQL_DeleteStaff( state, func_arg[i]["number"].get<std::string>() ) ;

                // When update a staff_info, updating the staff_list which in the ram .
                json tmp_list = json_SQL_GetStaffs( state, result );
                cout << tmp_list.dump(2) << endl ;
                j_staff_list.clear() ;
                j_staff_list = update_staff_list( tmp_list ) ;
            }

            else if ( func_name == "DeleteAlarmInfo" )
            {
                success += SQL_DeleteAlarm_Info( state, func_arg[i]["alarm_iid"].get<std::string>() ) ;
                do_update_alarm_list = true ;
            }
            else if ( func_name == "DeleteAlarmGroupInfo" )
            {
                success += SQL_DeleteAlarm_Group_Info( state, func_arg[i]["alarm_gid"].get<std::string>() ) ;
                do_update_alarm_list = true ;
            }

            else if ( func_name == "DeleteTimeSlot" )
            {
                success += SQL_DeleteTime_Slot( state, func_arg[i]["time_slot_id"].get<std::string>() ) ;
                success += SQL_DeleteTime_Slot_Group_bySId( state, func_arg[i]["time_slot_id"].get<std::string>() ) ;
                do_update_time_list = true ;
            }

            else if ( func_name == "DeleteTimeSlotGroup" )
            {
                success += SQL_DeleteTime_Slot_Group_byDuoId( state, func_arg[i]["time_group_id"].get<std::string>(), func_arg[i]["time_slot_id"].get<std::string>() ) ;
                do_update_time_list = true ;
            }

            else if ( func_name == "DeleteTimeGroup" )
            {
                success += SQL_DeleteTime_Group( state, func_arg[i]["time_group_id"].get<std::string>() ) ;
                success += SQL_DeleteTime_Slot_Group_byGId( state, func_arg[i]["time_group_id"].get<std::string>() ) ;
                do_update_time_list = true ;
            }

            else if ( func_name == "DeleteFence_info" )
            {
                success += SQL_DeleteFence_Info( state, func_arg[i]["fence_id"].get<std::string>() ) ;
            }

            else if ( func_name == "DeleteFence_group_by_fid" )
            {
                success += SQL_DeleteFence_Group( state, func_arg[i]["fence_id"].get<std::string>() ) ;
            }

            else if ( func_name == "DeleteFence_point_by_fid" )
            {
                success += SQL_DeleteFence_Point( state, func_arg[i]["fence_id"].get<std::string>() ) ;
            }


            else if ( func_name == "multiEdit_StaffDepartment")
                success += SQL_multiEdit_StaffDepartment( state, func_arg[i]["number"].get<std::string>(), func_arg[i]["department"].get<std::string>() ) ;

            else if ( func_name == "multiEdit_StaffType")
                success += SQL_multiEdit_StaffType( state, func_arg[i]["number"].get<std::string>(), func_arg[i]["type"].get<std::string>() ) ;

            else if ( func_name == "multiEdit_StaffJobTitle")
                success += SQL_multiEdit_StaffJobTitle( state, func_arg[i]["number"].get<std::string>(), func_arg[i]["jobTitle"].get<std::string>() ) ;

            else if ( func_name == "multiEdit_StaffSetColor")
                success += SQL_multiEdit_StaffSetColor( state, func_arg[i]["number"].get<std::string>(), func_arg[i]["color_type"].get<std::string>() ) ;

        } // for


//        if ( func_name == "AddStaff" )
//            success = SQL_AddStaff( state, func_arg ) ;


//        if ( func_name == "AddDepartment" )
//        {
//            success = SQL_AddDepartment( state, func_arg ) ;
//            ret = json_SQL_Return_inserted_dept_id( state, result );
//        }
//
//        else if ( func_name == "AddJobTitle" )
//        {
//            success = SQL_AddDepartment( state, func_arg ) ;
//            ret = json_SQL_Return_inserted_job_id( state, result );
//        }

        if ( func_name == "EditAnchor_Info" )
        {
            success += SQL_EditAnchor_Info( state, func_arg ) ;
        }

        else if ( func_name == "EditGroup_Info" )
        {
            success += SQL_EditGroup_Info( state, func_arg ) ;
        }

        else if ( func_name == "EditFence_Info" )
        {
            success += SQL_EditFence_Info( state, func_arg ) ;
        }


//        else if ( func_name == "EditGroup_Anchors" )
//        {
//            success = SQL_EditGroup_Info( state, func_arg ) ;
//        }




        else if ( func_name == "EditDepartment" )
        {
            success += SQL_EditDepartment( state, func_arg ) ;
        }

        else if ( func_name == "EditJobTitle" )
        {
            success += SQL_EditJobTitle( state, func_arg ) ;
        }

        else if ( func_name == "EditUserType" )
        {
            success += SQL_EditUserType( state, func_arg ) ;
        }


        else if ( func_name == "EditAlarmGroupInfo" )
        {
            success += SQL_EditAlarmGroupInfo( state, func_arg ) ;
            do_update_alarm_list = true ;
        }

        else if ( func_name == "EditMap" )
        {
            success += SQL_EditMap( state, func_arg ) ;
        }

        else if ( func_name == "EditTimeSlot" )
        {
            success += SQL_EditTime_Slot( state, func_arg ) ;
            do_update_time_list = true ;
        }

        else if ( func_name == "EditTimeGroup" )
        {
            success += SQL_EditTime_Group( state, func_arg ) ;
            do_update_time_list = true ;
        }


        else if ( func_name == "AddAlarmGroup")
        {
            success += SQL_AddAlarm_Group_Info( state, func_arg["alarm_group_name"].get<std::string>(), func_arg["time_group_id"].get<std::string>() );
            do_update_alarm_list = true ;
            ret = json_SQL_Return_alarm_gid( state, result );
        }

        else if (func_name == "AddTimeGroup" )
        {
            success += SQL_AddTime_Group( state, func_arg["time_group_name"].get<std::string>() );
            do_update_time_list = true ;
            ret = json_SQL_Return_time_gid( state, result );
        }



        else if (func_name == "AddTimeSlotGroup" )
        {
            success += SQL_AddTimeSlot_Group( state, func_arg["time_group_id"].get<std::string>(), func_arg["time_slot_id"].get<std::string>() );
            do_update_time_list = true ;
        }



//        do_update_time_list = true ;
//        do_update_alarm_list = true ;
        cout << func_name << endl ;

        if ( func_name == "GetAnchors" || func_name == "AddListAnchor" )
            ret = json_SQL_GetAnchors_info( state, result );
        else if ( func_name == "GetGroups" || func_name == "AddListGroup" )
            ret = json_SQL_GetGroups_info( state, result );
        else if ( func_name == "GetMaps" || func_name == "AddListMap" )
            ret = json_SQL_GetMaps( state, result );
        else if ( func_name == "GetAnchorsInMap" )
            ret = json_SQL_GetAnchorsInMap( state, result, func_arg ) ;
        else if ( func_name == "GetMainAnchorsInMap" )
            ret = json_SQL_GetMainAnchorsInMap( state, result, func_arg ) ;

        else if ( func_name == "GetFencesInMap" )
            ret = json_SQL_GetFencesInMap( state, result, func_arg ) ;
        else if ( func_name == "GetFence_group" )
            ret = json_SQL_GetFence_group( state, result, func_arg ) ;
        else if ( func_name == "GetFence_point" )
            ret = json_SQL_GetFence_point( state, result, func_arg ) ;
        else if ( func_name == "GetFence_info" )
            ret = json_SQL_GetFence_info( state, result, func_arg ) ;





        else if ( func_name == "GetOneStaffPhoto" )
            ret = json_SQL_GetOneStaffPhoto( state, result, func_arg ) ;


        else if ( func_name == "GetOneStaff" )
            ret = json_SQL_Get_One_Staff( state, result, func_arg ) ;
        else if ( func_name == "GetStaffs" )
        {
            ret = json_SQL_GetStaffs( state, result );
            j_staff_list = update_staff_list( ret ) ;
            cout << j_staff_list.dump(2) << endl ;

        }

        else if ( func_name == "GetDepartment_relation" )
            ret = json_SQL_GetDepartment_relation( state, result );
        else if ( func_name == "GetJobTitle_relation" )
            ret = json_SQL_GetJobTitle_relation( state, result );
        else if ( func_name == "GetDepartment_relation_list" )
            ret = json_SQL_GetDepartment_relation_list( state, result );
        else if ( func_name == "GetJobTitle_relation_list" )
            ret = json_SQL_GetJobTitle_relation_list( state, result );
        else if ( func_name == "GetUserTypes" )
            ret = json_SQL_GetUserTypes( state, result );
        else if ( func_name == "GetAlarmInfo" )
            ret = json_SQL_GetAlarmInfo_list( state, result );
        else if ( func_name == "GetTimeSlot_list" )
            ret = json_SQL_GetTimeSlot_list( state, result );


        if ( func_name == "GetAlarmGroup_list" || do_update_alarm_list )
        {
            // alarm_group
            json alarm_g = json_SQL_GetAlarmGroup_list( state, result );
            // cout << alarm_g.dump(2) << endl ;

            // alarm_info
            json alarm_i = json_SQL_GetAlarmInfo_list( state, result );
            // cout << alarm_i.dump(2) << endl ;

            j_alarm_list = json_alarm_GroupBy_id( alarm_g, alarm_i );

            if ( !do_update_alarm_list )
                ret = j_alarm_list ;

            do_update_alarm_list = false ;
        }


        if ( func_name == "GetTimeGroup_list" || do_update_time_list )
        {
            json time_g     = json_SQL_GetTimeGroup_list( state, result );
            json time_gi    = json_SQL_GetTimeSlot_group( state, result );
            json time_i     = json_SQL_GetTimeSlot_list( state, result );

            j_time_list = json_time_GroupBy_id( time_g, time_gi, time_i ) ;

            if ( !do_update_time_list )
                ret = j_time_list ;

            do_update_time_list = false ;
        }


        else if ( func_name == "GetGroup_Anchors" || func_name == "AddListGroup_Anchor" )
            ret = json_SQL_GetGroup_Anchors( state, result );
        else if ( func_name == "GetMaps_Groups" || func_name == "AddListMap_Group" )
            ret = json_SQL_GetMap_Groups( state, result );


        else if ( func_name == "GetTags" )
            ret = json_SQL_GetTags_info( state, result );

        else if ( func_name == "GetLocus" )
            ret = json_SQL_GetSingleLocus( state, func_arg["tag_id"].get<std::string>(), func_arg["start_date"].get<std::string>(),  func_arg["start_time"].get<std::string>(), func_arg["end_date"].get<std::string>(),  func_arg["end_time"].get<std::string>(), result ) ;

        else if ( func_name == "GetLocus_combine" )
            ret = json_SQL_GetSingleLocus_combine( state, func_arg["tag_id"].get<std::string>(), func_arg["start_date"].get<std::string>(),  func_arg["start_time"].get<std::string>(), func_arg["end_date"].get<std::string>(),  func_arg["end_time"].get<std::string>(), result ) ;

        else if ( func_name == "GetLocus_combine_hour" )
            ret = json_SQL_GetSingleLocus_combine_hour( state, func_arg["tag_id"].get<std::string>(), func_arg["start_date"].get<std::string>(),  func_arg["start_time"].get<std::string>(), func_arg["end_date"].get<std::string>(),  func_arg["end_time"].get<std::string>(), result ) ;

        else if ( func_name == "GetLocus_combine_min" )
            ret = json_SQL_GetSingleLocus_combine_min( state, func_arg["tag_id"].get<std::string>(), func_arg["start_date"].get<std::string>(),  func_arg["start_time"].get<std::string>(), func_arg["end_date"].get<std::string>(),  func_arg["end_time"].get<std::string>(), result ) ;


        // **********Truncate table********
        if ( func_name == "ClearAllAnchors" )
            success = SQL_TruncateTable( state, "anchor_info" );
        else if ( func_name == "ClearAllGroups" )
            success = SQL_TruncateTable( state, "group_info" );
        else if ( func_name == "ClearAllMaps" )
            success = SQL_TruncateTable( state, "map_info" );

        else if ( func_name == "ClearAllGroup_Anchors" )
            success = SQL_TruncateTable( state, "group_anchors" );
        else if ( func_name == "ClearAllMap_Groups" )
            success = SQL_TruncateTable( state, "map_groups" );





        //*/

        if ( ret["success"].empty() )
            ret["success"] = success ;


//        SQL_Close();
        SQL_Close_single( con, state, result );
        return ret ;

    }
    catch ( exception &e )
    {
        cout << "json parse error from CALL_SQL_FUNC" << endl;
        cout << e.what() << endl ;
        //SQL_Close();
        SQL_Close_single( con, state, result );
    }


}

json update_staff_list( json from_sql_latest_list ) // only for server cache ( for match alarm list ), not web request.
{
    json person ;
    json people ;
    for ( int i = 0 ; i < from_sql_latest_list["Values"].size() ; i++ )
    {
        person["number"]            = from_sql_latest_list["Values"][i]["number"];
        person["tag_id"]            = from_sql_latest_list["Values"][i]["tag_id"];
        person["Name"]              = from_sql_latest_list["Values"][i]["Name"];
        person["alarm_group_id"]    = from_sql_latest_list["Values"][i]["alarm_group_id"];
        people.push_back(person) ;
    }

    cout << people.dump(2) << endl ;
    return people ;
}

int SQL_AddAnchor( Statement *&state, string id, string x, string y, string type )
{
//    INSERT INTO anchor_info VALUES ( '0','65512',  '348', '5', 'main' );
    string query = "INSERT INTO anchor_info VALUES ( '"+ id + "', '"+ x +"', '" + y + "', '"+ type + "' );";
//    SQL_Open();
    return SQL_ExecuteUpdate_single( state, query ) ;
//    SQL_Close() ;
}

int SQL_AddGroup_Info( Statement *&state, string group_id, string group_name, string main_anchor_id, string mode, string mode_value, string fence )
{
    string query = "INSERT INTO group_info VALUES ( '" + group_id + "', '" +  group_name +  "', '" + main_anchor_id + "', '" + mode + "' ,'" + mode_value + "', '" + fence + "' );";
    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_AddMap( Statement *&state, string map_name, string map_file, string map_scale, string map_file_ext )
{
    string query = "INSERT INTO map_info VALUES ( '0', '" + map_name + "', '" + map_file + "', '" + map_scale + "', '" + map_file_ext + "' );";
    return SQL_ExecuteUpdate_single( state, query ) ;
}


int SQL_AddGroup_Anchor( Statement *&state, string group_id, string anchor_id )
{
    string query = "INSERT INTO group_anchors VALUES ( '0','" + group_id + "', '" + anchor_id + "' );";
    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_AddAlarm_Group( Statement *&state, string alarm_group_id, string alarm_info_id )
{
    string query = "INSERT INTO alarm_group VALUES ( '0','" + alarm_group_id + "', '" + alarm_info_id + "' );";
    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_AddMap_Group( Statement *&state, string map_id, string group_id )
{
    string query = "INSERT INTO map_groups VALUES ( '0','" + map_id + "', '" + group_id + "' );";
    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_AddAlarm_Info( Statement *&state, string alarm_name, string alarm_switch, string alarm_value, string alarm_group_id )
{
    string query = "INSERT INTO alarm_info VALUES ( '0','" + alarm_name + "', '" + alarm_switch + "', '" + alarm_value + "', '" + alarm_group_id +  "' );";
    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_AddAlarm_Group_Info( Statement *&state, string alarm_group_name, string time_group_id )
{
    string query = "INSERT INTO alarm_group_info VALUES ( '0','" + alarm_group_name + "', '" + time_group_id +  "' );";
    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_AddTime_Slot( Statement *&state, string time_slot_name, string Mon_start, string Mon_end, string Tue_start, string Tue_end,
                      string Wed_start, string Wed_end, string Thu_start, string Thu_end, string Fri_start, string Fri_end,
                      string Sat_start, string Sat_end, string Sun_start, string Sun_end )
{
    //time_slot_name, Mon_start, Mon_end, Tue_start, Tue_end, Wed_start, Wed_end, Thu_start, Thu_end, Fri_start, Fri_end, Sat_start, Sat_end, Sun_start, Sun_end
    string query = string("") + "INSERT INTO time_slot_info VALUES ( '0','" + time_slot_name + "', '" +
                   Mon_start + "', '" + Mon_end + "', '" + Tue_start + "', '" + Tue_end + "', '" + Wed_start + "', '" + Wed_end + "', '" +
                   Thu_start + "', '" + Thu_end + "', '" + Fri_start + "', '" + Fri_end + "', '" + Sat_start + "', '" + Sat_end + "', '" + Sun_start + "', '" + Sun_end  + "' );";
    return SQL_ExecuteUpdate_single( state, query ) ;
}


int SQL_AddTime_Group( Statement *&state, string time_group_name )
{
    // time_group_name
    string query = string("") + "INSERT INTO time_group_info VALUES ( '0','" + time_group_name  + "' );";
    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_AddTimeSlot_Group( Statement *&state, string time_group_id, string time_slot_id )
{
    // id, time_group_id,
    string query = string("") + "INSERT INTO time_slot_group VALUES ( '0','" + time_group_id  + "', '" + time_slot_id + "' );";
    return SQL_ExecuteUpdate_single( state, query ) ;
}



int SQL_AddLocus( Statement *&state, string tag_id, string x, string y, string group_id, string date,string time )
{
    string query = "INSERT INTO locus VALUES ( '0','" + tag_id + "', '" + x + "', '" + y + "', '" + group_id + "', '" +  date + "', '" + time + "' );";
    return SQL_ExecuteUpdate_single( state, query ) ;
}


int SQL_AddLocus_combine( Statement *&state, string tag_id, string x, string y, string group_id, string time )
{
    string query = "INSERT INTO locus_combine VALUES ( '0','" + tag_id + "', '" + x + "', '" + y + "', '" + group_id + "', '" +  time + "' );";
    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_AddTag( Statement *&state, string tag_id, string tag_name, string pic_path )
{
    string query = "INSERT INTO tag_info VALUES ( '" + tag_id + "', '" + tag_name + "', '" + pic_path + "' );";
    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_AddEvent( Statement *&state, string tag_id, string alarm_type, string status, string time )
{
    string query = "INSERT INTO event VALUES ( '0','" + tag_id + "', '" + alarm_type + "', '" + status + "', '" +  time + "' );";
    return SQL_ExecuteUpdate_single( state, query ) ;
}




int SQL_multiEdit_StaffDepartment( Statement *&state, string number, string department_id )
{
    string query = "UPDATE staff SET department_id = '" + department_id + "' where number = '" +  number + "' ;" ;
    SQL_OFF_SafeUpdate(state);
    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_multiEdit_StaffType( Statement *&state, string number, string type )
{
    string query = "UPDATE staff SET type = '" + type + "' where number = '" +  number + "' ;" ;
    SQL_OFF_SafeUpdate(state);
    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_multiEdit_StaffJobTitle( Statement *&state, string number, string jobTitle_id )
{
    string query = "UPDATE staff SET jobTitle_id = '" + jobTitle_id + "' where number = '" +  number + "' ;" ;
    SQL_OFF_SafeUpdate(state);
    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_multiEdit_StaffSetColor( Statement *&state, string number, string color_type )
{
    string query = "UPDATE staff SET color_type = '" + color_type + "' where number = '" +  number + "' ;" ;
    SQL_OFF_SafeUpdate(state);
    return SQL_ExecuteUpdate_single( state, query ) ;
}


int SQL_AddStaff( Statement *&state, json func_arg )
{

    string number       = func_arg["number"].get<std::string>() ;
    string tag_id       = func_arg["tag_id"].get<std::string>() ;
    string Name         = func_arg["Name"].get<std::string>() ;
    string lastName     = func_arg["lastName"].get<std::string>() ;
    string firstName    = func_arg["firstName"].get<std::string>() ;

    string EnglishName  = func_arg["EnglishName"].get<std::string>() ;
    string gender       = func_arg["gender"].get<std::string>() ;
    string card_id      = func_arg["card_id"].get<std::string>() ;
    string status       = func_arg["status"].get<std::string>() ;
    string color_type   = func_arg["color_type"].get<std::string>() ;
    string color        = func_arg["color"].get<std::string>() ;
    string department_id= func_arg["department_id"].get<std::string>() ;

    string jobTitle_id  = func_arg["jobTitle_id"].get<std::string>() ;
    string type         = func_arg["type"].get<std::string>() ;
    string birthday     = func_arg["birthday"].get<std::string>() ;
    string dateEntry    = func_arg["dateEntry"].get<std::string>() ;
    string dateLeave    = func_arg["dateLeave"].get<std::string>() ;

    string school       = func_arg["school"].get<std::string>() ;
    string education    = func_arg["education"].get<std::string>() ;
    string phoneJob     = func_arg["phoneJob"].get<std::string>() ;
    string phoneSelf    = func_arg["phoneSelf"].get<std::string>() ;
    string mail         = func_arg["mail"].get<std::string>() ;

    string address      = func_arg["address"].get<std::string>() ;
    string note         = func_arg["note"].get<std::string>() ;
//    string photo        = func_arg["photo"].get<std::string>() ;
    string exist        = func_arg["exist"].get<std::string>() ;

    string grade        = func_arg["grade"].get<std::string>() ;
    string tech_grade   = func_arg["tech_grade"].get<std::string>() ;
    string file_ext     = func_arg["file_ext"].get<std::string>() ;
    string alarm_group_id   = func_arg["alarm_group_id"].get<std::string>() ;

    string str_b64      = func_arg["photo"].get<std::string>() ;
    string decoded      = base64_decode(str_b64);

//    string str_bin = "";
//    for ( int i = 0 ;  i <(int)decoded.length() ; i++ )
//    {
//        bitset<8>b(decoded[i]) ;
//        str_bin += b.to_string();
//    }
    string photo        = str_b64;
//    cout << "?????" << endl ;

    /*
    "staff ( id INT UNSIGNED NOT NULL AUTO_INCREMENT, PRIMARY KEY (id), number VARCHAR(40) NOT NULL, UNIQUE (number), INDEX index_staff(number), " ;
     = "tag_id VARCHAR(16), INDEX index_tag_id( tag_id ), Name VARCHAR(40)" + ",lastName VARCHAR(40)" + ", firstName VARCHAR(40)" + ",EnglishName VARCHAR(40) ," ;
     = "gender VARCHAR(10)," + "card_id VARCHAR(40)," + "status VARCHAR(40)," + "department VARCHAR(40)," + "jobTitle VARCHAR(40)," +  "type VARCHAR(40),";
     = "birthday VARCHAR(10)," + "dateEntry VARCHAR(10)" + ", dateLeave VARCHAR(10)" + ", school VARCHAR(40)" + ", education VARCHAR(10)"
            + ", phoneJob VARCHAR(20)" + ", phoneSelf VARCHAR(20)" + ", mail VARCHAR(60)" + ", address TEXT" + ", note TEXT" + ", photo BLOB" + ", exist INT" + ")";
    */

    // id, number, tag_id, Name, lastName, firstName, EnglishName, gender, card_id, status, department, jobTitle, type, birthday, photo, note

    string query = string("") + "INSERT INTO staff VALUES ( '0','" + number + "','" + tag_id + "','" +  Name + "','" +  lastName + "','" + firstName  + "','" +
                   EnglishName + "','" + gender + "','" + card_id + "','" +  status + "','" + color_type + "','" + color + "','" + department_id + "','" +
                   jobTitle_id + "','" + type + "','" + birthday + "','" + dateEntry + "','" + dateLeave + "','" + school + "','" + education + "','" +
                   phoneJob + "','" + phoneSelf + "','" + mail + "','" + address + "','" + note + "','" + photo + "','" + exist + "','" + grade + "','" +
                   tech_grade + "','" + file_ext + "','" + alarm_group_id + "' );" ;

    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_AddDepartment( Statement *&state, json func_arg )
{

    string parent       = func_arg["parent"].get<std::string>() ;
    string p_id         = func_arg["p_id"].get<std::string>() ;
    string children     = func_arg["children"].get<std::string>() ;
//    string c_id         = func_arg["c_id"].get<std::string>() ;
    string color        = func_arg["color"].get<std::string>() ;
//    string exist        = func_arg["exist"].get<std::string>() ;


    string query0 = "SET @last_id_in_table = (SELECT AUTO_INCREMENT  FROM information_schema.tables WHERE table_name = 'department_relation' AND table_schema = DATABASE() );" ;
    SQL_ExecuteUpdate_single( state, query0 ) ;
    string query = string("") + "INSERT INTO department_relation VALUES ( '0','" + parent + "','" + p_id + "','" + children + "'," + "@last_id_in_table" + ",'" + color + "' );" ;

    return SQL_ExecuteUpdate_single( state, query ) ;
}


int SQL_AddJobTitle( Statement *&state, json func_arg )
{

    string parent       = func_arg["parent"].get<std::string>() ;
    string p_id         = func_arg["p_id"].get<std::string>() ;
    string children     = func_arg["children"].get<std::string>() ;
//    string c_id         = func_arg["c_id"].get<std::string>() ;
    string color        = func_arg["color"].get<std::string>() ;
//    string exist        = func_arg["exist"].get<std::string>() ;


    string query0 = "SET @last_id_in_table = (SELECT AUTO_INCREMENT  FROM information_schema.tables WHERE table_name = 'jobTitle_relation' AND table_schema = DATABASE() );" ;
    SQL_ExecuteUpdate_single( state, query0 ) ;
    string query = string("") + "INSERT INTO jobTitle_relation VALUES ( '0','" + parent + "','" + p_id + "','" + children + "'," + "@last_id_in_table" + ",'" + color + "' );" ;

    return SQL_ExecuteUpdate_single( state, query ) ;
}


int SQL_AddUserType( Statement *&state, json func_arg )
{

    string type     = func_arg["type"].get<std::string>() ;
    string color    = func_arg["color"].get<std::string>() ;

//    string query0 = "SET @last_id_in_table = (SELECT AUTO_INCREMENT  FROM information_schema.tables WHERE table_name = 'user_type' AND table_schema = DATABASE() );" ;
//    SQL_ExecuteUpdate_single( state, query0 ) ;
    string query = string("") + "INSERT INTO user_type VALUES ( '" + type + "','" + color  + "' );" ;

    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_AddFence_point( Statement *&state, json func_arg )
{

    string fence_point_x    = func_arg["point_x"].get<std::string>() ;
    string fence_point_y    = func_arg["point_y"].get<std::string>() ;

    string fence_id         = func_arg["fence_id"].get<std::string>() ;
    string point_order      = func_arg["point_order"].get<std::string>() ;

//    string query0 = "SET @last_id_in_table = (SELECT AUTO_INCREMENT  FROM information_schema.tables WHERE table_name = 'user_type' AND table_schema = DATABASE() );" ;
//    SQL_ExecuteUpdate_single( state, query0 ) ;
    string query = string("") + "INSERT INTO fence_point VALUES ( '0','" + fence_point_x + "','" + fence_point_y  + "','" + fence_id  + "','" + point_order  + "' );" ;

    return SQL_ExecuteUpdate_single( state, query ) ;
}


int SQL_AddFence_info( Statement *&state, json func_arg )
{

    //string fence_id     = func_arg["fence_id"].get<std::string>() ;

    string fence_name   = func_arg["fence_name"].get<std::string>() ;
    string map_id       = func_arg["map_id"].get<std::string>() ;
    string list_type    = func_arg["list_type"].get<std::string>() ;

//    string query0 = "SET @last_id_in_table = (SELECT AUTO_INCREMENT  FROM information_schema.tables WHERE table_name = 'user_type' AND table_schema = DATABASE() );" ;
//    SQL_ExecuteUpdate_single( state, query0 ) ;
    string query = string("") + "INSERT INTO fence_info VALUES ( '0','" + fence_name  + "','" + map_id  + "','" + list_type  + "' );" ;

    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_AddFence_group( Statement *&state, json func_arg )
{

    string fence_id     = func_arg["fence_id"].get<std::string>() ;
    string group_id     = func_arg["group_id"].get<std::string>() ;

//    string query0 = "SET @last_id_in_table = (SELECT AUTO_INCREMENT  FROM information_schema.tables WHERE table_name = 'user_type' AND table_schema = DATABASE() );" ;
//    SQL_ExecuteUpdate_single( state, query0 ) ;
    string query = string("") + "INSERT INTO fence_group VALUES ( '0','" + fence_id + "','" + group_id  + "' );" ;

    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_EditStaff( Statement *&state, json func_arg )
{

    string number       = func_arg["number"].get<std::string>() ;
    string tag_id       = func_arg["tag_id"].get<std::string>() ;
    string Name         = func_arg["Name"].get<std::string>() ;
    string lastName     = func_arg["lastName"].get<std::string>() ;
    string firstName    = func_arg["firstName"].get<std::string>() ;

    string EnglishName  = func_arg["EnglishName"].get<std::string>() ;
    string gender       = func_arg["gender"].get<std::string>() ;
    string card_id      = func_arg["card_id"].get<std::string>() ;
    string status       = func_arg["status"].get<std::string>() ;
    string color_type   = func_arg["color_type"].get<std::string>() ;
    string color        = func_arg["color"].get<std::string>() ;
    string department_id= func_arg["department_id"].get<std::string>() ;

    string jobTitle_id  = func_arg["jobTitle_id"].get<std::string>() ;
    string type         = func_arg["type"].get<std::string>() ;
    string birthday     = func_arg["birthday"].get<std::string>() ;
    string dateEntry    = func_arg["dateEntry"].get<std::string>() ;
    string dateLeave    = func_arg["dateLeave"].get<std::string>() ;

    string school       = func_arg["school"].get<std::string>() ;
    string education    = func_arg["education"].get<std::string>() ;
    string phoneJob     = func_arg["phoneJob"].get<std::string>() ;
    string phoneSelf    = func_arg["phoneSelf"].get<std::string>() ;
    string mail         = func_arg["mail"].get<std::string>() ;

    string address      = func_arg["address"].get<std::string>() ;
    string note         = func_arg["note"].get<std::string>() ;
//    string photo        = func_arg["photo"].get<std::string>() ;
    string exist        = func_arg["exist"].get<std::string>() ;

    string grade        = func_arg["grade"].get<std::string>() ;
    string tech_grade   = func_arg["tech_grade"].get<std::string>() ;
    string file_ext     = func_arg["file_ext"].get<std::string>() ;
    string alarm_group_id   = func_arg["alarm_group_id"].get<std::string>() ;


    string str_b64      = func_arg["photo"].get<std::string>() ;
    string decoded      = base64_decode(str_b64);

//    string str_bin = "";
//    for ( int i = 0 ;  i <(int)decoded.length() ; i++ )
//    {
//        bitset<8>b(decoded[i]) ;
//        str_bin += b.to_string();
//    }
    string photo        = str_b64;
//    cout << "?????" << endl ;

    /*
    "staff ( id INT UNSIGNED NOT NULL AUTO_INCREMENT, PRIMARY KEY (id), number VARCHAR(40) NOT NULL, UNIQUE (number), INDEX index_staff(number), " ;
     = "tag_id VARCHAR(16), INDEX index_tag_id( tag_id ), Name VARCHAR(40)" + ",lastName VARCHAR(40)" + ", firstName VARCHAR(40)" + ",EnglishName VARCHAR(40) ," ;
     = "gender VARCHAR(10)," + "card_id VARCHAR(40)," + "status VARCHAR(40)," + "department VARCHAR(40)," + "jobTitle VARCHAR(40)," +  "type VARCHAR(40),";
     = "birthday VARCHAR(10)," + "dateEntry VARCHAR(10)" + ", dateLeave VARCHAR(10)" + ", school VARCHAR(40)" + ", education VARCHAR(10)"
            + ", phoneJob VARCHAR(20)" + ", phoneSelf VARCHAR(20)" + ", mail VARCHAR(60)" + ", address TEXT" + ", note TEXT" + ", photo BLOB" + ", exist INT" + ")";
    */

    // id, number, tag_id, Name, lastName, firstName, EnglishName, gender, card_id, status, department, jobTitle, type, birthday, photo, note

    string query = string("") + "UPDATE staff SET tag_id = '" + tag_id + "', Name = '" + Name + "', lastName = '" +  lastName + "', firstName = '" + firstName
                   + "', EnglishName = '" + EnglishName  + "', gender = '" + gender + "', card_id = '" + card_id + "', status = '" + status + "', color_type = '" + color_type
                   + "', color = '" + color + "', department_id = '" + department_id + "', jobTitle_id = '" + jobTitle_id + "', type = '" + type + "', birthday = '" + birthday
                   + "', dateEntry = '" + dateEntry + "', dateLeave = '" + dateLeave + "', school = '" + school + "', education = '" + education + "', phoneJob = '" + phoneJob
                   + "', phoneSelf = '" + phoneSelf + "', mail = '" + mail + "', address = '" + address + "', note = '" + note + "', photo = '" + photo
                   + "', exist = '" + exist + "', grade = '" + grade + "', tech_grade = '" + tech_grade + "', file_ext = '" + file_ext + "', alarm_group_id = '" + alarm_group_id
                   + "' where number = '" +  number + "' ;" ;

    SQL_OFF_SafeUpdate(state);
    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_EditAnchor_Info( Statement *&state, json func_arg )
{
    // anchor_id, set_x, set_y, anchor_type
    string anchor_id    = func_arg["anchor_id"].get<std::string>() ;
    string set_x        = func_arg["set_x"].get<std::string>() ;
    string set_y        = func_arg["set_y"].get<std::string>() ;
    string anchor_type  = func_arg["anchor_type"].get<std::string>() ;


    string query = string("") + "UPDATE `PositioningSystem`.`anchor_info` SET `set_x`='" + set_x  + "', set_y = '" + set_y + "', anchor_type = '" + anchor_type + "' WHERE `anchor_id`='" + anchor_id + "';" ;

    SQL_OFF_SafeUpdate(state);
    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_EditGroup_Info( Statement *&state, json func_arg )
{
    // group_id, group_name, main_anchor_id, mode, mode_value, fence
    string group_id         = func_arg["group_id"].get<std::string>() ;
    string group_name       = func_arg["group_name"].get<std::string>() ;
    string main_anchor_id   = func_arg["main_anchor_id"].get<std::string>() ;
    string mode             = func_arg["mode"].get<std::string>() ;
    string mode_value       = func_arg["mode_value"].get<std::string>() ;
    string fence            = func_arg["fence"].get<std::string>() ;

    string query = string("") + "UPDATE `PositioningSystem`.`group_info` SET `main_anchor_id`='" + main_anchor_id + "', group_name = '" + group_name +
                   "', mode = '" + mode + "', mode_value = '" + mode_value + "', fence = '" + fence + "' WHERE `group_id`='" + group_id + "';" ;

    SQL_OFF_SafeUpdate(state);
    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_EditFence_Info( Statement *&state, json func_arg )
{
    // group_id, group_name, main_anchor_id, mode, mode_value, fence
    string fence_id     = func_arg["fence_id"].get<std::string>() ;
    string fence_name   = func_arg["fence_name"].get<std::string>() ;
    string map_id       = func_arg["map_id"].get<std::string>() ;
    string list_type    = func_arg["list_type"].get<std::string>() ;

    string query = string("") + "UPDATE `PositioningSystem`.`fence_info` SET `fence_name`='" + fence_name + "', map_id = '" + map_id +
                    "', list_type = '" + list_type + "' WHERE `fence_id`='" + fence_id + "';" ;

    SQL_OFF_SafeUpdate(state);
    return SQL_ExecuteUpdate_single( state, query ) ;
}

//int SQL_EditGroup_Anchors( Statement *&state, json func_arg )
//{
//    // group_id, group_name, main_anchor_id, mode, mode_value, fence
//    string group_id         = func_arg["group_id"].get<std::string>() ;
//    string anchor_id   = func_arg["anchor_id"].get<std::string>() ;
//
//    string query = string("") + "UPDATE `PositioningSystem`.`group_anchors` SET `anchor_id`='" + anchor_id + "' WHERE `group_id`='" + group_id + "'" ;
//
//    SQL_OFF_SafeUpdate(state);
//    return SQL_ExecuteUpdate_single( state, query ) ;
//}

int SQL_EditDepartment( Statement *&state, json func_arg )
{

//    string parent       = func_arg["parent"].get<std::string>() ;
//    string p_id         = func_arg["p_id"].get<std::string>() ;
    string children     = func_arg["name"].get<std::string>() ;
    string c_id         = func_arg["c_id"].get<std::string>() ;
    string color        = func_arg["color"].get<std::string>() ;
//    string exist        = func_arg["exist"].get<std::string>() ;


    string query = string("") + "UPDATE department_relation SET children = '" + children + "', color = '" + color + "' where c_id = '" +  c_id + "' ;" ;
    SQL_OFF_SafeUpdate(state);
    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_EditJobTitle( Statement *&state, json func_arg )
{

//    string parent       = func_arg["parent"].get<std::string>() ;
//    string p_id         = func_arg["p_id"].get<std::string>() ;
    string children     = func_arg["name"].get<std::string>() ;
    string c_id         = func_arg["c_id"].get<std::string>() ;
    string color        = func_arg["color"].get<std::string>() ;
//    string exist        = func_arg["exist"].get<std::string>() ;


    string query = string("") + "UPDATE jobTitle_relation SET children = '" + children + "', color = '" + color + "' where c_id = '" +  c_id + "' ;" ;
    SQL_OFF_SafeUpdate(state);
    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_EditUserType( Statement *&state, json func_arg )
{
    string type         = func_arg["type"].get<std::string>() ;
    string color        = func_arg["color"].get<std::string>() ;

//    string query = string("") + "UPDATE user_type SET type = '" + type + "', color = '" + color + "' where t_id = '" +  t_id + "' ;" ;
    string query = string("") + "UPDATE user_type SET color = '" + color + "' where type = '" +  type + "' ;" ;
    SQL_OFF_SafeUpdate(state);
    return SQL_ExecuteUpdate_single( state, query ) ;
}


int SQL_EditMap( Statement *&state, json func_arg )
{
    string map_id       = func_arg["map_id"].get<std::string>() ;
    string map_name     = func_arg["map_name"].get<std::string>() ;
    string map_file     = func_arg["map_file"].get<std::string>() ;
    string map_scale    = func_arg["map_scale"].get<std::string>() ;
    string map_file_ext = func_arg["map_file_ext"].get<std::string>() ;

//    string query = string("") + "UPDATE user_type SET type = '" + type + "', color = '" + color + "' where t_id = '" +  t_id + "' ;" ;
    string query = string("") + "UPDATE map_info SET map_name = '" + map_name + "', map_file = '" + map_file + "', map_scale = '" + map_scale + "', map_file_ext = '" + map_file_ext + "' where map_id = '" +  map_id + "' ;" ;
    SQL_OFF_SafeUpdate(state);
    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_EditTime_Slot( Statement *&state, json func_arg )
{
    // id, time_slot_name, Mon_start, Mon_end, Tue_start, Tue_end, Wed_start, Wed_end, Thu_start, Thu_end, Fri_start, Fri_end, Sat_start, Sat_end, Sun_start, Sun_end
    string id               = func_arg["time_slot_id"].get<std::string>() ;
    string time_slot_name   = func_arg["time_slot_name"].get<std::string>() ;
    string Mon_start        = func_arg["Mon_start"].get<std::string>() ;
    string Mon_end          = func_arg["Mon_end"].get<std::string>() ;
    string Tue_start        = func_arg["Tue_start"].get<std::string>() ;
    string Tue_end          = func_arg["Tue_end"].get<std::string>() ;
    string Wed_start        = func_arg["Wed_start"].get<std::string>() ;
    string Wed_end          = func_arg["Wed_end"].get<std::string>() ;
    string Thu_start        = func_arg["Thu_start"].get<std::string>() ;
    string Thu_end          = func_arg["Thu_end"].get<std::string>() ;
    string Fri_start        = func_arg["Fri_start"].get<std::string>() ;
    string Fri_end          = func_arg["Fri_end"].get<std::string>() ;
    string Sat_start        = func_arg["Sat_start"].get<std::string>() ;
    string Sat_end          = func_arg["Sat_end"].get<std::string>() ;
    string Sun_start        = func_arg["Sun_start"].get<std::string>() ;
    string Sun_end          = func_arg["Sun_end"].get<std::string>() ;



//    string query = string("") + "UPDATE user_type SET type = '" + type + "', color = '" + color + "' where t_id = '" +  t_id + "' ;" ;
    string query = string("") + "UPDATE time_slot_info SET time_slot_name = '" + time_slot_name + "', Mon_start = '" + Mon_start + "', Mon_end = '" + Mon_end +
                   "', Tue_start = '" + Tue_start + "', Tue_end = '" + Tue_end + "', Wed_start = '" + Wed_start + "', Wed_end = '" + Wed_end +
                   "', Thu_start = '" + Thu_start + "', Thu_end = '" + Thu_end + "', Fri_start = '" + Fri_start + "', Fri_end = '" + Fri_end +
                   "', Sat_start = '" + Sat_start + "', Sat_end = '" + Sat_end + "', Sun_start = '" + Sun_start + "', Sun_end = '" + Sun_end +
                   "' where id = '" +  id + "' ;" ;
    SQL_OFF_SafeUpdate(state);
    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_EditTime_Group( Statement *&state, json func_arg )
{
    // id, time_slot_name, Mon_start, Mon_end, Tue_start, Tue_end, Wed_start, Wed_end, Thu_start, Thu_end, Fri_start, Fri_end, Sat_start, Sat_end, Sun_start, Sun_end
    string time_group_id    = func_arg["time_group_id"].get<std::string>() ;
    string time_group_name  = func_arg["time_group_name"].get<std::string>() ;


//    string query = string("") + "UPDATE user_type SET type = '" + type + "', color = '" + color + "' where t_id = '" +  t_id + "' ;" ;
    string query = string("") + "UPDATE time_group_info SET time_group_name = '" + time_group_name + "' where id = '" +  time_group_id + "' ;" ;
    SQL_OFF_SafeUpdate(state);
    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_EditAlarmInfo( Statement *&state, json func_arg )
{
    string id                   = func_arg["alarm_iid"].get<std::string>() ;
    string alarm_name           = func_arg["alarm_name"].get<std::string>() ;
    string alarm_switch         = func_arg["alarm_switch"].get<std::string>() ;
    string alarm_value          = func_arg["alarm_value"].get<std::string>() ;
    string alarm_group_id       = func_arg["alarm_group_id"].get<std::string>() ;


//    string query = string("") + "UPDATE user_type SET type = '" + type + "', color = '" + color + "' where t_id = '" +  t_id + "' ;" ;
    string query = string("") + "UPDATE alarm_info SET alarm_name = '" + alarm_name + "', alarm_switch = '" + alarm_switch + "', alarm_value = '" + alarm_value + "', alarm_group_id = '" + alarm_group_id + "' where id = '" +  id + "' ;" ;
    SQL_OFF_SafeUpdate(state);
    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_EditAlarmGroupInfo( Statement *&state, json func_arg )
{
    string id               = func_arg["alarm_gid"].get<std::string>() ;
    string alarm_group_name = func_arg["alarm_group_name"].get<std::string>() ;
    string time_group_id     = func_arg["time_group_id"].get<std::string>() ;

//    string query = string("") + "UPDATE user_type SET type = '" + type + "', color = '" + color + "' where t_id = '" +  t_id + "' ;" ;
    string query = string("") + "UPDATE alarm_group_info SET alarm_group_name = '" + alarm_group_name + "', time_group_id = '" + time_group_id + "' where id = '" +  id + "' ;" ;
    SQL_OFF_SafeUpdate(state);
    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_DeleteDepartment( Statement *&state, string c_id )
{
    string query = string("") + "delete from department_relation where c_id = \"" + c_id + "\";";
    SQL_OFF_SafeUpdate(state);
    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_DeleteJobTitle( Statement *&state, string c_id )
{
    string query = string("") + "delete from jobTitle_relation where c_id = \"" + c_id + "\";";
    SQL_OFF_SafeUpdate(state);
    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_DeleteUserType( Statement *&state, string type )
{
    string query = string("") + "delete from user_type where type = \"" + type + "\";";
    SQL_OFF_SafeUpdate(state);
    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_DeleteTime_Slot( Statement *&state, string id )
{
    string query = string("") + "delete from time_slot_info where id = \"" + id + "\";";
    SQL_OFF_SafeUpdate(state);
    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_DeleteTime_Slot_Group_byGId( Statement *&state, string time_group_id )
{
    string query = string("") + "delete from time_slot_group where time_group_id = \"" + time_group_id + "\";";
    SQL_OFF_SafeUpdate(state);
    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_DeleteTime_Slot_Group_bySId( Statement *&state, string time_slot_id )
{
    string query = string("") + "delete from time_slot_group where time_slot_id = \"" + time_slot_id + "\";";
    SQL_OFF_SafeUpdate(state);
    return SQL_ExecuteUpdate_single( state, query ) ;
}


int SQL_DeleteTime_Slot_Group_byDuoId( Statement *&state, string time_group_id, string time_slot_id  )
{
    string query = string("") + "delete from time_slot_group where time_group_id = \"" + time_group_id + "\" and time_slot_id = \"" + time_slot_id + "\";";
    SQL_OFF_SafeUpdate(state);
    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_DeleteTime_Group( Statement *&state, string time_group_id )
{
    string query = string("") + "delete from time_group_info where id = \"" + time_group_id + "\";";
    SQL_OFF_SafeUpdate(state);
    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_DeleteFence_Point( Statement *&state, string fence_id )
{
    string query = string("") + "delete from fence_point where fence_id = \"" + fence_id + "\";";
    SQL_OFF_SafeUpdate(state);
    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_DeleteFence_Info( Statement *&state, string fence_id )
{
    string query = string("") + "delete from fence_info where fence_id = \"" + fence_id + "\";";
    SQL_OFF_SafeUpdate(state);
    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_DeleteFence_Group( Statement *&state, string fence_id )
{
    string query = string("") + "delete from fence_group where fence_id = \"" + fence_id + "\";";
    SQL_OFF_SafeUpdate(state);
    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_DeleteStaff( Statement *&state, string number )
{
    string query = string("") + "delete from staff where number = \"" + number + "\";";
    SQL_OFF_SafeUpdate(state);
    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_DeleteAlarm_Info( Statement *&state, string id )
{
    string query = string("") + "delete from alarm_info where id = \"" + id + "\";";
    SQL_OFF_SafeUpdate(state);
    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_DeleteAlarm_Group_Info( Statement *&state, string id )
{
    string query = string("") + "delete from alarm_group_info where id = \"" + id + "\";";
    SQL_OFF_SafeUpdate(state);
    return SQL_ExecuteUpdate_single( state, query ) ;
}


int SQL_OFF_SafeUpdate( Statement *&state )
{
    string query = "SET SQL_SAFE_UPDATES = 0;";
    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_DeleteAnchor_Info( Statement *&state, string id )
{
    string query = "delete from anchor_info where anchor_id = \"" + id + "\";";
    SQL_OFF_SafeUpdate(state);
    return SQL_ExecuteUpdate_single( state, query ) ;
}
int SQL_DeleteGroup_Info( Statement *&state, string id )
{
    string query = "delete from group_info where group_id = \"" + id + "\";";
    SQL_OFF_SafeUpdate(state);
    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_DeleteMap( Statement *&state, string id )
{
    string query = "delete from map_info where map_id = \"" + id + "\";";
    SQL_OFF_SafeUpdate(state);
    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_DeleteMap_Group_by_one_id( Statement *&state, string m_id )
{
    string query = "delete from map_groups where map_id = \"" + m_id + "\";";
    SQL_OFF_SafeUpdate(state);
    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_DeleteMap_Group_by_duo_id( Statement *&state, string m_id, string g_id )
{
    string query = "delete from map_groups where map_id = \"" + m_id + "\" and group_id = \"" + g_id + "\";";
    SQL_OFF_SafeUpdate(state);
    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_DeleteGroup_Anchor_by_one_id( Statement *&state, string gid )
{
    string query = "delete from group_anchors where group_id = \"" + gid + "\";";
    SQL_OFF_SafeUpdate(state);
    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_DeleteGroup_Anchor_by_duo_id( Statement *&state, string gid, string anid )
{
    string query = "delete from group_anchors where group_id = \"" + gid + "\" and anchor_id = \"" + anid + "\";";
    SQL_OFF_SafeUpdate(state);
    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_DeleteTag( Statement *&state, string id )
{
    string query = "delete from tag_info where tag_id = \"" + id + "\";";
    SQL_OFF_SafeUpdate(state);
    return SQL_ExecuteUpdate_single( state, query ) ;
}


int SQL_TruncateTable( Statement *&state, string id )
{
    string query = "TRUNCATE `PositioningSystem`.`" + id + "`;";
    cout << query<< endl ;
    SQL_OFF_SafeUpdate(state);
    return SQL_ExecuteUpdate_single( state, query ) ;
}

vector<vector<string>> SQL_GetAnchors_info()
{
    vector<vector<string>> foo;
    vector<string> temp ;
    string query = "SELECT * FROM anchor_info;";
//    SQL_ExecuteQuery( query ) ;
//INSERT INTO anchor_info VALUES ( '0','65504', '348', '5', '' );
    try
    {
        g_result = g_state->executeQuery(query);
        while (g_result->next())
        {
            string column_id = g_result->getString("id");
            string column_an_id = g_result->getString("anchor_id");
            string column_x = g_result->getString("set_x");
            string column_y = g_result->getString("set_y");
            string column_type = g_result->getString("anchor_type");

            cout << column_id  << " : " << column_an_id <<" : " << column_x << ":" << column_y << endl;
            //printf( "%x\n", colum1);
            temp.push_back(column_id);
            temp.push_back(column_an_id);
            temp.push_back(column_x);
            temp.push_back(column_y);
            temp.push_back(column_type);

            foo.push_back(temp);
            temp.clear();

        }
    }
    catch(sql::SQLException& e)
    {
        std::cout << e.what() << std::endl;
        return foo ;
    }
    return foo ;
}

json json_SQL_GetAnchors_info( Statement *&state, ResultSet *&result )
{
    json foo;
    foo["success"] = 0 ;
    json temp ;
    string query = "SELECT * FROM anchor_info;";

    try
    {
        result = state->executeQuery(query);

        while (result->next())
        {
            //string id = result->getString("id");
            string anchor_id    = result->getString("anchor_id");
            string set_x        = result->getString("set_x");
            string set_y        = result->getString("set_y");
            string anchor_type  = result->getString("anchor_type");

//            cout << id  << " : " << anchor_id <<" : " << set_x << ":" << set_y << endl;
            //printf( "%x\n", colum1);
            //temp["id"] = id;
            temp["anchor_id"]   = anchor_id;
            temp["set_x"]       = set_x;
            temp["set_y"]       = set_y;
            temp["anchor_type"] = anchor_type;

            foo["Values"].push_back(temp);
            temp.clear();

        }
    }
    catch(sql::SQLException& e)
    {
        std::cout << e.what() << std::endl;
        return foo ;
    }

    foo["success"] = 1 ;
    cout << foo.dump() << endl ;
    return foo ;
}

json json_SQL_GetGroups_info( Statement *&state, ResultSet *&result )
{
    json foo;
    foo["success"] = 0 ;
    json temp ;
    string query = "SELECT * FROM group_info;";

    try
    {
        result = state->executeQuery(query);

        while (result->next())
        {
            //string id = result->getString("id");
            string group_id         = result->getString("group_id");
            string group_name       = result->getString("group_name");
            string main_anchor_id   = result->getString("main_anchor_id");
            string mode             = result->getString("mode");
            string mode_value       = result->getString("mode_value");
            string fence            = result->getString("fence");


//            cout << id  << " : " << anchor_id <<" : " << set_x << ":" << set_y << endl;
            //printf( "%x\n", colum1);
            //temp["id"] = id;
            temp["group_id"]        = group_id;
            temp["group_name"]      = group_name;
            temp["main_anchor_id"]  = main_anchor_id;
            temp["mode"]            = mode;
            temp["mode_value"]      = mode_value;
            temp["fence"]           = fence;

            foo["Values"].push_back(temp);
            temp.clear();

        }
    }
    catch(sql::SQLException& e)
    {
        std::cout << e.what() << std::endl;
        return foo ;
    }

    foo["success"] = 1 ;
    cout << foo.dump() << endl ;
    return foo ;
}

json json_SQL_GetMaps( Statement *&state, ResultSet *&result )
{
    json foo;
    foo["success"] = 0 ;
    json temp ;
    string query = "SELECT * FROM map_info;";
    try
    {
        result = state->executeQuery(query);
        while (result->next())
        {
            //string id = result->getString("id");
            string map_id       = result->getString("map_id");
            string map_name     = result->getString("map_name");
            string map_file     = result->getString("map_file");
            string map_scale    = result->getString("map_scale");
            string map_file_ext = result->getString("map_file_ext");


            //string time = result->getString("time");

            //temp["id"] = id;
            temp["map_id"]          = map_id;
            temp["map_name"]        = map_name;
            temp["map_file"]        = map_file;
            temp["map_scale"]       = map_scale;
            temp["map_file_ext"]    = map_file_ext;
            //temp["time"] = time;

            foo["Values"].push_back(temp);
            temp.clear();
        }
    }
    catch(sql::SQLException& e)
    {
        std::cout << e.what() << std::endl;
        return foo ;
    }

    foo["success"] = 1 ;
    return foo ;
}

json json_SQL_GetAnchorsInMap( Statement *&state, ResultSet *&result, json func_arg )
{
    json foo;
    foo["success"] = 0 ;
    json temp ;
    string target = func_arg["map_id"].get<std::string>() ;
//    string query = string("") + "select gf.group_id, gf.group_name, gf.main_anchor_id, R.anchor_id from ( " +
//                   "   select GA.group_id, GA.anchor_id from ( " +
//                   "       select mg.group_id " +
//                   "       from map_groups mg where map_id = '" + target + "' " +
//                   "   ) R1 join group_anchors GA where R1.group_id = GA.group_id " +
//                   ")R join group_info gf where gf.group_id = R.group_id ;" ;

    string query = string("") + "select RR.group_id, RR.group_name, RR.main_anchor_id, RR.anchor_id, ai.set_x, ai.set_y from ( " +
                   "   select gf.group_id, gf.group_name, gf.main_anchor_id, R.anchor_id from ( " +
                   "   	select GA.group_id, GA.anchor_id from ( " +
                   "   		select mg.group_id from " +
                   "           map_groups mg where map_id = '" + target + "' " +
                   "       ) R1 join group_anchors GA where R1.group_id = GA.group_id " +
                   "   )R join group_info gf where gf.group_id = R.group_id " +
                   ")RR join anchor_info ai where RR.anchor_id = ai.anchor_id ;" ;

    try
    {
        result = state->executeQuery(query);
        while (result->next())
        {

            string group_id         = result->getString("group_id");
            string group_name       = result->getString("group_name");
            string main_anchor_id   = result->getString("main_anchor_id");
            string anchor_id        = result->getString("anchor_id");
            string set_x            = result->getString("set_x");
            string set_y            = result->getString("set_y");

            temp["group_id"]        = group_id;
            temp["group_name"]      = group_name;
            temp["main_anchor_id"]  = main_anchor_id;
            temp["anchor_id"]       = anchor_id;
            temp["set_x"]           = set_x;
            temp["set_y"]           = set_y;


            foo["Values"].push_back(temp);
            temp.clear();
        }
    }
    catch(sql::SQLException& e)
    {
        std::cout << e.what() << std::endl;
        return foo ;
    }

    foo["success"] = 1 ;
    return foo ;
}


json json_SQL_GetMainAnchorsInMap( Statement *&state, ResultSet *&result, json func_arg )
{
    json foo;
    foo["success"] = 0 ;
    json temp ;
    string target = func_arg["map_id"].get<std::string>() ;
    string query = string("") + "select an.group_id , an.group_name, an.main_anchor_id, ai.set_x, ai.set_y from (" +
                   "   select mg.group_id , gf.group_name, gf.main_anchor_id from (" +
                   "       select group_id from map_groups where map_id = '" + target + "' " +
                   "   )mg join group_info gf where mg.group_id = gf.group_id " +
                   ")an join anchor_info ai where an.main_anchor_id = ai.anchor_id ;" ;
    try
    {
        result = state->executeQuery(query);
        while (result->next())
        {
            // group_id, group_name, main_anchor_id, set_x, set_y
            string group_id         = result->getString("group_id");
            string group_name       = result->getString("group_name");
            string main_anchor_id   = result->getString("main_anchor_id");
            string set_x            = result->getString("set_x");
            string set_y            = result->getString("set_y");

            temp["group_id"]        = group_id;
            temp["group_name"]      = group_name;
            temp["main_anchor_id"]  = main_anchor_id;
            temp["set_x"]           = set_x;
            temp["set_y"]           = set_y;

            foo["Values"].push_back(temp);
            temp.clear();
        }
    }
    catch(sql::SQLException& e)
    {
        std::cout << e.what() << std::endl;
        return foo ;
    }

    foo["success"] = 1 ;
    return foo ;
}


bool save_photo( string file_name, string encodedData, string file_ext )
{

    string decodedData = base64_decode(encodedData);
    string file_exten = file_ext ;

    /*
    int file_exten_len = strlen(strstr( decodedData.c_str(), "\r\n"));
    cout << "file_exten_len :" << file_exten_len << endl ;
    file_exten = decodedData.substr( 1, file_exten_len - 1 ) ;
    cout << "file_exten :" << file_exten << endl ;
    //*/


    ofstream outPutFile;
    // outPutFile.open( file_name + ".jpg", ios::binary | ios::out);
    // outPutFile.open( file_name + ".png", ios_base::out | ios_base::binary );
    outPutFile.open( file_name + "." + file_exten, ios_base::out | ios_base::binary );
    outPutFile.write(decodedData.c_str(), decodedData.length());
    outPutFile.close();

}


json json_SQL_GetOneStaffPhoto( Statement *&state, ResultSet *&result, json func_arg )
{
    json foo;
    foo["success"] = 0 ;
    json temp ;
    string target = func_arg["number"].get<std::string>() ;
    string query = "SELECT * FROM staff where number = '" + target + "' ;";
    try
    {
        result = state->executeQuery(query);
        while (result->next())
        {
//            vector<char> vec;
//            string  photo  = result->getString("photo");
//            vec.insert(vec.end(), photo.begin(), photo.end());
//            cout << photo << endl ;
//            temp["photo"] = vec;

            string photo    = result->getString("photo");
            string file_ext = result->getString("file_ext");

            /*
            const std::string s = "ADP GmbH\nAnalyse Design & Programmierung\nGesellschaft mit beschränkter Haftung" ;
            std::string encoded = base64_encode(reinterpret_cast<const unsigned char*>(s.c_str()), s.length());
            std::string decoded = base64_decode(encoded);
            std::cout << "encoded: " << encoded << std::endl;
            std::cout << "decoded: " << decoded << std::endl;
            //*/

            /*
            string str_bin = "" ;
            // binary string
            for ( int i = 0 ;  i <(int)photo.length() ; i++ )
            {
                bitset<8>b(photo[i]) ;
                str_bin += b.to_string();
            }
            cout << str_bin << endl ;
            //*/

            std::string encoded = photo ;
//            encoded = base64_encode(reinterpret_cast<const unsigned char*>(photo.c_str()), photo.length());
            std::cout << "encoded: " << encoded << std::endl;

            if ( encoded.length() > 0)
            {
                save_photo( target, encoded, file_ext ) ;
            }

            temp["photo"]       = encoded;
            temp["file_ext"]    = file_ext;

            foo["Values"].push_back(temp);
            temp.clear();
        }
    }
    catch(sql::SQLException& e)
    {
        std::cout << e.what() << std::endl;
        return foo ;
    }

    foo["success"] = 1 ;
    return foo ;
}


json json_SQL_Get_One_Staff( Statement *&state, ResultSet *&result, json func_arg )
{
    json foo;
    foo["success"] = 0 ;
    json temp ;
    string target = func_arg["number"].get<std::string>() ;
    string query = "SELECT * FROM staff where number = '" + target + "' ;";
    try
    {

        result = state->executeQuery(query);
        if (result->next())
        {

            string tag_id       = result->getString("tag_id");
            string number       = result->getString("number");
            string Name         = result->getString("Name");
            string department_id= result->getString("department_id");
            string type         = result->getString("type");
            string note         = result->getString("note");

            string lastName     = result->getString("lastName");
            string firstName    = result->getString("firstName");
            string EnglishName  = result->getString("EnglishName");
            string gender       = result->getString("gender");
            string card_id      = result->getString("card_id");

            string status       = result->getString("status");
            string color_type    = result->getString("color_type");
            string color        = result->getString("color");
            string jobTitle_id  = result->getString("jobTitle_id");
            string birthday     = result->getString("birthday");

            string dateEntry    = result->getString("dateEntry");
            string dateLeave    = result->getString("dateLeave");
            string school       = result->getString("school");
            string education    = result->getString("education");

            string phoneJob     = result->getString("phoneJob");
            string phoneSelf    = result->getString("phoneSelf");
            string mail         = result->getString("mail");

            string address      = result->getString("address");
            string photo        = result->getString("photo");
            string exist        = result->getString("exist");
            string grade        = result->getString("grade");
            string tech_grade   = result->getString("tech_grade");
            string file_ext     = result->getString("file_ext");
            string alarm_group_id = result->getString("alarm_group_id");


            string query1 = "", query2 = "", department = "", jobTitle = "" ;
            query1 = "select * from department_relation where c_id = " + department_id + ";" ;
            query2 = "select * from jobTitle_relation where c_id = " + jobTitle_id + ";" ;
            result = state->executeQuery(query1);
            if (result->next())
                department = result->getString("children");

            result = state->executeQuery(query2);
            if (result->next())
                jobTitle = result->getString("children");


            temp["tag_id"]      = tag_id;
            temp["number"]      = number;
            temp["Name"]        = Name;
            temp["department_id"]   = department_id;
            temp["department"]  = department;
            temp["type"]        = type;
            temp["note"]        = note;

            temp["lastName"]    = lastName;
            temp["firstName"]   = firstName;
            temp["EnglishName"] = EnglishName;
            temp["gender"]      = gender;
            temp["card_id"]     = card_id;

            temp["status"]      = status;
            temp["color_type"]  = color_type;
            temp["color"]       = color;
            temp["jobTitle_id"] = jobTitle_id;
            temp["jobTitle"]    = jobTitle;
            temp["birthday"]    = birthday;

            temp["dateEntry"]   = dateEntry;
            temp["dateLeave"]   = dateLeave;
            temp["school"]      = school;
            temp["education"]   = education;

            temp["phoneJob"]    = phoneJob;
            temp["phoneSelf"]   = phoneSelf;
            temp["mail"]        = mail;

            temp["address"]     = address;
            temp["photo"]       = photo;
            temp["exist"]       = exist;
            temp["grade"]       = grade;
            temp["tech_grade"]  = tech_grade;
            temp["file_ext"]    = file_ext;
            temp["alarm_group_id"]  = alarm_group_id;


            foo["Values"].push_back(temp);
            temp.clear();
        }
    }
    catch(sql::SQLException& e)
    {
        std::cout << e.what() << std::endl;
        return foo ;
    }

    foo["success"] = 1 ;
    return foo ;
}




json json_SQL_GetStaffs( Statement *&state, ResultSet *&result )
{
    json foo;
    foo["success"] = 0 ;
    json temp ;
//    string query = "SELECT * FROM staff ORDER BY number;";
    string query = string("") + "select number," +  "tag_id, Name, lastName, firstName, EnglishName, gender, card_id, status, color_type, c.color, department_id," +
                   "jobTitle_id, type, birthday, dateEntry, dateLeave, school, education, phoneJob, phoneSelf, mail, address, note, photo, exist," +
                   "grade, tech_grade, file_ext, alarm_group_id ,e.children as department, e.color  as department_color, jobTitle, jobTitle_color from (" +
                   "SELECT number, tag_id, Name, lastName, firstName, EnglishName, gender, card_id, status, color_type, a.color," +
                   "department_id, jobTitle_id, type, birthday, dateEntry, dateLeave, school, education, phoneJob," +
                   "phoneSelf, mail, address, note, photo, exist, grade, tech_grade, file_ext, alarm_group_id, children as jobTitle, b.color as jobTitle_color FROM (" +
                   "SELECT * FROM staff )a left join jobTitle_relation b on b.c_id = a.jobTitle_id " +
                   ")c left join department_relation e on e.c_id = c.department_id ;" ;
    try
    {
        result = state->executeQuery(query);
        while (result->next())
        {

            string number       = result->getString("number");
            string tag_id       = result->getString("tag_id");
            string Name         = result->getString("Name");
            string lastName     = result->getString("lastName");
            string firstName    = result->getString("firstName");

            string EnglishName  = result->getString("EnglishName");
            string gender       = result->getString("gender");
            string card_id      = result->getString("card_id");
            string status       = result->getString("status");

            string department_id= result->getString("department_id");
            string jobTitle_id  = result->getString("jobTitle_id");
            string type         = result->getString("type");
            string birthday     = result->getString("birthday");
            string dateEntry    = result->getString("dateEntry");

            string dateLeave    = result->getString("dateLeave");
            string school       = result->getString("school");
            string education    = result->getString("education");
            string phoneJob     = result->getString("phoneJob");
            string phoneSelf    = result->getString("phoneSelf");

            string mail         = result->getString("mail");
            string address      = result->getString("address");
            string note         = result->getString("note");
//            string photo        = result->getString("photo");
            string exist        = result->getString("exist");

            string grade        = result->getString("grade");
            string tech_grade   = result->getString("tech_grade");
            string file_ext     = result->getString("file_ext");
            string alarm_group_id = result->getString("alarm_group_id");

            string department   = result->getString("department");
            string department_color = result->getString("department_color");
            string jobTitle     = result->getString("jobTitle");
            string jobTitle_color   = result->getString("jobTitle_color");

            string color_type   = result->getString("color_type");
            string color        = result->getString("color");



//            string query1 = "", query2 = "" , department = "", jobTitle = "" ;
//            query1 = "select * from department_relation where c_id = " + department_id + ";" ;
//            query2 = "select * from jobTitle_relation where c_id = " + jobTitle_id + ";" ;
//            result = state->executeQuery(query1);
//            if (result->next())
//                department = result->getString("children");
//
//            result = state->executeQuery(query2);
//            if (result->next())
//                jobTitle = result->getString("children");

            temp["number"]      = number;
            temp["tag_id"]      = tag_id;
            temp["Name"]        = Name;
            temp["lastName"]    = lastName;
            temp["firstName"]   = firstName;

            temp["EnglishName"] = EnglishName;
            temp["gender"]      = gender;
            temp["card_id"]     = card_id;
            temp["status"]      = status;

            temp["department_id"]= department_id;
            temp["jobTitle_id"] = jobTitle_id;
            temp["type"]        = type;
            temp["birthday"]    = birthday;
            temp["dateEntry"]   = dateEntry;

            temp["dateLeave"]   = dateLeave;
            temp["school"]      = school;
            temp["education"]   = education;
            temp["phoneJob"]    = phoneJob;
            temp["phoneSelf"]   = phoneSelf;

            temp["mail"]        = mail;
            temp["address"]     = address;
            temp["note"]        = note;
//            temp["photo"]       = photo;
            temp["exist"]       = exist;

            temp["grade"]       = grade;
            temp["tech_grade"]  = tech_grade;
            temp["file_ext"]    = file_ext;
            temp["alarm_group_id"]  = alarm_group_id;


            temp["department"]  = department;
            temp["department_color"]    = department_color;
            temp["jobTitle"]    = jobTitle;
            temp["jobTitle_color"]  = jobTitle_color;

            temp["color_type"]  = color_type;
            temp["color"]       = color;



            foo["Values"].push_back(temp);
            temp.clear();
        }
    }
    catch(sql::SQLException& e)
    {
        std::cout << e.what() << std::endl;
        return foo ;
    }

    foo["success"] = 1 ;
    return foo ;
}


json json_SQL_GetFencesInMap( Statement *&state, ResultSet *&result, json func_arg )
{
    json foo;
    foo["success"] = 0 ;
    json temp ;
    string target = func_arg["map_id"].get<std::string>() ;
    string query = string("") + "select * from fence_info where map_id = '" + target + "' ;";

    try
    {
        result = state->executeQuery(query);
        while (result->next())
        {
            // group_id, group_name, main_anchor_id, set_x, set_y
            string fence_id     = result->getString("fence_id");
            string fence_name   = result->getString("fence_name");
            string map_id       = result->getString("map_id");
            string list_type    = result->getString("list_type");


            temp["fence_id"]    = fence_id;
            temp["fence_name"]  = fence_name;
            temp["map_id"]      = map_id;
            temp["list_type"]   = list_type;

            foo["Values"].push_back(temp);
            temp.clear();
        }
    }
    catch(sql::SQLException& e)
    {
        std::cout << e.what() << std::endl;
        return foo ;
    }

    foo["success"] = 1 ;
    return foo ;
}

json json_SQL_GetFence_group( Statement *&state, ResultSet *&result, json func_arg )
{
    json foo;
    foo["success"] = 0 ;
    json temp ;
    string target = func_arg["fence_id"].get<std::string>() ;
    string query = string("") + "select * from fence_group where fence_id = '" + target + "' ;";

    try
    {
        result = state->executeQuery(query);
        while (result->next())
        {
            // group_id, group_name, main_anchor_id, set_x, set_y
            string fence_id = result->getString("fence_id");
            string group_id = result->getString("group_id");

            temp["fence_id"]    = fence_id;
            temp["group_id"]    = group_id;

            foo["Values"].push_back(temp);
            temp.clear();
        }
    }
    catch(sql::SQLException& e)
    {
        std::cout << e.what() << std::endl;
        return foo ;
    }

    foo["success"] = 1 ;
    return foo ;
}

json json_SQL_GetFence_point( Statement *&state, ResultSet *&result, json func_arg )
{
    json foo;
    foo["success"] = 0 ;
    json temp ;
    string target = func_arg["fence_id"].get<std::string>() ;
    string query = string("") + "select * from fence_point where fence_id = '" + target + "' ;";

    try
    {
        result = state->executeQuery(query);
        while (result->next())
        {
            // point_x INT UNSIGNED , point_y INT UNSIGNED, fence_id INT UNSIGNED, point_order TINYINT )

            string point_x      = result->getString("point_x");
            string point_y      = result->getString("point_y");
            string point_order  = result->getString("point_order");
            string fence_id     = result->getString("fence_id");

            temp["point_x"]     = point_x;
            temp["point_y"]     = point_y;
            temp["point_order"] = point_order;
            temp["fence_id"]    = fence_id;

            foo["Values"].push_back(temp);
            temp.clear();
        }
    }
    catch(sql::SQLException& e)
    {
        std::cout << e.what() << std::endl;
        return foo ;
    }

    foo["success"] = 1 ;
    return foo ;
}

json json_SQL_GetFence_info( Statement *&state, ResultSet *&result, json func_arg )
{
    json foo;
    foo["success"] = 0 ;
    json temp ;
    string target = func_arg["fence_id"].get<std::string>() ;
    string query = string("") + "select * from fence_info where fence_id = '" + target + "' ;";

    try
    {
        result = state->executeQuery(query);
        while (result->next())
        {
            // group_id, group_name, main_anchor_id, set_x, set_y
            string fence_id     = result->getString("fence_id");
            string fence_name   = result->getString("fence_name");
            string map_id       = result->getString("map_id");
            string list_type    = result->getString("list_type");


            temp["fence_id"]    = fence_id;
            temp["fence_name"]  = fence_name;
            temp["map_id"]      = map_id;
            temp["list_type"]   = list_type;

            foo["Values"].push_back(temp);
            temp.clear();
        }
    }
    catch(sql::SQLException& e)
    {
        std::cout << e.what() << std::endl;
        return foo ;
    }

    foo["success"] = 1 ;
    return foo ;
}

string Travel_tree( json j_tree, string target, json &ret_json ) // traveling by name
{

    for ( int i = 0 ; i < j_tree.size() ; i++ )
    {
        if ( j_tree[i]["parent"] == target )
        {
            json tp ;
            string key = j_tree[i]["children"].get<std::string>() ;
            string color = j_tree[i]["color"].get<std::string>() ;
            cout << key << "/" ;
            tp["name"] = key;
            tp["color"] = color ;

            json children ;
            string ret_v = Travel_tree( j_tree, key, children ) ;
//            if ( ret_v != "" )
//            {
//                tp["name"] = ret_v ;
            tp["children"] = children ;

//            }
            ret_json.push_back(tp);

        }
    }

//    // if can't not find key in the master list, return key
//    cout << "end level:" << target << endl ;
    cout  << endl ;
    return "" ;

}

string Travel_tree_by_id( json j_tree, string target, json &ret_json )
{
    // travel each node , and build the json tree( by recursive ).

    for ( int i = 0 ; i < j_tree.size() ; i++ )
    {
        if ( j_tree[i]["p_id"] == target )
        {
            json tp ;
            string c_key = j_tree[i]["c_id"].get<std::string>() ;
            string p_key = j_tree[i]["p_id"].get<std::string>() ;

            string name = j_tree[i]["children"].get<std::string>() ;
//            string children = j_tree[i]["children"].get<std::string>() ;
            string color = j_tree[i]["color"].get<std::string>() ;
//            cout << key << "/" ;
            tp["p_id"] = p_key ;

            tp["c_id"] = c_key ;
            tp["id"]   = c_key ;
            tp["name"] = name ;
//            tp["children"] = children ;
            tp["color"] = color ;

            json children ;
            string ret_v = Travel_tree_by_id( j_tree, c_key, children ) ;
//            if ( ret_v != "" )
//            {
//                tp["name"] = ret_v ;
            tp["children"] = children ;

//            }
            ret_json.push_back(tp);

        }
    }

//    // if can't not find c_key in the master list, return c_key
//    cout << "end level:" << target << endl ;
//    cout  << endl ;
    return "" ;

}


json json_SQL_GetDepartment_relation( Statement *&state, ResultSet *&result )
{
    json tree ;

    json foo ;
    foo["success"] = 0 ;
    json temp ;
    string query = "SELECT * FROM department_relation;";
    try
    {
        result = state->executeQuery(query);
        while (result->next()) // get each node from DB, and save into the temp json array.
        {

            string parent   = result->getString("parent");
            string p_id     = result->getString("p_id");
            string children = result->getString("children");
            string c_id     = result->getString("c_id");
            string color    = result->getString("color");


            temp["parent"]      = parent;
            temp["p_id"]        = p_id;
            temp["children"]    = children;
            temp["c_id"]        = c_id;
            temp["color"]       = color;


            tree.push_back(temp);
            temp.clear();
        }
    }
    catch(sql::SQLException& e)
    {
        std::cout << e.what() << std::endl;
        return foo ;
    }

    json ary ;
//    Travel_tree( tree, "", ary ) ;
    Travel_tree_by_id( tree, "0", ary ) ;
    foo["Values"] = ary ;
    foo["success"] = 1 ;
    return foo ;
}

json json_SQL_GetJobTitle_relation( Statement *&state, ResultSet *&result )
{
    json tree ;

    json foo ;
    foo["success"] = 0 ;
    json temp ;
    string query = "SELECT * FROM jobTitle_relation;";
    try
    {
        result = state->executeQuery(query);
        while (result->next()) // get each node from DB, and save into the temp json array.
        {

            string parent   = result->getString("parent");
            string p_id     = result->getString("p_id");
            string children = result->getString("children");
            string c_id     = result->getString("c_id");
            string color    = result->getString("color");


            temp["parent"]      = parent;
            temp["p_id"]        = p_id;
            temp["children"]    = children;
            temp["c_id"]        = c_id;
            temp["color"]       = color;


            tree.push_back(temp);
            temp.clear();
        }
    }
    catch(sql::SQLException& e)
    {
        std::cout << e.what() << std::endl;
        return foo ;
    }

    json ary ;
//    Travel_tree( tree, "", ary ) ;
    Travel_tree_by_id( tree, "0", ary ) ;
    foo["Values"] = ary ;
    foo["success"] = 1 ;
    return foo ;
}


json json_SQL_GetDepartment_relation_list( Statement *&state, ResultSet *&result )
{
    json tree ;

    json foo ;
    foo["success"] = 0 ;
    json temp ;
    string query = "SELECT * FROM department_relation;";
    try
    {
        result = state->executeQuery(query);
        while (result->next()) // get each node from DB, and save into the temp json array.
        {

            string parent   = result->getString("parent");
            string p_id     = result->getString("p_id");
            string children = result->getString("children");
            string c_id     = result->getString("c_id");
            string color    = result->getString("color");


            temp["parent"]      = parent;
            temp["p_id"]        = p_id;
            temp["children"]    = children;
            temp["c_id"]        = c_id;
            temp["color"]       = color;


            tree.push_back(temp);
            temp.clear();
        }
    }
    catch(sql::SQLException& e)
    {
        std::cout << e.what() << std::endl;
        return foo ;
    }

    json ary ;
//    Travel_tree( tree, "", ary ) ;
//    Travel_tree_by_id( tree, "0", ary ) ;
    foo["Values"] = tree ;
    foo["success"] = 1 ;
    return foo ;
}


json json_SQL_GetJobTitle_relation_list( Statement *&state, ResultSet *&result )
{
    json tree ;

    json foo ;
    foo["success"] = 0 ;
    json temp ;
    string query = "SELECT * FROM jobTitle_relation;";
    try
    {
        result = state->executeQuery(query);
        while (result->next()) // get each node from DB, and save into the temp json array.
        {

            string parent   = result->getString("parent");
            string p_id     = result->getString("p_id");
            string children = result->getString("children");
            string c_id     = result->getString("c_id");
            string color    = result->getString("color");


            temp["parent"]      = parent;
            temp["p_id"]        = p_id;
            temp["children"]    = children;
            temp["c_id"]        = c_id;
            temp["color"]       = color;


            tree.push_back(temp);
            temp.clear();
        }
    }
    catch(sql::SQLException& e)
    {
        std::cout << e.what() << std::endl;
        return foo ;
    }

    json ary ;
//    Travel_tree( tree, "", ary ) ;
//    Travel_tree_by_id( tree, "0", ary ) ;
    foo["Values"] = tree ;
    foo["success"] = 1 ;
    return foo ;
}


json json_SQL_GetUserTypes( Statement *&state, ResultSet *&result )
{
    json tree ;

    json foo ;
    foo["success"] = 0 ;
    json temp ;
    string query = "SELECT * FROM user_type;";
    try
    {
        result = state->executeQuery(query);
        while (result->next()) // get each node from DB, and save into the temp json array.
        {
            string type     = result->getString("type");
            string color    = result->getString("color");

            temp["type"]    = type;
            temp["color"]   = color;

            tree.push_back(temp);
            temp.clear();
        }
    }
    catch(sql::SQLException& e)
    {
        std::cout << e.what() << std::endl;
        return foo ;
    }

    foo["Values"] = tree ;
    foo["success"] = 1 ;
    return foo ;
}

json json_alarm_GroupBy_id( json group, json single )
{
    json ret = group ;

    for ( int i = 0 ; i < ret["Values"].size() ; i++ )
    {
        for ( int j = 0 ; j < single["Values"].size() ; j++ )
        {
            if ( ret["Values"][i]["alarm_gid"] == single["Values"][j]["alarm_group_id"] )
            {
                ret["Values"][i]["elements"].push_back( single["Values"][j] ) ;
            }
        }
    }
    cout << ret.dump(2) << endl ;
    return ret ;
}


//json json_SQL_GetAlarmTypes( Statement *&state, ResultSet *&result )
//{
//    json tree ;
//
//    json foo ;
//    foo["success"] = 0 ;
//    json temp ;
//    string query = "SELECT * FROM alarm_info ;";
//    try
//    {
//        result = state->executeQuery(query);
//        while (result->next()) // get each node from DB, and save into the temp json array.
//        {
//            string alarm_id     = result->getString("id");
//            string alarm_name   = result->getString("alarm_name");
//            string alarm_switch = result->getString("alarm_switch");
//            string alarm_value  = result->getString("alarm_value");
//
//            temp["alarm_id"]        = alarm_id;
//            temp["alarm_name"]      = alarm_name;
//            temp["alarm_switch"]    = alarm_switch;
//            temp["alarm_value"]     = alarm_value;
//
//            tree.push_back(temp);
//            temp.clear();
//        }
//    }
//    catch(sql::SQLException& e)
//    {
//        std::cout << e.what() << std::endl;
//        return foo ;
//    }
//
//    foo["Values"] = tree ;
//    foo["success"] = 1 ;
//    return foo ;
//}

json json_SQL_GetAlarmGroup_list( Statement *&state, ResultSet *&result )
{
    json tree ;

    json foo ;
    foo["success"] = 0 ;
    json temp ;
    string query = "SELECT * FROM alarm_group_info ;";
    try
    {
        result = state->executeQuery(query);
        while (result->next()) // get each node from DB, and save into the temp json array.
        {
            string alarm_gid        = result->getString("id");
            string alarm_group_name = result->getString("alarm_group_name");
            string time_group_id     = result->getString("time_group_id");

            temp["alarm_gid"]           = alarm_gid;
            temp["alarm_group_name"]    = alarm_group_name;
            temp["time_group_id"]        = time_group_id;

            tree.push_back(temp);
            temp.clear();
        }
    }
    catch(sql::SQLException& e)
    {
        std::cout << e.what() << std::endl;
        return foo ;
    }

    foo["Values"] = tree ;
    foo["success"] = 1 ;
    return foo ;
}

json json_SQL_GetAlarmInfo_list( Statement *&state, ResultSet *&result )
{
    json tree ;

    json foo ;
    foo["success"] = 0 ;
    json temp ;
    string query = "SELECT * FROM alarm_info ;";
    try
    {
        result = state->executeQuery(query);
        while (result->next()) // get each node from DB, and save into the temp json array.
        {

            string alarm_iid        = result->getString("id");
            string alarm_name       = result->getString("alarm_name");

            string alarm_switch     = result->getString("alarm_switch");
            string alarm_value      = result->getString("alarm_value");
            string alarm_group_id   = result->getString("alarm_group_id");

            temp["alarm_iid"]       = alarm_iid;
            temp["alarm_name"]      = alarm_name;

            temp["alarm_switch"]    = alarm_switch;
            temp["alarm_value"]     = alarm_value;
            temp["alarm_group_id"]  = alarm_group_id;

            tree.push_back(temp);
            temp.clear();
        }
    }
    catch(sql::SQLException& e)
    {
        std::cout << e.what() << std::endl;
        return foo ;
    }

    foo["Values"] = tree ;
    foo["success"] = 1 ;
    return foo ;
}

json json_SQL_GetTimeSlot_list( Statement *&state, ResultSet *&result )
{
    json tree ;

    json foo ;
    foo["success"] = 0 ;
    json temp ;
    string query = "SELECT * FROM time_slot_info ;";
    try
    {
        result = state->executeQuery(query);
        while (result->next()) // get each node from DB, and save into the temp json array.
        {
            // id, time_slot_name, Mon_start, Mon_end, Tue_start, Tue_end, Wed_start, Wed_end, Thu_start, Thu_end, Fri_start, Fri_end, Sat_start, Sat_end, Sun_start, Sun_end
            string time_slot_id     = result->getString("id");
            string time_slot_name   = result->getString("time_slot_name");

            string Mon_start    = result->getString("Mon_start");
            string Mon_end      = result->getString("Mon_end");
            string Tue_start    = result->getString("Tue_start");
            string Tue_end      = result->getString("Tue_end");
            string Wed_start    = result->getString("Wed_start");
            string Wed_end      = result->getString("Wed_end");
            string Thu_start    = result->getString("Thu_start");
            string Thu_end      = result->getString("Thu_end");
            string Fri_start    = result->getString("Fri_start");
            string Fri_end      = result->getString("Fri_end");
            string Sat_start    = result->getString("Sat_start");
            string Sat_end      = result->getString("Sat_end");
            string Sun_start    = result->getString("Sun_start");
            string Sun_end      = result->getString("Sun_end");

            temp["time_slot_id"]    = time_slot_id;
            temp["time_slot_name"]  = time_slot_name;

            temp["Mon_start"]   = Mon_start;
            temp["Mon_end"]     = Mon_end;
            temp["Tue_start"]   = Tue_start;
            temp["Tue_end"]     = Tue_end;
            temp["Wed_start"]   = Wed_start;
            temp["Wed_end"]     = Wed_end;
            temp["Thu_start"]   = Thu_start;
            temp["Thu_end"]     = Thu_end;
            temp["Fri_start"]   = Fri_start;
            temp["Fri_end"]     = Fri_end;
            temp["Sat_start"]   = Sat_start;
            temp["Sat_end"]     = Sat_end;
            temp["Sun_start"]   = Sun_start;
            temp["Sun_end"]     = Sun_end;

            tree.push_back(temp);
            temp.clear();
        }
    }
    catch(sql::SQLException& e)
    {
        std::cout << e.what() << std::endl;
        return foo ;
    }

    foo["Values"] = tree ;
    foo["success"] = 1 ;
    return foo ;
}

json json_SQL_GetTimeGroup_list( Statement *&state, ResultSet *&result )
{
    json tree ;

    json foo ;
    foo["success"] = 0 ;
    json temp ;
    string query = "SELECT * FROM time_group_info ;";
    try
    {
        result = state->executeQuery(query);
        while (result->next()) // get each node from DB, and save into the temp json array.
        {
            string time_group_id    = result->getString("id");
            string time_group_name  = result->getString("time_group_name");


            temp["time_group_id"]   = time_group_id;
            temp["time_group_name"] = time_group_name;


            tree.push_back(temp);
            temp.clear();
        }
    }
    catch(sql::SQLException& e)
    {
        std::cout << e.what() << std::endl;
        return foo ;
    }

    foo["Values"] = tree ;
    foo["success"] = 1 ;
    return foo ;
}

json json_SQL_GetTimeSlot_group( Statement *&state, ResultSet *&result )
{
    json tree ;

    json foo ;
    foo["success"] = 0 ;
    json temp ;
    string query = "SELECT * FROM time_slot_group ;";
    try
    {
        result = state->executeQuery(query);
        while (result->next()) // get each node from DB, and save into the temp json array.
        {
            // id, time_group_info_id, time_slot_id
            string time_group_id    = result->getString("time_group_id");
            string time_slot_id     = result->getString("time_slot_id");

            temp["time_group_id"]   = time_group_id;
            temp["time_slot_id"]    = time_slot_id;


            tree.push_back(temp);
            temp.clear();
        }
    }
    catch(sql::SQLException& e)
    {
        std::cout << e.what() << std::endl;
        return foo ;
    }

    foo["Values"] = tree ;
    foo["success"] = 1 ;
    return foo ;
}

json json_time_GroupBy_id( json group, json group_single, json single )
{
    json j_combine ;
    for ( int i = 0 ; i < group_single["Values"].size() ; i++ )
    {
        for ( int j = 0 ; j < single["Values"].size() ; j++ )
        {
            if (  group_single["Values"][i]["time_slot_id"] == single["Values"][j]["time_slot_id"] )
            {
                json j_tmp = single["Values"][j] ;
                j_tmp["time_group_id"] = group_single["Values"][i]["time_group_id"] ;
                j_combine["Values"].push_back( j_tmp ) ;
            }
        }
    }

    cout << "combine :" << j_combine.dump(2) << endl ;

    json ret = group ;

    for ( int i = 0 ; i < ret["Values"].size() ; i++ )
    {
        for ( int j = 0 ; j < j_combine["Values"].size() ; j++ )
        {
            if ( ret["Values"][i]["time_group_id"] == j_combine["Values"][j]["time_group_id"] )
            {
                ret["Values"][i]["elements"].push_back( j_combine["Values"][j] ) ;
            }
        }
    }
    cout << ret.dump(2) << endl ;

    return ret ;
}

json json_SQL_Return_inserted_map_id( Statement *&state, ResultSet *&result )
{
    json tree ;

    json foo ;
    foo["success"] = 0 ;
    json temp ;
    string query = "select map_id from map_info order by id desc limit 0,1;";
    try
    {
        result = state->executeQuery(query);
        while (result->next())
        {
            string map_id     = result->getString("map_id");
            temp["map_id"]    = map_id;
            tree = temp ;
//            tree.push_back(temp);
            temp.clear();
        }
    }
    catch(sql::SQLException& e)
    {
        std::cout << e.what() << std::endl;
        return foo ;
    }

    foo["Values"] = tree ;
    foo["success"] = 1 ;
    return foo ;
}

json json_SQL_Return_inserted_dept_id( Statement *&state, ResultSet *&result )
{
    json tree ;

    json foo ;
    foo["success"] = 0 ;
    json temp ;
    string query = "select c_id from department_relation order by id desc limit 0,1;";
    try
    {
        result = state->executeQuery(query);
        while (result->next())
        {
            string c_id     = result->getString("c_id");
            temp["c_id"]    = c_id;
            tree = temp ;
//            tree.push_back(temp);
            temp.clear();
        }
    }
    catch(sql::SQLException& e)
    {
        std::cout << e.what() << std::endl;
        return foo ;
    }

    foo["Values"] = tree ;
    foo["success"] = 1 ;
    return foo ;
}


json json_SQL_Return_inserted_job_id( Statement *&state, ResultSet *&result )
{
    json tree ;

    json foo ;
    foo["success"] = 0 ;
    json temp ;
    string query = "select c_id from jobTitle_relation order by id desc limit 0,1;";
    try
    {
        result = state->executeQuery(query);
        while (result->next())
        {
            string c_id     = result->getString("c_id");
            temp["c_id"]    = c_id;
            tree = temp ;
//            tree.push_back(temp);
            temp.clear();
        }
    }
    catch(sql::SQLException& e)
    {
        std::cout << e.what() << std::endl;
        return foo ;
    }

    foo["Values"] = tree ;
    foo["success"] = 1 ;
    return foo ;
}

json json_SQL_Return_inserted_fence_id( Statement *&state, ResultSet *&result )
{
    json tree ;

    json foo ;
    foo["success"] = 0 ;
    json temp ;
    string query = "select fence_id from fence_info order by fence_id desc limit 0,1;";
    try
    {
        result = state->executeQuery(query);
        while (result->next())
        {
            string fence_id     = result->getString("fence_id");
            temp["fence_id"]    = fence_id;
            tree = temp ;
//            tree.push_back(temp);
            temp.clear();
        }
    }
    catch(sql::SQLException& e)
    {
        std::cout << e.what() << std::endl;
        return foo ;
    }

    foo["Values"] = tree ;
    foo["success"] = 1 ;
    return foo ;
}

json json_SQL_Return_alarm_gid( Statement *&state, ResultSet *&result )
{
    json tree ;

    json foo ;
    foo["success"] = 0 ;
    json temp ;
    string query = "select id from alarm_group_info order by id desc limit 0,1;";
    try
    {
        result = state->executeQuery(query);
        while (result->next())
        {
            string id     = result->getString("id");
            temp["alarm_gid"]    = id;
            tree = temp ;
//            tree.push_back(temp);
            temp.clear();
        }
    }
    catch(sql::SQLException& e)
    {
        std::cout << e.what() << std::endl;
        return foo ;
    }

    foo["Values"] = tree ;
    foo["success"] = 1 ;
    return foo ;
}

json json_SQL_Return_time_gid( Statement *&state, ResultSet *&result )
{
    json tree ;

    json foo ;
    foo["success"] = 0 ;
    json temp ;
    string query = "select id from time_group_info order by id desc limit 0,1;";
    try
    {
        result = state->executeQuery(query);
        while (result->next())
        {
            string id     = result->getString("id");
            temp["time_gid"]    = id;
            tree = temp ;
//            tree.push_back(temp);
            temp.clear();
        }
    }
    catch(sql::SQLException& e)
    {
        std::cout << e.what() << std::endl;
        return foo ;
    }

    foo["Values"] = tree ;
    foo["success"] = 1 ;
    return foo ;
}



json json_SQL_GetGroup_Anchors( Statement *&state, ResultSet *&result )
{

    json foo;
    foo["success"] = 0 ;
    json temp ;
    //string query = "SELECT * FROM group_anchors;";
    string query = "select G.group_id, G.group_name, G.main_anchor_id, G_A.anchor_id from  group_anchors G_A,  group_info G where G_A.group_id = G.group_id ;";
    try
    {
        result = state->executeQuery(query);
        while (result->next())
        {
            string group_id         = result->getString("group_id");
            string group_name       = result->getString("group_name");
            string main_anchor_id   = result->getString("main_anchor_id");
            string anchor_id        = result->getString("anchor_id");

            temp["group_id"]        = group_id;
            temp["group_name"]      = group_name;
            temp["main_anchor_id"]  = main_anchor_id;
            temp["anchor_id"]       = anchor_id;
            foo["Values"].push_back(temp);
            temp.clear();

        }
    }
    catch(sql::SQLException& e)
    {
        std::cout << e.what() << std::endl;
        return foo ;
    }

    foo["success"] = 1 ;
    return foo ;
}


json json_SQL_GetMap_Groups( Statement *&state, ResultSet *&result )
{

    json foo;
    foo["success"] = 0 ;
    json temp ;
    string query = "SELECT * FROM map_groups;";
    //string query = "select B.map_id, B.main_anchor_id, A.anchor_id from  map_groups A,  group_info B where A.map_id = B.map_id ;";
    try
    {
        result = state->executeQuery(query);
        while (result->next())
        {
            string map_id       = result->getString("map_id");
            string group_id     = result->getString("group_id");

            temp["map_id"]      = map_id;
            temp["group_id"]    = group_id;
            foo["Values"].push_back(temp);
            temp.clear();

        }
    }
    catch(sql::SQLException& e)
    {
        std::cout << e.what() << std::endl;
        return foo ;
    }

    foo["success"] = 1 ;
    return foo ;
}



json json_SQL_GetTags_info( Statement *&state, ResultSet *&result )
{
    json foo;
    foo["success"] = 0 ;
    json temp ;
    string query = "SELECT * FROM tag_info;";
    try
    {
        result = state->executeQuery(query);
        while (result->next())
        {
            string tag_id       = result->getString("tag_id");
            string tag_name     = result->getString("tag_name");
            string pic_path     = result->getString("pic_path");

            temp["tag_id"]      = tag_id;
            temp["tag_name"]    = tag_name;
            temp["pic_path"]    = pic_path;

            foo["Values"].push_back(temp);
            temp.clear();
        }
    }
    catch(sql::SQLException& e)
    {
        std::cout << e.what() << std::endl;
        return foo ;
    }

    foo["success"] = 1 ;
    return foo ;
}

json Combine_staff_info( json tag_list, json one_tag )
{
    json ret_j = tag_list;

    if ( !one_tag.empty() )
    {
        for ( int j = 0 ; j < j_staff_list.size() ; j++ )
        {
            if ( one_tag["tag_id"].get<std::string>() == j_staff_list[j]["tag_id"].get<std::string>() )
            {
                json a;
                a = one_tag ;
                a["number"] = j_staff_list[j]["number"] ;
                a["Name"]   = j_staff_list[j]["Name"] ;
                ret_j.push_back( a ) ;
                break;
            } // if

        } // for loop j_staff_list

        ret_j.push_back( one_tag ) ;
    } // if one_tag != empty
    return ret_j;

    // return ret_j ;
}

json Find_staff_byTag( string tag_id )
{
//    cout << j_staff_list.dump(2) << endl ;

    for ( int i = 0 ; i < j_staff_list.size() ; i++ )
    {
        if ( j_staff_list[i]["tag_id"].get<std::string>() == tag_id )
        {
            return j_staff_list[i] ;
        } // if
    } // for
    return nullptr ;

} // Find_staff_byTag

json Find_alarm_group_byStaff( json aStaff )
{

    for ( int i = 0 ; i < j_alarm_list["Values"].size() ; i++ )
    {
        if ( j_alarm_list["Values"][i]["alarm_gid"] == aStaff["alarm_group_id"] )
        {
            return j_alarm_list["Values"][i] ;
        }
    }
    return nullptr ;
} // Find_alarm_byStaff

json Find_single_alarm_byAlarmName( json the_alarm_group, string alarm_name )
{
    // alarm_name : low_power, help, active, hidden
    for ( int i = 0 ; i < the_alarm_group["elements"].size() ; i++ )
    {
        if ( the_alarm_group["elements"][i]["alarm_name"].get<std::string>() == alarm_name )
            return the_alarm_group["elements"][i] ;
    } // for
    return nullptr ;
} // Find_single_alarm_byAlarmName

json Find_time_group_byTime_gid( string time_group_id )
{
    for ( int i = 0 ; i < j_time_list["Values"].size() ; i++ )
    {
        if ( j_time_list["Values"][i]["time_group_id"].get<std::string>() == time_group_id )
            return j_time_list["Values"][i] ;
    } // for
    return nullptr ;
}


int Clock_to_int_byFullDate( string str_with_date )
{
    int hh = 0, mm = 0, ss = 0 ;
    int Y = 0, M = 0, D = 0 ;
    string tmp = str_with_date ;
    // 2019/12/13/18:30:50:54 -> 2019-12-13/18:30:50:54
    for ( int i = 0 ; i <2 ; i++ )
        tmp = tmp.replace( tmp.find( "/"),1,"-" );

    cout << tmp << endl ;
    int current = 0;

    int y_pos = tmp.find_first_of("-", current)+1;
    int m_pos = tmp.find_first_of("-", y_pos)+1;
    int d_pos = tmp.find_first_of("/", m_pos)+1;

    int pos_1st = tmp.find_first_of(":", d_pos) +1;
    int pos_2nd = tmp.find_first_of(":", pos_1st) +1;
    int pos_3rd = tmp.find_first_of(":", pos_2nd) +1;
//    cout << pos_1st << " " << pos_2nd << " " << pos_3rd << endl ;


    Y = atoi( tmp.substr(current, y_pos - current).c_str() );
    M = atoi( tmp.substr(y_pos, m_pos - y_pos).c_str() );
    D = atoi( tmp.substr(m_pos, d_pos - m_pos).c_str() );

    hh = atoi( tmp.substr(d_pos, pos_1st - d_pos).c_str() );
    mm = atoi( tmp.substr(pos_1st, pos_2nd - pos_1st).c_str() );
    ss = atoi( tmp.substr(pos_2nd, pos_3rd - pos_2nd).c_str() );
    cout << hh << " " << mm << " " << ss << endl ;

    return Y*60*60*24*31*12 + M*60*60*24*31 + D*60*60*24 + hh*60*60 + mm*60 + ss ;

}

int Clock_to_int_bySQLDate( string str_with_date ) // return sql date format : hh mm ss to int.
{
    int hh = 0, mm = 0, ss = 0 ;
    int Y = 0, M = 0, D = 0 ;
    string tmp = str_with_date ;
    // 2019-12-13 18:30:50:54.82

    cout << tmp << endl ;
    int current = 0;
    int y_pos = tmp.find_first_of("-", current)+1;
    int m_pos = tmp.find_first_of("-", y_pos)+1;
    int d_pos = tmp.find_first_of(" ", m_pos)+1;

    int pos_1st = tmp.find_first_of(":", d_pos) +1;
    int pos_2nd = tmp.find_first_of(":", pos_1st) +1;
    int pos_3rd = tmp.find_first_of(".", pos_2nd) +1;
//    cout << pos_1st << " " << pos_2nd << " " << pos_3rd << endl ;
    Y = atoi( tmp.substr(current, y_pos - current).c_str() );
    M = atoi( tmp.substr(y_pos, m_pos - y_pos).c_str() );
    D = atoi( tmp.substr(m_pos, d_pos - m_pos).c_str() );

    hh = atoi( tmp.substr(d_pos, pos_1st - d_pos).c_str() );
    mm = atoi( tmp.substr(pos_1st, pos_2nd - pos_1st).c_str() );
    ss = atoi( tmp.substr(pos_2nd, pos_3rd - pos_2nd).c_str() );
    cout << Y << " " << M << " " << D << endl ;
    cout << hh << " " << mm << " " << ss << endl ;

    return hh*3600 + mm*60 + ss ;

}

int Clock_to_int_byFullSQLDate( string str_with_date )
{
    int hh = 0, mm = 0, ss = 0 ;
    int Y = 0, M = 0, D = 0 ;
    string tmp = str_with_date ;
    // 2019-12-13 18:30:50:54.82

    cout << tmp << endl ;
    int current = 0;
    int y_pos = tmp.find_first_of("-", current)+1;
    int m_pos = tmp.find_first_of("-", y_pos)+1;
    int d_pos = tmp.find_first_of(" ", m_pos)+1;

    int pos_1st = tmp.find_first_of(":", d_pos) +1;
    int pos_2nd = tmp.find_first_of(":", pos_1st) +1;
    int pos_3rd = tmp.find_first_of(".", pos_2nd) +1;
//    cout << pos_1st << " " << pos_2nd << " " << pos_3rd << endl ;
    Y = atoi( tmp.substr(current, y_pos - current).c_str() );
    M = atoi( tmp.substr(y_pos, m_pos - y_pos).c_str() );
    D = atoi( tmp.substr(m_pos, d_pos - m_pos).c_str() );

    hh = atoi( tmp.substr(d_pos, pos_1st - d_pos).c_str() );
    mm = atoi( tmp.substr(pos_1st, pos_2nd - pos_1st).c_str() );
    ss = atoi( tmp.substr(pos_2nd, pos_3rd - pos_2nd).c_str() );
    cout << Y << " " << M << " " << D << endl ;
    cout << hh << " " << mm << " " << ss << endl ;

    return Y*60*60*24*31*12 + M*60*60*24*31 + D*60*60*24 + hh*60*60 + mm*60 + ss ;

}

int Clock_to_int( string str_without_date )
{
    int hh = 0, mm = 0, ss = 0 ;

    // 18:30:50:54 -> 18:30:50:54
    string tmp = str_without_date ;
//    cout << tmp << endl ;
    int pos = 0;

    int pos_1st = tmp.find_first_of(":", pos) +1;
    int pos_2nd = tmp.find_first_of(":", pos_1st) +1;
    int pos_3rd = tmp.find_first_of(":", pos_2nd) +1;
//    cout << pos_1st << " " << pos_2nd << " " << pos_3rd << endl ;

    hh = atoi( tmp.substr(pos, pos_1st - pos).c_str() );
    mm = atoi( tmp.substr(pos_1st, pos_2nd - pos_1st).c_str() );
    ss = atoi( tmp.substr(pos_2nd, pos_3rd - pos_2nd).c_str() );
//    cout << hh << " " << mm << " " << ss << endl ;

    return hh*3600 + mm*60 + ss ;

}


bool Walk_single_time_group_byWeekDay( json target_time_slot, int WeekDay, string tag_time )
{
    json time_elements = target_time_slot["elements"] ;
    cout << "elements :" << time_elements.dump(2) << endl ;
    string str_day = "" ;

    if ( WeekDay == 1 )
        str_day = "Mon" ;
    else if ( WeekDay == 2 )
        str_day = "Tue" ;
    else if ( WeekDay == 3 )
        str_day = "Wed" ;
    else if ( WeekDay == 4 )
        str_day = "Thu" ;
    else if ( WeekDay == 5 )
        str_day = "Fri" ;
    else if ( WeekDay == 6 )
        str_day = "Sat" ;
    else if ( WeekDay == 7 )
        str_day = "Sun" ;

    string day_start = str_day + "_start", day_end = str_day + "_end" ;
//    cout << "start time :" << day_start << ", end time :" << day_end << endl ;
    int db_clock_start = 0, db_clock_end = 0, tag_clock = 0 ;
    for ( int i = 0 ; i < time_elements.size() ; i++ )
    {
        cout << i << "->" << time_elements[i][day_start].get<std::string>() << endl ;
        string _start = time_elements[i][day_start].get<std::string>() ;
        string _end = time_elements[i][day_end].get<std::string>() ;

        db_clock_start = Clock_to_int( _start ) ;
        db_clock_end = Clock_to_int( _end ) ;
        tag_clock = Clock_to_int_bySQLDate( tag_time ) ;

//        cout << "start int :" << db_clock_start << endl ;
//        cout << "end int :" << db_clock_end << endl ;
//        cout << "tag :" << tag_clock << endl ;


        if ( tag_clock >= db_clock_start && tag_clock <= db_clock_end )
            return true ;

    } // for

    return false ;

}


json Request_GetAlarmList()
{
    json foo;

    foo = j_response ;

    foo["success"] = 1 ;
    return foo ;
}

void Request_Add2AlarmList( string temp_id, string temp_status, string temp_date_time )
{
    json foo;
    foo["success"] = 0 ;
    json temp ;

    for ( int i = 0 ; i < j_response["Values"].size() ; i++ )
    {

        if ( j_response["Values"][i]["tag_id"] == temp_id ) // tag already in list
        {
            j_response["Values"][i]["tag_status"]  = temp_status;
            j_response["Values"][i]["tag_time"]    = temp_date_time;
        } // if
        else
        {
            temp["tag_id"]      = temp_id;
            temp["tag_status"]  = temp_status;
            temp["tag_time"]    = temp_date_time;
            j_response["Values"].push_back(temp);
            temp.clear();
        } // else

    } // for


    foo["success"] = 1 ;
//    return foo ;
}

json Request_RemoveFromAlarmList( Statement *&state, json func_arg )
{
    json foo;
    foo["success"] = 0 ;
    json temp ;

    string tmp_id           = func_arg["tag_id"].get<std::string>() ;
    string tmp_alarm_type   = func_arg["alarm_type"].get<std::string>() ;
    // string tmp_event_type   = func_arg["tag_status"].get<std::string>() ;
    string tmp_event_type   = "End" ;
    string tmp_time         = func_arg["tag_time"].get<std::string>() ;

    try
    {
        string query = "INSERT INTO event VALUES ( '0', '" + tmp_id + "', '" + tmp_alarm_type + "', '" + tmp_event_type + "', '" + tmp_time + "' );";
        SQL_ExecuteUpdate_single( state, query ) ;

    }
    catch(sql::SQLException& e)
    {
        std::cout << e.what() << std::endl;
        return foo ;
    }


    int act_success = 0 ;
    for ( int i = 0 ; i < j_response["Values"].size() ; i++ )
    {
        if ( j_response["Values"][i]["tag_id"] == tmp_id ) // tag already in list
        {
//            j_response["Values"][i].erase("tag_id");
//            j_response["Values"][i].erase("tag_status");
//            j_response["Values"][i].erase("tag_time");
            j_response["Values"].erase(i);
            act_success = 1 ;
        } // if

    } // for


    foo["success"] = act_success ;
    return foo ;
}



string Str2Time_BackDate( string date )
{

    tm tm_;
    time_t t_;
    char buf[128]= {0};

    //strcpy(buf, "2012-01-30");
    string in = date + " 00:00:00" ;
//    cout << in << endl ;


    strcpy (buf, in.c_str());

    strptime(buf, "%Y-%m-%d %H:%M:%S", &tm_); //将字符串转换为tm时间
    tm_.tm_isdst = -1;
    t_  = mktime(&tm_); //将tm时间转换为秒时间
    //t_ += 3600;  //秒数加3600
    t_ -= 86400;

    tm_ = *localtime(&t_);//输出时间
    strftime(buf, 64, "%Y-%m-%d", &tm_);
    cout << buf << endl;

    string val_out = "nothing";
//    cout << "before :" << val_out << endl ;
    val_out = string(buf);
    cout << "LastDay :" << val_out  << "<<" << endl ;

    return val_out ;

}

string Str2Time_ShiftHour( string date )
{

    tm tm_;
    time_t t_;
    char buf[128]= {0};

    //strcpy(buf, "2012-01-30");
    string in = date + ":00:00";
//    cout << in << endl ;


    strcpy (buf, in.c_str());

    strptime(buf, "%Y-%m-%d %H:00:00", &tm_); //将字符串转换为tm时间
    tm_.tm_isdst = -1;
    t_  = mktime(&tm_); //将tm时间转换为秒时间
    //t_ += 3600;  //秒数加3600
    t_ += 3600;

    tm_ = *localtime(&t_);//输出时间
    strftime(buf, 64, "%Y-%m-%d %H", &tm_);
//    cout << buf << endl;

    string val_out = "nothing";
//    cout << "before :" << val_out << endl ;
    val_out = string(buf);
//    cout << "after :" << val_out  << "<<" << endl ;


    return val_out ;

}


string Str2Time_ShiftMin( string date )
{

    tm tm_;
    time_t t_;
    char buf[128]= {0};

    //strcpy(buf, "2012-01-30");
    string in = date + ":00";
//    cout << in << endl ;


    strcpy (buf, in.c_str());

    strptime(buf, "%Y-%m-%d %H:%M:00", &tm_); //将字符串转换为tm时间
    tm_.tm_isdst = -1;
    t_  = mktime(&tm_); //将tm时间转换为秒时间
    //t_ += 3600;  //秒数加3600
    t_ += 60;

    tm_ = *localtime(&t_);//输出时间
    strftime(buf, 64, "%Y-%m-%d %H:%M", &tm_);
//    cout << buf << endl;

    string val_out = "nothing";
//    cout << "before :" << val_out << endl ;
    val_out = string(buf);
//    cout << "after :" << val_out  << "<<" << endl ;


    return val_out ;

}


string Str2Time_Hour( string date, string time )
{

    tm tm_;
    time_t t_;
    char buf[128]= {0};

    //strcpy(buf, "2012-01-30");
    string in = date + " " + time ;
    cout << "in :" << in << endl ;


    strcpy (buf, in.c_str());

    strptime(buf, "%Y-%m-%d %H:00:00", &tm_); //将字符串转换为tm时间
    tm_.tm_isdst = -1;
    t_  = mktime(&tm_); //将tm时间转换为秒时间
    //t_ += 3600;  //秒数加3600
//    t_ += 3600;

    tm_ = *localtime(&t_);//输出时间
    strftime(buf, 64, "%Y-%m-%d %H", &tm_);
    cout << "buf :" << buf << endl;

    string val_out = "nothing";
//    cout << "before :" << val_out << endl ;
    val_out = string(buf);
//    cout << "after :" << val_out  << "<<" << endl ;


    return val_out ;

}

string Str2Time_Min( string date, string time )
{

    tm tm_;
    time_t t_;
    char buf[128]= {0};

    //strcpy(buf, "2012-01-30");
    string in = date + " " + time ;
    cout << "in :" << in << endl ;


    strcpy (buf, in.c_str());

    strptime(buf, "%Y-%m-%d %H:%M:00", &tm_); //将字符串转换为tm时间
    tm_.tm_isdst = -1;
    t_  = mktime(&tm_); //将tm时间转换为秒时间
    //t_ += 3600;  //秒数加3600
//    t_ += 3600;

    tm_ = *localtime(&t_);//输出时间
    strftime(buf, 64, "%Y-%m-%d %H:%M", &tm_);
    cout << "buf :" << buf << endl;

    string val_out = "nothing";
//    cout << "before :" << val_out << endl ;
    val_out = string(buf);
//    cout << "after :" << val_out  << "<<" << endl ;


    return val_out ;

}


string Str2Time_ShiftDate( string date )
{

    tm tm_;
    time_t t_;
    char buf[128]= {0};

    //strcpy(buf, "2012-01-30");
    string in = date + " 00:00:00" ;
//    cout << in << endl ;


    strcpy (buf, in.c_str());

    strptime(buf, "%Y-%m-%d %H:%M:%S", &tm_); //将字符串转换为tm时间
    tm_.tm_isdst = -1;
    t_  = mktime(&tm_); //将tm时间转换为秒时间
    //t_ += 3600;  //秒数加3600
    t_ += 86400;

    tm_ = *localtime(&t_);//输出时间
    strftime(buf, 64, "%Y-%m-%d", &tm_);
//    cout << buf << endl;

    string val_out = "nothing";
//    cout << "before :" << val_out << endl ;
    val_out = string(buf);
//    cout << "after :" << val_out  << "<<" << endl ;


    return val_out ;

}

bool Time_In_Interval( string input, string starting, string ending)
{

    tm tm_, tm_start, tm_end;
    time_t t_, t_start, t_end;

    char buf[128]= {0};
    char buf_start[128]= {0};
    char buf_end[128]= {0};


    strcpy (buf, input.c_str());
    strcpy (buf_start, starting.c_str());
    strcpy (buf_end, ending.c_str());

    strptime(buf, "%Y-%m-%d %H:%M:%S", &tm_); //将字符串转换为tm时间
    strptime(buf_start, "%Y-%m-%d %H:%M:%S", &tm_start); //将字符串转换为tm时间
    strptime(buf_end, "%Y-%m-%d %H:%M:%S", &tm_end); //将字符串转换为tm时间

    tm_.tm_isdst = -1;
    tm_start.tm_isdst = -1;
    tm_end.tm_isdst = -1;

    t_  = mktime(&tm_); //将tm时间转换为秒时间
    t_start  = mktime(&tm_start); //将tm时间转换为秒时间
    t_end  = mktime(&tm_end); //将tm时间转换为秒时间

    if ( t_ >= t_start && t_ <= t_end )
        return true ;
    else
        return false ;

}


json json_SQL_GetSingleLocus( Statement *&state, string tag_id, string start_date, string start_time, string end_date, string end_time, ResultSet *&result )
{
    json foo;
    foo["success"] = 0 ;
    json temp ;

    string query = "select * from locus where tag_id = '" + tag_id + "' ";
    string query2 ;

    //25.26.27.28
    if ( start_date != end_date )
        query2 = "and ( date = '" + start_date + "' and time between '" + start_time + "' and '" + "23:59:59" +"' ) ;";
    else // ( start_date == end_date )
        query2 = "and ( date = '" + start_date + "' and time between '" + start_time + "' and '" + end_time +"' ) ;";



    /*
    select * from locus
    where tag_id = '000000000000000C'
    and ( date = '2019-03-27' and time between '00::00' and '14:20:00' ) limit 0,864000;
    */
    query = query + query2 ;
    cout << query << endl ;
    try
    {
        result = state->executeQuery(query);
        while (result->next())
        {
            string coordinate_x     = result->getString("coordinate_x");
            string coordinate_y     = result->getString("coordinate_y");
            string group_id         = result->getString("group_id");

            temp["coordinate_x"]    = coordinate_x;
            temp["coordinate_y"]    = coordinate_y;
            temp["group_id"]        = group_id;

            foo["Values"].push_back(temp);
            temp.clear();
        }

        string flag = "1" ;
        string in = start_date ;
        string shift_date = Str2Time_ShiftDate( in );

        // after got the first day locus, shift to the next day,and return to web.
        if ( start_date != end_date )
            start_date = shift_date;
        else if ( start_date == end_date )
            flag = "0" ;
        else
            flag = "calculate date error" ;

        foo["start_date"]   = start_date;
        foo["start_time"]   = "00:00:00";
        foo["end_date"]     = end_date;
        foo["end_time"]     = end_time;
        foo["Status"]       = flag ;
        foo["tag_id"]       = tag_id ;
    }
    catch(sql::SQLException& e)
    {
        std::cout << e.what() << std::endl;
        return foo ;
    }

    foo["success"] = 1 ;
    return foo ;

}


json json_SQL_GetSingleLocus_combine( Statement *&state, string tag_id, string start_date, string start_time, string end_date, string end_time, ResultSet *&result )
{
    json foo;
    foo["success"] = 0 ;
    json temp ;

    string query = "select * from locus_combine where tag_id = '" + tag_id + "' ";
    string query2 = "";

    //25.26.27.28
    if ( start_date != end_date )
        query2 = "and ( time between '" + start_date + " " + start_time + "' and '" + start_date + " 23:59:59" + "' ) ;";
    else // ( start_date == end_date )
        query2 = "and ( time between '" + start_date + " " + start_time + "' and '" + start_date + " " + end_time + "' ) ;";
    /*
    select * from locus
    where tag_id = '000000000000000C'
    and ( date = '2019-03-27' and time between '00::00' and '14:20:00' ) limit 0,864000;
    */


    string query3 = " select coordinate_x, coordinate_y, map_id, time from ( select coordinate_x, coordinate_y, group_id, time from locus_combine" ;
    string query4 = " where tag_id = '" + tag_id + "' and time between '" ;
    string query5 = "" ;
    if ( start_date != end_date )
        query5 = start_date + " " + start_time + "' and '" + start_date + " " + "23:59:59" + "' ";
    else // ( start_date == end_date )
        query5 = start_date + " " + start_time + "' and '" + start_date + " " + end_time + "' ";

    string query6 = ")a join map_groups b on b.group_id = a.group_id limit 0,86400  ;" ;
    /*
    select coordinate_x, coordinate_y, map_id, time from (
        select coordinate_x, coordinate_y, group_id, time from locus_combine
        where tag_id = '000000000000000C' and time between '2019-03-29 10:00:32.72' and '2019-03-29 11:00:32.72'
    )a join map_groups b on b.group_id = a.group_id limit 0,86400  ;
    */

    // get the specific TAG in specific DAY & TIME with map_id
    string today_index_in_locus_index       = SQL_Get_indexOf_locus_index_by_date(start_date) ;
    string next_date_index_in_locus_index   = "" ;
    next_date_index_in_locus_index          = SQL_Get_date_by_indexOf_locus_index(today_index_in_locus_index) ;

    string query11 = "select coordinate_x, coordinate_y, map_id, time from (" ;
    string query12 = "select * from (" ;
    // search from the first data's id
    string query13 = "select * from locus_combine where id >= (select index_id from locus_index where date = '" + start_date + "') " ;
    cout << "next indext:" << next_date_index_in_locus_index << endl ;
    if ( next_date_index_in_locus_index != "" )
        query13 += "and id <= '" + next_date_index_in_locus_index + "'" ;

    string query14 = " )e where tag_id = '" + tag_id + "' and time between '";
    string query15 = "";
    if ( start_date != end_date )
        query15 = start_date + " " + start_time + "' and '" + start_date + " " + "23:59:59" + "' ";
    else // ( start_date == end_date )
        query15 = start_date + " " + start_time + "' and '" + start_date + " " + end_time + "' ";

    string query16 = ")a join map_groups b on b.group_id = a.group_id limit 0,864000 ;" ;
    /*
    select coordinate_x, coordinate_y, map_id, time from (
        select coordinate_x, coordinate_y, group_id, time from (
            select * from locus_combine
            where id > (select index_id from locus_index where date = '2019-03-29')
        )e where tag_id = '000000000000000C' and time between '2019-03-29 13:00:32.72' and '2019-03-29 16:00:32.72'
    )a join map_groups b on b.group_id = a.group_id limit 0,864000;
    */


    // get the one day locus ( all tag )
    string query20 = "select a.id, tag_id,coordinate_x, coordinate_y, map_id, time from (" ;
    string query21 = "select * from locus_combine where id >= (select index_id from locus_index where date = '" + start_date + "') " ;
    if ( next_date_index_in_locus_index != "" )
        query21 += "and id <= '" + next_date_index_in_locus_index + "' " ;
    string query22 = ")a join map_groups b on b.group_id = a.group_id limit 0,864000;" ;
    /*
    select * from locus_combine
    	where id >= (select index_id from locus_index where date = '2019-03-29') and id <= '22320127' limit 0,864000;
    */

    string interval_start = start_date + " " + start_time ;
    string interval_end = end_date + " " + end_time ;
    if ( start_date != end_date )
        interval_end = start_date + " " + "23:59:59" ;
    else // ( start_date == end_date )
        interval_end = start_date + " " + end_time ;

    query = query11 + query12 + query13 + query14 + query15 + query16 ;
//    query = query3 + query4 + query5 + query6 ;
//    query = query + query2 ;
//    query = query20 + query21 + query22 ;

    cout << query << endl ;
    int cnt = 0 ;
    try
    {
        string time = "" ;
        string sql_tag_id = "" ;
        string coordinate_x = "" ;
        string coordinate_y = "" ;
        string map_id = "" ;


        result = state->executeQuery(query);


        while (result->next())
        {
//            time = result->getString("time");
////            sql_tag_id = result->getString("tag_id");
////
////
////            if (  sql_tag_id == tag_id && Time_In_Interval( time, interval_start, interval_end )  )
////            {
//                cout << cnt << endl;
//                coordinate_x = result->getString("coordinate_x");
//                coordinate_y = result->getString("coordinate_y");
//                map_id = result->getString("map_id");

//
//                temp["coordinate_x"] = coordinate_x;
//                temp["coordinate_y"] = coordinate_y;
//                temp["map_id"] = map_id;
//                temp["time"] = time;
            temp["coordinate_x"] = result->getString("coordinate_x");
            temp["coordinate_y"] = result->getString("coordinate_y");
            temp["map_id"] = result->getString("map_id");
            temp["time"] = result->getString("time");
            foo["Values"].push_back(temp);
            cnt++;
            temp.clear();
//            }

        }


        string flag = "1" ;
        string in = start_date ;
        string shift_date = Str2Time_ShiftDate( in );

        // after got the first day locus, shift to the next day,and return to web.
        if ( start_date != end_date )
            start_date = shift_date;
        else if ( start_date == end_date )
            flag = "0" ;
        else
            flag = "calculate date error" ;


        foo["start_date"] = start_date;
        foo["start_time"] = "00:00:00";
        foo["end_date"] = end_date;
        foo["end_time"] = end_time;
        foo["Status"] = flag ;
        foo["tag_id"] = tag_id ;
        foo["amount"] = cnt ;
    }
    catch(sql::SQLException& e)
    {
        std::cout << e.what() << std::endl;
        return foo ;
    }

    foo["success"] = 1 ;
    return foo ;

}



json json_SQL_GetSingleLocus_combine_hour( Statement *&state, string tag_id, string start_date, string start_time, string end_date, string end_time, ResultSet *&result )
{
    json foo;
    foo["success"] = 0 ;
    json temp ;

    string query = "";

//    string start_hour = Str2Time_Hour( start_date , start_time ) ; // "2019-04-02", "21:30:57" _->> "2019-04-02 21"
    string end_hour = Str2Time_Hour( end_date, end_time ) ;

//    string start_hour = Str2Time_Hour( "2019-03-29", "00:30:32" ) ;// "2019-04-02", "21:30:57" _->> "2019-04-02 21"
    string start_hour = Str2Time_Hour( start_date, start_time ) ;// "2019-04-02", "21:30:57" _->> "2019-04-02 21"

    end_hour = Str2Time_Hour( end_date, end_time ) ;

//    string query_next_hour = Str2Time_ShiftHour( start_date , start_time ) ;
    cout << endl << "date :" << start_date << endl << "time :" << start_time << endl ;
    cout << "time2hour :" << start_hour << endl ;

    cout << endl << "date :" << end_date << endl << "time :" << end_time << endl ;
    cout << "time2hour :" << end_hour << endl ;
    cout << endl ;

    string index_of_hour_locus_index = SQL_Get_indexOf_locus_index_by_hour( start_hour ) ;

    string next_hour_index_in_locus_index = "" ;
    next_hour_index_in_locus_index = SQL_Get_indexOf_locus_index_by_next_hour( index_of_hour_locus_index );
    string query30 = "select a.id ,coordinate_x, coordinate_y, map_id, time from (" ;
    string query31 = " select * from locus_combine where id >= (select index_id from locus_index_hour where datetime = '" + start_hour + "') " ;
    if ( next_hour_index_in_locus_index != "" )
        query31 += "and id <= '" + next_hour_index_in_locus_index + "' " ;
    string query32 = ")a join map_groups b on b.group_id = a.group_id where tag_id = '" + tag_id + "' ;" ;
    /*
    select a.id ,coordinate_x, coordinate_y, map_id, time from (
    	select * from locus_combine
    	where id >=  '8451948' and id <= '9661440'
    )a join map_groups b on b.group_id = a.group_id where tag_id = '000000000000000C' ;
    */


    query = query30 + query31 + query32 ;
    cout << query << endl ;


    string interval_start = start_date + " " + start_time ;
    string interval_end = end_date + " " + end_time ;
    if ( start_date != end_date )
        interval_end = start_date + " " + "23:59:59" ;
    else // ( start_date == end_date )
        interval_end = start_date + " " + end_time ;

    int cnt = 0 ;
    try
    {
        string time = "" ;
        string sql_tag_id = "" ;
        string coordinate_x = "" ;
        string coordinate_y = "" ;
        string map_id = "" ;


        result = state->executeQuery(query);


        while (result->next())
        {

            time = result->getString("time");

            if ( Time_In_Interval( time, interval_start, interval_end ) )
            {
                temp["coordinate_x"] = result->getString("coordinate_x");
                temp["coordinate_y"] = result->getString("coordinate_y");
                temp["map_id"] = result->getString("map_id");
                temp["time"] = result->getString("time");
                foo["Values"].push_back(temp);
                cnt++;
                temp.clear();
            }

        }


        string flag = "1" ;
        string in = start_hour ;
        string shift_hour = Str2Time_ShiftHour( in );
        shift_hour = Str2Time_ShiftHour( in );
        cout << "start_hour :" << in << endl ;
        // ex. "2019-04-02 21"

        // after got the first day locus, shift to the next day,and return to web.
        if ( start_hour != end_hour )
            start_hour = shift_hour;
        else if ( start_hour == end_hour )
            flag = "0" ;
        else
            flag = "calculate date error" ;

        cout << "shift_hour2 :" << shift_hour << endl ;
        cout << "in shift " << start_hour << endl << endl ;

//        date_part( start_hour ) ;
//        time_part( start_hour ) ;
        string complete_start_hour = start_hour + ":00:00" ;

//        foo["start_date"] = date_part( start_hour ) ;
//        foo["start_time"] = time_part( start_hour ) ;
        foo["start_date"] = Only_get_Date( complete_start_hour ) ;
        foo["start_time"] = Only_get_Time( complete_start_hour ) ;
        foo["end_date"] = end_date;
        foo["end_time"] = end_time;
        foo["Status"] = flag ;
        foo["tag_id"] = tag_id ;
        foo["amount"] = cnt ;
    }
    catch(sql::SQLException& e)
    {
        std::cout << e.what() << std::endl;
        return foo ;
    }

    foo["success"] = 1 ;
    return foo ;

}


json json_SQL_GetSingleLocus_combine_min( Statement *&state, string tag_id, string start_date, string start_time, string end_date, string end_time, ResultSet *&result )
{
    json foo;
    foo["success"] = 0 ;
    json temp ;

    string query = "";

//    string start_hour = Str2Time_Hour( start_date , start_time ) ; // "2019-04-02", "21:30:57" _->> "2019-04-02 21"
    string end_hour = Str2Time_Min( end_date, end_time ) ;

    string start_hour = Str2Time_Min( start_date, start_time ) ;// "2019-04-02", "21:30:57" _->> "2019-04-02 21"

    end_hour = Str2Time_Min( end_date, end_time ) ;

//    string query_next_hour = Str2Time_ShiftHour( start_date , start_time ) ;
    cout << endl << "date :" << start_date << endl << "time :" << start_time << endl ;
    cout << "time2hour :" << start_hour << endl ;

    cout << endl << "date :" << end_date << endl << "time :" << end_time << endl ;
    cout << "time2hour :" << end_hour << endl ;
    cout << endl ;

    string index_of_min_locus_index = SQL_Get_indexOf_locus_index_by_min( start_hour ) ;

    string next_min_index_in_locus_index = "" ;
    next_min_index_in_locus_index = SQL_Get_indexOf_locus_index_by_next_min( index_of_min_locus_index );
    string query30 = "select a.id ,coordinate_x, coordinate_y, map_id, time from (" ;
    string query31 = " select * from locus_combine where id >= (select index_id from locus_index_min where datetime = '" + start_hour + "') " ;
    if ( next_min_index_in_locus_index != "" )
        query31 += "and id <= '" + next_min_index_in_locus_index + "' " ;
    string query32 = ")a join map_groups b on b.group_id = a.group_id where tag_id = '" + tag_id + "' ;" ;
    /*
    select a.id ,coordinate_x, coordinate_y, map_id, time from (
    	select * from locus_combine
    	where id >=  '8451948' and id <= '9661440'
    )a join map_groups b on b.group_id = a.group_id where tag_id = '000000000000000C' ;
    */


    query = query30 + query31 + query32 ;

    cout << query << endl ;

    string interval_start = start_date + " " + start_time ;
    string interval_end = end_date + " " + end_time ;
    if ( start_date != end_date )
        interval_end = start_date + " " + "23:59:59" ;
    else // ( start_date == end_date )
        interval_end = start_date + " " + end_time ;


    int cnt = 0 ;
    try
    {
        string time = "" ;
        string sql_tag_id = "" ;
        string coordinate_x = "" ;
        string coordinate_y = "" ;
        string map_id = "" ;


        result = state->executeQuery(query);


        while (result->next())
        {
            time = result->getString("time");

            if ( Time_In_Interval( time, interval_start, interval_end ) )
            {
                temp["coordinate_x"] = result->getString("coordinate_x");
                temp["coordinate_y"] = result->getString("coordinate_y");
                temp["map_id"] = result->getString("map_id");
                temp["time"] = result->getString("time");
                foo["Values"].push_back(temp);
                cnt++;
                temp.clear();
            }

        }


        string flag = "1" ;
        string in = start_hour ;
        string shift_hour = Str2Time_ShiftMin( in );
        shift_hour = Str2Time_ShiftMin( in );
        cout << "start_hour :" << in << endl ;
        // ex. "2019-04-02 21"

        // after got the first day locus, shift to the next day,and return to web.
        if ( start_hour != end_hour )
            start_hour = shift_hour;
        else if ( start_hour == end_hour )
            flag = "0" ;
        else
            flag = "calculate date error" ;

        cout << "shift_hour2 :" << shift_hour << endl ;
        cout << "in shift " << start_hour << endl << endl ;

//        date_part( start_hour ) ;
//        time_part( start_hour ) ;
        string complete_start_hour = start_hour + ":00" ;

//        foo["start_date"] = date_part( start_hour ) ;
//        foo["start_time"] = time_part( start_hour ) ;
        foo["start_date"] = Only_get_Date( complete_start_hour ) ;
        foo["start_time"] = Only_get_Time( complete_start_hour ) ;
        foo["end_date"] = end_date;
        foo["end_time"] = end_time;
        foo["Status"] = flag ;
        foo["tag_id"] = tag_id ;
        foo["amount"] = cnt ;
    }
    catch(sql::SQLException& e)
    {
        std::cout << e.what() << std::endl;
        return foo ;
    }

    foo["success"] = 1 ;
    return foo ;

}

string Only_get_Time( string tmp )
{
    // 2019/12/13/18:30:50:54 -> 2019-12-13/18:30:50:54
//    for ( int i = 0 ; i <2; i++ )
//        tmp = tmp.replace( tmp.find( "/"),1,"-" );

    int current = 0;
    int pos = tmp.find_first_of(" ", current) + 1 ;

//    tmp = tmp.replace( tmp.find_last_of( ":"),1,"." );
    string rets = tmp.substr(pos, tmp.length() - pos) ;

//    cout << rets << endl ;
    return rets;

//    cout << tmp << endl ;

}

string Only_get_Date( string tmp )
{
    // 2019/12/13/18:30:50:54 -> 2019-12-13/18:30:50:54
//    for ( int i = 0 ; i <2; i++ )
//        tmp = tmp.replace( tmp.find( "/"),1,"-" );

    int current = 0;
    int pos = tmp.find_first_of(" ", current);

    // cout << tmp.substr(current, pos - current)<<endl;
    string rets = tmp.substr(current, pos - current) ;

    return rets;

}




string date_part( string date_with_hour )
{

    tm tm_;
    time_t t_;
    char buf[128]= {0};

    //strcpy(buf, "2012-01-30");
    string in = date_with_hour ; //+ ":00:00" ;
    cout << in << endl ;


    strcpy (buf, in.c_str());

    strptime(buf, "%Y-%m-%d %H:00:00", &tm_); //将字符串转换为tm时间
//    tm_.tm_isdst = -1;
    t_  = mktime(&tm_); //将tm时间转换为秒时间
    //t_ += 3600;  //秒数加3600
//    t_ += 3600;

    tm_ = *localtime(&t_);//输出时间
    strftime(buf, 64, "%Y-%m-%d", &tm_);
    cout << buf << endl;

    string val_out = "nothing";
    val_out = string(buf);
    return val_out ;
}

string time_part ( string date_with_hour )
{
    tm tm_;
    time_t t_;
    char buf[128]= {0};

    //strcpy(buf, "2012-01-30");
    string in = date_with_hour ; //+ ":00:00" ;
    cout << in << endl ;


    strcpy (buf, in.c_str());

    strptime(buf, "%Y-%m-%d %H:00:00", &tm_); //将字符串转换为tm时间
//    tm_.tm_isdst = -1;
    t_  = mktime(&tm_); //将tm时间转换为秒时间
    //t_ += 3600;  //秒数加3600
//    t_ += 3600;

    tm_ = *localtime(&t_);//输出时间
    strftime(buf, 64, "%H:%M:%S", &tm_);
    cout << buf << endl;

    string val_out = "nothing";
    val_out = string(buf);
    return val_out ;
}


string SQL_Get_indexOf_locus_index_by_hour( string date_hour )
{
    // if today's date is 2019/03/29, index of locus_index is 3, get the data of that index of locus_index "4" in the database.
    string ret_val = "";
    Connection *con = nullptr;//= connpool.GetConnection();;
    Statement *state = nullptr;
    ResultSet *result = nullptr;
    try
    {
        SQL_Open_single( con, state, result ) ;


        string get_index = "select * from locus_index_hour where datetime = '" + date_hour + "' ;" ;
        /*
        select * from locus_index_hour where datetime = '2019-04-03 14' ;
        */

        result = state->executeQuery( get_index );
        if (result->next())
        {
            string rownum = result->getString("id");
            ret_val = rownum ;
        }


        SQL_Close_single( con, state, result );

    }
    catch ( exception &e )
    {
        cout << "json parse error from SQL_Get_indexOf_locus_index_by_hour" << endl;
        cout << e.what() << endl ;
        //SQL_Close();
        SQL_Close_single( con, state, result );
        return ret_val;
    }

    return ret_val;
}

string SQL_Get_indexOf_locus_index_by_min( string date_hour )
{
    // if today's date is 2019/03/29, index of locus_index is 3, get the data of that index of locus_index "4" in the database.
    string ret_val = "";
    Connection *con = nullptr;//= connpool.GetConnection();;
    Statement *state = nullptr;
    ResultSet *result = nullptr;
    try
    {
        SQL_Open_single( con, state, result ) ;


        string get_index = "select * from locus_index_min where datetime = '" + date_hour + "' ;" ;
        /*
        select * from locus_index_hour where datetime = '2019-04-03 14' ;
        */

        result = state->executeQuery( get_index );
        if (result->next())
        {
            string rownum = result->getString("id");
            ret_val = rownum ;
        }


        SQL_Close_single( con, state, result );

    }
    catch ( exception &e )
    {
        cout << "json parse error from SQL_Get_indexOf_locus_index_by_min" << endl;
        cout << e.what() << endl ;
        //SQL_Close();
        SQL_Close_single( con, state, result );
        return ret_val;
    }

    return ret_val;
}

string SQL_Get_indexOf_locus_index_by_next_hour( string rownum )
{
    // if today's date is 2019/03/29, index of locus_index is 3, get the data of that index of locus_index "4" in the database.
    string ret_val = "";
    Connection *con = nullptr;//= connpool.GetConnection();;
    Statement *state = nullptr;
    ResultSet *result = nullptr;
    try
    {
        SQL_Open_single( con, state, result ) ;


        string get_index = "select * from locus_index_hour where id = " + rownum + "+1 ;" ;
        /*
        select * from locus_index_hour where datetime = '2019-04-03 14' ;
        */

        cout << "query :" << get_index << endl ;
        result = state->executeQuery( get_index );
        if (result->next())
        {
            string ret_rownum = result->getString("index_id");
            ret_val = ret_rownum ;
        }


        SQL_Close_single( con, state, result );

    }
    catch ( exception &e )
    {
        cout << "json parse error from SQL_Get_indexOf_locus_index_by_next_hour" << endl;
        cout << e.what() << endl ;
        //SQL_Close();
        SQL_Close_single( con, state, result );
        return ret_val;
    }

    return ret_val;
}


string SQL_Get_indexOf_locus_index_by_next_min( string rownum )
{
    // if today's date is 2019/03/29, index of locus_index is 3, get the data of that index of locus_index "4" in the database.
    string ret_val = "";
    Connection *con = nullptr;//= connpool.GetConnection();;
    Statement *state = nullptr;
    ResultSet *result = nullptr;
    try
    {
        SQL_Open_single( con, state, result ) ;


        string get_index = "select * from locus_index_min where id = " + rownum + "+1 ;" ;
        /*
        select * from locus_index_hour where datetime = '2019-04-03 14' ;
        */

        cout << "query :" << get_index << endl ;
        result = state->executeQuery( get_index );
        if (result->next())
        {
            string ret_rownum = result->getString("index_id");
            ret_val = ret_rownum ;
        }


        SQL_Close_single( con, state, result );

    }
    catch ( exception &e )
    {
        cout << "json parse error from SQL_Get_indexOf_locus_index_by_next_min" << endl;
        cout << e.what() << endl ;
        //SQL_Close();
        SQL_Close_single( con, state, result );
        return ret_val;
    }

    return ret_val;
}



string SQL_Get_indexOf_locus_index_by_date( string date )
{
    // if today's date is 2019/03/29, index of locus_index is 3, get the data of that index of locus_index "4" in the database.

    string ret_val = "";
    Connection *con = nullptr;//= connpool.GetConnection();;
    Statement *state = nullptr;
    ResultSet *result = nullptr;
    try
    {
        SQL_Open_single( con, state, result ) ;


        string get_next_index = "select * from ( SELECT  @rownum := @rownum + 1 AS 'rownum',date,index_id " ;
        string get_next_index2 = "FROM  locus_index,(SELECT @rownum := 0)b  )c where date = '" + date + "' ; " ;
        /*
        select * from ( SELECT  @rownum := @rownum + 1 AS 'rownum',date,index_id
            FROM  locus_index,(SELECT @rownum := 0)b
        )c where date = '2019-03-28';
        */


        result = state->executeQuery( get_next_index + get_next_index2 );
        if (result->next())
        {
            string rownum = result->getString("rownum");
            string date = result->getString("date");
            string index_id = result->getString("index_id");
            ret_val = rownum ;
        }


        SQL_Close_single( con, state, result );

    }
    catch ( exception &e )
    {
        cout << "json parse error from SQL_Get_indexOf_locus_index_by_date" << endl;
        cout << e.what() << endl ;
        //SQL_Close();
        SQL_Close_single( con, state, result );
        return ret_val;
    }

    return ret_val;
}

string SQL_Get_date_by_indexOf_locus_index( string rownum )
{
    // if today's date is 2019/03/29, index of locus_index is 3, get the data of that index of locus_index "4" in the database.

    string ret_val = "";
    Connection *con = nullptr;//= connpool.GetConnection();;
    Statement *state = nullptr;
    ResultSet *result = nullptr;
    try
    {
        SQL_Open_single( con, state, result ) ;


        string get_next_index = "select * from ( SELECT  @rownum := @rownum + 1 AS 'rownum',date,index_id " ;
        string get_next_index2 = "FROM  locus_index,(SELECT @rownum := 0)b )c where rownum = " + rownum + "+1 ; " ;

        result = state->executeQuery( get_next_index + get_next_index2 );
        if (result->next())
        {
            string rownum = result->getString("rownum");
            string date = result->getString("date");
            string index_id = result->getString("index_id");
            ret_val = index_id ;
        }


        SQL_Close_single( con, state, result );

    }
    catch ( exception &e )
    {
        cout << "json parse error from SQL_Get_date_by_indexOf_locus_index" << endl;
        cout << e.what() << endl ;
        //SQL_Close();
        SQL_Close_single( con, state, result );
        return ret_val;
    }

    return ret_val;
}



void SQL_Update_locus_index( string date )
{

    Connection *con = nullptr;//= connpool.GetConnection();;
    Statement *state = nullptr;
    ResultSet *result = nullptr;

    try
    {
        SQL_Open_single( con, state, result ) ;


        string search_index = "select * from locus_index where date ='" + date + "';";
        result = state->executeQuery(search_index);


        if ( !result->next() )
        {

            // select * from locus_combine where time like '2019-03-29%' limit 0,1 ;
            string search_locus = "select * from locus_combine where time like '" + date + "%' limit 0,1 ;";

            // find the record in the locus
            result = state->executeQuery(search_locus);
            string id = "" ;

            if ( result->next() ) // if got the record in locus
            {
                id = result->getString("id");
                // add the index into locus_index
                string query = "INSERT INTO locus_index VALUES ( '" + date + "', '" + id + "' );";
                SQL_ExecuteUpdate_single( state, query ) ;
            }
        }

        SQL_Close_single( con, state, result );

    }
    catch ( exception &e )
    {
        cout << "json parse error from SQL_Update_locus_index" << endl;
        cout << e.what() << endl ;
        //SQL_Close();
        SQL_Close_single( con, state, result );
    }
}

void SQL_Update_locus_index_hour( string datetime )
{
    // get the first locus in An Hour
    Connection *con = nullptr;//= connpool.GetConnection();;
    Statement *state = nullptr;
    ResultSet *result = nullptr;

    try
    {
        SQL_Open_single( con, state, result ) ;


        string search_index = "select * from locus_index_hour where datetime ='" + datetime + "';";
        result = state->executeQuery(search_index);


        if ( !result->next() ) // this hour not record yet,so build it
        {
            string search_index = "select * from locus_index_hour order by id desc limit 0,1 ;";
            result = state->executeQuery(search_index);
            string previous_index = "" ;

            if ( result->next() ) // if got last_index
                previous_index = result->getString("index_id");

            // select * from locus_combine where time like '2019-03-29%' limit 0,1 ;
            string search_locus = "select * from locus_combine where time like '" + datetime + "%' " ;

            if ( previous_index != "" ) // if got last_index, query search from last_index
                search_locus += "and id >= " + previous_index + " limit 0,1 ;";
            else
                search_locus += "limit 0,1 ;";

            // find the record in the locus
            result = state->executeQuery(search_locus);
            string id = "" ;

            if ( result->next() ) // if got the record in locus
            {
                id = result->getString("id");
                // add the index into locus_index
                string query = "INSERT INTO locus_index_hour VALUES ( '0', '" + datetime + "', '" + id + "' );";
                SQL_ExecuteUpdate_single( state, query ) ;
            }
        }

        SQL_Close_single( con, state, result );

    }
    catch ( exception &e )
    {
        cout << "json parse error from SQL_Update_locus_index_hour" << endl;
        cout << e.what() << endl ;
        //SQL_Close();
        SQL_Close_single( con, state, result );
    }
}


void SQL_Update_locus_index_hour_min( string datetime )
{
    // get the first locus in An Hour
    Connection *con = nullptr;//= connpool.GetConnection();;
    Statement *state = nullptr;
    ResultSet *result = nullptr;

    try
    {
        SQL_Open_single( con, state, result ) ;


        string search_index = "select * from locus_index_min where datetime ='" + datetime + "';";
        result = state->executeQuery(search_index);

        // if still record this index_min
        if ( !result->next() )
        {
            string search_index = "select * from locus_index_min order by id desc limit 0,1 ;";
            result = state->executeQuery(search_index);
            string previous_index = "" ;

            if ( result->next() )
                previous_index = result->getString("index_id");

            // select * from locus_combine where time like '2019-03-29%' limit 0,1 ;
            string search_locus = "select * from locus_combine where time like '" + datetime + "%' " ;

            if ( previous_index != "" )
                search_locus += "and id >= " + previous_index + " limit 0,1 ;";
            else
                search_locus += "limit 0,1 ;";

            // find the record in the locus
            result = state->executeQuery(search_locus);
            string id = "" ;

            if ( result->next() ) // if got the record in locus
            {
                id = result->getString("id");
                // add the index into locus_index
                string query = "INSERT INTO locus_index_min VALUES ( '0', '" + datetime + "', '" + id + "' );";
                SQL_ExecuteUpdate_single( state, query ) ;
            }
        }

        SQL_Close_single( con, state, result );

    }
    catch ( exception &e )
    {
        cout << "json parse error from SQL_Update_locus_index_hour_min" << endl;
        cout << e.what() << endl ;
        //SQL_Close();
        SQL_Close_single( con, state, result );
    }
}



int SQL_EventType( Statement *&state, json func_arg )
{

    string type     = func_arg["type"].get<std::string>() ;
    string color    = func_arg["color"].get<std::string>() ;

//    string query0 = "SET @last_id_in_table = (SELECT AUTO_INCREMENT  FROM information_schema.tables WHERE table_name = 'user_type' AND table_schema = DATABASE() );" ;
//    SQL_ExecuteUpdate_single( state, query0 ) ;
    string query = string("") + "INSERT INTO user_type VALUES ( '" + type + "','" + color  + "' );" ;

    return SQL_ExecuteUpdate_single( state, query ) ;
}


json RequestList::request_TagList ;
json RequestList::visible_list ; // last next tag_list
json RequestList::invisible_list ;
json RequestList::alarm_status_list ; // allow delete from web UI
json RequestList::alarm_top50_list ;  // keep latest 50 alarm tag_id

int RequestList::bar;

bool RequestList::remove_from_invisible_list( string target_tag )
{
    for ( int i = 0 ; i < invisible_list.size() ; i++ )
    {
        if ( invisible_list[i]["tag_id"] == target_tag )
        {
//            invisible_list[i].erase("tag_id");
//            invisible_list[i].erase("tag_time");
//            //input[i].erase("tag_id");
            invisible_list.erase(i) ;
            return true ;
        }
    }
    return false ;
}

bool RequestList::remove_from_status_list( string target_tag )
{
    for ( int i = 0 ; i < alarm_status_list.size() ; i++ )
    {
        if ( alarm_status_list[i]["tag_id"].get<std::string>() == target_tag )
        {
//            alarm_status_list[i].erase("tag_id");
//            alarm_status_list[i].erase("tag_time");
//            //input[i].erase("tag_id");
            alarm_status_list.erase(i) ;
            return true ;
        }
    }
    return false ;
}

bool RequestList::search_visible_list( string target_tag )
{
    for ( int i = 0 ; i < visible_list.size() ; i++ )
    {
        if ( visible_list[i]["tag_id"].get<std::string>() == target_tag )
        {
            return true ;
        }
    }
    return false ;
}

bool RequestList::search_invisible_list( string target_tag )
{
    for ( int i = 0 ; i < invisible_list.size() ; i++ )
    {
        if ( invisible_list[i]["tag_id"].get<std::string>() == target_tag )
        {
            return true ;
        }
    }
    return false ;
}


json RequestList::add_to_alarm_top50_list( json j_list, json input )
{
    json j_ret ;
    if ( 10 <= j_list.size() )
    {
////        j_list[0].erase("tag_id") ;
////        j_list[0].erase("tag_time") ;
//        j_list[0].clear();
//        j_list.erase(0) ;
        for ( int i = 1 ; i < 10 ; i++ )
        {
            j_ret.push_back(j_list[i]);
        }
        //j_ret.push_back(input);
    } // if
    else
    {
        j_ret = j_list ;
        //j_ret.push_back(input) ;
    }
    j_ret.push_back(input) ;

    return j_ret ;
}

json RequestList::combine_staff_info_to_alarm_list( json staff, json alarm )
{
    json rtn ;
    json temp ;
    for ( int i = 0 ; i < alarm.size() ; i++ )
    {
        for ( int j = 0 ; j < staff.size() ; j++ )
        {
            if ( alarm[i]["tag_id"] == staff[j]["tag_id"] )
            {

                temp["tag_id"]      = alarm[i]["tag_id"] ;
                temp["tag_time"]    = alarm[i]["tag_time"] ;

                temp["Name"]        = staff[j]["Name"] ;
                temp["number"]      = staff[j]["number"] ;
                rtn.push_back(temp) ;

            }
        }
    }
    return rtn ;
}

json RequestList::Call_RequestList_func( string func_name, json func_arg )
{

    json ret ;
    int success = 0 ;

    Connection *con = nullptr;//= connpool.GetConnection();;
    Statement *state = nullptr;
    ResultSet *result = nullptr;

    try
    {
        SQL_Open_single( con, state, result ) ;

        if ( func_name == "GetTagList")
            ret = request_TagList ;


        if ( func_name == "EditInvisibleList" )
        {
            SQL_AddEvent( state,  func_arg["tag_id"].get<std::string>(), "Invisible", "End", func_arg["tag_time"].get<std::string>() );
            remove_from_invisible_list( func_arg["tag_id"].get<std::string>() ) ;
            ret = invisible_list ;
        }

        if ( func_name == "GetInvisibleList" )
        {
            ret = invisible_list ;
        }

        else if ( func_name == "GetAlarmStatusList" )
        {
            ret = alarm_status_list ;
        }
        else if ( func_name == "GetAlarmTop50List" )
        {
            ret = alarm_top50_list ;
        }





        SQL_Close_single( con, state, result );
        return ret ;

    }
    catch(json::parse_error)
    {
        cout << "Call_RequestList_func:parse_error" << endl ;
    }
    catch(json::type_error)
    {
        cout << "Call_RequestList_func:type_error" << endl ;
    }
    catch ( exception &e )
    {
        cout << "json parse error from Call_RequestList_func" << endl;
        cout << e.what() << endl ;
        //SQL_Close();
        SQL_Close_single( con, state, result );
    }

}
