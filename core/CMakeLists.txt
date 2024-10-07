cmake_minimum_required(VERSION 3.20)

project(Online_Movie_Booking_Core)

# GoogleTest requires at least c++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# coverage option
OPTION(ENABLE_COVERAGE "User gcov" ON)
MESSAGE(STATUS ENABLE_COVERAGE=${ENABLE_COVERAGE})
IF(ENABLE_COVERAGE)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage")
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
ENDIF()

enable_testing()
find_package(GTest REQUIRED)

set(sources src/User.cpp src/Show.cpp src/Ticket.cpp)
set(test_sources ${sources} src/UserTest.cpp src/MovieTest.cpp src/TheaterTest.cpp)
set(test_sources ${test_sources} src/ShowTest.cpp src/TicketTest.cpp)
add_executable(test_core ${test_sources})
target_link_libraries(test_core gtest gmock GTest::gtest_main)


# build core library, make it can be delivered in binary
# add_library(core, SHARED, ${SOURCES})_

