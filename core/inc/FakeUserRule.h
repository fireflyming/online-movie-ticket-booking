#ifndef BOOKING_FAKE_USER_RULE_H
#define BOOKING_FAKE_USER_RULE_H

#include "UserRule.h"

//! A fake implementation of User Rule Interfaces
/*!
    Just for unit testing
 */ 
class FakeUserRule : public UserRule
{
public:
    int checkPassword(const std::string& password) { return 0; }
    int checkEmail(const std::string& email) { return 0; }
    std::string encodePassword(const std::string& password) { return password; }
};

#endif

