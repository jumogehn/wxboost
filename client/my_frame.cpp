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
#include "my_panel.h"
#include "my_frame.h"

//----------------------------------------------------------------------
// MyFrame
//----------------------------------------------------------------------

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(TEXT_QUIT,   MyFrame::OnQuit)
    EVT_MENU(TEXT_ABOUT,  MyFrame::OnAbout)
    EVT_IDLE(MyFrame::OnIdle)
END_EVENT_TABLE()

MyFrame::MyFrame(wxFrame *frame, const wxChar *title, int x, int y, int w, int h)
       : wxFrame(frame, wxID_ANY, title, wxPoint(x, y), wxSize(w, h) )
{
#if wxUSE_STATUSBAR
    CreateStatusBar(2);
#endif // wxUSE_STATUSBAR

    m_panel = new MyPanel( this, 10, 10, 300, 100 );
}

void MyFrame::OnQuit (wxCommandEvent& WXUNUSED(event) )
{
    Close(true);
}

void MyFrame::OnAbout( wxCommandEvent& WXUNUSED(event) )
{
    wxBeginBusyCursor();

    wxMessageDialog dialog(this,
      _T("This is an exercise of learning wxwidgets and boost.asio\n")
      _T("IO is taken from the boost.asio example - \n")
      _T("   http://www.boost.org/doc/libs/1_53_0/doc/html/boost_asio/examples.html\n")
      _T("GUI is taken from the wxwidgets example - \n")
      _T("   samples/text - Robert Roebling, Julian Smart, Vadim Zeitlin\n")
      _T("\n")
      _T(""),
      _T("About wxboost"),
      wxOK | wxICON_INFORMATION);

    dialog.ShowModal();

    wxEndBusyCursor();
}


void MyFrame::OnIdle( wxIdleEvent& event )
{
    // track the window which has the focus in the status bar
    static wxWindow *s_windowFocus = (wxWindow *)NULL;
    wxWindow *focus = wxWindow::FindFocus();
    if ( focus && (focus != s_windowFocus) )
    {
        s_windowFocus = focus;

        wxString msg;
        msg.Printf(
#ifdef __WXMSW__
                _T("Focus: wxWindow = %p, HWND = %08x"),
#else
                _T("Focus: wxWindow = %p"),
#endif
                s_windowFocus
#ifdef __WXMSW__
                , (unsigned int) s_windowFocus->GetHWND()
#endif
                  );

#if wxUSE_STATUSBAR
        SetStatusText(msg);
#endif // wxUSE_STATUSBAR
    }
    event.Skip();
}

