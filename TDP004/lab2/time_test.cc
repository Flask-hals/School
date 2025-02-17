#include "catch.hpp"
#include "Time.h"
#include <sstream>

using namespace std;

TEST_CASE ("Constructors and getters")
{
   SECTION("Default")
   {
      Time empty{};
      CHECK( empty.get_hour()   == 0 );
      CHECK( empty.get_minute() == 0 );
      CHECK( empty.get_second() == 0 );
   }



   SECTION("Integer")
   {
      Time t0{0,0,0};
      Time t1{12,30,30};
      Time t2{23,59,59};

      CHECK_THROWS( Time{13,35,60} );
      CHECK_THROWS( Time{13,60,35} );
      CHECK_THROWS( Time{24,35,35} );
             
      CHECK( t0.get_hour()   == 0 );
      CHECK( t0.get_minute() == 0 );
      CHECK( t0.get_second() == 0 );
      CHECK( t1.get_hour()   == 12 );
      CHECK( t1.get_minute() == 30 );
      CHECK( t1.get_second() == 30 );
      CHECK( t2.get_hour()   == 23 );
      CHECK( t2.get_minute() == 59 );
      CHECK( t2.get_second() == 59 );
   }



   SECTION("String")
   {
      Time t0{"00:00:00"};
      Time t1{"12:30:30"};
      Time t2{"23:59:59"};
      Time t3{""};

      CHECK_THROWS(Time{"12:30:60"});
      CHECK_THROWS(Time{"12:60:35"});
      CHECK_THROWS(Time{"24:35:35"});
      CHECK_THROWS(Time{"20;50;59"});
      CHECK_THROWS(Time{"2s:5b:c9"});
      CHECK_THROWS(Time{"aawfkjag24:35:35"});
      CHECK_THROWS(Time{"24:35:355219875awfakj"});
      CHECK_THROWS(Time{"24:3gsadgl5:35"});

      CHECK( t0.get_hour()   == 0 );
      CHECK( t0.get_minute() == 0 );
      CHECK( t0.get_second() == 0 );
      CHECK( t1.get_hour()   == 12 );
      CHECK( t1.get_minute() == 30 );
      CHECK( t1.get_second() == 30 );
      CHECK( t2.get_hour()   == 23 );
      CHECK( t2.get_minute() == 59 );
      CHECK( t2.get_second() == 59 );
      CHECK( t3.to_string() == "00:00:00");  
   }

}
 
TEST_CASE ("is_am") 
{
   Time t0{"05:00:00"};
   Time t1{"14:00:00"};
   Time t2{"00:00:00"};
   Time t3{"12:00:00"};
   CHECK       ( t0.is_am() );
   CHECK_FALSE ( t1.is_am() );
   CHECK       ( t2.is_am() );
   CHECK_FALSE ( t3.is_am() );
}


TEST_CASE ("to_string")
{
   Time t0{};
   Time t1{11, 59, 59};
   Time t2{12, 0, 0};
   Time t3{13, 0, 0};
   Time t4{23, 59, 59};
   SECTION("24 hour format no argument")
   {
      CHECK( t0.to_string() == "00:00:00" );
      CHECK( t1.to_string() == "11:59:59" );
      CHECK( t2.to_string() == "12:00:00" );
      CHECK( t3.to_string() == "13:00:00" );
      CHECK( t4.to_string() == "23:59:59" );
   }
   
   SECTION("24 hour format with argument")
   {
      CHECK( t0.to_string(24) == "00:00:00");
      CHECK( t1.to_string(24) == "11:59:59" );
      CHECK( t2.to_string(24) == "12:00:00" );
      CHECK( t3.to_string(24) == "13:00:00" );
      CHECK( t4.to_string(24) == "23:59:59" );
      CHECK_THROWS( t0.to_string(22));
      CHECK_THROWS( t2.to_string(25));
   } 

   SECTION("12 hour format")
   {
      CHECK( t0.to_string(12) == "12:00:00am");
      CHECK( t1.to_string(12) == "11:59:59am" );
      CHECK( t2.to_string(12) == "12:00:00pm" );
      CHECK( t3.to_string(12) == "01:00:00pm" );
      CHECK( t4.to_string(12) == "11:59:59pm" );
      CHECK_THROWS( t0.to_string(11));
      CHECK_THROWS( t1.to_string(13));
   }
}

// Fyll med flera tester av andra funktioner och operatorer!
TEST_CASE ("operator++")
{
   Time t0("11:59:59");
   Time t1("12:59:59");
   Time t2("14:00:59");
   Time t3("16:00:59");
   Time t4("23:59:59");

   SECTION("second_change")
   {
   CHECK    ((++t4).to_string() == "00:00:00");
   CHECK    ((t4++).to_string() == "00:00:00");
   CHECK    (t4.to_string() == "00:00:01");
   }

   SECTION("minute_change")
   {
   CHECK    ((++t2).to_string() == "14:01:00");
   CHECK    ((t3++).to_string() == "16:00:59");
   CHECK    (t3.to_string() == "16:01:00");
   }

   SECTION("hour_change")
   {
   CHECK    ((++t0).to_string() == "12:00:00");
   CHECK    ((t1++).to_string() == "12:59:59");
   CHECK    (t1.to_string() == "13:00:00");
   }
}


TEST_CASE ("operators")
{
   Time t0{"00:00:00"};
   Time t1{"13:00:00"};
   Time t2{"12:00:00"};
   Time t3{13, 0, 0};
   Time t4{23, 59, 59};
   Time t5{"00:00:00"};
   Time t6{"15:39:12"};
   std::stringstream os;

   SECTION("operator<")
   {
   CHECK    (t0 < t1);
   CHECK_FALSE (t1<t2);
   }

   SECTION("operator>")
   {
      CHECK    (t1>t2);
      CHECK_FALSE (t2>t1);
   }

   SECTION("operator<=")
   {
      CHECK    (t0<=t5);
      CHECK_FALSE (t1<=t2);
   }
   
   SECTION("operator>=")
   {
      CHECK    (t5>=t0);
      CHECK_FALSE (t3>=t4);
   }

   SECTION("operator==")
   {
      CHECK    (t0==t5);
      CHECK_FALSE (t0==t1);
   }
   
   SECTION("operator!=")
   {
      CHECK    (t1!=t2);
      CHECK_FALSE (t5!=t0);
   }

   SECTION("operator<<")
   {  
      os << t6;
      CHECK    ( os.str() == "15:39:12");
      os.str("");
      os << t4;
      CHECK    ( os.str() == "23:59:59");
      os.str("");
      os << t0;
      CHECK    ( os.str() == "00:00:00");
   }

}
TEST_CASE ("convert_to_second")
{
   Time t0("11:59:59");
   Time t1("01:01:01");

   CHECK    (t0.convert_to_second() == 43199);
   CHECK    (t1.convert_to_second() == 3661);
}