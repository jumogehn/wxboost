/////////////////////////////////////////////////////////////////////////////
// Name:        text.cpp
// Purpose:     TextCtrl wxWidgets sample
// Author:      Robert Roebling
// Modified by:
// RCS-ID:      $Id: text.cpp 41744 2006-10-08 20:38:14Z VZ $
// Copyright:   (c) Robert Roebling, Julian Smart, Vadim Zeitlin
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef WXBOOST_MY_FRAME
#define WXBOOST_MY_FRAME

#include <wx/wx.h>

#include "my_panel.h"
#include "my_text_ctrl.h"
#include <wx/frame.h>

//----------------------------------------------------------------------
// class definitions
//----------------------------------------------------------------------

class MyFrame: public wxFrame
{
public:
    MyFrame(wxFrame *frame, const wxChar *title, int x, int y, int w, int h);

    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

#if wxUSE_LOG
    void OnLogClear(wxCommandEvent& event);
#endif // wxUSE_LOG

    void OnLogKey(wxCommandEvent& event)
    {
        MyTextCtrl::ms_logKey = event.IsChecked();
    }

    void OnLogChar(wxCommandEvent& event)
    {
        MyTextCtrl::ms_logChar = event.IsChecked();
    }

    void OnLogMouse(wxCommandEvent& event)
    {
        MyTextCtrl::ms_logMouse = event.IsChecked();
    }

    void OnLogText(wxCommandEvent& event)
    {
        MyTextCtrl::ms_logText = event.IsChecked();
    }

    void OnLogFocus(wxCommandEvent& event)
    {
        MyTextCtrl::ms_logFocus = event.IsChecked();
    }

    void OnIdle( wxIdleEvent& event );

private:

    MyPanel *m_panel;

    DECLARE_EVENT_TABLE()
};

#endif//WXBOOST_MY_FRAME
