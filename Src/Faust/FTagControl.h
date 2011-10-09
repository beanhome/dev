#ifndef FTAGCONTROL_H
#define FTAGCONTROL_H

#include "wx/wx.h" 
#include "Config.h"
#include "Utils.h"
#include "FListControl.h"

class FEvent;

class FTagControl : public wxPanel
{
	public:
		FTagControl(); 
		FTagControl(wxWindow *parent, wxWindowID id, const wxString& sLabel); 

		virtual bool Create(wxWindow *parent, wxWindowID id, const wxString& sLabel);
		
		string GetJoinQuery() const;

		void Save(FEvent& oEvent) const;
		void Load(const FEvent& oEvent);
		void ApplyModif(FEvent& oEvent);

		void ClearSelection();
		void SetSelection(const wxString& sName, bool bSelect);
		void SetSelection(const string& sName, bool bSelect);
		void SetSelection(const wxString& sName, ESelectState eSelect);
		void SetSelection(const string& sName, ESelectState eSelect);

		//ESelectState GetSelectState(const string& sName) const;

	public:
		enum
		{
			ID_Tag,

			ID_FTagControl_MAX
		};

		DECLARE_EVENT_TABLE()

		void OnChangeTag(wxCommandEvent& event);

	protected:
		void UpdateTagList();
		void GetTag(vector<string>& aTag) const;

	protected:
		FListControl*		m_pTag;
};

#endif