#ifndef FLOCATIONLISTCONTROL_H
#define FLOCATIONLISTCONTROL_H

#include "wx/wx.h" 
#include "Config.h"
#include "Utils.h"
#include "FLocation.h"


class FLocationLine : public wxPanel
{
public:
	FLocationLine(); 
	FLocationLine(wxWindow *parent, wxWindowID id, const FLocation& oLoc, bool bEdit);

	const FLocation& GetLocation() const { return m_oLocation; }
	void SetLocation(const FLocation& oLocation) { m_oLocation = oLocation; }

public:
	enum
	{
		ID_EditBtn,
		ID_DelBtn
	};

public:
	DECLARE_EVENT_TABLE()

	void OnEditButton(wxCommandEvent& event);
	void OnDelButton(wxCommandEvent& event);

	DECLARE_DYNAMIC_CLASS(FLocationLine)

private:

	wxBoxSizer*			m_pSizer;
	wxTextCtrl*			m_pText;
	wxButton*			m_pEditBtn;
	wxButton*			m_pDelBtn;

	FLocation			m_oLocation;
};

class FLocationListControl : public wxPanel
{
public:
	FLocationListControl(wxWindow *parent, wxWindowID id, wxString& sLabel, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, bool bEdit = false); 

	void AddLocation(const FLocation& oLoc);
	void ClearLocation();

	void CopyLocation(vector<FLocation>& aLoc);

public:
	enum
	{
		ID_AddBtn
	};

	DECLARE_EVENT_TABLE()

	void OnAddButton(wxCommandEvent& event);

private:
	bool				m_bEdit;
	
	wxWindow*			m_pLocationPanel;
	wxButton*			m_pAddBtn;

};

#endif