#ifndef FFILTERPANEL_H
#define FFILTERPANEL_H

#include "wx/wx.h" 
#include "Config.h"
#include "Utils.h"
//#include "FDatation.h"
//#include "wx/datectrl.h"

class FDatationControl;
class FLocationControl;
class FRoleControlView;
class FTagControl;
class FNameRefControl;

class FFilterPanel : public wxScrolledWindow
{
	public:
		FFilterPanel(wxWindow *parent, wxWindowID id); 

		string GetQuery() const;

	public:
		DECLARE_EVENT_TABLE()

	private:

	private:
		wxTextCtrl*			m_pNameRegExp;

		FNameRefControl*	m_pNameRefControl;

		FRoleControlView*	m_pRoleControl;

		FDatationControl*	m_pDatationControl;

		FLocationControl*	m_pLocationControl;
		
		FTagControl*		m_pTagControl;

		FDatationControl*	m_pLastEventControl;
};

#endif