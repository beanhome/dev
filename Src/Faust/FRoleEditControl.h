#ifndef FRoleEditControl_H
#define FRoleEditControl_H

#include "wx/wx.h" 
#include "Utils.h"
#include "Config.h"
#include "FDatation.h"
#include "wx/datectrl.h"

class FEvent;

class FRoleEditControl : public wxWindow
{
	public:
		FRoleEditControl(wxWindow *parent, wxWindowID id, const wxString& sLabel); 

		void Save(FEvent& oEvent) const;
		void Load(const FEvent& oEvent);
		
	public:
		enum
		{
			ID_Role,
			ID_CreateBtn
		};

		DECLARE_EVENT_TABLE()

		void OnChangeRole(wxCommandEvent& event);
		void OnCreateButton(wxCommandEvent& event);
		

	private:
		void UpdateRoleList();
		void UpdateRole();

	private:
		wxListBox*			m_pRole;
		wxButton*			m_pCreateBtn;

};

#endif