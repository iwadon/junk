#include <wx/wxprec.h>
#ifdef __BORLANDC__
#pragma hdrstop
#endif
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class MyApp : public wxApp
{
public:
  bool OnInit();
};

class MyFrame : public wxFrame
{
public:
  MyFrame();
  virtual ~MyFrame();
  void OnQuit(wxCommandEvent &event);
  void OnAbout(wxCommandEvent &event);
protected:
  DECLARE_EVENT_TABLE()
};

enum {
  MENU_QUIT = wxID_EXIT,
  MENU_ABOUT = wxID_ABOUT,
};

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_MENU(MENU_QUIT, MyFrame::OnQuit)
EVT_MENU(MENU_ABOUT, MyFrame::OnAbout)
END_EVENT_TABLE()

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
  if (!wxApp::OnInit()) {
    return false;
  }
  MyFrame *frame = new MyFrame;
  frame->Show(true);
  return true;
}

MyFrame::MyFrame()
  : wxFrame(NULL, wxID_ANY, wxT("wx_sample"))
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

MyFrame::~MyFrame()
{
}

void MyFrame::OnQuit(wxCommandEvent &WXUNUSED(event))
{
  Close(true);
}

void MyFrame::OnAbout(wxCommandEvent &WXUNUSED(event))
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
