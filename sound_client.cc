#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <wx/wxprec.h>
#ifdef __BORLANDC__
#pragma hdrstop
#endif
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class SoundClientApp : public wxApp
{
public:
  bool OnInit();
};

class SoundClientFrame : public wxFrame
{
public:
  SoundClientFrame();
  ~SoundClientFrame();
  void OnQuit(wxCommandEvent &event);
  void OnAbout(wxCommandEvent &event);
protected:
  DECLARE_EVENT_TABLE()
};

enum {
  MENU_QUIT = wxID_EXIT,
  MENU_ABOUT = wxID_ABOUT,
};

BEGIN_EVENT_TABLE(SoundClientFrame, wxFrame)
EVT_MENU(MENU_QUIT, SoundClientFrame::OnQuit)
EVT_MENU(MENU_ABOUT, SoundClientFrame::OnAbout)
END_EVENT_TABLE()

IMPLEMENT_APP(SoundClientApp)

bool SoundClientApp::OnInit()
{
  if (!wxApp::OnInit()) {
    return false;
  }
  SoundClientFrame *frame = new SoundClientFrame;
  frame->Show(true);
  return true;
}

SoundClientFrame::SoundClientFrame()
  : wxFrame(NULL, wxID_ANY, wxT("wx_sample"), wxDefaultPosition, wxSize(800, 600))
{
  wxMenu *menu_file = new wxMenu;
  menu_file->Append(MENU_QUIT, "E&xit", "Quit this program");

  wxMenu *menu_help = new wxMenu;
  menu_help->Append(MENU_ABOUT, "&About", "Show about dialog");

  wxMenuBar *menubar = new wxMenuBar;
  menubar->Append(menu_file, "&File");
  menubar->Append(menu_help, "&Help");

  SetMenuBar(menubar);
}

SoundClientFrame::~SoundClientFrame()
{
}

void SoundClientFrame::OnQuit(wxCommandEvent &WXUNUSED(event))
{
  Close(true);
}

void SoundClientFrame::OnAbout(wxCommandEvent &WXUNUSED(event))
{
    wxMessageBox(wxString::Format
                 (
                    "Welcome to %s!\n"
                    "\n"
                    "This is the minimal wxWidgets sample\n"
                    "running under %s.",
                    wxVERSION_STRING,
                    wxGetOsDescription()
                 ),
                 "About wxWidgets minimal sample",
                 wxOK | wxICON_INFORMATION,
                 this);
}
