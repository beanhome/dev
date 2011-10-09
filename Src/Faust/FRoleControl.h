#ifndef FROLECONTROL_H
#define FROLECONTROL_H

#include "wx/wx.h" 
#include "Utils.h"
#include "Config.h"
#include "FListControl.h"

class FEvent;

class FRoleControl : public wxPanel
{
	public:
		FRoleControl(wxWindow *parent, wxWindowID id, const wxString& sLabel); 

		virtual string GetLogin() const;

		void ClearSelection();
		void SetSelection(const wxString& sRole, bool bSelect = true);
		void SetSelection(const string& sRole, bool bSelect = true);

		void SetSelection(const wxString& sRole, ESelectState eState);
		void SetSelection(const string& sRole, ESelectState eState);

		void ApplyModif(FEvent& oEvent);

	public:
		enum
		{
			ID_Role,

			ID_FRoleControl_MAX
		};

		DECLARE_EVENT_TABLE()

		void OnChangeRole(wxCommandEvent& event);

	protected:
		void Create(wxSizer* pSizer);

		void UpdateRoleList();
		void GetRole(vector<string>& aRole) const;

	protected:
		FListControl*			m_pRole;

};

#endif