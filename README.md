# Online Movie Booking Service

Copyright @ 2024 **Guoqiang Li**  guoqiang.kevin.li@outlook.com

Distributed under the MIT License


This is an online movie booking service for fun! It is its purpose to demonstrate morden C++ skills and software engineering experience.

It has two parts:

**1. Core:** The core service to provice functionalities:
  
- cinema manager: managing theater(s), movie(s), show(s);
     
- theatergoer: to booking, cancelling seat(s);

**2. Demo:** The demo to show the usage of **core** service

By default, the demo provides TCP service running on port 3365, and it supports input from stdin running the service. 


# How to build

To build the project, you need a C++ compiler to support C++14. The dependent tools and libraries can be installed with **conan**.

Below procedure is a sample which verified on Debian linux.

1) Clone the repo from https://github.com/fireflyming/online-movie-ticket-booking
2) Install conan package manager: **pip install conan**
3) Install the required tools and libraries with conan:

>**cd repo_directory_you_clone_the_code**
     
>**conan profile detect --force**
     
>**conan install . --output-folder=build --build=missing**
     
>**cd build**

4) Generate build project files with CMake

>**cmake .. -DCMAKE_TOOLCHAIN_FILE=./build/Release/generators/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release**
>
>**make**
 
 6) Procedure above will build the UT executables: **core/test_core**, **demo/test_demo** and booking application: **demo/BookApp**

Or if you have installed required tools and libraries with other package management tool, e.g. **apt** or **pacman**, you can use cmake directly, for example:
   
>**cd repo_directory_you_clone_the_code**
   
>**mkdir build && cd build**

>**cmake ..**

>**make**


# Generate API documentation with doxygen

 1) Generate **core** documentation

 >**cd repo_directory_you_clone_the_code**
>
>**cd core/doc**
>
>**doxygen**
>
>Open **html/index.html** with a web browser.
    
 3) Generate **demo** documentation

>**cd repo_directory_you_clone_the_code**
>
>**cd demo/doc**
>
>**doxygen**

Open **html/index.html** with a web browser.

# Run unit test

After successful build with the tips in **How to build**, two unit test programs can be run to check unit test cases.
 
>**cd repo_directory_you_clone_the_code**
>
>**cd build**
>
>**./core/test_core**
>
>**./demo/test_demo**

# Run the book service application

>**cd repo_directory_you_clone_the_code**
>
>**cd build**
>
>**./demo/BookApp**

After the **BookApp** startup successfully, you can query all movies on showing, query all shows of a movie, and book a seat of a show.

1) Operate in the console directly
Below welcomed message will be displayed on the term after **BookApp** startup.
>liming@x230:~/workspace/github/online-movie-ticket-booking/build$ ./demo/BookApp
>
>Welcome to Online Movie Booking Service!
>
>Usage:
>
>  'movies' - to display all movies
>
>  'query <movie id>' - query shows of a movie
>
>  'book <show> <seat> - book a show seat
   
2) Opearate will a tcp client, e.g. telnet, to connect to the booking service
>liming@x230:~/workspace/github/online-movie-ticket-booking/demo/build$ telnet 127.0.0.1 3365
>
>Trying 127.0.0.1...
>
>Connected to 127.0.0.1.
>
>Escape character is '^]'.
>
>Welcome to Online Movie Booking Service!
>
>Usage:
>
>  'movies' - to display all movies
>
>  'query <movie id>' - query shows of a movie
>
>  'book <show> <seat> - book a show seat

You can more than one telnet client at the same time. 

# TODO List
1. Solve the issue which blocks generate unit test coverage report
2. Verify on Windows 10 environment
3. Docker support? The dock service has been blocked in China, need to apply a Cloud machine to try.
