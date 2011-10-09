#ifndef FRoleEditControl_H
#define FRoleEditControl_H

#include "wx/wx.h" 
#include "Utils.h"
#include "Config.h"
#include "FRoleControl.h"

class FEvent;

class FRoleControlEdit : public FRoleControl
{
	public:
		FRoleControlEdit(wxWindow *parent, wxWindowID id, const wxString& sLabel); 

		void Save(FEvent& oEvent) const;
		void Load(const FEvent& oEvent);
		
	public:
		enum
		{
			ID_CreateBtn = ID_FRoleControl_MAX
		};

		DECLARE_EVENT_TABLE()

		void OnCreateButton(wxCommandEvent& event);
		
	private:

	private:
		wxButton*			m_pCreateBtn;

};

#endif