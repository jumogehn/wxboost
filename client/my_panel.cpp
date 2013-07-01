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
#include "my_panel.h"

//----------------------------------------------------------------------
// MyPanel
//----------------------------------------------------------------------

MyTextCtrl    *MyPanel::m_textrich = 0;

MyPanel::MyPanel( wxFrame *frame, int x, int y, int w, int h )
       : wxPanel( frame, wxID_ANY, wxPoint(x, y), wxSize(w, h) )
{
  m_textrich = new MyTextCtrl(this, wxID_ANY, _T("Conversation here\n"),
                              wxPoint(5, 10), wxSize(200, 230),
                              wxTE_RICH | wxTE_MULTILINE | wxTE_READONLY | wxTE_AUTO_URL);
  m_textrich->SetDefaultStyle(wxTextAttr());

  // single line text controls
  m_enter = new MyTextCtrl( this, 100, _T("Say hi!"),
                            wxPoint(5,170), wxSize(200,70), wxTE_MULTILINE);
  m_enter->SetClientData((void *)_T("client data"));

#if wxUSE_LOG
  m_log = new wxTextCtrl( this, wxID_ANY, _T("This is the log window.\n"),
                          wxPoint(5,260), wxSize(200,100),
                          wxTE_MULTILINE | wxTE_READONLY /* | wxTE_RICH */);

  m_logOld = wxLog::SetActiveTarget( new wxLogTextCtrl( m_log ) );
#endif // wxUSE_LOG

  // lay out the controls
  wxBoxSizer *col1 = new wxBoxSizer(wxVERTICAL);
  col1->Add( m_textrich, 1, wxALL | wxEXPAND, 10 );
  col1->Add( m_enter, 0, wxALL | wxEXPAND, 10 );

#if wxUSE_LOG
  col1->Add( m_log, 0, wxALL | wxEXPAND, 10 );
#endif

  SetAutoLayout( true );
  SetSizer(col1);
}

