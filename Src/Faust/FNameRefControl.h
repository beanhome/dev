#ifndef FNAMEREFCONTROL_H
#define FNAMEREFCONTROL_H

#include "wx/wx.h" 
#include "Config.h"
#include "Utils.h"
#include "FListControl.h"

class FEvent;

class FNameRefControl : public wxPanel
{
	public:
		FNameRefControl(wxWindow *parent, wxWindowID id, const wxString& sLabel); 

		string GetValue();
		void SetValue(const string& sValue);

		bool IsValid() const;

		//void Save(FEvent& oEvent) const;
		//void Load(const FEvent& oEvent);
		//void ApplyModif(FEvent& oEvent);

	public:
		enum
		{
			ID_NameRef,

			ID_FNameRefControl_MAX
		};

		DECLARE_EVENT_TABLE()

		void OnSetNameFilter(wxCommandEvent& oEvent);
		void OnChangeName(wxCommandEvent& oEvent);

	protected:

	protected:
		wxComboBox*			m_pNameRef;
};

#endif