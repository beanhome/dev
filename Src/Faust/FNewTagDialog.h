#ifndef FNEWTAGDIALOG_H
#define FNEWTAGDIALOG_H

#include "wx/wx.h" 
#include "Config.h"
#include "Utils.h"

class FNewTagDialog : public wxDialog
{
	public:
		FNewTagDialog(wxWindow *parent, wxWindowID id);

		string GetTagName() const;

	public:
		enum
		{
			ID_Name
		};

		DECLARE_EVENT_TABLE()

		void OnCreateButton(wxCommandEvent& event);

	private:
		wxTextCtrl*		m_pName;
};

#endif