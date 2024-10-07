#include "gtest/gtest.h"

#include "../inc/Movie.h"

using namespace std;
using namespace testing;

TEST(MovieTest, ctor)
{
     string name("Beautiful Mind");
     int duration = 150;

     Movie movie(name, duration);
     EXPECT_EQ(movie.getName(), name);
     EXPECT_EQ(movie.getDuration(), duration);

     Movie movie2(movie);
     EXPECT_EQ(movie2.getName(), name);
     EXPECT_EQ(movie2.getDuration(), duration);

     Movie movie3 = movie2;
     EXPECT_EQ(movie3.getName(), name);
     EXPECT_EQ(movie3.getDuration(), duration);
}

TEST(MovieTest, setgetor)
{
     string name("Beautiful Mind");
     int duration = 150;

     Movie movie(name, duration);

     string new_name = "Intersateller";
     int new_duration = 146;
     movie.setName(new_name);
     movie.setDuration(new_duration);

     EXPECT_EQ(movie.getName(), new_name);
     EXPECT_EQ(movie.getDuration(), new_duration);
}

