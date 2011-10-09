#include "FViewWindow.h"
#include "FFilterPanel.h"
#include "FResultPanel.h"
#include "FResultEntry.h"
#include "FEditPanel.h"
#include "FSQLClient.h"
#include "FApp.h"
#include "FMainFrame.h"

BEGIN_EVENT_TABLE(FViewWindow, wxPanel)
	EVT_BUTTON(ID_ResearchBtn,	FViewWindow::OnClickResearch)
	EVT_BUTTON(ID_ApplyBtn,		FViewWindow::OnClickApply)
END_EVENT_TABLE();

FViewWindow::FViewWindow(wxWindow* pParent, wxWindowID id)
	: wxPanel(pParent, id)
	, m_pFilterPanel(NULL)
	, m_pResultPanel(NULL)
	, m_pEditPanel(NULL)
{
	wxFlexGridSizer* pSizer = new wxFlexGridSizer(3, 3, 5, 5);
	{
		pSizer->AddGrowableCol(1);
		pSizer->AddGrowableRow(1);

		// Filter Title
		wxStaticText* pFilterTitle = new wxStaticText(this, wxID_ANY, wxT("Filter"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE);
		pSizer->Add(pFilterTitle, 0, wxALIGN_CENTRE_HORIZONTAL | wxTOP, 5);

		// Result Title
		wxStaticText* pResultTitle = new wxStaticText(this, wxID_ANY, wxT("Result"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE);
		pSizer->Add(pResultTitle, 0, wxALIGN_CENTRE_HORIZONTAL | wxTOP, 5);

		// Edit Title
		wxStaticText* pEditTitle = new wxStaticText(this, wxID_ANY, wxT("Edit"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE);
		pSizer->Add(pEditTitle, 0, wxALIGN_CENTRE_HORIZONTAL | wxTOP, 5);

		// Filter Panel
		m_pFilterPanel = new FFilterPanel(this, wxID_ANY);
		pSizer->Add(m_pFilterPanel, 0, wxEXPAND);

		// Result Panel
		m_pResultPanel = new FResultPanel(this, wxID_ANY);
		pSizer->Add(m_pResultPanel, 0, wxEXPAND);

		// Edit Panel
		m_pEditPanel = new FEditPanel(this, wxID_ANY);
		pSizer->Add(m_pEditPanel, 0, wxEXPAND);

		// Filter Bar
		m_pExecButton = new wxButton(this, ID_ResearchBtn, wxT("Search"), wxDefaultPosition, wxSize(160, -1));
		pSizer->Add(m_pExecButton, 0, wxLEFT|wxRIGHT, 5);
		
		// Result Bar
		m_pFoundText = new wxStaticText(this, wxID_ANY, wxT("No Research"));//, wxDefaultPosition, wxSize(160, -1));
		pSizer->Add(m_pFoundText, 0, wxLEFT|wxRIGHT|wxTOP, 5);

		// Edit Bar
		m_pApplyButton = new wxButton(this, ID_ApplyBtn, wxT("Apply"), wxDefaultPosition, wxSize(160, -1));
		pSizer->Add(m_pApplyButton, 0, wxLEFT|wxRIGHT, 5);
	}
	SetSizer(pSizer);
	Layout();
}



void FViewWindow::UpdateEvent()
{
	m_pResultPanel->UpdateEvent();
}

void FViewWindow::UpdateComp()
{
	const SelectSet& aSelection = m_pResultPanel->GetSelection();

	vector<FEvent*> aEvent;
	for (SelectSet::const_iterator it = aSelection.begin() ; it != aSelection.end() ; ++it)
	{
		FResultEntry* pEntry = *it;
		FEvent* pEvent = pEntry->GetEvent();
		aEvent.push_back(pEvent);
	}

	m_pEditPanel->UpdateComp(aEvent);

	Layout();
}


void FViewWindow::ParseFile(const wxString& filename)
{
	m_pResultPanel->ParseFile(filename);
}

void FViewWindow::OnClickResearch(wxCommandEvent& WXUNUSED(event))
{
	string sQuery = m_pFilterPanel->GetQuery();

	PGresult* res;
	FApp::s_oSQLClient.Query(sQuery.c_str(), &res);
	{
		m_pResultPanel->ParseResult(res);
		
		string sFoundText = (FormatString("Found %d Result%s", PQntuples(res), (PQntuples(res) > 1 ? "s" : "")));
		m_pFoundText->SetLabel(wxString(sFoundText.c_str(), wxConvISO8859_1));
	}
	FApp::s_oSQLClient.Clear(res);

	m_pEditPanel->ClearSelection();
}

void FViewWindow::OnClickApply(wxCommandEvent& WXUNUSED(event))
{
	FMainFrame* pMainFrame = wxDynamicCast(wxTheApp->GetTopWindow(), FMainFrame);
	if (pMainFrame == NULL) return;

	const SelectSet& aSelection = m_pResultPanel->GetSelection();

	for (SelectSet::const_iterator it = aSelection.begin() ; it != aSelection.end() ; ++it)
	{
		FResultEntry* pEntry = *it;
		FEvent& oEvent = *pEntry->GetEvent();

		bool res = true;
		res &= pEntry->ApplyToEvent();
		/*res &= */m_pEditPanel->ApplyModif(oEvent); // TODO return bool

		if (res)
		{
			oEvent.Save();
		}
		else
		{
			wxMessageDialog oDialog(this, wxT("Wrong Info"), wxT("Error"));
			oDialog.ShowModal();
		}
	}
}
