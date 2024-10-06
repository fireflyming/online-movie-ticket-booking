#ifndef BOOKING_USER_H
#define BOOKING_USER_H

#include <string>
#include "UserRule.h"

//! User class
/*!
    A class used to manage theatergoer.
 */

class User {
public:
     //! State enumeration
     /*! Used to identify user status, log on / off */
     enum class State {
          On,  /*! user online */
          Off  /*! user offline */
     };

     //! Grade enumeration
     /*! Used to identify user grade, e.g. for price discount */
     enum class Grade {
         Grade1,  /*!< grade 1, lowest level */
         Grade2,
         Grade3   /*!< grade 3, highest level */ 
     };

     //! Result enumeration
     /*! Used to identify the result of user register */
     enum class Result {
          Result0, /*!< result 0, success */
          Result1, /*!< result 1, failure, for invalid password */
          Result2, /*!< result 2, failure, for cellphone already registered */
          Result3, /*!< result 3, failure, for cellphone invalid */
          Result4, /*!< result 4, failure, for email already registered */
          Result5, /*!< result 5, failure, for email invalid */
          Result99  /*!< result 99, failure system error */
     };


     //! constructor
     /*!
       Just create an empty object
      */
     User();

     //! copy and assign constructor are not allowed
     User (const User&)  = delete;
     User operator=(const User&) = delete;

     //! destructor
     ~User();

     //! register a user
     /*!
       \param userRule user info checker
       \param password user password
       \param firstName user first name
       \param lastName user last name
       \param phone user cell phone, must be unique
       \param email user email address, must be unique
       \param grade user grade, Grade1 (lowest) by default
       \return Result an userId allocated if success
      */
     Result doRegister(UserRule& userRule,
          const std::string& password,
          const std::string& firstName, const std::string& lastName,
          const std::string& phone, const std::string& email,
          Grade grade = Grade::Grade1);

     //! get user id
     /*!
      \return user id
          -1 for an invalid user id
      */
     int getUserId() const;


     //! get user password
     /*!
      \return string user password
      */
     std::string getPassword() const;


     //! get user grade
     /*!
       \return user grade
      */
    Grade getUserGrade() const;

     //! change user grade
     /*!
       \param grade new user grade
      */
    void setUserGrade(Grade grade);

     //! reset user password
     /*!
       \param userRule user info checker
       \param password new user password
       \return Result
      */
    Result resetPassword(UserRule &userRule,
                         const std::string& password);

    //! TODO
    /*!
       getFirstName()
       setFirstName()
       getLastName()
       setLastName()
       getCellPhone()
       setCellPhone()
       getEmail()
       setEmail()
    */


private:
     int m_userId;             /*!< unique user id */
     //State m_state;            /*!< user status */
     Grade m_grade;            /*!< user grade, may affects price discount */
     std::string m_password;   /*!< encoded user password */
     std::string m_firstName;  /*!< first name */
     std::string m_lastName;   /*!< last name */
     std::string m_cellPhone;  /*!< cell phone number, must be unique */
     std::string m_email;      /*!< email address, must be unique */
};

#endif

