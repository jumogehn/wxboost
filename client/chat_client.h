//
// chat_client.h
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2012 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef WXBOOST_CHAT_CLIENT
#define WXBOOST_CHAT_CLIENT

#include "my_panel.h"
#include "my_text_ctrl.h"
#include "chat_message.hpp"
#include <wx/event.h>
#include <wx/string.h>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>

using boost::asio::ip::tcp;

typedef std::deque<chat_message> chat_message_queue;

class chat_client
{
public:
  chat_client(boost::asio::io_service& io_service,
              tcp::resolver::iterator endpoint_iterator)
    : io_service_(io_service),
    socket_(io_service)
  {
    boost::asio::async_connect(socket_, endpoint_iterator,
                               boost::bind(&chat_client::handle_connect, this,
                                           boost::asio::placeholders::error));
  }

  void write(const chat_message& msg)
  {
    io_service_.post(boost::bind(&chat_client::do_write, this, msg));
  }

  void close()
  {
    io_service_.post(boost::bind(&chat_client::do_close, this));
  }

private:

  void handle_connect(const boost::system::error_code& error)
  {
    if (!error)
    {
      boost::asio::async_read(socket_,
                              boost::asio::buffer(read_msg_.data(), chat_message::header_length),
                              boost::bind(&chat_client::handle_read_header, this,
                                          boost::asio::placeholders::error));
    }
  }

  void handle_read_header(const boost::system::error_code& error)
  {
    if (!error && read_msg_.decode_header())
    {
      boost::asio::async_read(socket_,
                              boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
                              boost::bind(&chat_client::handle_read_body, this,
                                          boost::asio::placeholders::error));
    }
    else
    {
      do_close();
    }
  }

  void handle_read_body(const boost::system::error_code& error)
  {
    if (!error)
    {
      //std::cout.write(read_msg_.body(), read_msg_.body_length());
      //std::cout << "\n";

      wxCommandEvent event( wxEVT_MY_EVENT, MyPanel::m_textrich->GetId());
      //event.SetEventObject( this );
      // Give it some contents
      wxString text = wxString::FromUTF8(read_msg_.body(), read_msg_.body_length());
      event.SetString(text.c_str());
      // Send it
      wxPostEvent(MyPanel::m_textrich, event);

      boost::asio::async_read(socket_,
                              boost::asio::buffer(read_msg_.data(), chat_message::header_length),
                              boost::bind(&chat_client::handle_read_header, this,
                                          boost::asio::placeholders::error));
    }
    else
    {
      do_close();
    }
  }

  void do_write(chat_message msg)
  {
    bool write_in_progress = !write_msgs_.empty();
    write_msgs_.push_back(msg);
    if (!write_in_progress)
    {
      boost::asio::async_write(socket_,
                               boost::asio::buffer(write_msgs_.front().data(),
                                                   write_msgs_.front().length()),
                               boost::bind(&chat_client::handle_write, this,
                                           boost::asio::placeholders::error));
    }
  }

  void handle_write(const boost::system::error_code& error)
  {
    if (!error)
    {
      write_msgs_.pop_front();
      if (!write_msgs_.empty())
      {
        boost::asio::async_write(socket_,
                                 boost::asio::buffer(write_msgs_.front().data(),
                                                     write_msgs_.front().length()),
                                 boost::bind(&chat_client::handle_write, this,
                                             boost::asio::placeholders::error));
      }
    }
    else
    {
      do_close();
    }
  }

  void do_close()
  {
    socket_.close();
  }

private:
  boost::asio::io_service& io_service_;
  tcp::socket socket_;
  chat_message read_msg_;
  chat_message_queue write_msgs_;
};

#endif//WXBOOST_CHAT_CLIENT
