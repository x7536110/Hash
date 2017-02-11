/***************************************************************
 * Name:      HASHMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Richard (x7536110@outlook.com)
 * Created:   2017-02-11
 * Copyright: Richard ()
 * License:   GPL v3
 **************************************************************/

#include "HASHMain.h"
#include <wx/msgdlg.h>
#include <wx/filedlg.h>
#include <wx/clipbrd.h>
#include "md5.h"

//(*InternalHeaders(HASHDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(HASHDialog)
const long HASHDialog::ID_BUTTON1 = wxNewId();
const long HASHDialog::ID_BUTTON2 = wxNewId();
const long HASHDialog::ID_BUTTON3 = wxNewId();
const long HASHDialog::ID_BUTTON4 = wxNewId();
const long HASHDialog::ID_BUTTON5 = wxNewId();
const long HASHDialog::ID_CHECKBOX1 = wxNewId();
const long HASHDialog::ID_CHECKBOX2 = wxNewId();
const long HASHDialog::ID_CHECKBOX3 = wxNewId();
const long HASHDialog::ID_CHECKBOX4 = wxNewId();
const long HASHDialog::ID_STATICTEXT1 = wxNewId();
const long HASHDialog::ID_STATICTEXT2 = wxNewId();
const long HASHDialog::ID_GAUGE1 = wxNewId();
const long HASHDialog::ID_GAUGE2 = wxNewId();
const long HASHDialog::ID_TEXTCTRL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(HASHDialog,wxDialog)
    //(*EventTable(HASHDialog)
    //*)
END_EVENT_TABLE()

HASHDialog::HASHDialog(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(HASHDialog)
    Create(parent, wxID_ANY, _(" MD5&SHA1 Generator - Richard - x7536110@outlook.com"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(500,340));
    browse = new wxButton(this, ID_BUTTON1, _("Browse..."), wxPoint(16,248), wxSize(72,24), 0, wxDefaultValidator, _T("ID_BUTTON1"));
    clear = new wxButton(this, ID_BUTTON2, _("Clear"), wxPoint(96,248), wxSize(72,24), 0, wxDefaultValidator, _T("ID_BUTTON2"));
    copy = new wxButton(this, ID_BUTTON3, _("Copy"), wxPoint(176,248), wxSize(72,24), 0, wxDefaultValidator, _T("ID_BUTTON3"));
    save = new wxButton(this, ID_BUTTON4, _("Save..."), wxPoint(256,248), wxSize(72,24), 0, wxDefaultValidator, _T("ID_BUTTON4"));
    stop = new wxButton(this, ID_BUTTON5, _("Stop"), wxPoint(336,248), wxSize(72,24), 0, wxDefaultValidator, _T("ID_BUTTON5"));
    version = new wxCheckBox(this, ID_CHECKBOX1, _("Version"), wxPoint(424,240), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    version->SetValue(true);
    date = new wxCheckBox(this, ID_CHECKBOX2, _("Date"), wxPoint(424,264), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
    date->SetValue(true);
    md5check = new wxCheckBox(this, ID_CHECKBOX3, _("MD5"), wxPoint(424,288), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
    md5check->SetValue(true);
    sha1check = new wxCheckBox(this, ID_CHECKBOX4, _("SHA1"), wxPoint(424,312), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
    sha1check->SetValue(false);
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("File"), wxPoint(16,288), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Total"), wxPoint(16,312), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    file = new wxGauge(this, ID_GAUGE1, 100, wxPoint(56,288), wxSize(352,15), 0, wxDefaultValidator, _T("ID_GAUGE1"));
    total = new wxGauge(this, ID_GAUGE2, 100, wxPoint(56,312), wxSize(352,15), 0, wxDefaultValidator, _T("ID_GAUGE2"));
    TextCtrl1 = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxPoint(16,16), wxSize(464,208), wxTE_MULTILINE|wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    Center();

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&HASHDialog::OnbrowseClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&HASHDialog::OnclearClick);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&HASHDialog::OncopyClick);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&HASHDialog::OnsaveClick);
    Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&HASHDialog::OnCheckBox1Click);
    Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&HASHDialog::OnTextCtrl1Text);
    //*)
}

HASHDialog::~HASHDialog()
{
    //(*Destroy(HASHDialog)
    //*)
}

void HASHDialog::OnQuit(wxCommandEvent& event)
{
    Close();
}

void HASHDialog::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void HASHDialog::OnCheckBox1Click(wxCommandEvent& event)
{
}
#include <fstream>
#include <iostream>
#include <ostream>
#include <string.h>
#include <wx/datetime.h>
using std::fstream;
using std::ostream;

void HASHDialog::OnbrowseClick(wxCommandEvent& event)
{

    wxString caption=wxT("Choose a file...");
    wxString wildcard=wxT("any file(*.*)|*.*");
    wxString defaultDir=wxT("C:\\");
    wxString defaultFilename=wxEmptyString;
    wxString path=wxEmptyString;
    int size;

    char path_c[255];
    wxFileDialog dialog(this,caption,defaultDir,defaultFilename,wildcard,wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    if(dialog.ShowModal()==wxID_OK)
    {
        path = dialog.GetPath();
        //int filterIndex = dialog.GetFilterIndex();
        //TextCtrl1->LoadFile(path);
    }

    string md5_str;
    string sha1_str;

    if(md5check->GetValue())
    {
        CMD5 cmd5;
        strncpy(path_c,(const char*)path.mb_str(wxConvUTF8),255);
        ifstream fin(path_c,ios::binary);
        cmd5.GenerateMD5(fin,size);
        fin.close();
        md5_str=cmd5.ToString();
    }


    TextCtrl1->Clear();

    wxDateTime now=wxDateTime::Now();
    std::streambuf *sbOld = std::cout.rdbuf();
    std::cout.rdbuf(TextCtrl1);
    //cout<<path<<"\n"<<now.Format()<<"\n"<<""<<md5_str;

    if(version->GetValue())
        cout<<"File: "<<path<<"\n"<<"Size: "<<size<<"Byte"<<"\n";
    if(date->GetValue())
        cout<<"Modified: "<<now.Format()<<"\n";
    if(md5check->GetValue())
        cout<<"MD5: "<<md5_str<<"\n";
    if(sha1check->GetValue())
        ;


}


void HASHDialog::OnTextCtrl1Text(wxCommandEvent& event)
{

}

void HASHDialog::OnclearClick(wxCommandEvent& event)
{
    TextCtrl1->Clear();
}

void HASHDialog::OncopyClick(wxCommandEvent& event)
{
    wxTheClipboard->Open();
    wxTheClipboard->SetData(new wxTextDataObject(TextCtrl1->GetValue()));
    wxTheClipboard->Close();
}

void HASHDialog::OnsaveClick(wxCommandEvent& event)
{

    wxString caption=wxT("Choose a location to save...");
    wxString wildcard=wxT("text file(*.txt)|*.txt");
    wxString defaultDir=wxT("C:\\");
    wxString defaultFilename=wxEmptyString;
    wxFileDialog dialog(this,caption,defaultDir,defaultFilename,wildcard,wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if(dialog.ShowModal()==wxID_OK)
    {
        TextCtrl1->SaveFile(dialog.GetPath());
    }
}
