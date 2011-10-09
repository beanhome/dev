#ifndef FLOGINDIALOG_H
#define FLOGINDIALOG_H

#include "wx/wx.h" 
#include "Config.h"
#include "Utils.h"
#include "FLocation.h"
#include "FLocationControl.h"

class FLocationControl;

class FLoginDialog : public wxFrame
{
	public:
		FLoginDialog(const wxString& title, const string& sHost, const string& sPort, const string& sBaseName, const string& sLogin, const string& sPassword, const string& sError);
		virtual ~FLoginDialog();

		string	GetHost()		const { return string(m_pHost->GetValue().mb_str(wxConvISO8859_1)); }
		string	GetPort()		const { return string(m_pPort->GetValue().mb_str(wxConvISO8859_1)); }
		string	GetBaseName()	const { return string(m_pBaseName->GetValue().mb_str(wxConvISO8859_1)); }
		string	GetLogin()		const { return string(m_pLogin->GetValue().mb_str(wxConvISO8859_1)); }
		string	GetPassword()	const { return string(m_pPassword->GetValue().mb_str(wxConvISO8859_1)); }

	public:
		enum
		{
			ID_Host,
			ID_Port,
			ID_BaseName,
			ID_Login,
			ID_Password,
			ID_OkButton,
			ID_CancelButton
		};

		DECLARE_EVENT_TABLE()
		void OnClickOkButton(wxCommandEvent& event);
		void OnClickCancelButton(wxCommandEvent& event);


	private:
		wxTextCtrl*		m_pHost;
		wxTextCtrl*		m_pPort;
		wxTextCtrl*		m_pBaseName;
		wxTextCtrl*		m_pLogin;
		wxTextCtrl*		m_pPassword;

		wxButton*		m_pOkButton;
		wxButton*		m_pCancelButton;
};

#endif