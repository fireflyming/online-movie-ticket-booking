#include <gtest/gtest.h>

#include "inc/Ticket.h"
#include "../inc/BookService.h"

using namespace std;

static BookService g_bookService;

TEST(BookServiceTest, queryMovies)
{
    g_bookService.loadData();

    cout << g_bookService.queryMovies();
}

TEST(BookServiceTest, queryMovieShows)
{
    cout << g_bookService.queryMovieShows(0);
    cout << "--------------------------------------------------------------" << endl;
    cout << g_bookService.queryMovieShows(1);
    cout << "--------------------------------------------------------------" << endl;
    cout << g_bookService.queryMovieShows(2);
    cout << "--------------------------------------------------------------" << endl;
    cout << g_bookService.queryMovieShows(3);
    cout << "--------------------------------------------------------------" << endl;
}

TEST(BookServiceTest, bookSeats)
{
    cout << g_bookService.queryMovieShows(0);
    cout << "--------------------------------------------------------------" << endl;

    vector<Show::seat_t> seats { 1, 2, 3 };
    auto tickets = g_bookService.bookSeats(1, 1, seats);
    for (auto ticket : tickets)
    {
        cout << ticket->print() << endl;
    }

    cout << g_bookService.queryMovieShows(0);
    cout << "--------------------------------------------------------------" << endl;
}

