cmake_minimum_required(VERSION 3.20)

project(Online_Movie_Booking_Core)

# GoogleTest requires at least c++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#find_package(BOOST REQUIRED)

enable_testing()
find_package(GTest REQUIRED)

set(sources src/User.cpp)
set(test_sources ${sources} src/UserTest.cpp)
add_executable(core_test ${test_sources})
target_link_libraries(core_test gtest gmock GTest::gtest_main)

