#ifndef FROLECONTROLVIEW_H
#define FROLECONTROLVIEW_H

#include "wx/wx.h" 
#include "Utils.h"
#include "Config.h"
#include "FRoleControl.h"

class FRoleControlView : public FRoleControl
{
	public:
		FRoleControlView(wxWindow *parent, wxWindowID id, const wxString& sLabel); 
		
		virtual string GetLogin() const;

		string GetJoinQuery() const;

		void Activate(bool bActivate);
		bool IsActivated() const;

	public:
		enum
		{
			ID_Activate = ID_FRoleControl_MAX,
			ID_Login,
		};

		DECLARE_EVENT_TABLE()

		void OnChangeLogin(wxCommandEvent& event);
		void OnActivate(wxCommandEvent& event);

	private:
		void UpdateLoginList(const string& sLogin);

	private:
		wxCheckBox*			m_pActivateCheckBox;
		wxChoice*			m_pLogin;
		wxTextCtrl*			m_pLoginControl;

};

#endif