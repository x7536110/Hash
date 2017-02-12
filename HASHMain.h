/***************************************************************
 * Name:      HASHMain.h
 * Purpose:   Defines Application Frame
 * Author:    Richard (x7536110@outlook.com)
 * Created:   2017-02-11
 * Copyright: Richard ()
 * License:   GPL v3
 **************************************************************/

#ifndef HASHMAIN_H
#define HASHMAIN_H

//(*Headers(HASHDialog)
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/gauge.h>
//*)

class HASHDialog: public wxDialog
{
    public:

        HASHDialog(wxWindow* parent,wxWindowID id = -1);
        virtual ~HASHDialog();

    private:

        //(*Handlers(HASHDialog)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnCheckBox1Click(wxCommandEvent& event);
        void OnbrowseClick(wxCommandEvent& event);
        void OnTextCtrl1Text(wxCommandEvent& event);
        void OnclearClick(wxCommandEvent& event);
        void OncopyClick(wxCommandEvent& event);
        void OnsaveClick(wxCommandEvent& event);
        void OnInit(wxInitDialogEvent& event);
        //*)

        //(*Identifiers(HASHDialog)
        static const long ID_BUTTON1;
        static const long ID_BUTTON2;
        static const long ID_BUTTON3;
        static const long ID_BUTTON4;
        static const long ID_BUTTON5;
        static const long ID_CHECKBOX1;
        static const long ID_CHECKBOX2;
        static const long ID_CHECKBOX3;
        static const long ID_CHECKBOX4;
        static const long ID_STATICTEXT1;
        static const long ID_GAUGE1;
        static const long ID_TEXTCTRL1;
        //*)

        //(*Declarations(HASHDialog)
        wxButton* clear;
        wxButton* stop;
        wxCheckBox* version;
        wxButton* save;
        wxStaticText* StaticText1;
        wxButton* copy;
        wxButton* browse;
        wxCheckBox* sha1check;
        wxCheckBox* date;
        wxCheckBox* md5check;
        wxTextCtrl* TextCtrl1;
        wxGauge* file;
        //*)

        DECLARE_EVENT_TABLE()

        int gauge_now;
        int gauge_last;
        int64_t filesize;
};

#endif // HASHMAIN_H
