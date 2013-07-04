/////////////////////////////////////////////////////////////////////////////
// Name:        text.cpp
// Purpose:     TextCtrl wxWidgets sample
// Author:      Robert Roebling
// Modified by:
// RCS-ID:      $Id: text.cpp 41744 2006-10-08 20:38:14Z VZ $
// Copyright:   (c) Robert Roebling, Julian Smart, Vadim Zeitlin
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "my_text_ctrl.h"
#include "my_chat.h"
#include "chat_message.hpp"
#include <wx/buffer.h>

//----------------------------------------------------------------------
// MyTextCtrl
//----------------------------------------------------------------------
DEFINE_EVENT_TYPE(wxEVT_MY_EVENT)

BEGIN_EVENT_TABLE(MyTextCtrl, wxTextCtrl)
    EVT_KEY_UP(MyTextCtrl::OnKeyUp)
    EVT_COMMAND(wxID_ANY, wxEVT_MY_EVENT, MyTextCtrl::OnMyEvent)
END_EVENT_TABLE()

void MyTextCtrl::OnMyEvent( wxCommandEvent &event )
{
    wxString text = event.GetString();
    AppendText(text);
}

void MyTextCtrl::OnKeyUp(wxKeyEvent& event)
{
    if (event.GetKeyCode() == WXK_RETURN) {
      wxCharBuffer utf8_str = GetValue().utf8_str();
      chat_message msg;  //TODO: chat_message must use wxChatBuffer
      msg.body_length(strlen(utf8_str.data()));
      std::memcpy(msg.body(), utf8_str.data(), msg.body_length());
      msg.encode_header();
      MyChat::chat_client_ptr->write(msg);
      Clear();
    }

    event.Skip();
}

