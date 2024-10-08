#include <sstream>

#include "../../core/inc/User.h"
#include "../../core/inc/Show.h"
#include "../../core/inc/Movie.h"
#include "../../core/inc/Ticket.h"
#include "../../core/inc/Theater.h"
#include "../../core/inc/FakeUserRule.h"

#include "../inc/BookService.h"

using namespace std;

void BookService::loadData()
{
    // to avoid reloading
    if (!m_users.empty())
    {
        return;
    }


    FakeUserRule userRule;

    // construct two users
    shared_ptr<User> user1 = make_shared<User>();
    User::Result res;
    res = user1->doRegister(userRule, "User1!Yes", "First1", "Last1", "18512345678", "user01@movie.com");
    if (res == User::Result::Result0)
    {
        m_users.push_back(user1);
    }

    shared_ptr<User> user2 = make_shared<User>();
    res = user2->doRegister(userRule, "User2!Yes", "First2", "Last2", "18512345679", "user02@movie.com");
    if (res == User::Result::Result0)
    {
        m_users.push_back(user2);
    }


    // construct three movies
    m_movies.push_back(make_shared<Movie>("Beautiful Mind", 150));
    m_movies.push_back(make_shared<Movie>("Intersateller", 160));
    m_movies.push_back(make_shared<Movie>("Tianic", 180));
  

    // construct two threaters
    m_theaters.push_back(make_shared<Theater>("King Room", 20));
    m_theaters.push_back(make_shared<Theater>("Queen Room", 10));
  


    // construct six shows each day

    // morning 
    m_shows.push_back(make_shared<Show>(m_movies[0], m_theaters[0], "2024-10-08 09:30:00", 40));
    m_shows.push_back(make_shared<Show>(m_movies[1], m_theaters[1], "2024-10-08 09:30:00", 45));

    // afternoon
    m_shows.push_back(make_shared<Show>(m_movies[1], m_theaters[0], "2024-10-08 14:00:00", 45));
    m_shows.push_back(make_shared<Show>(m_movies[0], m_theaters[1], "2024-10-08 14:00:00", 50));

    // evening
    m_shows.push_back(make_shared<Show>(m_movies[2], m_theaters[0], "2024-10-08 19:30:00", 50));
    m_shows.push_back(make_shared<Show>(m_movies[2], m_theaters[1], "2024-10-08 19:30:00", 55));
}


std::string BookService::queryMovies() const
{
    ostringstream oss;
    for (int i = 0; i < m_movies.size(); ++i)
    {
        oss << "[" << i << "] [" << m_movies[i]->getName() << "]\r\n";
    }
    return oss.str();
}

std::string BookService::queryMovieShows(int movieId) const
{
    ostringstream oss;

    if (movieId >= m_movies.size())
    {
        oss << "No show for the movie id: " << movieId << "\r\n";
        return oss.str();
    }

    oss << "Shows for movie [" << m_movies[movieId]->getName() << "]\r\n";
    for (auto show : m_shows)
    {
        if (show->getMovieName() == m_movies[movieId]->getName())
        {
            oss << "[" << show->getShowId() << "] [" << show->getTheaterName()
               << "] [" << show->getStartTime() << "] [" << show->getPrice()
               << "]\r\n\t" << show->showSeats() << "\r\n";
     
        }
    }
    return oss.str();
}

vector<shared_ptr<Ticket>> BookService::bookSeats(
    int userId, int showId, const vector<Show::seat_t>& seats)
{
    vector<shared_ptr<Ticket>> tickets;

    // input wrong userId or showId
    if (userId > m_users.size() || showId > m_shows.size())
    {
        return tickets;
    }

    --showId, --userId;
    if (m_shows[showId]->bookSeats(seats))
    { 
        lock_guard<mutex> guard(m_mutex_tickets);
        for (auto seat : seats)
        {
            shared_ptr<Ticket> ticket = make_shared<Ticket>(m_users[userId], m_shows[showId], seat, m_shows[showId]->getPrice());
            m_tickets.push_back(ticket);
            tickets.push_back(ticket);
        }
    }
    
    return tickets;
}

