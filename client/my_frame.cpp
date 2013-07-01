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

    EVT_MENU(TEXT_LOG_KEY,  MyFrame::OnLogKey)
    EVT_MENU(TEXT_LOG_CHAR, MyFrame::OnLogChar)
    EVT_MENU(TEXT_LOG_MOUSE,MyFrame::OnLogMouse)
    EVT_MENU(TEXT_LOG_TEXT, MyFrame::OnLogText)
    EVT_MENU(TEXT_LOG_FOCUS,MyFrame::OnLogFocus)
#if wxUSE_LOG
    EVT_MENU(TEXT_CLEAR,    MyFrame::OnLogClear)
#endif // wxUSE_LOG

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
      _T("This is a text control sample. It demonstrates the many different\n")
      _T("text control styles, the use of the clipboard, setting and handling\n")
      _T("tooltips and intercepting key and char events.\n")
      _T("\n")
        _T("Copyright (c) 1999, Robert Roebling, Julian Smart, Vadim Zeitlin"),
        _T("About wxTextCtrl Sample"),
        wxOK | wxICON_INFORMATION);

    dialog.ShowModal();

    wxEndBusyCursor();
}

#if wxUSE_LOG
void MyFrame::OnLogClear(wxCommandEvent& WXUNUSED(event))
{
    m_panel->m_log->Clear();
}
#endif // wxUSE_LOG

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

