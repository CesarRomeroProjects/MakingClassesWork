#include "catch_amalgamated.hpp"

#include <string>
#include <fstream>  


#include "GenericQueue.hpp"


namespace{




TEST_CASE("MyFirstEnqueue", "[RequiredQueue]")
{
    GenericQueue<std::string> a;
    a.enqueue("Mike");
    REQUIRE( a.front() == "Mike" );
}

TEST_CASE("FrontThrowsWhenNone", "[RequiredQueue]")
{
    GenericQueue<std::string> q;
    REQUIRE_THROWS_AS( q.front(), QueueEmptyException );
}

TEST_CASE("FrontHasValue", "[FYI]")
{
    GenericQueue<std::string> q;
    q.enqueue("Foxy");
    REQUIRE( q.front() == "Foxy");
}

TEST_CASE("ChangedFrontValue", "[FYI]")
{
    GenericQueue<std::string> q;
    q.enqueue("Foxy");
    q.enqueue("Freddy");
    q.dequeue();
    REQUIRE( q.front() == "Freddy");
}

TEST_CASE("CopyConstructor", "[FYI]")
{
    GenericQueue<std::string> q;
    q.enqueue("Mike");
    q.enqueue("Goomba");
    q.enqueue("Harold");

    GenericQueue copyQueue{GenericQueue(q)};
    copyQueue.enqueue("David");

    REQUIRE( q.size() == 3);
    REQUIRE( copyQueue.size() == 4);
}

TEST_CASE("EmptyQueue", "[FYI]")
{
    GenericQueue<std::string> q;
    REQUIRE( q.isEmpty() );
    REQUIRE_THROWS_AS( q.front(), QueueEmptyException );
}

TEST_CASE("EmptyQueue2", "[FYI]")
{
    GenericQueue<int> q;
    REQUIRE( q.isEmpty() );
    REQUIRE_THROWS_AS( q.front(), QueueEmptyException );
}

TEST_CASE("SingleElementQueue", "[FYI]")
{
    GenericQueue<float> q;
    REQUIRE( q.size() == 0 );
    REQUIRE( q.isEmpty() );
    REQUIRE_THROWS_AS( q.front(), QueueEmptyException );
    q.enqueue(12.05f);
    REQUIRE( q.size() == 1 );
    REQUIRE( q.isEmpty() == false );
    REQUIRE( q.front() == 12.05f );
    q.dequeue();
    REQUIRE( q.size() == 0 );
    REQUIRE( q.isEmpty() );
    REQUIRE_THROWS_AS( q.front(), QueueEmptyException );
}

TEST_CASE("DeepCopy")
{
    GenericQueue<std::string> a;
    a.enqueue("Mike");
    GenericQueue<std::string> b{a};
    b.dequeue();
    REQUIRE( a.front() == "Mike" );
    REQUIRE( b.isEmpty() );
}

TEST_CASE("AssignmentCopy")
{
    GenericQueue<unsigned> a;
    a.enqueue(1000);
    GenericQueue<unsigned> b;
    b.enqueue(500);
    b.dequeue();
    REQUIRE( a.front() == 1000 );
    REQUIRE( b.isEmpty() );
}

TEST_CASE("AssignmentCopy2")
{
    GenericQueue<double> a;
    a.enqueue(30.04);
    a.enqueue(40.83);
    GenericQueue<double> b;
    b.enqueue(12.03);
    b = a;
    b.dequeue();
    REQUIRE( a.front() == 30.04 );
    REQUIRE( a.size() == 2 );
    REQUIRE( b.size() == 1 );
}

TEST_CASE("AssignmentCopy3")
{
    GenericQueue<std::string> a;
    GenericQueue<std::string> b;
    b.enqueue("A");
    b = a;
    REQUIRE( a.isEmpty() );
    REQUIRE( b.isEmpty() );
}

TEST_CASE("AssignmentCopy4")
{
    GenericQueue<std::string> a;
    a.enqueue("A");
    a.enqueue("B");
    a.enqueue("C");
    GenericQueue<std::string> b;
    b.enqueue("4");
    b.enqueue("5");
    b.enqueue("6");
    b = a;
    REQUIRE( a.size() == b.size() );
    while(!a.isEmpty() && !b.isEmpty())
    {
        REQUIRE(a.front() == b.front());
        a.dequeue();
        b.dequeue();
    }
    REQUIRE(a.isEmpty() == b.isEmpty());
}
               
} // end namespace

