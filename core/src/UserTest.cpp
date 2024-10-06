#include "gmock/gmock.h"

#include "../inc/User.h"
#include "../inc/UserRule.h"

using namespace std;
using namespace testing;

//! Mocking UserRule

class MockUserRule : public UserRule
{
public:
    MOCK_METHOD1(checkPassword, int(const string&));
    MOCK_METHOD1(checkEmail, int(const string&));
    MOCK_METHOD1(encodePassword, string(const string&));
};



TEST(UserTest, ctor)
{
    User user;
    EXPECT_EQ(user.getUserId(), -1);
    EXPECT_EQ(user.getUserGrade(), User::Grade::Grade1);
    user.setUserGrade(User::Grade::Grade3);
    EXPECT_EQ(user.getUserGrade(), User::Grade::Grade3);
}

TEST(UserTest, resetPassword)
{
    MockUserRule mockUserRule;
    User user;
    string password = "Pass8Word%";
    string encodedPassword = "encodedPassword";

    EXPECT_CALL(mockUserRule, checkPassword(password))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(mockUserRule, encodePassword(password))
        .Times(1)
        .WillOnce(Return(encodedPassword));

    EXPECT_EQ(user.resetPassword(mockUserRule, password), User::Result::Result0);
    EXPECT_EQ(user.getPassword(), encodedPassword);

    password = "abc";
    EXPECT_CALL(mockUserRule, checkPassword(password))
        .Times(1)
        .WillOnce(Return(-1));
    EXPECT_EQ(user.resetPassword(mockUserRule, password), User::Result::Result1);

    password = "abcDEF@1234567890abcDEF@1234567890";
    EXPECT_CALL(mockUserRule, checkPassword(password))
        .Times(1)
        .WillOnce(Return(-1));
    EXPECT_EQ(user.resetPassword(mockUserRule, password), User::Result::Result1);

    password = "abc@12345";
    EXPECT_CALL(mockUserRule, checkPassword(password))
        .Times(1)
        .WillOnce(Return(-2));
    EXPECT_EQ(user.resetPassword(mockUserRule, password), User::Result::Result1);

    password = "abcA12345";
    EXPECT_CALL(mockUserRule, checkPassword(password))
        .Times(1)
        .WillOnce(Return(-3));
    EXPECT_EQ(user.resetPassword(mockUserRule, password), User::Result::Result1);

    password = "ABC@12345";
    EXPECT_CALL(mockUserRule, checkPassword(password))
        .Times(1)
        .WillOnce(Return(-4));
    EXPECT_EQ(user.resetPassword(mockUserRule, password), User::Result::Result1);

    password = "abc/12345";
    EXPECT_CALL(mockUserRule, checkPassword(password))
        .Times(1)
        .WillOnce(Return(-2));
    EXPECT_EQ(user.resetPassword(mockUserRule, password), User::Result::Result1);
}

TEST(UserTest, doRegister)
{
}

