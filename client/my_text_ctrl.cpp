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
    EVT_KEY_DOWN(MyTextCtrl::OnKeyDown)
    EVT_KEY_UP(MyTextCtrl::OnKeyUp)
    EVT_CHAR(MyTextCtrl::OnChar)

    EVT_TEXT(wxID_ANY, MyTextCtrl::OnText)
    EVT_TEXT_ENTER(wxID_ANY, MyTextCtrl::OnTextEnter)
    EVT_TEXT_URL(wxID_ANY, MyTextCtrl::OnTextURL)
    EVT_TEXT_MAXLEN(wxID_ANY, MyTextCtrl::OnTextMaxLen)

    EVT_MOUSE_EVENTS(MyTextCtrl::OnMouseEvent)

    EVT_SET_FOCUS(MyTextCtrl::OnSetFocus)
    EVT_KILL_FOCUS(MyTextCtrl::OnKillFocus)

    EVT_COMMAND(wxID_ANY, wxEVT_MY_EVENT, MyTextCtrl::OnMyEvent)
END_EVENT_TABLE()

bool MyTextCtrl::ms_logKey = false;
bool MyTextCtrl::ms_logChar = false;
bool MyTextCtrl::ms_logMouse = false;
bool MyTextCtrl::ms_logText = false;
bool MyTextCtrl::ms_logFocus = false;


void MyTextCtrl::OnMyEvent( wxCommandEvent &event )
{
    wxString text = event.GetString();
    AppendText(text);
}


void MyTextCtrl::LogKeyEvent(const wxChar *name, wxKeyEvent& event) const
{
    wxString key;
    long keycode = event.GetKeyCode();
    {
        switch ( keycode )
        {
            case WXK_BACK: key = _T("BACK"); break;
            case WXK_TAB: key = _T("TAB"); break;
            case WXK_RETURN: key = _T("RETURN"); break;
            case WXK_ESCAPE: key = _T("ESCAPE"); break;
            case WXK_SPACE: key = _T("SPACE"); break;
            case WXK_DELETE: key = _T("DELETE"); break;
            case WXK_START: key = _T("START"); break;
            case WXK_LBUTTON: key = _T("LBUTTON"); break;
            case WXK_RBUTTON: key = _T("RBUTTON"); break;
            case WXK_CANCEL: key = _T("CANCEL"); break;
            case WXK_MBUTTON: key = _T("MBUTTON"); break;
            case WXK_CLEAR: key = _T("CLEAR"); break;
            case WXK_SHIFT: key = _T("SHIFT"); break;
            case WXK_ALT: key = _T("ALT"); break;
            case WXK_CONTROL: key = _T("CONTROL"); break;
            case WXK_MENU: key = _T("MENU"); break;
            case WXK_PAUSE: key = _T("PAUSE"); break;
            case WXK_CAPITAL: key = _T("CAPITAL"); break;
            case WXK_END: key = _T("END"); break;
            case WXK_HOME: key = _T("HOME"); break;
            case WXK_LEFT: key = _T("LEFT"); break;
            case WXK_UP: key = _T("UP"); break;
            case WXK_RIGHT: key = _T("RIGHT"); break;
            case WXK_DOWN: key = _T("DOWN"); break;
            case WXK_SELECT: key = _T("SELECT"); break;
            case WXK_PRINT: key = _T("PRINT"); break;
            case WXK_EXECUTE: key = _T("EXECUTE"); break;
            case WXK_SNAPSHOT: key = _T("SNAPSHOT"); break;
            case WXK_INSERT: key = _T("INSERT"); break;
            case WXK_HELP: key = _T("HELP"); break;
            case WXK_NUMPAD0: key = _T("NUMPAD0"); break;
            case WXK_NUMPAD1: key = _T("NUMPAD1"); break;
            case WXK_NUMPAD2: key = _T("NUMPAD2"); break;
            case WXK_NUMPAD3: key = _T("NUMPAD3"); break;
            case WXK_NUMPAD4: key = _T("NUMPAD4"); break;
            case WXK_NUMPAD5: key = _T("NUMPAD5"); break;
            case WXK_NUMPAD6: key = _T("NUMPAD6"); break;
            case WXK_NUMPAD7: key = _T("NUMPAD7"); break;
            case WXK_NUMPAD8: key = _T("NUMPAD8"); break;
            case WXK_NUMPAD9: key = _T("NUMPAD9"); break;
            case WXK_MULTIPLY: key = _T("MULTIPLY"); break;
            case WXK_ADD: key = _T("ADD"); break;
            case WXK_SEPARATOR: key = _T("SEPARATOR"); break;
            case WXK_SUBTRACT: key = _T("SUBTRACT"); break;
            case WXK_DECIMAL: key = _T("DECIMAL"); break;
            case WXK_DIVIDE: key = _T("DIVIDE"); break;
            case WXK_F1: key = _T("F1"); break;
            case WXK_F2: key = _T("F2"); break;
            case WXK_F3: key = _T("F3"); break;
            case WXK_F4: key = _T("F4"); break;
            case WXK_F5: key = _T("F5"); break;
            case WXK_F6: key = _T("F6"); break;
            case WXK_F7: key = _T("F7"); break;
            case WXK_F8: key = _T("F8"); break;
            case WXK_F9: key = _T("F9"); break;
            case WXK_F10: key = _T("F10"); break;
            case WXK_F11: key = _T("F11"); break;
            case WXK_F12: key = _T("F12"); break;
            case WXK_F13: key = _T("F13"); break;
            case WXK_F14: key = _T("F14"); break;
            case WXK_F15: key = _T("F15"); break;
            case WXK_F16: key = _T("F16"); break;
            case WXK_F17: key = _T("F17"); break;
            case WXK_F18: key = _T("F18"); break;
            case WXK_F19: key = _T("F19"); break;
            case WXK_F20: key = _T("F20"); break;
            case WXK_F21: key = _T("F21"); break;
            case WXK_F22: key = _T("F22"); break;
            case WXK_F23: key = _T("F23"); break;
            case WXK_F24: key = _T("F24"); break;
            case WXK_NUMLOCK: key = _T("NUMLOCK"); break;
            case WXK_SCROLL: key = _T("SCROLL"); break;
            case WXK_PAGEUP: key = _T("PAGEUP"); break;
            case WXK_PAGEDOWN: key = _T("PAGEDOWN"); break;
            case WXK_NUMPAD_SPACE: key = _T("NUMPAD_SPACE"); break;
            case WXK_NUMPAD_TAB: key = _T("NUMPAD_TAB"); break;
            case WXK_NUMPAD_ENTER: key = _T("NUMPAD_ENTER"); break;
            case WXK_NUMPAD_F1: key = _T("NUMPAD_F1"); break;
            case WXK_NUMPAD_F2: key = _T("NUMPAD_F2"); break;
            case WXK_NUMPAD_F3: key = _T("NUMPAD_F3"); break;
            case WXK_NUMPAD_F4: key = _T("NUMPAD_F4"); break;
            case WXK_NUMPAD_HOME: key = _T("NUMPAD_HOME"); break;
            case WXK_NUMPAD_LEFT: key = _T("NUMPAD_LEFT"); break;
            case WXK_NUMPAD_UP: key = _T("NUMPAD_UP"); break;
            case WXK_NUMPAD_RIGHT: key = _T("NUMPAD_RIGHT"); break;
            case WXK_NUMPAD_DOWN: key = _T("NUMPAD_DOWN"); break;
            case WXK_NUMPAD_PAGEUP: key = _T("NUMPAD_PAGEUP"); break;
            case WXK_NUMPAD_PAGEDOWN: key = _T("NUMPAD_PAGEDOWN"); break;
            case WXK_NUMPAD_END: key = _T("NUMPAD_END"); break;
            case WXK_NUMPAD_BEGIN: key = _T("NUMPAD_BEGIN"); break;
            case WXK_NUMPAD_INSERT: key = _T("NUMPAD_INSERT"); break;
            case WXK_NUMPAD_DELETE: key = _T("NUMPAD_DELETE"); break;
            case WXK_NUMPAD_EQUAL: key = _T("NUMPAD_EQUAL"); break;
            case WXK_NUMPAD_MULTIPLY: key = _T("NUMPAD_MULTIPLY"); break;
            case WXK_NUMPAD_ADD: key = _T("NUMPAD_ADD"); break;
            case WXK_NUMPAD_SEPARATOR: key = _T("NUMPAD_SEPARATOR"); break;
            case WXK_NUMPAD_SUBTRACT: key = _T("NUMPAD_SUBTRACT"); break;
            case WXK_NUMPAD_DECIMAL: key = _T("NUMPAD_DECIMAL"); break;

            default:
            {
               if ( wxIsprint((int)keycode) )
                   key.Printf(_T("'%c'"), (char)keycode);
               else if ( keycode > 0 && keycode < 27 )
                   key.Printf(_("Ctrl-%c"), _T('A') + keycode - 1);
               else
                   key.Printf(_T("unknown (%ld)"), keycode);
            }
        }
    }

#if wxUSE_UNICODE
    key += wxString::Format(_T(" (Unicode: %#04x)"), event.GetUnicodeKey());
#endif // wxUSE_UNICODE

    wxLogMessage( _T("%s event: %s (flags = %c%c%c%c)"),
                  name,
                  key.c_str(),
                  GetChar( event.ControlDown(), _T('C') ),
                  GetChar( event.AltDown(), _T('A') ),
                  GetChar( event.ShiftDown(), _T('S') ),
                  GetChar( event.MetaDown(), _T('M') ) );
}

static wxString GetMouseEventDesc(const wxMouseEvent& ev)
{
    // click event
    wxString button;
    bool dbl, up;
    if ( ev.LeftDown() || ev.LeftUp() || ev.LeftDClick() )
    {
        button = _T("Left");
        dbl = ev.LeftDClick();
        up = ev.LeftUp();
    }
    else if ( ev.MiddleDown() || ev.MiddleUp() || ev.MiddleDClick() )
    {
        button = _T("Middle");
        dbl = ev.MiddleDClick();
        up = ev.MiddleUp();
    }
    else if ( ev.RightDown() || ev.RightUp() || ev.RightDClick() )
    {
        button = _T("Right");
        dbl = ev.RightDClick();
        up = ev.RightUp();
    }
    else
    {
        return _T("Unknown mouse event");
    }

    return wxString::Format(_T("%s mouse button %s"),
                            button.c_str(),
                            dbl ? _T("double clicked")
                                : up ? _T("released") : _T("clicked"));
}

void MyTextCtrl::OnMouseEvent(wxMouseEvent& ev)
{
    ev.Skip();

    if ( !ms_logMouse )
        return;

    if ( !ev.Moving() )
    {
        wxString msg;
        if ( ev.Entering() )
        {
            msg = _T("Mouse entered the window");
        }
        else if ( ev.Leaving() )
        {
            msg = _T("Mouse left the window");
        }
        else
        {
            msg = GetMouseEventDesc(ev);
        }

        msg << _T(" at (") << ev.GetX() << _T(", ") << ev.GetY() << _T(") ");

        long pos;
        wxTextCtrlHitTestResult rc = HitTest(ev.GetPosition(), &pos);
        if ( rc != wxTE_HT_UNKNOWN )
        {
            msg << _T("at position ") << pos << _T(' ');
        }

        msg << _T("[Flags: ")
            << GetChar( ev.LeftIsDown(), _T('1') )
            << GetChar( ev.MiddleIsDown(), _T('2') )
            << GetChar( ev.RightIsDown(), _T('3') )
            << GetChar( ev.ControlDown(), _T('C') )
            << GetChar( ev.AltDown(), _T('A') )
            << GetChar( ev.ShiftDown(), _T('S') )
            << GetChar( ev.MetaDown(), _T('M') )
            << _T(']');

        wxLogMessage(msg);
    }
    //else: we're not interested in mouse move events
}

void MyTextCtrl::OnSetFocus(wxFocusEvent& event)
{
    if ( ms_logFocus )
        wxLogMessage( wxT("%p got focus."), this);

    event.Skip();
}

void MyTextCtrl::OnKillFocus(wxFocusEvent& event)
{
    if ( ms_logFocus )
        wxLogMessage( wxT("%p lost focus"), this);

    event.Skip();
}

void MyTextCtrl::OnText(wxCommandEvent& event)
{
    if ( !ms_logText )
        return;

    MyTextCtrl *win = (MyTextCtrl *)event.GetEventObject();
    const wxChar *changeVerb = win->IsModified() ? _T("changed")
                                                 : _T("set by program");
    const wxChar *data = (const wxChar *)(win->GetClientData());
    if ( data )
    {
        wxLogMessage(_T("Text %s in control \"%s\""), changeVerb, data);
    }
    else
    {
        wxLogMessage(_T("Text %s in some control"), changeVerb);
    }
}

void MyTextCtrl::OnTextEnter(wxCommandEvent& event)
{
    if ( !ms_logText )
        return;

    MyTextCtrl *win = (MyTextCtrl *)event.GetEventObject();
    const wxChar *data = (const wxChar *)(win->GetClientData());
    if ( data )
    {
        wxLogMessage(_T("Enter pressed in control '%s'"), data);
    }
    else
    {
        wxLogMessage(_T("Enter pressed in some control"));
    }
}

void MyTextCtrl::OnTextMaxLen(wxCommandEvent& WXUNUSED(event))
{
    wxLogMessage(_T("You can't enter more characters into this control."));
}

void MyTextCtrl::OnTextURL(wxTextUrlEvent& event)
{
    const wxMouseEvent& ev = event.GetMouseEvent();

    // filter out mouse moves, too many of them
    if ( ev.Moving() )
        return;

    long start = event.GetURLStart(),
         end = event.GetURLEnd();

    wxLogMessage(_T("Mouse event over URL '%s': %s"),
                 GetValue().Mid(start, end - start).c_str(),
                 GetMouseEventDesc(ev).c_str());
}

void MyTextCtrl::OnChar(wxKeyEvent& event)
{
    if ( ms_logChar )
        LogKeyEvent( _T("Char"), event);

    event.Skip();
}

void MyTextCtrl::OnKeyUp(wxKeyEvent& event)
{
    if ( ms_logKey )
        LogKeyEvent( _T("Key up"), event);

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

void MyTextCtrl::OnKeyDown(wxKeyEvent& event)
{
    switch ( event.GetKeyCode() )
    {
        case WXK_F1:
            // show current position and text length
            {
                long line, column, pos = GetInsertionPoint();
                PositionToXY(pos, &column, &line);

                wxLogMessage(_T("Current position: %ld\nCurrent line, column: (%ld, %ld)\nNumber of lines: %ld\nCurrent line length: %ld\nTotal text length: %u (%ld)"),
                        pos,
                        line, column,
                        (long) GetNumberOfLines(),
                        (long) GetLineLength(line),
                        (unsigned int) GetValue().length(),
                        GetLastPosition());

                long from, to;
                GetSelection(&from, &to);

                wxString sel = GetStringSelection();

                wxLogMessage(_T("Selection: from %ld to %ld."), from, to);
                wxLogMessage(_T("Selection = '%s' (len = %u)"),
                             sel.c_str(),
                             (unsigned int) sel.length());
            }
            break;

        case WXK_F2:
            // go to the end
            SetInsertionPointEnd();
            break;

        case WXK_F3:
            // go to position 10
            SetInsertionPoint(10);
            break;

        case WXK_F4:
            if (!m_hasCapture)
            {
                wxLogDebug( wxT("Now capturing mouse and events.") );
                m_hasCapture = true;
                CaptureMouse();
            }
            else
            {
                wxLogDebug( wxT("Stopped capturing mouse and events.") );
                m_hasCapture = false;
                ReleaseMouse();
            }
            break;

        case WXK_F5:
            // insert a blank line
            WriteText(_T("\n"));
            break;

        case WXK_F6:
            wxLogMessage(_T("IsModified() before SetValue(): %d"),
                         IsModified());
            ChangeValue(_T("ChangeValue() has been called"));
            wxLogMessage(_T("IsModified() after SetValue(): %d"),
                         IsModified());
            break;

        case WXK_F7:
            wxLogMessage(_T("Position 10 should be now visible."));
            ShowPosition(10);
            break;

        case WXK_F8:
            wxLogMessage(_T("Control has been cleared"));
            Clear();
            break;

        case WXK_F9:
            WriteText(_T("WriteText() has been called"));
            break;

        case WXK_F10:
            AppendText(_T("AppendText() has been called"));
            break;

        case WXK_F11:
            DiscardEdits();
            wxLogMessage(_T("Control marked as non modified"));
            break;
    }

    if ( ms_logKey )
        LogKeyEvent( wxT("Key down"), event);

    event.Skip();
}

