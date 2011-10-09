#include "FResultEntry.h"
#include "libpq-fe.h"
#include "Config.h"
#include "Utils.h"
#include "FMainFrame.h"
#include "FApp.h"
#include "FResultPanel.h"

BEGIN_EVENT_TABLE(FResultEntry, wxPanel)
	EVT_CHECKBOX(ID_Select, OnSelect)
	//EVT_ENTER_WINDOW(OnEnterWindow)
	//EVT_LEAVE_WINDOW(OnLeaveWindow)
	EVT_LEFT_DOWN(OnLeftClick)
	EVT_RIGHT_UP(OnRightClick)
	EVT_LEFT_DCLICK(OnLeftDClick)
	EVT_MENU(ID_Edit, OnEdit)
	EVT_MENU(ID_Delete, OnDelete)
END_EVENT_TABLE()


FResultEntry::FResultEntry(wxWindow *parent, FEvent* pEvent)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE)
	, m_pEvent(pEvent)
	, m_pDebugText(NULL)
	, m_pNameText(NULL)
	, m_pStartDateText(NULL)
	, m_pEndDateText(NULL)
	, m_pDescText(NULL)
	, m_bSelected(false)
{
	//FApp::s_oEventMap.Add(pEvent);

	m_oBGColor = GetBackgroundColour();
	m_oBGColorSelected = 0x00FFA040;

	int iBorder = 5;

	wxBoxSizer* pVertSizer = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* pSizer = new wxBoxSizer(wxHORIZONTAL);

	pSizer->AddSpacer(iBorder);

	m_pSelectCheckBox = new wxCheckBox(this, ID_Select, wxT(""));
	pSizer->Add(m_pSelectCheckBox, 0, wxALIGN_CENTER_VERTICAL |wxRIGHT, 5);
	
#ifdef DEBUG_EVENTREF
	m_pDebugText = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(30, -1));
	pSizer->Add(m_pDebugText, 0, wxALIGN_CENTER_VERTICAL, 0);
#endif

	m_pStartDateText = new wxTextCtrl(this, wxID_ANY, wxT("Start"), wxDefaultPosition, wxSize(70,-1));
	pSizer->Add(m_pStartDateText, 0, wxALIGN_CENTER_VERTICAL, 0);

	m_pEndDateText = new wxTextCtrl(this, wxID_ANY, wxT("End"), wxDefaultPosition, wxSize(70,-1));
	pSizer->Add(m_pEndDateText, 0, wxALIGN_CENTER_VERTICAL, 0);

	m_pNameText = new wxTextCtrl(this, wxID_ANY, wxT("Name"), wxDefaultPosition, wxDefaultSize);
	pSizer->Add(m_pNameText, 0, wxALIGN_CENTER_VERTICAL, 0);

	m_pDescText = new wxTextCtrl(this, wxID_ANY, wxT("Desc"), wxDefaultPosition, wxDefaultSize/*, wxTE_MULTILINE*/);
	pSizer->Add(m_pDescText, 1, wxALIGN_CENTER_VERTICAL | wxEXPAND, 0);

	pSizer->AddSpacer(iBorder);

	pVertSizer->AddSpacer(iBorder);
	pVertSizer->Add(pSizer, 1, wxEXPAND);
	pVertSizer->AddSpacer(iBorder);

	SetSizerAndFit(pVertSizer);
	Layout();

	//Connect(wxEVT_ENTER_WINDOW, wxMouseEventHandler(FResultEntry::OnEnterWindow));  
	//Connect(wxEVT_LEAVE_WINDOW, wxMouseEventHandler(FResultEntry::OnLeaveWindow));  


	UpdateEvent();
}

FResultEntry::~FResultEntry()
{
	FApp::s_oEventMap.Remove(m_pEvent);
}


void FResultEntry::UpdateEvent()
{
	//if (m_pDebugText != NULL)		m_pDebugText->SetValue(wxString(FormatString("%d %d", m_pEvent->GetKey(), m_pEvent->GetRef()).c_str(), wxConvISO8859_1));
	if (m_pNameText != NULL)		m_pNameText->SetValue(wxString(m_pEvent->GetName().c_str(), wxConvISO8859_1));
	if (m_pStartDateText != NULL)	m_pStartDateText->SetValue(wxString(m_pEvent->GetDatation().GetStart().GetFormated(), wxConvISO8859_1));
	if (m_pEndDateText != NULL)		m_pEndDateText->SetValue(wxString(m_pEvent->GetDatation().GetEnd().GetFormated(), wxConvISO8859_1));
	if (m_pDescText != NULL)		m_pDescText->SetValue(wxString(m_pEvent->GetDescription().c_str(), wxConvISO8859_1));
}

bool FResultEntry::ApplyToEvent()
{
	if (m_pNameText != NULL)		m_pEvent->SetName(m_pNameText->GetValue().mb_str(wxConvISO8859_1));
	if (m_pDescText != NULL)		m_pEvent->SetDescription(m_pDescText->GetValue().mb_str(wxConvISO8859_1));

	bool res = true;
	if (m_pStartDateText != NULL)	res &= m_pEvent->GetDatation().GetStart().Parse(m_pStartDateText->GetValue().mb_str(wxConvISO8859_1));
	if (m_pEndDateText != NULL)		res &= m_pEvent->GetDatation().GetEnd().Parse(m_pEndDateText->GetValue().mb_str(wxConvISO8859_1));

	return res;
}



void FResultEntry::Edit()
{
	if (m_pEvent->GetKey() > 0)
	{
		FMainFrame* pMainFrame = wxDynamicCast(wxTheApp->GetTopWindow(), FMainFrame);
		pMainFrame->NewEventPage(m_pEvent->GetKey());
	}
}

void FResultEntry::Delete()
{
	wxWindow* pParent = GetParent();

	if (m_pEvent->GetKey() > 0)
	{
		bool res = true;
		FApp::s_oSQLClient.Query("BEGIN");

		res &= FApp::s_oSQLClient.Query(FormatString("DELETE FROM \"Event_Location\" WHERE event_id = %d;", m_pEvent->GetKey()));
		res &= FApp::s_oSQLClient.Query(FormatString("DELETE FROM \"Event_Role\" WHERE event_id = %d;", m_pEvent->GetKey()));
		res &= FApp::s_oSQLClient.Query(FormatString("DELETE FROM \"Event_Tags\" WHERE event_id = %d;", m_pEvent->GetKey()));
		res &= FApp::s_oSQLClient.Query(FormatString("DELETE FROM \"Event\" WHERE id = %d;", m_pEvent->GetKey()));
		
		FApp::s_oSQLClient.Query(res ? "COMMIT" : "ROLLBACK");
	}

	Destroy();

	pParent->Layout();
	//pParent->GetSizer()->Fit(pParent);
	pParent->GetParent()->Layout();

}

void FResultEntry::Select(bool bSelect)
{
	DoSelect(bSelect);

	FResultPanel* pResultPanel = wxDynamicCast(GetGrandParent(), FResultPanel);

	if (m_bSelected)
		pResultPanel->AddSelection(this);
	else
		pResultPanel->RemSelection(this);
}

void FResultEntry::DoSelect(bool bSelect)
{
	m_bSelected = bSelect;

	m_pSelectCheckBox->SetValue(m_bSelected);

	SetBackgroundColour(m_bSelected ? m_oBGColorSelected : m_oBGColor);
	Refresh();

	if (m_pEvent->GetKey() > 0 && m_bSelected)
	{
		if (m_pEvent->IsIncomplete())
			m_pEvent->Load();
		UpdateEvent();
	}
}


void FResultEntry::OnEnterWindow(wxMouseEvent& event)
{
	Log("Enter Window %d\n", GetRect().Contains(event.GetPosition()));
	Log("Mouse : %d %d \n", event.GetX(), event.GetY());
	Log("Window : %d %d -> %d %d\n", GetRect().GetX(), GetRect().GetY(), GetRect().GetRight(), GetRect().GetBottom());
}

void FResultEntry::OnLeaveWindow(wxMouseEvent& event)
{
	Log("Leave Window %d\n", GetRect().Contains(event.GetPosition()));
	Log("Mouse : %d %d \n", event.GetX(), event.GetY());
	Log("Window : %d %d -> %d %d\n", GetRect().GetX(), GetRect().GetY(), GetRect().GetRight(), GetRect().GetBottom());
}

void FResultEntry::OnRightClick(wxMouseEvent& event)
{
	if (FApp::s_oSQLClient.IsWriter())
	{
		wxMenu* pMenu = new wxMenu;

		pMenu->Append(ID_Edit, wxT("Edit"));
		pMenu->Append(ID_Delete, wxT("Delete"));

		PopupMenu(pMenu, event.GetPosition());
	}
}

void FResultEntry::OnLeftClick(wxMouseEvent& event)
{
	Select(!m_bSelected);
}

void FResultEntry::OnLeftDClick(wxMouseEvent& event)
{
	Edit();
}

void FResultEntry::OnEdit(wxCommandEvent& event)
{
	Edit();
}

void FResultEntry::OnDelete(wxCommandEvent& event)
{
	Delete();
}

void FResultEntry::OnSelect(wxCommandEvent& event)
{
	Select(m_pSelectCheckBox->IsChecked());
}
