#ifndef BOOKING_THEATER_H
#define BOOKING_THEATER_H

#include <string>

//! Theater class
/*!
   A class used to present theater objects.
 */

class Theater
{
public:
     //! constructor
     /*!
        The default constructor
        \param name theater name
        \param capacity theater seats
      */
     Theater(std::string name, int capacity)
         : m_name(name), m_capacity(capacity) {} 

     //! destructor
     virtual ~Theater() {}

     //! get theater name
     /*!
       \return string theater name
      */
     std::string getName() const { return m_name; }

     //! get theater capacity
     /*!
       \return int theater capacity
      */
     int getCapacity() const { return m_capacity; }

     //! set theater name
     /*!
       \param name theater name
      */
     void setName(const std::string& name) { m_name = name; }

     //! set theater capacity
     /*!
       \param capacity theater capacity
      */
     void setCapacity(int capacity) { m_capacity = capacity; }

private:
    std::string m_name; /*!< theater name */
    int m_capacity;     /*!< theater seats number */
};

#endif

