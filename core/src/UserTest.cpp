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

TEST(UserTest, resetPasswordWithMockUserRule)
{
    MockUserRule mockUserRule;
    User user;

    // success case
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

    // bad case: length too short
    password = "abc";
    EXPECT_CALL(mockUserRule, checkPassword(password))
        .Times(1)
        .WillOnce(Return(-1));
    EXPECT_EQ(user.resetPassword(mockUserRule, password), User::Result::Result1);

    // bad case: length too long
    password = "abcDEF@1234567890abcDEF@1234567890";
    EXPECT_CALL(mockUserRule, checkPassword(password))
        .Times(1)
        .WillOnce(Return(-1));
    EXPECT_EQ(user.resetPassword(mockUserRule, password), User::Result::Result1);

    // bad case: missing UPPER letter
    password = "abc@12345";
    EXPECT_CALL(mockUserRule, checkPassword(password))
        .Times(1)
        .WillOnce(Return(-4));
    EXPECT_EQ(user.resetPassword(mockUserRule, password), User::Result::Result1);

    // bad case: missing SPECIAL character
    password = "abcA12345";
    EXPECT_CALL(mockUserRule, checkPassword(password))
        .Times(1)
        .WillOnce(Return(-2));
    EXPECT_EQ(user.resetPassword(mockUserRule, password), User::Result::Result1);

    // bad case: missing LOWER letter
    password = "ABC@12345";
    EXPECT_CALL(mockUserRule, checkPassword(password))
        .Times(1)
        .WillOnce(Return(-3));
    EXPECT_EQ(user.resetPassword(mockUserRule, password), User::Result::Result1);

    // base case: missing digital number
    password = "abc@defgh";
    EXPECT_CALL(mockUserRule, checkPassword(password))
        .Times(1)
        .WillOnce(Return(-5));
    EXPECT_EQ(user.resetPassword(mockUserRule, password), User::Result::Result1);
}

TEST(UserTest, doRegisterWithMockUserRule)
{
     MockUserRule mockUserRule;
     User user;
     string password, firstName, lastName, phone, email;

     // bad case: invalid password (length too short)
    password = "abc@E5";
    firstName = "First_Name";
    lastName = "Last_Name";
    phone = "12345678";
    email = "username@email.com";
    EXPECT_CALL(mockUserRule, checkPassword(password))
        .Times(1)
        .WillOnce(Return(-5));
    EXPECT_EQ(user.doRegister(mockUserRule, password, firstName, lastName, phone, email), User::Result::Result1);

    // bad case: invalid email(invalid address)
    password = "abc@EDFG5";
    firstName = "First_Name";
    lastName = "Last_Name";
    phone = "12345678";
    email = "username#email.com";

    string encodedPassword = "EncodedPassword";
    EXPECT_CALL(mockUserRule, encodePassword(password))
        .Times(1)
        .WillOnce(Return(encodedPassword));
    EXPECT_CALL(mockUserRule, checkPassword(password))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(mockUserRule, checkEmail(email))
        .Times(1)
        .WillOnce(Return(-1));
    EXPECT_EQ(user.doRegister(mockUserRule, password, firstName, lastName, phone, email), User::Result::Result5);

   // success case: with default user grade
    password = "abc@EDFG5";
    firstName = "First_Name";
    lastName = "Last_Name";
    phone = "12345678";
    email = "username@email.com";
    EXPECT_CALL(mockUserRule, encodePassword(password))
        .Times(1)
        .WillOnce(Return(encodedPassword));
    EXPECT_CALL(mockUserRule, checkPassword(password))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(mockUserRule, checkEmail(email))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_EQ(user.doRegister(mockUserRule, password, firstName, lastName, phone, email), User::Result::Result0);
    EXPECT_EQ(user.getUserId(), 1);
    EXPECT_EQ(user.getUserGrade(), User::Grade::Grade1);
    EXPECT_EQ(user.getPassword(), encodedPassword);

   // success case: with higher user grade
    User user2;
    password = "abc@EDFG2";
    firstName = "First_Name_2";
    lastName = "Last_Name_2";
    phone = "1234567";
    email = "username2@email.com";
    User::Grade grade = User::Grade::Grade3;
    EXPECT_CALL(mockUserRule, encodePassword(password))
        .Times(1)
        .WillOnce(Return(encodedPassword));
    EXPECT_CALL(mockUserRule, checkPassword(password))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(mockUserRule, checkEmail(email))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_EQ(user2.doRegister(mockUserRule, password, firstName, lastName, phone, email, grade), User::Result::Result0);
    EXPECT_EQ(user2.getUserId(), 2);
    EXPECT_EQ(user2.getUserGrade(), User::Grade::Grade3);
    EXPECT_EQ(user2.getPassword(), encodedPassword);
}

