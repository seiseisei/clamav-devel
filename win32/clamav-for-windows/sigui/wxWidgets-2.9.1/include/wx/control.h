/////////////////////////////////////////////////////////////////////////////
// Name:        wx/control.h
// Purpose:     wxControl common interface
// Author:      Vadim Zeitlin
// Modified by:
// Created:     26.07.99
// RCS-ID:      $Id$
// Copyright:   (c) wxWidgets team
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_CONTROL_H_BASE_
#define _WX_CONTROL_H_BASE_

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

#include "wx/defs.h"

#if wxUSE_CONTROLS

#include "wx/window.h"      // base class

extern WXDLLIMPEXP_DATA_CORE(const char) wxControlNameStr[];


// ----------------------------------------------------------------------------
// Ellipsize() constants
// ----------------------------------------------------------------------------

enum wxEllipsizeFlags
{
    wxELLIPSIZE_FLAGS_NONE = 0,
    wxELLIPSIZE_FLAGS_PROCESS_MNEMONICS = 1,
    wxELLIPSIZE_FLAGS_EXPAND_TABS = 2,

    wxELLIPSIZE_FLAGS_DEFAULT = wxELLIPSIZE_FLAGS_PROCESS_MNEMONICS |
                                wxELLIPSIZE_FLAGS_EXPAND_TABS
};

// NB: Don't change the order of these values, they're the same as in
//     PangoEllipsizeMode enum.
enum wxEllipsizeMode
{
    wxELLIPSIZE_NONE,
    wxELLIPSIZE_START,
    wxELLIPSIZE_MIDDLE,
    wxELLIPSIZE_END
};

// ----------------------------------------------------------------------------
// wxControl is the base class for all controls
// ----------------------------------------------------------------------------

class WXDLLIMPEXP_CORE wxControlBase : public wxWindow
{
public:
    wxControlBase() { }

    virtual ~wxControlBase();

    // Create() function adds the validator parameter
    bool Create(wxWindow *parent, wxWindowID id,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize,
                long style = 0,
                const wxValidator& validator = wxDefaultValidator,
                const wxString& name = wxControlNameStr);

    // get the control alignment (left/right/centre, top/bottom/centre)
    int GetAlignment() const { return m_windowStyle & wxALIGN_MASK; }

    // set label with mnemonics
    virtual void SetLabel(const wxString& label)
    {
        m_labelOrig = label;

        InvalidateBestSize();

        wxWindow::SetLabel(label);
    }

    // return the original string, as it was passed to SetLabel()
    // (i.e. with wx-style mnemonics)
    virtual wxString GetLabel() const { return m_labelOrig; }

    // set label text (mnemonics will be escaped)
    virtual void SetLabelText(const wxString& text)
    {
        SetLabel(EscapeMnemonics(text));
    }

    // get just the text of the label, without mnemonic characters ('&')
    virtual wxString GetLabelText() const { return GetLabelText(GetLabel()); }

    // controls by default inherit the colours of their parents, if a
    // particular control class doesn't want to do it, it can override
    // ShouldInheritColours() to return false
    virtual bool ShouldInheritColours() const { return true; }


    // WARNING: this doesn't work for all controls nor all platforms!
    //
    // simulates the event of given type (i.e. wxButton::Command() is just as
    // if the button was clicked)
    virtual void Command(wxCommandEvent &event);

    virtual bool SetFont(const wxFont& font);

    // wxControl-specific processing after processing the update event
    virtual void DoUpdateWindowUI(wxUpdateUIEvent& event);



    // static utilities for mnemonics char (&) handling
    // ------------------------------------------------

    // returns the given string without mnemonic characters ('&')
    static wxString GetLabelText(const wxString& label);

    // returns the given string without mnemonic characters ('&')
    // this function is identic to GetLabelText() and is provided for clarity
    // and for symmetry with the wxStaticText::RemoveMarkup() function.
    static wxString RemoveMnemonics(const wxString& str);

    // escapes (by doubling them) the mnemonics
    static wxString EscapeMnemonics(const wxString& str);


    // miscellaneous static utilities
    // ------------------------------

    // replaces parts of the given (multiline) string with an ellipsis if needed
    static wxString Ellipsize(const wxString& label, const wxDC& dc,
                              wxEllipsizeMode mode, int maxWidth,
                              int flags = wxELLIPSIZE_FLAGS_DEFAULT);

    // return the accel index in the string or -1 if none and puts the modified
    // string into second parameter if non NULL
    static int FindAccelIndex(const wxString& label,
                              wxString *labelOnly = NULL);

    // this is a helper for the derived class GetClassDefaultAttributes()
    // implementation: it returns the right colours for the classes which
    // contain something else (e.g. wxListBox, wxTextCtrl, ...) instead of
    // being simple controls (such as wxButton, wxCheckBox, ...)
    static wxVisualAttributes
        GetCompositeControlsDefaultAttributes(wxWindowVariant variant);

protected:
    // choose the default border for this window
    virtual wxBorder GetDefaultBorder() const;

    // creates the control (calls wxWindowBase::CreateBase inside) and adds it
    // to the list of parents children
    bool CreateControl(wxWindowBase *parent,
                       wxWindowID id,
                       const wxPoint& pos,
                       const wxSize& size,
                       long style,
                       const wxValidator& validator,
                       const wxString& name);

    // initialize the common fields of wxCommandEvent
    void InitCommandEvent(wxCommandEvent& event) const;

    // Ellipsize() helper:
    static wxString DoEllipsizeSingleLine(const wxString& label, const wxDC& dc,
                                          wxEllipsizeMode mode, int maxWidth,
                                          int replacementWidth, int marginWidth);

    // this field contains the label in wx format, i.e. with '&' mnemonics,
    // as it was passed to the last SetLabel() call
    wxString m_labelOrig;

    wxDECLARE_NO_COPY_CLASS(wxControlBase);
};

// ----------------------------------------------------------------------------
// include platform-dependent wxControl declarations
// ----------------------------------------------------------------------------

#if defined(__WXUNIVERSAL__)
    #include "wx/univ/control.h"
#elif defined(__WXPALMOS__)
    #include "wx/palmos/control.h"
#elif defined(__WXMSW__)
    #include "wx/msw/control.h"
#elif defined(__WXMOTIF__)
    #include "wx/motif/control.h"
#elif defined(__WXGTK20__)
    #include "wx/gtk/control.h"
#elif defined(__WXGTK__)
    #include "wx/gtk1/control.h"
#elif defined(__WXMAC__)
    #include "wx/osx/control.h"
#elif defined(__WXCOCOA__)
    #include "wx/cocoa/control.h"
#elif defined(__WXPM__)
    #include "wx/os2/control.h"
#endif

#endif // wxUSE_CONTROLS

#endif
    // _WX_CONTROL_H_BASE_
