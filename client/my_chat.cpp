/////////////////////////////////////////////////////////////////////////////
// Name:        text.cpp
// Purpose:     TextCtrl wxWidgets sample
// Author:      Robert Roebling
// Modified by:
// RCS-ID:      $Id: text.cpp 41744 2006-10-08 20:38:14Z VZ $
// Copyright:   (c) Robert Roebling, Julian Smart, Vadim Zeitlin
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "my_chat.h"
#include "my_frame.h"


boost::asio::io_service *MyChat::io_service_ptr = 0;
chat_client             *MyChat::chat_client_ptr = 0;
boost::thread           *MyChat::io_thread = 0;

IMPLEMENT_APP(MyChat)

//----------------------------------------------------------------------
// MyChat
//----------------------------------------------------------------------

bool MyChat::OnInit()
{
    // Create the main frame window
    MyFrame *frame = new MyFrame((wxFrame *) NULL,
            _T("Text wxWidgets sample"), 50, 50, 700, 550);
    frame->SetSizeHints( 500, 400 );

    wxMenu *file_menu = new wxMenu;
    file_menu->Append(TEXT_ABOUT, _T("&About\tAlt-A"));
    file_menu->AppendSeparator();
    file_menu->Append(TEXT_QUIT, _T("E&xit\tAlt-X"), _T("Quit this sample"));

    wxMenuBar *menu_bar = new wxMenuBar( wxMB_DOCKABLE );
    menu_bar->Append(file_menu, _T("&File"));

#if wxUSE_LOG
    wxMenu *menuLog = new wxMenu;
    menuLog->AppendCheckItem(TEXT_LOG_KEY, _T("Log &key events"));
    menuLog->AppendCheckItem(TEXT_LOG_CHAR, _T("Log &char events"));
    menuLog->AppendCheckItem(TEXT_LOG_MOUSE, _T("Log &mouse events"));
    menuLog->AppendCheckItem(TEXT_LOG_TEXT, _T("Log &text events"));
    menuLog->AppendCheckItem(TEXT_LOG_FOCUS, _T("Log &focus events"));
    menuLog->AppendSeparator();
    menuLog->Append(TEXT_CLEAR, _T("&Clear the log\tCtrl-L"),
                    _T("Clear the log window contents"));

    // select only the interesting events by default
    MyTextCtrl::ms_logText = true;

    menuLog->Check(TEXT_LOG_KEY, MyTextCtrl::ms_logKey);
    menuLog->Check(TEXT_LOG_CHAR, MyTextCtrl::ms_logChar);
    menuLog->Check(TEXT_LOG_TEXT, MyTextCtrl::ms_logText);

    menu_bar->Append(menuLog, _T("&Log"));
#endif // wxUSE_LOG

    frame->SetMenuBar(menu_bar);

    frame->Show(true);

    SetTopWindow(frame);

    io_service_ptr = new boost::asio::io_service;

    tcp::resolver resolver(*io_service_ptr);
    tcp::resolver::query query("127.0.0.1", "9096");
    tcp::resolver::iterator iterator = resolver.resolve(query);

    chat_client_ptr = new chat_client(*io_service_ptr, iterator);

    io_thread = new boost::thread(boost::bind(&boost::asio::io_service::run, io_service_ptr));

    return true;
}

