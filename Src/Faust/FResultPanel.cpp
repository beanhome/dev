#include "FResultPanel.h"
#include "libpq-fe.h"
#include <assert.h>
#include "FResultEntry.h"
//#include "libpqtypes.h"
#include "Config.h"
#include "Utils.h"
#include "FDatation.h"
#include "FSQLClient.h"
#include "FQuery.h"
#include "FApp.h"
#include "FMainFrame.h"
#include "FViewWindow.h"
#include "FFileParser.h"


BEGIN_EVENT_TABLE(FResultPanel, wxPanel)
EVT_CHECKBOX(ID_SelectAll, FResultPanel::OnSelectAll)
END_EVENT_TABLE();


FResultPanel::FResultPanel(wxWindow *parent, wxWindowID id)
	: wxPanel(parent, id, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE)
{
	//SetBackgroundColour(wxColour(0x000000FF));

	wxSizer* pSizer = new wxBoxSizer(wxVERTICAL);
	{
		// Result SubTitle
		wxBoxSizer* pTitleCenterSizer = new wxBoxSizer(wxHORIZONTAL);
		{
			int iBorder = 5;
			pTitleCenterSizer->AddSpacer(iBorder + 1);

			m_pSelectAllCheckBox = new wxCheckBox(this, ID_SelectAll, wxT(""));
			pTitleCenterSizer->Add(m_pSelectAllCheckBox, 0, wxALIGN_CENTER_VERTICAL |wxRIGHT, 5);

			pTitleCenterSizer->Add(new wxStaticText(this, wxID_ANY, wxT("Start"), wxDefaultPosition, wxSize(70,-1), wxALIGN_CENTRE), 0, wxALIGN_CENTRE_HORIZONTAL);
			pTitleCenterSizer->Add(new wxStaticText(this, wxID_ANY, wxT("End"), wxDefaultPosition, wxSize(70,-1), wxALIGN_CENTRE), 0, wxALIGN_CENTRE_HORIZONTAL);
			pTitleCenterSizer->Add(new wxStaticText(this, wxID_ANY, wxT("Title"), wxDefaultPosition, wxSize(100,-1), wxALIGN_CENTRE), 0, wxALIGN_CENTRE_HORIZONTAL);
			pTitleCenterSizer->Add(new wxStaticText(this, wxID_ANY, wxT("Desc"), wxDefaultPosition, wxSize(200,-1), wxALIGN_CENTRE), 1, wxALIGN_CENTRE_HORIZONTAL | wxEXPAND);
		}
		pSizer->Add(pTitleCenterSizer, 0, wxTOP|wxBOTTOM, 5);

		m_pResultPanel = new wxScrolledWindow(this, wxID_ANY);
		m_pResultSizer = new wxBoxSizer(wxVERTICAL);
		m_pResultPanel->SetScrollbars(10, 10, 50, 50);
		m_pResultPanel->SetSizer(m_pResultSizer);
		pSizer->Add(m_pResultPanel, 1, wxEXPAND);

	}
	SetSizer(pSizer);
	SetSizeHints(400, 150);
	Layout();
}

bool FResultPanel::ParseResult(PGresult* pResult)
{
	Freeze();

	m_pResultSizer->Clear(true);

	int iTuplesCount = PQntuples(pResult);

	for (int i=0 ; i<iTuplesCount ; ++i)
	{
		FEvent* pEvent = FApp::s_oEventMap.Add(pResult, i, false);

		FResultEntry* pEntry = new FResultEntry(m_pResultPanel, pEvent);
		m_pResultSizer->Add(pEntry, 0, wxEXPAND, 0);
		m_pResultSizer->AddSpacer(2);
	}

	m_pResultSizer->Fit(m_pResultPanel);

	m_pResultPanel->Layout();
	Layout();	
	GetParent()->Layout();

	Thaw();
	
	return true;
}

bool FResultPanel::ParseFile(const wxString& filename)
{
	Freeze();

	FFileParser oParser(filename);
	string sName;

	oParser.ParseParam();

	while (oParser.IsEOF())
	{
		oParser.ParseName(sName);

		FEvent* pEvent = NULL;

		PGresult* pResult;
		FApp::s_oSQLClient.Query(FormatString("SELECT id,name,description,start,finish,parent FROM \"Event\" WHERE name = '%s'; ", sName.c_str()), &pResult);
		if (PQntuples(pResult) == 1)
		{
			pEvent = FApp::s_oEventMap.Add(pResult, 0, false);
		}
		else
		{
			pEvent = FApp::s_oEventMap.Add();
			pEvent->SetName(sName.c_str());
		}

		oParser.ParseEvent(*pEvent);

		FResultEntry* pEntry = new FResultEntry(m_pResultPanel, pEvent);
		m_pResultSizer->Add(pEntry, 0, wxEXPAND, 0);
		m_pResultSizer->AddSpacer(2);
	}

	m_pResultSizer->Fit(m_pResultPanel);

	m_pResultPanel->Layout();
	Layout();	
	GetParent()->Layout();

	Thaw();

	return true;
}


void FResultPanel::UpdateEvent()
{
	wxWindowList & children = m_pResultPanel->GetChildren();
	for ( wxWindowList::Node *node = children.GetFirst(); node; node = node->GetNext() )
	{
		FResultEntry* pCurResultEntry = (FResultEntry*)node->GetData();
		pCurResultEntry->UpdateEvent();
	}
}


void FResultPanel::AddSelection(FResultEntry* entry)
{
	m_aSelection.insert(entry);

	FViewWindow* pViewWindow = wxDynamicCast(GetParent(), FViewWindow);
	assert(pViewWindow != NULL);
	pViewWindow->UpdateComp();
}

void FResultPanel::RemSelection(FResultEntry* entry)
{
	m_aSelection.erase(entry);

	FViewWindow* pViewWindow = wxDynamicCast(GetParent(), FViewWindow);
	assert(pViewWindow != NULL);
	pViewWindow->UpdateComp();
}

void FResultPanel::OnSelectAll(wxCommandEvent& event)
{
	bool bSelect = m_pSelectAllCheckBox->IsChecked();

	m_aSelection.clear();

	wxWindowList & children = m_pResultPanel->GetChildren();
	for ( wxWindowList::Node *node = children.GetFirst(); node; node = node->GetNext() )
	{
		FResultEntry* pCurResultEntry = (FResultEntry*)node->GetData();
		pCurResultEntry->DoSelect(bSelect);

		if (bSelect)
			m_aSelection.insert(pCurResultEntry);
	}

	FViewWindow* pViewWindow = wxDynamicCast(GetParent(), FViewWindow);
	assert(pViewWindow != NULL);
	pViewWindow->UpdateComp();
}


