/////////////////////////////////////////////////////////////////////////////
// Name:        text.cpp
// Purpose:     TextCtrl wxWidgets sample
// Author:      Robert Roebling
// Modified by:
// RCS-ID:      $Id: text.cpp 41744 2006-10-08 20:38:14Z VZ $
// Copyright:   (c) Robert Roebling, Julian Smart, Vadim Zeitlin
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef WXBOOST_MY_CHAT
#define WXBOOST_MY_CHAT

#include <wx/wx.h>

#include "chat_client.h"
#include <wx/app.h>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>


//----------------------------------------------------------------------
// class definitions
//----------------------------------------------------------------------

class MyChat: public wxApp
{
public:
    bool OnInit();

    static boost::asio::io_service *io_service_ptr;
    static chat_client             *chat_client_ptr;
    static boost::thread           *io_thread;
};

enum
{
    TEXT_QUIT = wxID_EXIT,
    TEXT_ABOUT = wxID_ABOUT,
    TEXT_END
};

#endif//WXBOOST_MY_CHAT
