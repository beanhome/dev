#ifndef FROLECONTROLVIEW_H
#define FROLECONTROLVIEW_H

#include "wx/wx.h" 
#include "Utils.h"
#include "Config.h"
#include "FRoleControl.h"

class FRoleControlComp : public FRoleControl
{
	public:
		FRoleControlComp(wxWindow *parent, wxWindowID id, const wxString& sLabel); 

	public:
		enum
		{
		};

		DECLARE_EVENT_TABLE()

	private:

	private:

};

#endif