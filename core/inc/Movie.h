#ifndef BOOKING_MOVIE_H
#define BOOKING_MOVIE_H

#include <string>

//! Movie class
/*!
   A class used to present movie objects.
 */

class Movie
{
public:
     //! constructor
     /*!
        The default constructor
        \param name movie name
        \param duration movie duration
      */
     Movie(std::string name, int duration)
         : m_name(name), m_duration(duration) {} 

     //! destructor
     virtual ~Movie() {}

     //! get movie name
     /*!
       \return string movie name
      */
     std::string getName() const { return m_name; }

     //! get movie duration
     /*!
       \return int movie duration
      */
     int getDuration() const { return m_duration; }

     //! set movie name
     /*!
       \param name movie name
      */
     void setName(const std::string& name) { m_name = name; }

     //! set movie duration
     /*!
       \param duration movie duration
      */
     void setDuration(int duration) { m_duration = duration; }

private:
    std::string m_name; /*!< movie name */
    int m_duration;       /*!< movie duration in minutes */
};

#endif

