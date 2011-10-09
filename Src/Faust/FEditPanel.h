#ifndef FEDITPANEL_H
#define FEDITPANEL_H

#include "wx/wx.h" 
#include "Config.h"
#include "Utils.h"
#include "FDatation.h"
#include "wx/datectrl.h"
#include "FViewWindow.h"

class FDatationControl;
class FLocationListControl;
class FNameRefControl;
class FRoleControlEdit;
class FTagControlEdit;
class FEvent;

class FEditPanel : public wxScrolledWindow
{
	public:
		FEditPanel(wxWindow *parent, wxWindowID id); 

		void ClearSelection();

		void UpdateComp(vector<FEvent*> aEvent);

		void ApplyModif(FEvent& oEvent);

	public:
		enum
		{
		};
		DECLARE_EVENT_TABLE()

	private:
		void UpdateRoleSelection(SelectCountRoleMap aRole, int iSelectionCount);
		void UpdateTagSelection(SelectCountTagMap aTags, int iSelectionCount);
		void UpdateLocationSelection(SelectCountLocMap aLocations, int iSelectionCount);

	private:
		FNameRefControl*	m_pNameRef;

		//FDatationControl*	m_pDatationControl;

		FLocationListControl*	m_pLocationControl;
		
		FRoleControlEdit*	m_pRoleControl;

		FTagControlEdit*	m_pTagControl;

		wxButton*			m_pExecButton;
};

#endif