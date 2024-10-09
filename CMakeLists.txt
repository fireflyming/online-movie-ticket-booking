cmake_minimum_required (VERSION 3.30)

project(Online_Movie_Booking)

find_package(GTest REQUIRED)
find_package(Boost REQUIRED)
find_package(Doxygen REQUIRED)

add_subdirectory(core)
add_subdirectory(demo)

