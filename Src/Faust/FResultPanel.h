#ifndef FRESULTPANEL_H
#define FRESULTPANEL_H

#include "Config.h"
#include "Utils.h"

#include "wx/wx.h" 
#include "libpq-fe.h"

class FEvent;
class FResultEntry;

typedef set<FResultEntry*> SelectSet;

class FResultPanel : public wxPanel
{
	public:
		FResultPanel(wxWindow *parent, wxWindowID id); 

		bool ParseResult(PGresult* pResult);
		bool ParseFile(const wxString& filename);

		void UpdateEvent();

		void AddSelection(FResultEntry* id);
		void RemSelection(FResultEntry* id);

		const SelectSet& GetSelection() const { return m_aSelection; }

		enum
		{
			ID_SelectAll
		};
		DECLARE_EVENT_TABLE()
		void OnSelectAll(wxCommandEvent& event);

	private:
		wxScrolledWindow*	m_pResultPanel;
		wxBoxSizer*			m_pResultSizer;
		wxCheckBox*			m_pSelectAllCheckBox;

		SelectSet			m_aSelection;
};

#endif