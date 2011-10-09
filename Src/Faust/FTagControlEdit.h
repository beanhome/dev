#ifndef FTAGCONTROLEDIT_H
#define FTAGCONTROLEDIT_H

#include "wx/wx.h" 
#include "Utils.h"
#include "Config.h"
#include "FTagControl.h"


class FTagControlEdit : public FTagControl
{
	public:
		FTagControlEdit(); 
		//FTagControlEdit(wxWindow *parent, wxWindowID id, const wxString& sLabel); 

		virtual bool Create(wxWindow *parent, wxWindowID id, const wxString& sLabel);
	public:
		enum
		{
			ID_CreateBtn = ID_FTagControl_MAX
		};

		DECLARE_EVENT_TABLE()

		void OnCreateButton(wxCommandEvent& event);
		
	private:
		wxButton*			m_pCreateBtn;

};

#endif