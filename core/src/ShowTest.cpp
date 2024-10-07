#include "gtest/gtest.h"

#include "../inc/Show.h"

using namespace std;

TEST(ShowTest, ctor)
{
    string movie_name = "Beautiful Mind";
    int movie_duration = 127;
    shared_ptr<Movie> movie = make_shared<Movie>(movie_name, movie_duration);

    string  theater_name = "King Room";
    int theater_capacity = 20;
    shared_ptr<Theater> theater = make_shared<Theater>(theater_name, theater_capacity);

    string show_starttime = "2024-10-07 14:30:00";
    Show show(movie, theater, show_starttime);
    EXPECT_EQ(show.getMovieName(), movie_name);
    EXPECT_EQ(show.getTheaterName(), theater_name);
    EXPECT_EQ(show.getShowId(), 1);
}

TEST(ShowTest, showSeats)
{
    string movie_name = "Beautiful Mind";
    int movie_duration = 127;
    shared_ptr<Movie> movie = make_shared<Movie>(movie_name, movie_duration);

    string  theater_name = "King Room";
    int theater_capacity = 5; // a mini theater for easy testing
    shared_ptr<Theater> theater = make_shared<Theater>(theater_name, theater_capacity);

    string show_starttime = "2024-10-07 14:30:00";
    Show show(movie, theater, show_starttime);
    string all_available("0[O] 1[O] 2[O] 3[O] 4[O]");
    EXPECT_EQ(show.showSeats(), all_available);

    vector<Show::seat_t> seats {1, 4};
    show.bookSeats(seats);
    string three_available("0[O] 1[X] 2[O] 3[O] 4[X]");
    EXPECT_EQ(show.showSeats(), three_available);
}

TEST(ShowTest, bookSeats)
{
    string movie_name = "Beautiful Mind";
    int movie_duration = 127;
    shared_ptr<Movie> movie = make_shared<Movie>(movie_name, movie_duration);

    string  theater_name = "King Room";
    int theater_capacity = 5; // a mini theater for easy testing
    shared_ptr<Theater> theater = make_shared<Theater>(theater_name, theater_capacity);

    string show_starttime = "2024-10-07 14:30:00";
    Show show(movie, theater, show_starttime);

    // bad case: book non-exist seat
    vector<Show::seat_t> seats { static_cast<Show::seat_t>(theater_capacity) + 1 };
    EXPECT_FALSE(show.bookSeats(seats));

    // success case: book one seat
    seats = vector<Show::seat_t> { static_cast<Show::seat_t>(theater_capacity) - 1 };
    EXPECT_TRUE(show.bookSeats(seats));

    // bad case: book one unavailable seat
    seats = vector<Show::seat_t> { static_cast<Show::seat_t>(theater_capacity) - 1 };
    EXPECT_FALSE(show.bookSeats(seats));

    // success case: book two available seats
    seats = vector<Show::seat_t> { 0, 1 };
    EXPECT_TRUE(show.bookSeats(seats));

    // bad case: book two seats, one available, another unavailable
    seats = vector<Show::seat_t> { 1, 2 };
    EXPECT_FALSE(show.bookSeats(seats));

    // success case: book two available seats from big to small
    seats = vector<Show::seat_t> { 3, 2 };
    EXPECT_TRUE(show.bookSeats(seats));

    // all seats booked
    string all_booked("0[X] 1[X] 2[X] 3[X] 4[X]");
    EXPECT_EQ(show.showSeats(), all_booked);
}

TEST(ShowTest, cancelSeats)
{
    string movie_name = "Beautiful Mind";
    int movie_duration = 127;
    shared_ptr<Movie> movie = make_shared<Movie>(movie_name, movie_duration);

    string  theater_name = "King Room";
    int theater_capacity = 5; // a mini theater for easy testing
    shared_ptr<Theater> theater = make_shared<Theater>(theater_name, theater_capacity);

    string show_starttime = "2024-10-07 14:30:00";
    Show show(movie, theater, show_starttime);

    // first, book all seats
    vector<Show::seat_t> seats { 0, 1, 2, 3, 4 };
    EXPECT_TRUE(show.bookSeats(seats));
    string all_booked("0[X] 1[X] 2[X] 3[X] 4[X]");
    EXPECT_EQ(show.showSeats(), all_booked);

    // bad case: cancel an non-exist seat
    Show::seat_t seat = static_cast<Show::seat_t>(theater_capacity) + 1;
    EXPECT_FALSE(show.cancelSeat(seat));

    // success case: cancel a booked seat
    seat = static_cast<Show::seat_t>(theater_capacity) - 1;
    EXPECT_TRUE(show.cancelSeat(seat));

    // bad case: cancel an unbooked seat
    seat = static_cast<Show::seat_t>(theater_capacity) - 1;
    EXPECT_FALSE(show.cancelSeat(seat));

    // success case: cancel all seats
    for (int i = 0; i < theater_capacity - 1; ++i) {
        EXPECT_TRUE(show.cancelSeat(static_cast<Show::seat_t>(i)));
    }

    // all seats are cancelled
    string all_available("0[O] 1[O] 2[O] 3[O] 4[O]");
    EXPECT_EQ(show.showSeats(), all_available);
}

