#include "FLocationListControl.h"
#include "Utils.h"
#include "FQuery.h"
#include "FApp.h"
#include "FLocationDialog.h"

//////////////////////////////////////////////////////////////////////////

BEGIN_EVENT_TABLE(FLocationLine, wxPanel)
	EVT_BUTTON(ID_EditBtn, OnEditButton)
	EVT_BUTTON(ID_DelBtn, OnDelButton)
END_EVENT_TABLE()

IMPLEMENT_DYNAMIC_CLASS(FLocationLine, wxWindow)


FLocationLine::FLocationLine()
	: wxPanel()
	, m_pSizer(NULL)
	, m_pText(NULL)
	, m_pEditBtn(NULL)
	, m_pDelBtn(NULL)
{

}

FLocationLine::FLocationLine(wxWindow *parent, wxWindowID id, const FLocation& oLoc, bool bEdit)
	: wxPanel(parent, id)
	, m_pSizer(NULL)
	, m_pText(NULL)
	, m_pEditBtn(NULL)
	, m_pDelBtn(NULL)
	, m_oLocation(oLoc)
{
	wxBoxSizer* pSizer = new wxBoxSizer(wxHORIZONTAL);

	m_pText = new wxTextCtrl(this, wxID_ANY, wxString(m_oLocation.GetFormated().c_str(), wxConvISO8859_1), wxDefaultPosition, wxSize(90, -1), wxTE_READONLY);
	pSizer->Add(m_pText);

	if (bEdit)
	{
		m_pEditBtn = new wxButton(this, ID_EditBtn, wxT("Edit"), wxDefaultPosition, wxSize(25, -1));
		pSizer->Add(m_pEditBtn, 0, wxLEFT, 5);

		m_pDelBtn = new wxButton(this, ID_DelBtn, wxT("Del"), wxDefaultPosition, wxSize(25, -1));
		pSizer->Add(m_pDelBtn, 0, wxLEFT, 5);
	}

	SetSizeHints(150, -1, 150, -1);
	SetSizerAndFit(pSizer);
	Layout();
}

void FLocationLine::OnEditButton(wxCommandEvent& event)
{
	FLocationDialog oDialog(this, wxID_ANY);
	oDialog.SetLocation(m_oLocation);

	if (oDialog.ShowModal() == wxID_OK)
	{
		m_oLocation = oDialog.GetLocation();
		m_pText->SetLabel(wxString(m_oLocation.GetFormated().c_str(), wxConvISO8859_1));
	}
}

void FLocationLine::OnDelButton(wxCommandEvent& event)
{
	wxWindow* pLocPanel = GetParent();
	wxWindow* pPanel = pLocPanel->GetParent();
	Destroy();

	pPanel->GetParent()->Layout();
}



//////////////////////////////////////////////////////////////////////////

BEGIN_EVENT_TABLE(FLocationListControl, wxWindow)
	EVT_BUTTON(ID_AddBtn, OnAddButton)
END_EVENT_TABLE()

FLocationListControl::FLocationListControl(wxWindow *parent, wxWindowID id, wxString& sLabel, const wxPoint& pos, const wxSize& size, bool bEdit)
	: wxPanel(parent, id, pos, size)
	, m_bEdit(bEdit)
	, m_pAddBtn(NULL)
{
	wxStaticBoxSizer* pStaticBoxSizer = new wxStaticBoxSizer(wxVERTICAL, this, sLabel);
	{
		m_pLocationPanel = new wxWindow(this, wxID_ANY);
		wxBoxSizer* pSizer = new wxBoxSizer(wxVERTICAL);
		m_pLocationPanel->SetSizer(pSizer);
		pStaticBoxSizer->Add(m_pLocationPanel);

		m_pAddBtn = new wxButton(this, ID_AddBtn, wxT("Add Location"), wxDefaultPosition, wxSize(150, -1));
		pStaticBoxSizer->Add(m_pAddBtn, 0, 0, 0);
	}
	//SetSizerAndFit(pStaticBoxSizer);
	SetSizer(pStaticBoxSizer);
	GetSizer()->Fit(this);

	Layout();
}

void FLocationListControl::ClearLocation()
{
	m_pLocationPanel->DestroyChildren();
}


void FLocationListControl::AddLocation(const FLocation& oLoc)
{
	FLocationLine* pLine = new FLocationLine(m_pLocationPanel, wxID_ANY, oLoc, m_bEdit);
	m_pLocationPanel->GetSizer()->Add(pLine, 1, wxEXPAND | wxBOTTOM, 3);
	//Layout();
	//GetParent()->Fit();
	GetParent()->Layout();
	GetParent()->Refresh();
}




void FLocationListControl::CopyLocation(vector<FLocation>& aLoc)
{
	wxWindowList& oChildren = m_pLocationPanel->GetChildren();

	aLoc.clear();
	for (wxWindowList::Node* pNode = oChildren.GetFirst() ; pNode != NULL ; pNode = pNode->GetNext())
	{
		wxWindow* current = pNode->GetData();
		FLocationLine* pLine = wxDynamicCast(current, FLocationLine);
		if (pLine != NULL)
			aLoc.push_back(pLine->GetLocation());
	}
}


void FLocationListControl::OnAddButton(wxCommandEvent& event)
{
	FLocationDialog oDialog(this, wxID_ANY);

	if (oDialog.ShowModal() == wxID_OK)
	{
		AddLocation(oDialog.GetLocation());
	}
}




