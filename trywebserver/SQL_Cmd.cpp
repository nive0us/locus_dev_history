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
string sql_create_locus2    = "coordinate_x INT UNSIGNED, coordinate_y INT UNSIGNED, group_id SMALLINT UNSIGNED, `time` datetime(2) )";
string sql_create_locus     = sql_create_table + sql_create_locus1 + sql_create_locus2 ;


string sql_create_map1      = "map_info ( map_id INT UNSIGNED NOT NULL AUTO_INCREMENT, PRIMARY KEY (map_id), map_name VARCHAR(16), " ;
string sql_create_map2      = "map_path VARCHAR(64) )";
string sql_create_map_info  = sql_create_table + sql_create_map1 + sql_create_map2 ;


string sql_create_group1    = "group_info ( group_id SMALLINT UNSIGNED NOT NULL AUTO_INCREMENT, PRIMARY KEY (group_id), " ;
string sql_create_group2    = "main_anchor_id VARCHAR(16), mode VARCHAR(8), mode_value VARCHAR(8), fence VARCHAR(8) )";
string sql_create_group_info    = sql_create_table + sql_create_group1 + sql_create_group2 ;

string sql_create_anchor1   = "anchor_info ( anchor_id SMALLINT UNSIGNED NOT NULL AUTO_INCREMENT, PRIMARY KEY (anchor_id), " ;
string sql_create_anchor2   = "set_x INT UNSIGNED, set_y INT UNSIGNED, anchor_type VARCHAR(16) )";
string sql_create_anchor_info   = sql_create_table + sql_create_anchor1 + sql_create_anchor2 ;

string sql_create_group_anchor1 = "group_anchors ( id INT UNSIGNED NOT NULL AUTO_INCREMENT, PRIMARY KEY (id), group_id SMALLINT UNSIGNED, " ;
string sql_create_group_anchor2 = "anchor_id SMALLINT UNSIGNED )";
string sql_create_group_anchor  = sql_create_table + sql_create_group_anchor1 + sql_create_group_anchor2 ;

string sql_create_map_group1 = "map_groups ( id INT UNSIGNED NOT NULL AUTO_INCREMENT, PRIMARY KEY (id), map_id INT UNSIGNED, " ;
string sql_create_map_group2 = "group_id SMALLINT UNSIGNED )";
string sql_create_map_group  = sql_create_table + sql_create_map_group1 + sql_create_map_group2 ;




string sql_create_tag1  = "tag_info ( tag_id INT UNSIGNED NOT NULL, PRIMARY KEY (tag_id), tag_name VARCHAR(16), " ;
string sql_create_tag2  = "pic_path VARCHAR(128) )";
string sql_create_tag   = sql_create_table + sql_create_tag1 + sql_create_tag2 ;


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

        cout << func_name << endl ;

        if ( func_name == "GetAnchors" || func_name == "AddListAnchor" )
            ret = json_SQL_GetAnchors_info( state, result );
        else if ( func_name == "GetGroups" || func_name == "AddListGroup" )
            ret = json_SQL_GetGroups_info( state, result );
        else if ( func_name == "GetMaps" || func_name == "AddListMap" )
            ret = json_SQL_GetMaps( state, result );


        else if ( func_name == "GetGroup_Anchors" || func_name == "AddListGroup_Anchor" )
            ret = json_SQL_GetGroup_Anchors( state, result );
        else if ( func_name == "GetMaps_Groups" || func_name == "AddListMap_Group" )
            ret = json_SQL_GetGroup_Anchors( state, result );

        else if ( func_name == "GetTags" )
            ret = json_SQL_GetTags_info( state, result );

        else if ( func_name == "GetLocus" )
            ret = json_SQL_GetSingleLocus( state, func_arg["tag_id"].get<std::string>(), func_arg["time_start"].get<std::string>(),  func_arg["time_end"].get<std::string>(), result ) ;


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



int SQL_AddLocus( Statement *&state, string tag_id, string x, string y, string group_id, string time )
{
    string query = "INSERT INTO locus VALUES ( '0','" + tag_id + "', '" + x + "', '" + y + "', '" + group_id + "', '" + time + "' );";
    return SQL_ExecuteUpdate_single( state, query ) ;
}

int SQL_AddTag( Statement *&state, string tag_id, string tag_name, string pic_path )
{
    string query = "INSERT INTO tag_info VALUES ( '" + tag_id + "', '" + tag_name + "', '" + pic_path + "' );";
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

json json_SQL_GetSingleLocus( Statement *&state, string tag_id, string time_start, string time_end, ResultSet *&result ) {
    json foo;
    foo["success"] = 0 ;
    json temp ;
    string query = "select * from locus where tag_id = '" + tag_id + "' and time >= '" + time_start + "'and time =< '" + time_end + "' ;";
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
    }
    catch(sql::SQLException& e)
    {
        std::cout << e.what() << std::endl;
        return foo ;
    }

    foo["success"] = 1 ;
    return foo ;


}
