#include <boost/atomic/atomic.hpp>

#include "../inc/User.h"
#include "../inc/UserRule.h"

using namespace std;


// The user id is unique in system,
// It should be read the last value from disk/database when system startup,
// and  the last value should be saved to disk/database when system shutdown.
// But here, we just use global variable to emulate.
static boost::atomic<int> g_userId(1);


User::User()
     : m_userId(-1), m_grade(User::Grade::Grade1)
{
}

User::~User()
{
}


User::Result User::doRegister(
    UserRule& userRule,
    const std::string& password,
    const std::string& firstName,
    const std::string& lastName,
    const std::string& phone,
    const std::string& email,
    Grade grade)
{
    // TODO:
    // We should query phone, email already exist in system or not
    // If yes, return Result2 or Result4
 
    Result result = resetPassword(userRule, password);
    if (result != Result::Result0)
    {
        return result; 
    }

    if (userRule.checkEmail(email) != 0)
    {
        return Result::Result5;
    }

    m_firstName = firstName;
    m_lastName = lastName;
    m_cellPhone = phone;
    m_email = email;
    m_grade = grade;
    m_userId = g_userId.fetch_add(1);

    return Result::Result0;
}

int User::getUserId() const
{
     return m_userId;
}

std::string User::getPassword() const
{
     return m_password;
}

User::Grade User::getUserGrade() const
{
     return m_grade;
}

void User::setUserGrade(User::Grade grade)
{
     m_grade = grade;
}

User::Result User::resetPassword(UserRule& userRule, const std::string& password)
{
    if (userRule.checkPassword(password) != 0)
    {
        return Result::Result1; 
    }
    m_password = userRule.encodePassword(password);
    return Result::Result0;
}

