//#include "Alarm.h"
//
//using namespace std;
//
//
//json Alarm::visible_list ; // last next tag_list
//json Alarm::invisible_list ;
//
//int Alarm::bar;
//
//bool Alarm::remove_from_invisible_list( json input, string target_tag )
//{
//    for ( int i = 0 ; i < input.size() ; i++ )
//    {
//        if ( input[i]["tag_id"] == target_tag )
//        {
//            input[i].erase("tag_id");
//            input[i].erase("time");
//            //input[i].erase("tag_id");
//            return true ;
//        }
//    }
//    return false ;
//}
//
//bool Alarm::search_visible_list( json input, string target_tag )
//{
//    for ( int i = 0 ; i < input.size() ; i++ )
//    {
//        if ( input[i]["tag_id"] == target_tag )
//        {
//            return true ;
//        }
//    }
//    return false ;
//}
//
//
//json Alarm::Call_Alarm_func( string func_name, json func_arg ) {
//
//
//
//
//}
