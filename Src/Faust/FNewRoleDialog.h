#ifndef FNEWROLEDIALOG_H
#define FNEWROLEDIALOG_H

#include "wx/wx.h" 
#include "Config.h"
#include "Utils.h"

class FNewRoleDialog : public wxDialog
{
	public:
		enum EMode
		{
			EM_NewUser,
			EM_NewGroup,
			EM_EditUser,
		};

		FNewRoleDialog(wxWindow *parent, wxWindowID id, const wxString& sTitle, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, EMode eMode = EM_NewUser);

		string GetRoleName() const;
		string GetPassword() const;
		string GetParentRole() const;

	public:
		enum
		{
			ID_NameEntry,
			ID_NameChoice,
			ID_Password,
			ID_ParentRole
		};

		DECLARE_EVENT_TABLE()

		void OnOkButton(wxCommandEvent& event);

	private:
		void UpdateGroupList();
		void UpdateUserList();


	private:
		wxTextCtrl*		m_pNameEntry;
		wxChoice*		m_pNameChoice;
		wxTextCtrl*		m_pPassword;
		wxListBox*		m_pParentRole;

		EMode			m_eMode;
};

#endif