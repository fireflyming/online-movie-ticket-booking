#include <boost/atomic/atomic.hpp>
#include <sstream>

#include "../inc/Show.h"

using namespace std;

// The show id is unique in system.
// It should be read from / save to a persistent storage 
static boost::atomic<int> g_showId(1);

Show::Show(shared_ptr<Movie> movie,
           shared_ptr<Theater> theater,
           string starttime,
           int price)
    : m_movie(movie), m_theater(theater), m_starttime(starttime), m_price(price)
{
    m_showId = g_showId.fetch_add(1);

    // allocate seats for booking
    m_seats = make_unique<vector<seat_t>>(m_theater->getCapacity(), 0);
}

string Show::getMovieName() const
{
    return m_movie->getName();
}

string Show::getTheaterName() const
{
    return m_theater->getName();
}

bool Show::bookSeats(const vector<seat_t>& seats)
{
    lock_guard<mutex> guard(m_mutex);

    // check if all seats are available or not
    for (auto i : seats) {
        if (i >= m_seats->size() || m_seats->data()[i] != 0) {
            return false;
        }
    }

    // book all the seats
    for (auto i : seats) {
        m_seats->data()[i] = 1;
    }
    return true;
}

bool Show::cancelSeat(seat_t seat)
{
    lock_guard<mutex> guard(m_mutex);
    if (seat >= m_seats->size() || m_seats->data()[seat] != 1) {
        return false;
    }

    m_seats->data()[seat] = 0;
    return true;
}

string Show::showSeats()
{
    lock_guard<mutex> guard(m_mutex);
    ostringstream oss;
    for (int i = 0; i < m_seats->size(); ++i) {
        oss << i << (m_seats->data()[i] ? "[X]" : "[O]");
        if (i < m_seats->size() - 1) {
            oss << " ";
        }
    }
    return oss.str();
}

