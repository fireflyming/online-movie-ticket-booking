#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iostream>
#include <memory>
#include <utility>
#include <thread>
#include <boost/asio.hpp>

#include "inc/Ticket.h"
#include "../inc/BookService.h"

using namespace std;
using boost::asio::ip::tcp;

static BookService g_bookService;
static const int g_tcp_port = 3365;

string welcome();
void process_stdin();
string process_command(const char *);

// running backend tcp service thread
void run_tcp_server(int tcp_port);

int main(int argc, char *argv[])
{
    g_bookService.loadData();

    try
    {
        //run_tcp_server(g_tcp_port);
        thread tcp(run_tcp_server, g_tcp_port);
        process_stdin();
        tcp.join();

    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}

string welcome()
{
    ostringstream oss;
    oss << "Welcome to Online Movie Booking Service!\r\n"
        << "Usage:\r\n"
        << "  'movies' - to display all movies\r\n"
        << "  'query <movie id>' - query shows of a movie\r\n"
        << "  'book <show> <seat> - book a show seat\r\n";
        // << "  'shutdown' - shutdown the service\r\n"
    return oss.str(); 
}

void process_stdin()
{
    printf(welcome().c_str());    

    char buf[1024];
    while (true)
    {
        printf("cli> ");
        memset(buf, '\0', sizeof(buf));
        fgets(buf, sizeof(buf)-1, stdin);
        printf("%s", process_command(buf).c_str());
    }
}

string process_command(const char *buf)
{
    const char * const cmd_movies = "movies";
    const char * const cmd_query = "query ";
    const char * const cmd_book = "book ";
    if (strncasecmp(cmd_movies, buf, strlen(cmd_movies)) == 0)
    {
        return g_bookService.queryMovies();
    }
    else if (strncasecmp(cmd_query, buf, strlen(cmd_query)) == 0)
    {
        int movieId = 0;
        sscanf(buf + strlen(cmd_query), "%d", &movieId);
        return g_bookService.queryMovieShows(movieId);
    }
    else if (strncasecmp(cmd_book, buf, strlen(cmd_book)) == 0)
    {
        int showId = 0, seat = 0, userId = 1;
        sscanf(buf + strlen(cmd_book), "%d %d", &showId, &seat);
        vector<Show::seat_t> seats { static_cast<Show::seat_t>(seat) };
        auto tickets = g_bookService.bookSeats(userId, showId, seats);
        ostringstream oss;
        if (tickets.size())
        {
            oss << "Book sucess. Ticket Informaation:\r\n";
            for (auto ticket : tickets)
            {
                oss << ticket->print();
            }
            oss << "\r\n";
        }
        else
        {
             oss << "Book failure.\r\n";
        }
        return oss.str();
    }
    return "";
}


//
// async_tcp_echo_server.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2024 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

class session
  : public std::enable_shared_from_this<session>
{
public:
  session(tcp::socket socket)
    : socket_(std::move(socket))
  {
  }

  void start()
  {
    string msg = welcome();
    memset(data_, '\0', sizeof(data_));
    strncpy(data_, msg.c_str(), sizeof(data_)-1);
    int length = msg.length();
    do_write(length);
    
    do_read();
  }

private:
  void do_read()
  {
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
        [this, self](boost::system::error_code ec, std::size_t length)
        {
          if (!ec)
          {
            string s = process_command(data_);
            memset(data_, '\0', sizeof(data_));
            strncpy(data_, s.c_str(), sizeof(data_)-1);
            length = s.length();
            do_write(length);
          }
        });
  }

  void do_write(std::size_t length)
  {
    auto self(shared_from_this());
    boost::asio::async_write(socket_, boost::asio::buffer(data_, length),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
          if (!ec)
          {
            do_read();
          }
        });
  }

  tcp::socket socket_;
  enum { max_length = 4096 };
  char data_[max_length];
};

class server
{
public:
  server(boost::asio::io_context& io_context, short port)
    : acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
  {
    do_accept();
  }

private:
  void do_accept()
  {
    acceptor_.async_accept(
        [this](boost::system::error_code ec, tcp::socket socket)
        {
          if (!ec)
          {
            std::make_shared<session>(std::move(socket))->start();
          }

          do_accept();
        });
  }

  tcp::acceptor acceptor_;
};

void run_tcp_server(int port)
{
  try
  {
    boost::asio::io_context io_context;
    server s(io_context, port);
    io_context.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }
}

