#ifndef BOOKING_SHOW_H
#define BOOKING_SHOW_H

#include <string>
#include <memory>
#include <mutex>
#include <vector>

#include "Movie.h"
#include "Theater.h"

class Show
{
public:
    //! define a type for seat number
    typedef unsigned seat_t;

    //! constructor
    /*!
      \param movie the movie
      \param theater the theater
      \param stattime show start time
      \param price show price
    */
    Show(std::shared_ptr<Movie> movie,
         std::shared_ptr<Theater> theater, std::string starttime, int price);

    //! copy and assign constructor are not allowed
    Show(const Show&) = delete;
    Show operator=(const Show&) = delete;

    //! destructor 
    ~Show() {}

    //! get show id
    /*!
      \return int show id
     */ 
    int getShowId() const { return m_showId; } 

    //! get show price
    /*!
      \return int show price
     */
    int getPrice() const { return m_price; }

    //! get start time
    /*!
      \return string start time
     */ 
    std::string getStartTime() const { return m_starttime; } 

    //! get movie name
    /*!
      \return string movie name
     */ 
     std::string getMovieName() const;
    
    //! get theater name
    /*!
      \return string theater name
     */ 
     std::string getTheaterName() const;

     //! book seat(s)
     /*!
         If user book more than one seats a time,
         success only all seats available. Otherwise, it fails.
       \param seats seat(s) need booking
       \return bool true for success, false for failure 
     */
     bool bookSeats(const std::vector<seat_t>& seats);

     //! cancel a seat
     /*!
       only allow user cancel a seat each time
       \param seat the seat number need to cancel
       \return bool true for sucess, false for failure
      */
     bool cancelSeat(seat_t seat);

     //! show all seats' status
     /*!
      \return string seats status with format "SeatNo[O|X] ..." 
            0 means the seat is available, X means the seat is not available
      */
     std::string showSeats(); 

private:
    int m_showId;    /*!< show id, be unique */
    int m_price;     /*!< show price */
    std::string m_starttime; /*!< the show start time YYYY-MM-DD HH:MM:SS */
    //std::string m_endtime;   /*!< the show end time */
    std::shared_ptr<Movie> m_movie; /*!< the movie be playing */
    std::shared_ptr<Theater> m_theater; /*!< the theater used to play the movie */
    std::unique_ptr<std::vector<seat_t>> m_seats; /*!< the seats booked (1) or not (0) */ 
    std::mutex m_mutex;  /* mutex to avoid over booking */
};

#endif

