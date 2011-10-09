#include "FListControl.h"
#include "Config.h"
#include "Utils.h"
#include "FQuery.h"
#include "FApp.h"
#include "FEvent.h"
#include <wx\utils.h>

BEGIN_EVENT_TABLE(FListLine, wxPanel)
	EVT_LEFT_DOWN(OnLeftClick)
END_EVENT_TABLE()

wxColour FListLine::s_oColour[ESelectState_MAX] = { wxColour((unsigned long)0x00FFFFFF), wxColour((unsigned long)0x00FFA040), wxColour((unsigned long)0x00FFD0B0) };

FListLine::FListLine(wxWindow *parent, wxWindowID id, const wxString& sLabel, const wxPoint& pos, const wxSize& size)
	: wxPanel(parent, id, pos, size)
	, m_eState(EUnselect)
	, m_pLabel(NULL)
{
	wxBoxSizer* pSizer = new wxBoxSizer(wxHORIZONTAL);
	{
		m_pLabel = new wxStaticText(this, ID_Label, sLabel/*, wxDefaultPosition, wxSize(-1, 10)*/);
		pSizer->Add(m_pLabel, 1, wxALIGN_CENTER_VERTICAL | wxEXPAND | wxLEFT, 4);
		m_pLabel->Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(FListLine::OnLeftClick), NULL, this );
	}
	SetSizerAndFit(pSizer);
	Layout();

	SetBackgroundColour(s_oColour[m_eState]);
}

void FListLine::Update()
{
	SetBackgroundColour(s_oColour[m_eState]);
	Refresh();
}

void FListLine::OnLeftClick(wxMouseEvent& oEvent)
{
	switch (m_eState)
	{
		case ESelect:
			m_eState = EUnselect;
			break;

		case EUnselect:
		case EUndefined:
			m_eState = ESelect;
			break;
	}

	Update();
}






//////////////////////////////////////////////////////////////////////////

BEGIN_EVENT_TABLE(FListControl, wxScrolledWindow)
END_EVENT_TABLE()

FListControl::FListControl(wxWindow *parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
	: wxScrolledWindow(parent, id, pos, size, wxBORDER_SIMPLE)
{
	wxBoxSizer* pSizer = new wxBoxSizer(wxVERTICAL);
	{
	}
	SetScrollbars(10, 10, 50, 50);
	ShowScrollbars(wxSHOW_SB_NEVER, wxSHOW_SB_DEFAULT);
	SetSizeHints(150, 150);
	SetSizer(pSizer);
	Layout();
}


void FListControl::Clear()
{
	DestroyChildren();
}

void FListControl::Append(const wxString& sLabel)
{
	FListLine* pLine = new FListLine(this, wxID_ANY, sLabel);
	GetSizer()->Add(pLine, 1, wxEXPAND);
}


FListLine* FListControl::GetLine(int n) const
{
	int i=0;
	wxWindowList::Node* pNode = GetChildren().GetFirst();

	while (i<n && pNode != NULL)
	{
		pNode = pNode->GetNext();
		++i;
	}

	wxWindow* current = pNode->GetData();
	FListLine* pLine = wxDynamicCast(current, FListLine);

	return pLine;
}

wxString FListControl::GetString(int n) const
{
	const FListLine* pLine = GetLine(n);
	return (pLine != NULL ? pLine->GetLabel() : wxT(""));
}

ESelectState FListControl::GetLineState(const wxString& sLabel) const
{
	int n;
	const FListLine* pLine = FindString(sLabel, n);
	return (pLine != NULL ? pLine->GetSelectState() : EUnselect);
}


int FListControl::FindString(const wxString& sLabel) const
{
	int n = -1;
	FindString(sLabel, n);

	return n;
}

FListLine* FListControl::FindString(const wxString& sLabel, int& n) const
{
	const wxWindowList& oChildren = GetChildren();

	int i = 0;
	for (wxWindowList::Node* pNode = oChildren.GetFirst() ; pNode != NULL ; pNode = pNode->GetNext())
	{
		wxWindow* current = pNode->GetData();
		FListLine* pLine = wxDynamicCast(current, FListLine);

		if (pLine->GetLabel() == sLabel)
		{
			n = i;
			return pLine;
		}

		i++;
	}

	n = -1;
	return NULL;
}


void FListControl::DeselectAll()
{
	wxWindowList& oChildren = GetChildren();

	for (wxWindowList::Node* pNode = oChildren.GetFirst() ; pNode != NULL ; pNode = pNode->GetNext())
	{
		wxWindow* current = pNode->GetData();
		FListLine* pLine = wxDynamicCast(current, FListLine);
		pLine->Unselect();
	}
}


void FListControl::SetSelection(const wxString& sLabel, ESelectState eSelect)
{
	int n;
	FListLine* pLine = FindString(sLabel, n);

	if (pLine != NULL)
		pLine->SetSelecState(eSelect);
}


void FListControl::SetSelection(int n, ESelectState eSelect)
{
	assert(n != -1);

	FListLine* pLine = GetLine(n);

	if (pLine != NULL)
		pLine->SetSelecState(eSelect);
}



bool FListControl::IsSelected(int n) const
{
	const FListLine* pLine = GetLine(n);

	return pLine != NULL && pLine->IsSelected();
}

uint FListControl::GetCount() const
{
	const wxWindowList& oChildren = GetChildren();
	return oChildren.GetCount();
}

void FListControl::GetSelectList(SelectMap& aMap) const
{
	const wxWindowList& oChildren = GetChildren();
	aMap.clear();

	for (wxWindowList::Node* pNode = oChildren.GetFirst() ; pNode != NULL ; pNode = pNode->GetNext())
	{
		wxWindow* current = pNode->GetData();
		const FListLine* pLine = wxDynamicCast(current, FListLine);
		
		aMap.insert(SelectPair(string(pLine->GetLabel().mb_str(wxConvISO8859_1)), pLine->GetSelectState()));
	}
}




