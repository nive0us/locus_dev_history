#include "SQL_Cmd.h"

DBPool  g_connpool = DBPool::GetInstance();

Connection *g_con = nullptr;//= connpool.GetConnection();;
Statement *g_state = nullptr;
ResultSet *g_result = nullptr;

//Connection *g_con2 = nullptr;//= connpool.GetConnection();;
//Statement *g_state2 = nullptr;
//ResultSet *g_result2 = nullptr;




string sql_create_database  = "create database IF NOT EXISTS `PositioningSystem` character set utf8" ;


string sql_create_table     = "CREATE TABLE IF NOT EXISTS  " ;


string sql_create_locus1    = "locus ( id INT UNSIGNED NOT NULL AUTO_INCREMENT, PRIMARY KEY (id), tag_id VARCHAR(16), " ;
string sql_create_locus2    = "coordinate_x INT UNSIGNED, coordinate_y INT UNSIGNED, group_id SMALLINT UNSIGNED, `date` date,`time`time(2) )";
string sql_create_locus     = sql_create_table + sql_create_locus1 + sql_create_locus2 ;


string sql_create_map1      = "map_info ( map_id INT UNSIGNED NOT NULL AUTO_INCREMENT, PRIMARY KEY (map_id), map_name VARCHAR(16), " ;
string sql_create_map2      = "map_path VARCHAR(64) )";
string sql_create_map_info  = sql_create_table + sql_create_map1 + sql_create_map2 ;


string sql_create_group1        = "group_info ( group_id SMALLINT UNSIGNED NOT NULL AUTO_INCREMENT, PRIMARY KEY (group_id), " ;
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
string sql_create_locus_combine     = sql_create_table + sql_create_locus1 + sql_create_locus2 ;





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
string sql_create_event2    = "status TINYINT, `time`datetime(2) )";
string sql_create_event     = sql_create_table + sql_create_event1 + sql_create_event2 ;




string sql_create_staff1    = "staff ( id INT UNSIGNED NOT NULL AUTO_INCREMENT, PRIMARY KEY (id), number VARCHAR(40) NOT NULL, UNIQUE (number), INDEX index_staff(number), " ;
string sql_create_staff2    = string("") + "tag_id VARCHAR(16), INDEX index_tag_id( tag_id ), Name VARCHAR(40)" + ",lastName VARCHAR(40)" + ", firstName VARCHAR(40)" + ",EnglishName VARCHAR(40) ," ;
string sql_create_staff3    = string("") + "gender VARCHAR(10)," + "card_id VARCHAR(40)," + "status VARCHAR(40)," + "set_color VARCHAR(10)," + "department VARCHAR(40)," + "jobTitle VARCHAR(40)," +  "type VARCHAR(40),";
string sql_create_staff4    = string("") + "birthday VARCHAR(10)," + "dateEntry VARCHAR(10)" + ", dateLeave VARCHAR(10)" + ", school VARCHAR(40)" + ", education VARCHAR(10)"
                              + ", phoneJob VARCHAR(20)" + ", phoneSelf VARCHAR(20)" + ", mail VARCHAR(60)" + ", address TEXT" + ", note TEXT" + ", photo BLOB" + ", exist INT" + ")";
string sql_create_staff     = sql_create_table + sql_create_staff1 + sql_create_staff2 + sql_create_staff3 + sql_create_staff4 ;



string sql_create_card_correspond1  = "card_correspond ( id INT UNSIGNED NOT NULL AUTO_INCREMENT, PRIMARY KEY (id), card VARCHAR(24) NOT NULL, INDEX index_card( card ), UNIQUE (card)," ;
string sql_create_card_correspond2  = "number VARCHAR(40) , status TINYINT, `time`datetime(2) )";
string sql_create_card_correspond   = sql_create_table + sql_create_card_correspond1 + sql_create_card_correspond2 ;

string sql_create_department_relation1  = "department_relation ( id INT UNSIGNED NOT NULL AUTO_INCREMENT, PRIMARY KEY (id), " ;
string sql_create_department_relation2  = "master VARCHAR(40), slave VARCHAR(40), color VARCHAR(10), isJobTitle TINYINT )";
string sql_create_department_relation   = sql_create_table + sql_create_department_relation1 + sql_create_department_relation2 ;


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
//        SQL_ExecuteUpdate( sql_create_card_correspond ) ;

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
                success += SQL_AddGroup( state, func_arg[i]["group_id"].get<std::string>(), func_arg[i]["main_anchor_id"].get<std::string>(),
                                         func_arg[i]["mode"].get<std::string>(), func_arg[i]["mode_value"].get<std::string>(), func_arg[i]["fence"].get<std::string>() ) ;

            else if ( func_name == "AddListMap" )
                success += SQL_AddMap( state, func_arg[i]["map_id"].get<std::string>(), func_arg[i]["map_name"].get<std::string>(), func_arg[i]["map_path"].get<std::string>() ) ;


            else if ( func_name == "AddListGroup_Anchor" )
                success += SQL_AddGroup_Anchor( state, func_arg[i]["group_id"].get<std::string>(), func_arg[i]["main_anchor_id"].get<std::string>() );

            else if ( func_name == "AddListMap_Group" )
                success += SQL_AddMap_Group( state, func_arg[i]["map_id"].get<std::string>(), func_arg[i]["group_id"].get<std::string>() );

//            else if ( func_name == "DeleteAnchor" )
//                success = SQL_DeleteAnchor( state, func_arg["anchor_id"] );
//
//            else if ( func_name == "DeleteGroup" )
//                success = SQL_DeleteGroup( state, func_arg["group_id"] );
//
//            else if ( func_name == "DeleteGroup_Anchor" )
//                success = SQL_DeleteGroup_Anchor( state, func_arg["group_id"], func_arg["anchor_id"] );
//
//            else if ( func_name == "DeleteMap" )
//                success = SQL_DeleteMap( state, func_arg["map_id"] );

        } // for

        if ( func_name == "AddStaff" )
            success = SQL_AddStaff( state, func_arg ) ;

        cout << func_name << endl ;

        if ( func_name == "GetAnchors" || func_name == "AddListAnchor" )
            ret = json_SQL_GetAnchors_info( state, result );
        else if ( func_name == "GetGroups" || func_name == "AddListGroup" )
            ret = json_SQL_GetGroups_info( state, result );
        else if ( func_name == "GetMaps" || func_name == "AddListMap" )
            ret = json_SQL_GetMaps( state, result );

        else if ( func_name == "GetStaffs" )
            ret = json_SQL_GetStaffs( state, result );


        else if ( func_name == "GetGroup_Anchors" || func_name == "AddListGroup_Anchor" )
            ret = json_SQL_GetGroup_Anchors( state, result );
        else if ( func_name == "GetMaps_Groups" || func_name == "AddListMap_Group" )
            ret = json_SQL_GetGroup_Anchors( state, result );

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

int SQL_AddAnchor( Statement *&state, string id, string x, string y, string type )
{
//    INSERT INTO anchor_info VALUES ( '0','65512',  '348', '5', 'main' );
    string query = "INSERT INTO anchor_info VALUES ( '"+ id + "', '"+ x +"', '" + y + "', '"+ type + "' );";
//    SQL_Open();
    return SQL_ExecuteUpdate_single( state, query ) ;
//    SQL_Close() ;
}

int SQL_AddGroup( Statement *&state, string group_id, string main_anchor_id, string mode, string mode_value, string fence )
{
    string query = "INSERT INTO group_info VALUES ( '" + group_id + "', '"+  main_anchor_id + "', '" + mode + "' ,'" + mode_value + "', '" + fence + "' );";
    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_AddMap( Statement *&state, string map_id, string map_name, string map_path )
{
    string query = "INSERT INTO map_info VALUES ( '" + map_id + "', '" + map_name + "', '" + map_path + "' );";
    return SQL_ExecuteUpdate_single( state, query ) ;
}


int SQL_AddGroup_Anchor( Statement *&state, string group_id, string main_anchor_id )
{
    string query = "INSERT INTO group_anchors VALUES ( '0','" + group_id + "', '" + main_anchor_id + "' );";
    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_AddMap_Group( Statement *&state, string map_id, string group_id )
{
    string query = "INSERT INTO map_groups VALUES ( '0','" + map_id + "', '" + group_id + "' );";
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

int SQL_AddEvent( Statement *&state, string tag_id, string status, string time )
{
    string query = "INSERT INTO event VALUES ( '0','" + tag_id + "', '" + status + "', '" +  time + "' );";
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
    string set_color    = func_arg["set_color"].get<std::string>() ;
    string department   = func_arg["department"].get<std::string>() ;

    string jobTitle     = func_arg["jobTitle"].get<std::string>() ;
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
    string photo        = func_arg["photo"].get<std::string>() ;
    string exist        = func_arg["exist"].get<std::string>() ;

    /*
    "staff ( id INT UNSIGNED NOT NULL AUTO_INCREMENT, PRIMARY KEY (id), number VARCHAR(40) NOT NULL, UNIQUE (number), INDEX index_staff(number), " ;
     = "tag_id VARCHAR(16), INDEX index_tag_id( tag_id ), Name VARCHAR(40)" + ",lastName VARCHAR(40)" + ", firstName VARCHAR(40)" + ",EnglishName VARCHAR(40) ," ;
     = "gender VARCHAR(10)," + "card_id VARCHAR(40)," + "status VARCHAR(40)," + "department VARCHAR(40)," + "jobTitle VARCHAR(40)," +  "type VARCHAR(40),";
     = "birthday VARCHAR(10)," + "dateEntry VARCHAR(10)" + ", dateLeave VARCHAR(10)" + ", school VARCHAR(40)" + ", education VARCHAR(10)"
            + ", phoneJob VARCHAR(20)" + ", phoneSelf VARCHAR(20)" + ", mail VARCHAR(60)" + ", address TEXT" + ", note TEXT" + ", photo BLOB" + ", exist INT" + ")";
    */

    // id, number, tag_id, Name, lastName, firstName, EnglishName, gender, card_id, status, department, jobTitle, type, birthday, photo, note

    string query = string("") + "INSERT INTO staff VALUES ( '0','" + number + "','" + tag_id + "','" +  Name + "','" +  lastName + "','" + firstName  + "','" +
                   EnglishName + "','" + gender + "','" + card_id + "','" +  status + "','" + set_color + "','" + department + "','" + jobTitle + "','" + type + "','" +
                   birthday + "','" + dateEntry + "','" + dateLeave + "','" + school + "','" + education + "','" + phoneJob + "','" + phoneSelf + "','" +
                   mail + "','" + address + "','" + note + "','" + photo + "','" + exist + "' );" ;

    return SQL_ExecuteUpdate_single( state, query ) ;
}




int SQL_OFF_SafeUpdate( Statement *&state )
{
    string query = "SET SQL_SAFE_UPDATES = 0;";
    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_DeleteAnchor( Statement *&state, string id )
{
    string query = "delete from anchor_info where anchor_id = \"" + id + "\";";
    SQL_OFF_SafeUpdate(state);
    return SQL_ExecuteUpdate_single( state, query ) ;
}
int SQL_DeleteGroup( Statement *&state, string id )
{
    string query = "delete from groups where group_id = \"" + id + "\";";
    SQL_OFF_SafeUpdate(state);
    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_DeleteMap( Statement *&state, string id )
{
    string query = "delete from maps where map_id = \"" + id + "\";";
    SQL_OFF_SafeUpdate(state);
    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_DeleteGroup_Anchor( Statement *&state, string gid, string anid )
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
            string anchor_id = result->getString("anchor_id");
            string set_x = result->getString("set_x");
            string set_y = result->getString("set_y");
            string anchor_type = result->getString("anchor_type");

//            cout << id  << " : " << anchor_id <<" : " << set_x << ":" << set_y << endl;
            //printf( "%x\n", colum1);
            //temp["id"] = id;
            temp["anchor_id"] = anchor_id;
            temp["set_x"] = set_x;
            temp["set_y"] = set_y;
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
            string group_id = result->getString("group_id");
            string main_anchor_id = result->getString("main_anchor_id");
            string mode = result->getString("mode");
            string mode_value = result->getString("mode_value");
            string fence = result->getString("fence");


//            cout << id  << " : " << anchor_id <<" : " << set_x << ":" << set_y << endl;
            //printf( "%x\n", colum1);
            //temp["id"] = id;
            temp["group_id"] = group_id;
            temp["main_anchor_id"] = main_anchor_id;
            temp["mode"] = mode;
            temp["mode_value"] = mode_value;
            temp["fence"] = fence;

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
            string map_id = result->getString("map_id");
            string map_name = result->getString("map_name");
            string map_path = result->getString("map_path");
            //string time = result->getString("time");

            //temp["id"] = id;
            temp["map_id"] = map_id;
            temp["map_name"] = map_name;
            temp["map_path"] = map_path;
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


json json_SQL_GetStaffs( Statement *&state, ResultSet *&result )
{
    json foo;
    foo["success"] = 0 ;
    json temp ;
    string query = "SELECT * FROM staff ORDER BY number;";
    try
    {
        result = state->executeQuery(query);
        while (result->next())
        {

            string tag_id = result->getString("tag_id");
            string number = result->getString("number");
            string Name = result->getString("Name");
            string department = result->getString("department");
            string type = result->getString("type");
            string note = result->getString("note");

            temp["tag_id"] = tag_id;
            temp["number"] = number;
            temp["Name"] = Name;
            temp["department"] = department;
            temp["type"] = type;
            temp["note"] = note;

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

json json_SQL_GetGroup_Anchors( Statement *&state, ResultSet *&result )
{

    json foo;
    foo["success"] = 0 ;
    json temp ;
    //string query = "SELECT * FROM group_anchors;";
    string query = "select G.group_id, G.main_anchor_id, G_A.anchor_id from  group_anchors G_A,  group_info G where G_A.group_id = G.group_id ;";
    try
    {
        result = state->executeQuery(query);
        while (result->next())
        {
            //string id = result->getString("id");
            string group_id = result->getString("group_id");
            string main_anchor_id = result->getString("main_anchor_id");
            string anchor_id = result->getString("anchor_id");

            //temp["id"] = id;
            temp["group_id"] = group_id;
            temp["main_anchor_id"] = main_anchor_id;
            temp["anchor_id"] = anchor_id;
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
            //string id = result->getString("id");
            string map_id = result->getString("map_id");
            string group_id = result->getString("group_id");
//            string anchor_id = result->getString("anchor_id");

            //temp["id"] = id;
            temp["map_id"] = map_id;
            temp["group_id"] = group_id;
//            temp["anchor_id"] = anchor_id;
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
            string tag_id = result->getString("tag_id");
            string tag_name = result->getString("tag_name");
            string pic_path = result->getString("pic_path");

            temp["tag_id"] = tag_id;
            temp["tag_name"] = tag_name;
            temp["pic_path"] = pic_path;

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
            string coordinate_x = result->getString("coordinate_x");
            string coordinate_y = result->getString("coordinate_y");
            string group_id = result->getString("group_id");

            temp["coordinate_x"] = coordinate_x;
            temp["coordinate_y"] = coordinate_y;
            temp["group_id"] = group_id;

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

        foo["start_date"] = start_date;
        foo["start_time"] = "00:00:00";
        foo["end_date"] = end_date;
        foo["end_time"] = end_time;
        foo["Status"] = flag ;
        foo["tag_id"] = tag_id ;
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


        if ( !result->next() )
        {
            string search_index = "select * from locus_index_min order by id desc limit 0,1 ;";
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


