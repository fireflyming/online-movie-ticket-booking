#ifndef BOOKING_BOOK_SERVICE_H
#define BOOKING_BOOK_SERVICE_H

#include <vector>
#include <string>
#include <mutex>
#include <memory>

/**
 * It will be convenient if we implement below classes.
 * But now, we directly use std::vector to manage objects.
 *
class UserManager;
class MovieManager;
class TheaterManager;
class ShowManager;
class TicketManager;
*/

//! BookService class
 /*
  * It is the interface class to manage User, Movie, Theater, Show and Ticket.
  *   - Accepting user registration, logon, logoff, book seats, query movies
  *   - Service provider: online/offline a movie, add/remove a theater, arrange show(s)
  */

class User;
class Show;
class Movie;
class Ticket;
class Theater;

class BookService
{
public: 
    BookService() {}
    ~BookService() {}

    //! copy and assign constructor are not allowed
    BookService(const BookService&) = delete;
    BookService& operator=(const BookService&) = delete;

    //! load data from storage
    /*
     * Now just for testing, we construct below fake data:
     *   -- Two users
     *   -- Three Movies: {"Beautiful Mind", "Intersateller", "Tianic"}
     *   -- Two Theaters: {"King Room", "Queen Room"}
     */
    void loadData(/* const std::string & source */ );

    //! query all online movies
    /*!
     * \return string each line a movie with format: [seqno] [movie name]
     */
    std::string queryMovies() const;

    //! query all shows of a movie
    /*!
     * \return string two lines a show of a movie with format: [showno] [theater name] [start time] [price]\r\n seats 
     */
    std::string queryMovieShows(int movieId) const;
     
    //! book seats
    /*!
       A user books seats for a show.
       \param userId user id
       \param showId show id
       \param seats seat numbers of a show
       \return vector<Ticket> if success return booking tickets
    */
    std::vector<std::shared_ptr<Ticket>>
    bookSeats(int userId, int showId, const std::vector<Show::seat_t>& seats);     

    // TODO: interface for cancelling a seat

private:
    std::vector<std::shared_ptr<User>> m_users; /*<! user manager */
    std::vector<std::shared_ptr<Movie>> m_movies; /*<! movie manager */
    std::vector<std::shared_ptr<Theater>> m_theaters; /*<! theater manager */
    std::vector<std::shared_ptr<Show>> m_shows; /*<! show manager */
    std::vector<std::shared_ptr<Ticket>> m_tickets; /*<! ticket manager */
    std::mutex m_mutex_tickets; /*<! mutext for ticket manager */

/**
     UserManager m_userMgr;
     MovieManager m_movieMgr;
     TheaterManager m_theaterMgr;
     ShowManager m_showMgr;
     TicketManager m_tickMgr;
*/
};

#endif

