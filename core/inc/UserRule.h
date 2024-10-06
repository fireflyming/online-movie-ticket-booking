#ifndef BOOKING_USERRULE_H
#define BOOKING_USERRULE_H

#include <string>

//! User Rule Interface
/*!
  We assume that security team provide us interfaces (library)
  used to check password, email address, to encode password.

  By now, they just provide us interface declaration, the implementation
  is not ready yet.
 */

class UserRule {
public:
     //! check user password
     /*!
       A valid password's length [8, 32], includes at least one digital,
       upper letter, lower letter and special character @#!$%^&*()_
       \param password user password
       \return an integer
           0 (success)
           -1 (length error)
           -2 (missing special character)
           -3 (missing lower letter)
           -4 (missing upper letter)
           -5 (missing digital number)
       */
     virtual int checkPassword(const std::string& password) = 0;

     //! check user email
     /*!
       \param email user email address
       \return an integer
           0 (success)
          -1 (invalid address)
          -2 (the email domain was not allowed)
       */
     virtual int checkEmail(const std::string& email) = 0;

     //! encode user password
     /*!
        \param password raw user password
        \return string encoded user password
      */
     virtual std::string encodePassword(const std::string& password) = 0;
};

#endif

