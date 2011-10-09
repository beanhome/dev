#ifndef FVIEWWINDOW_H
#define FVIEWWINDOW_H

#include "wx/wx.h" 
#include "Utils.h"
#include "FLocation.h"

class FFilterPanel;
class FResultPanel;
class FEditPanel;


typedef map<string, int> SelectCountRoleMap;
typedef pair<string, int> SelectCountRolePair;

typedef map<string, int> SelectCountTagMap;
typedef pair<string, int> SelectCountTagPair;

typedef map<FLocation, int, ltloc> SelectCountLocMap;
typedef pair<FLocation, int> SelectCountLocPair;
//typedef map<FLocation, ESelectState, ltloc> SelectLocMap;
//typedef pair<FLocation, ESelectState> SelectLocPair;

class FViewWindow: public wxPanel
{
	public:
		FViewWindow(wxWindow* pParent, wxWindowID id);
		void UpdateEvent();

		void UpdateComp();

		void ParseFile(const wxString& filename);

	public:
		enum
		{
			ID_ResearchBtn,
			ID_ApplyBtn
		};
		DECLARE_EVENT_TABLE()
		void OnClickResearch(wxCommandEvent& event);
		void OnClickApply(wxCommandEvent& event);


	private:
		FFilterPanel*		m_pFilterPanel;
		FResultPanel*		m_pResultPanel;
		FEditPanel*			m_pEditPanel;

		wxButton*			m_pExecButton;
		wxStaticText*		m_pFoundText;
		wxButton*			m_pApplyButton;

};

#endif