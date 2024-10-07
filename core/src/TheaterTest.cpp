#include "gtest/gtest.h"

#include "../inc/Theater.h"

using namespace std;
using namespace testing;

TEST(TheaterTest, ctor)
{
     string name("King Room");
     int capacity = 20;

     Theater theater(name, capacity);
     EXPECT_EQ(theater.getName(), name);
     EXPECT_EQ(theater.getCapacity(), capacity);

     Theater theater2(theater);
     EXPECT_EQ(theater2.getName(), name);
     EXPECT_EQ(theater2.getCapacity(), capacity);

     Theater theater3 = theater2;
     EXPECT_EQ(theater3.getName(), name);
     EXPECT_EQ(theater3.getCapacity(), capacity);
}

TEST(TheaterTest, setgetor)
{
     string name("King Room");
     int capacity = 20;

     Theater theater(name, capacity);

     string new_name = "Queeen Room";
     int new_capacity = 30;
     theater.setName(new_name);
     theater.setCapacity(new_capacity);

     EXPECT_EQ(theater.getName(), new_name);
     EXPECT_EQ(theater.getCapacity(), new_capacity);
}

