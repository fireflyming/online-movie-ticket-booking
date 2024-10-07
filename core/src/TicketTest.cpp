#include <memory>
#include <sstream>
#include <gtest/gtest.h>

#include "../inc/Ticket.h"
#include "../inc/FakeUserRule.h"

using namespace std;

class MockUserRule;

TEST(TicketTest, print)
{
    // a user
    FakeUserRule userRule;
    shared_ptr<User> user = make_shared<User>();
    string password, firstName, lastName, phone, email;

    password = "abc@EDFG5";
    firstName = "First_Name";
    lastName = "Last_Name";
    phone = "12345678";
    email = "username@email.com";
    EXPECT_EQ(user->doRegister(userRule, password, firstName, lastName, phone, email), User::Result::Result0);


    // a movie
    string movie_name = "Beautiful Mind";
    int movie_duration = 127;
    shared_ptr<Movie> movie = make_shared<Movie>(movie_name, movie_duration);

    // a theater
    string  theater_name = "King Room";
    int theater_capacity = 5; // a mini theater for easy testing
    shared_ptr<Theater> theater = make_shared<Theater>(theater_name, theater_capacity);

    // a show for booking
    string show_starttime = "2024-10-07 14:30:00";
    shared_ptr<Show> show = make_shared<Show>(movie, theater, show_starttime);

    // booking a seat
    vector<Show::seat_t> seats { 0 };
    EXPECT_TRUE(show->bookSeats(seats));

    // generate a ticket if success
    int price = 80;
    Ticket ticket(user, show, seats[0], price);

    ostringstream ticket_info;
    ticket_info << "User Id: " << user->getUserId() << ","
                << "Movie Name: " << movie_name << ","
                << "Theater Name: " << theater_name << ","
                << "Start Time: " << show_starttime << ","
                << "Seat Number: " << seats[0] << ","
                << "Price: " << price;
    EXPECT_EQ(ticket.print(), ticket_info.str());
}

