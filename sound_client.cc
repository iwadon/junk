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
  void OnConnectButtonClicked(wxCommandEvent &event);
private:
  wxButton *connect_button_;
protected:
  DECLARE_EVENT_TABLE()
};

enum {
  ID_CONNECT_BUTTON = 1,

  MENU_QUIT = wxID_EXIT,
  MENU_ABOUT = wxID_ABOUT,
};

BEGIN_EVENT_TABLE(SoundClientFrame, wxFrame)
  EVT_MENU(MENU_QUIT, SoundClientFrame::OnQuit)
  EVT_MENU(MENU_ABOUT, SoundClientFrame::OnAbout)
  EVT_BUTTON(ID_CONNECT_BUTTON, SoundClientFrame::OnConnectButtonClicked)
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
  : wxFrame(NULL, wxID_ANY, wxT("Sound Client"), wxDefaultPosition, wxDefaultSize)
{
  // menu Bar
  wxMenuBar *menubar = new wxMenuBar;
  wxMenu *menu = new wxMenu;
  menu->Append(MENU_QUIT, "E&xit", "Quit this program");
  menubar->Append(menu, "&File");
  menu = new wxMenu;
  menu->Append(MENU_ABOUT, "&About", "Show about dialog");
  menubar->Append(menu, "&Help");
  SetMenuBar(menubar);

  wxPanel *panel = new wxPanel(this, wxID_ANY);

  wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
  connect_button_ = new wxButton(panel, ID_CONNECT_BUTTON, "Connect");
  sizer->Add(connect_button_, 0, 0, 0);
  sizer->Add(new wxStaticText(panel, wxID_ANY, wxT("---")), 0, 0, 0);
  sizer->SetSizeHints(panel);
  panel->SetSizer(sizer);
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

void SoundClientFrame::OnConnectButtonClicked(wxCommandEvent &event)
{
  connect_button_->SetLabel("OK");
}
