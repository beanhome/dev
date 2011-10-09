#ifndef FDateControl_H
#define FDateControl_H

#include "wx/wx.h" 
#include "Config.h"
#include "Utils.h"
#include "FDatation.h"
#include "wx/datectrl.h"

class FDateControl : public wxPanel
{
	public:
		FDateControl(wxWindow *parent, wxWindowID id, const wxString& sLabel); 

		bool IsActivated() { return m_pDateCheckBox != NULL && m_pDateCheckBox->IsChecked(); }
		void Activate(bool bActivate);

		wxTextCtrl* GetTextControl() const { return m_pDateEntry; }

		FDate GetDate() const;

		enum
		{
			ID_Text,
			ID_CheckBox,
			ID_CalButton
		};

	public:
		DECLARE_EVENT_TABLE()

		void OnCheckStartDate(wxCommandEvent& event);
		void OnClickStartDateCalBtn(wxCommandEvent& event);

	private:
		wxStaticText*		m_pDateText;
		wxCheckBox*			m_pDateCheckBox;
		wxTextCtrl*			m_pDateEntry;
		wxButton*			m_pDateCalBtn;
};

#endif