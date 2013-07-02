/////////////////////////////////////////////////////////////////////////////
// Name:        text.cpp
// Purpose:     TextCtrl wxWidgets sample
// Author:      Robert Roebling
// Modified by:
// RCS-ID:      $Id: text.cpp 41744 2006-10-08 20:38:14Z VZ $
// Copyright:   (c) Robert Roebling, Julian Smart, Vadim Zeitlin
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef WXBOOST_MY_TEXT_CTRL
#define WXBOOST_MY_TEXT_CTRL

#include <wx/wx.h>

#include <wx/textctrl.h>

DECLARE_EVENT_TYPE(wxEVT_MY_EVENT, -1)

//----------------------------------------------------------------------
// class definitions
//----------------------------------------------------------------------

// a text ctrl which allows to call different wxTextCtrl functions
// interactively by pressing function keys in it
class MyTextCtrl : public wxTextCtrl
{
public:
    MyTextCtrl(wxWindow *parent, wxWindowID id, const wxString &value,
               const wxPoint &pos, const wxSize &size, int style = 0)
        : wxTextCtrl(parent, id, value, pos, size, style)
    {
        m_hasCapture = false;
    }

    void OnKeyDown(wxKeyEvent& event);
    void OnKeyUp(wxKeyEvent& event);
    void OnChar(wxKeyEvent& event);

    void OnText(wxCommandEvent& event);
    void OnTextEnter(wxCommandEvent& event);
    void OnTextURL(wxTextUrlEvent& event);
    void OnTextMaxLen(wxCommandEvent& event);

    void OnMouseEvent(wxMouseEvent& event);

    void OnSetFocus(wxFocusEvent& event);
    void OnKillFocus(wxFocusEvent& event);

    void OnMyEvent(wxCommandEvent& event);

private:
    static inline wxChar GetChar(bool on, wxChar c) { return on ? c : _T('-'); }

    void LogKeyEvent(const wxChar *name, wxKeyEvent& event) const;

    bool m_hasCapture;

    DECLARE_EVENT_TABLE()
};

#endif//WXBOOST_MY_TEXT_CTRL
