#include <cstdio>
#include <cstring>
#include <sstream>
#include <iostream>

#include "inc/Ticket.h"
#include "../inc/BookService.h"

using namespace std;

static BookService g_bookService;

string welcome();
void process_stdin();
string process_command(const char *);

int main(int argc, char *argv[])
{
    g_bookService.loadData();

    //TODO start TCP service

    process_stdin();  

    return 0;
}


string welcome()
{
    ostringstream oss;
    oss << "Welcome to Online Movie Booking Service!\r\n"
        << "Usage:\r\n"
        << "  'movies' - to display all movies\r\n"
        << "  'query <movie id>' - query shows of a movie\r\n"
        << "  'book <show> <seat> - book a show seat\r\n";
        // << "  'shutdown' - shutdown the service\r\n"
    return oss.str(); 
}

void process_stdin()
{
    printf(welcome().c_str());    

    char buf[1024];
    while (true)
    {
        printf("cli> ");
        memset(buf, '\0', sizeof(buf));
        fgets(buf, sizeof(buf)-1, stdin);
        printf("%s", process_command(buf).c_str());
    }
}

string process_command(const char *buf)
{
    const char * const cmd_movies = "movies";
    const char * const cmd_query = "query ";
    const char * const cmd_book = "book ";
    if (strncasecmp(cmd_movies, buf, strlen(cmd_movies)) == 0)
    {
        return g_bookService.queryMovies();
    }
    else if (strncasecmp(cmd_query, buf, strlen(cmd_query)) == 0)
    {
        int movieId = 0;
        sscanf(buf + strlen(cmd_query), "%d", &movieId);
        return g_bookService.queryMovieShows(movieId);
    }
    else if (strncasecmp(cmd_book, buf, strlen(cmd_book)) == 0)
    {
        int showId = 0, seat = 0, userId = 1;
        sscanf(buf + strlen(cmd_book), "%d %d", &showId, &seat);
        vector<Show::seat_t> seats { static_cast<Show::seat_t>(seat) };
        auto tickets = g_bookService.bookSeats(userId, showId, seats);
        ostringstream oss;
        if (tickets.size())
        {
            oss << "Book sucess. Ticket Informaation:\r\n";
            for (auto ticket : tickets)
            {
                oss << ticket->print();
            }
            oss << "\r\n";
        }
        else
        {
             oss << "Book failure.\r\n";
        }
        return oss.str();
    }
    return "";
}

