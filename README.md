# Online Movie Booking Service

Copyright @ 2024 **Guoqiang Li**  guoqiang.kevin.li@outlook.com

Distributed under the MIT License


This is an online movie booking service for fun! It is its purpose to demonstrate morden C++ skills and software engineering experience.

It has two parts:

  **1. Core:** The core service to provice functionalities:
  
       -- cinema manager: managing theater(s), movie(s), show(s);
        
       -- theatergoer: to booking, cancelling seat(s);

  **2. Demo:** The demo to show the usage of **core** service

      By default, the demo provides TCP service running on port 3365, and it supports input from stdin running the service. 


# How to build

  To build the project, you need a C++ compiler to support C++14. The dependent tools and libraries can be installed with **conan**.

  Below procedure is a sample which verified on Debian linux.

  1) Clone the repo from https://github.com/fireflyming/online-movie-ticket-booking
  2) Install conan package manager: **pip install conan**
  3) Install the required tools and libraries with conan:

     **cd repo_directory_you_clone_the_code**
     
     **conan profile detect --force**
     
     **conan install . --output-folder=build --build=missing**
     
     **cd build**

  4) Generate build project files with CMake

     **cmake .. -DCMAKE_TOOLCHAIN_FILE=./build/Release/generators/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release**

     **make**
 
  6) Procedure above will build the UT executables: **core/test_core**, **demo/test_demo** and booking application: **demo/BookApp**

Or if you have installed required tools and libraries with other package management tool, e.g. **apt** or **pacman**, you can use cmake directly, for example:
   
   **cd repo_directory_you_clone_the_code**
   
   **mkdir build && cd build**

   **cmake ..**

   **make**


# Generate API documentation with doxygen

   1) Generate **core** documentation

      **cd repo_directory_you_clone_the_code**

      **cd core/doc**

      **doxygen**
      
      Open **html/index.html** with a web browser.
    
   3) Generate **demo** documentation

      **cd repo_directory_you_clone_the_code**

      **cd demo/doc**

      **doxygen**
      
      Open **html/index.html** with a web browser.
