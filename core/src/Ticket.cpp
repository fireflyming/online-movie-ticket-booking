#include <sstream>
#include "../inc/Ticket.h"

using namespace std;

Ticket::Ticket(shared_ptr<User> user,
               shared_ptr<Show> show,
               Show::seat_t seat,
               int price)
    : m_user(user), m_show(show), m_seat(seat), m_price(price)
{
}

Ticket::~Ticket()
{
}

string Ticket::print()
{
    ostringstream oss;
    oss << "User Id: " << m_user->getUserId() << ","
        << "Movie Name: " << m_show->getMovieName() << ","
        << "Theater Name: " << m_show->getTheaterName() << ","
        << "Start Time: " << m_show->getStartTime() << ","
        << "Seat Number: " << m_seat << ","
        << "Price: " << m_price;
    return oss.str();
}

