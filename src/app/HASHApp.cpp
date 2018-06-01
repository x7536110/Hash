/***************************************************************
 * Name:      HASHApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Richard (x7536110@outlook.com)
 * Created:   2017-02-11
 * Copyright: Richard ()
 * License:
 **************************************************************/

#include "HASHApp.h"

//(*AppHeaders
#include "HASHMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(HASHApp);

bool HASHApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	HASHDialog Dlg(0);
    	SetTopWindow(&Dlg);
    	Dlg.ShowModal();
    	wxsOK = false;
    }
    //*)

    return wxsOK;

}

