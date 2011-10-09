#ifndef FLISTCONTROL_H
#define FLISTCONTROL_H

#include "wx/wx.h" 
#include "Config.h"
#include "Utils.h"

enum ESelectState
{
	EUnselect,
	ESelect,
	EUndefined,

	ESelectState_MAX
};

typedef map<string, ESelectState> SelectMap;
typedef pair<string, ESelectState> SelectPair;

class FListLine : public wxPanel
{
	public:
		FListLine(wxWindow *parent, wxWindowID id, const wxString& sLabel, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);

		bool IsSelected() const { return m_eState == ESelect; } 
		ESelectState GetSelectState() const { return m_eState; } 

		void SetSelecState(ESelectState eState) { m_eState = eState; Update(); }
		void Select(bool bSelect = true) { m_eState = (bSelect ? ESelect : EUnselect); Update(); }
		void Unselect() { Select(false); }

		wxString GetLabel() const { return m_pLabel->GetLabel(); }

	public:
		enum
		{
			ID_Label,
			ID_FListLine_MAX
		};

		DECLARE_EVENT_TABLE()

		void OnLeftClick(wxMouseEvent& oEvent);

	public:
		static wxColour s_oColour[ESelectState_MAX];

	protected:
		void Update();

	protected:
		ESelectState		m_eState;
		wxStaticText*		m_pLabel;
};

class FListControl : public wxScrolledWindow
{
	public:
		FListControl(wxWindow *parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize); 

		void				Clear();
		void				Append(const wxString& sLabel);

		int 				FindString(const wxString& sLabel) const;
		FListLine*			FindString(const wxString& sLabel, int& n) const;
		FListLine*			GetLine(int n) const;
		wxString			GetString(int n) const;
		ESelectState		GetLineState(const wxString& sLabel) const;
		void				GetSelectList(SelectMap& aMap) const;
		
		void				DeselectAll();
		void				SetSelection(const wxString& sLabel, bool bSelect = true) { SetSelection(sLabel, (bSelect ? ESelect : EUnselect)); }
		void				SetSelection(int n, bool bSelect = true) { SetSelection(n, (bSelect ? ESelect : EUnselect)); }
		void 				SetSelection(const wxString& sLabel, ESelectState eSelect);
		void 				SetSelection(int n, ESelectState eSelect);
		bool 				IsSelected(int n) const;
		uint 				GetCount() const;

	public:
		enum
		{
			ID_FListControl_MAX
		};

		DECLARE_EVENT_TABLE()

	protected:

	protected:
};

#endif