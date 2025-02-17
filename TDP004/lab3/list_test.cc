#include "list.h"
#include "catch.hpp"

//=======================================================================
// Test cases
//=======================================================================

TEST_CASE( "Create an empty list" ) 
{
    List l{};

    CHECK( l.is_empty() );
    CHECK( l.size() == 0 );
}



TEST_CASE( "Insert an item in an empty list" ) 
{
    List l{};

    l.insert(5);
  
    CHECK_FALSE( l.is_empty() );
    CHECK_FALSE( l.size() == 0 );
  
}

TEST_CASE("Destructor")
{
    List l{};
    List l2{};

    l.insert(1);
    l2.insert(1);

    l.~List();

    CHECK(  l.is_empty() );
    CHECK_FALSE(  l2.is_empty() );
}

TEST_CASE("Flyttkonstruktor")
{
    List l{};

    l.insert(5);
    l.insert(3);
    l.insert(9);
    l.insert(7);

    List l2{std::move(l)};

    CHECK(  l.is_empty() );
    CHECK_FALSE(  l2.is_empty() );
}

TEST_CASE("Kopieringstilldelningsoperator")
{
    List l{};
    List l2{};

    l.insert(5);
    l.insert(3);
    l.insert(9);
    l.insert(7);

    l2.insert(5);

    l2 = l;

    l.insert(999);

    CHECK( l.print() == "3 5 7 9 999 ");
    CHECK( l2.print() == "3 5 7 9 ");
}

TEST_CASE("Flyttoperator")
{
    List l{};
    List l2 {};

    l.insert(5);
    l.insert(3);
    l.insert(9);
    l.insert(7);
    l2.insert(10);

    l = std::move(l2);

    CHECK( l.print() == "10 ");
    CHECK( l2.print() == "3 5 7 9 ");

    l = std::move(l2);

    CHECK_FALSE( l.print() == "10 ");
    CHECK_FALSE( l2.print() == "3 5 7 9 ");
}

TEST_CASE("Kopieringskonstruktor")
{
    List l{};

    l.insert(5);
    l.insert(3);
    l.insert(9);
    l.insert(7);

    List l2 {l};
    l2.insert(10);

    CHECK( l.print() == "3 5 7 9 ");
    CHECK( l2.print() == "3 5 7 9 10 ");

    l2.remove(10);

    CHECK_FALSE( l2.print() == "3 5 7 9 10 ");

}

TEST_CASE("Clear")
{
    List l{};

    l.insert(5);
    l.insert(3);
    l.insert(9);
    l.insert(7);

    l.clear();

    CHECK( l.is_empty() );
    l.insert(7);
    CHECK_FALSE( l.is_empty() );
}

TEST_CASE("Remove")
{
    List l{};
    List l2{};

    l.insert(5);
    l.insert(3);
    l.insert(9);
    l.insert(7);
    l2.insert(5);
    l2.insert(3);
    l2.insert(9);
    l2.insert(7);

    CHECK( l.print() == "3 5 7 9 " );  
    l.remove(5);
    CHECK( l.print() == "3 7 9 " );
    l.remove(3);
    CHECK( l.print() == "7 9 " );
    l.remove(9);
    CHECK( l.print() == "7 " ); 
    l.remove(7);
    CHECK( l.print() == "" );

    l2.insert(3);
    l2.insert(5);

    CHECK( l2.print() == "3 3 5 5 7 9 ");

    l2.remove(5);

    CHECK( l2.print() == "3 3 5 7 9 ");

    l2.remove(3);
    l2.remove(3);

    CHECK( l2.print() == "5 7 9 ");   

}

TEST_CASE("Remove non existing values")
{
    List l{};
    List l2{};

    l.insert(5);
    l.insert(5);
    l.insert(5);

    CHECK( l.print() == "5 5 5 ");
    CHECK( l.size() == 3);

    l.remove(3);

    CHECK( l.print() == "5 5 5 ");
    CHECK( l.size() == 3);

    l2.remove(3);

    CHECK( l2.print() == "");
}

TEST_CASE("Move empty list")
{
    List l{};

    List l2{std::move(l)};

    CHECK( l.is_empty());
    CHECK( l2.is_empty());

}

TEST_CASE("Move itself")
{
    List l{};
    l.insert(15);
    l.insert(47);

    l = std::move(l);

    CHECK( l.print() == "15 47 ");

    l = l;

    CHECK( l.print() == "15 47 ");
}