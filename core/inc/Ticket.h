#ifndef BOOKING_TICKET_H
#define BOOKING_TICKET_H

#include <string>
#include <memory>

#include "User.h"
#include "Show.h"

//! Ticket class
/*!
  A class used to present ticket objects.
 */

class Ticket
{
public:
    //! constructor
    /*!
       \param user shared pointer to a User object
       \param show shared pointer to a Show object
       \param seat the seat number
       \param price ticket price
     */
    Ticket(std::shared_ptr<User> user, std::shared_ptr<Show> show, Show::seat_t seat, int price);

    //! copy and assign constructor are not allowed
    Ticket(const Ticket&) = delete;
    Ticket operator=(const Ticket&) = delete;

    //! destructor
    ~Ticket();
    
    //! print ticket
    /*!
      print the ticket information with format:
        <User Id>,<Movie Name>,<Theater Name>,<Start Time>,<Seat Number>,<Price>
      \return string  ticket infomation
    */
    std::string print();

private:
    std::shared_ptr<User> m_user; /*!< user who owns the ticket */
    std::shared_ptr<Show> m_show; /*!< the show user booked */
    Show::seat_t m_seat;          /*!< the seat number */
    int m_price;                  /*!< ticket price */
    // std::string m_bookTime;    /*!< booking time */
    // enum Status m_state;       /*!< the status of ticket */
};

#endif

