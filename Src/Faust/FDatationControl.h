#ifndef FDatationControl_H
#define FDatationControl_H

#include "wx/wx.h" 
#include "Config.h"
#include "Utils.h"
#include "FDatation.h"
#include "wx/datectrl.h"

class FDateControl;

class FDatationControl : public wxPanel
{
	public:
		FDatationControl(wxWindow *parent, wxWindowID id, const wxString& sLabel, wxPoint pos = wxDefaultPosition, wxSize size = wxDefaultSize, bool bNoActivate = false); 

		void Activate(bool bActivate);
		bool IsActivated() const;

		bool IsStartActivated() const;
		bool IsEndActivated() const;

		void SetDatation(const FDatation& oDatation);

		FDate GetStartDate() const;
		FDate GetEndDate() const;

		enum
		{
			ID_Activate,
			ID_StartDate,
			ID_EndDate
		};

	public:
		DECLARE_EVENT_TABLE()

		void OnActivate(wxCommandEvent& event);

	private:
		wxCheckBox*			m_pActivateCheckBox;
		FDateControl*		m_pStartDate;
		FDateControl*		m_pEndDate;
};

#endif