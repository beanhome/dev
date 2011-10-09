#include "FEventWindow.h"
#include "FFilterPanel.h"
#include "FResultPanel.h"
#include "FSQLClient.h"
#include "FApp.h"
#include "FLocationControl.h"
#include "Config.h"
#include "Utils.h"
#include "FDatation.h"
#include "FMainFrame.h"
#include "FLocationListControl.h"
#include "FQuery.h"
#include "FDatationControl.h"
#include "FRoleControlEdit.h"
#include "FTagControlEdit.h"
#include "FNameRefControl.h"


BEGIN_EVENT_TABLE(FEventWindow, wxPanel)
	EVT_BUTTON( ID_Save,		FEventWindow::OnSave)
	EVT_BUTTON( ID_New,			FEventWindow::OnNew)
END_EVENT_TABLE();

FEventWindow::FEventWindow(wxWindow* pParent, wxWindowID id, uint key)
	: wxPanel(pParent, id)
	, m_pEvent(FApp::s_oEventMap.Add(key))
{
	m_pSizer = new wxBoxSizer( wxHORIZONTAL );
	{
		wxBoxSizer* pLeftSizer = new wxBoxSizer( wxVERTICAL );
		{
			wxScrolledWindow* pParamPanel = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxScrolledWindowStyle | wxBORDER_SIMPLE);
			wxBoxSizer* pParamSizer = new wxBoxSizer( wxVERTICAL );
			{
#ifdef DEBUG_EVENTREF
				wxString sName = wxString(FormatString("Name   (%d) : ", m_uId).c_str(), wxConvISO8859_1);
#else
				wxString sName = wxT("Name : ");
#endif
				wxStaticBoxSizer* pNameSizer = new wxStaticBoxSizer(wxVERTICAL, pParamPanel, sName);
				{
					m_pNameControl = new wxTextCtrl(pParamPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(150, -1));
					pNameSizer->Add(m_pNameControl);
				}
				pParamSizer->Add(pNameSizer, 0, wxLEFT|wxRIGHT|wxTOP, 5);

				m_pNameRefControl = new FNameRefControl(pParamPanel, wxID_ANY, wxString(wxT("Reference : ")));
				pParamSizer->Add(m_pNameRefControl, 0, wxLEFT|wxRIGHT|wxTOP, 5);

				m_pDatationControl = new FDatationControl(pParamPanel, wxID_ANY, wxT("Datation : "), wxDefaultPosition, wxDefaultSize, true);
				pParamSizer->Add(m_pDatationControl, 0, wxLEFT|wxRIGHT|wxTOP, 5);

				m_pLocationListControl = new FLocationListControl(pParamPanel, wxID_ANY, wxString(wxT("Location :")), wxDefaultPosition, wxSize(150, -1), true);
				pParamSizer->Add(m_pLocationListControl, 0, wxLEFT|wxRIGHT|wxTOP, 5);

				m_pRoleControl = new FRoleControlEdit(pParamPanel, ID_Role, wxT("Roles : "));
				pParamSizer->Add(m_pRoleControl, 0, wxLEFT|wxRIGHT|wxTOP, 5);

				m_pTagControl = new FTagControlEdit;
				m_pTagControl->Create(pParamPanel, ID_Tag, wxT("Tags : "));
				pParamSizer->Add(m_pTagControl, 0, wxLEFT|wxRIGHT|wxTOP, 5);
			}

			pParamPanel->SetScrollbars(10, 10, 50, 50);
			pParamPanel->ShowScrollbars(wxSHOW_SB_NEVER, wxSHOW_SB_DEFAULT);
			pParamPanel->SetSizer(pParamSizer);
			pParamPanel->SetSizeHints(160 + 10 + 16, wxDefaultCoord);
			Layout();
			
			pLeftSizer->Add(pParamPanel, 1, wxEXPAND | wxLEFT|wxRIGHT|wxTOP, 5);

			m_pSaveButton = new wxButton(this, ID_Save, wxT("Save"));
			pLeftSizer->Add(m_pSaveButton, 0, wxEXPAND | wxLEFT|wxRIGHT|wxTOP, 5);

			m_pNewButton = new wxButton(this, ID_New, wxT("New"));
			pLeftSizer->Add(m_pNewButton, 0, wxEXPAND | wxLEFT|wxRIGHT|wxTOP, 5);
		}
		m_pSizer->Add(pLeftSizer, 0, wxEXPAND);

		wxBoxSizer* pRightSizer = new wxBoxSizer( wxVERTICAL );
		{
			m_pDescText = new wxStaticText(this, wxID_ANY, wxT("Description :"));
			pRightSizer->Add(m_pDescText, 0, wxLEFT|wxRIGHT|wxTOP, 5);

			m_pDescControl = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
			pRightSizer->Add(m_pDescControl, 1, wxEXPAND | wxLEFT|wxRIGHT|wxTOP, 5);
		}
		m_pSizer->Add(pRightSizer, 1, wxEXPAND);
	}

	SetSizerAndFit(m_pSizer);
	Layout();

	if (m_pEvent->GetKey() > 0)
	{
		Load();
	}

	m_pSaveButton->Enable(m_pEvent->GetKey() > 0);
}

FEventWindow::~FEventWindow()
{
	FApp::s_oEventMap.Remove(m_pEvent);
}


void FEventWindow::Load()
{
	m_pEvent->Load();

	m_pNameControl->SetLabel(wxString(m_pEvent->GetName().c_str(), wxConvISO8859_1));
	m_pDescControl->SetLabel(wxString(m_pEvent->GetDescription().c_str(), wxConvISO8859_1));
	
	m_pDatationControl->SetDatation(m_pEvent->GetDatation());

	m_pLocationListControl->ClearLocation();
	for (uint i=0 ; i<m_pEvent->GetLocation().size() ; ++i)
	{
		m_pLocationListControl->AddLocation(m_pEvent->GetLocation()[i]);
	}

	m_pRoleControl->Load(*m_pEvent);
	m_pTagControl->Load(*m_pEvent);
}

void FEventWindow::Save()
{
	m_pEvent->SetName(m_pNameControl->GetValue().mb_str(wxConvISO8859_1));
	m_pEvent->SetDescription(m_pDescControl->GetValue().mb_str(wxConvISO8859_1));

	if (m_pNameRefControl->IsValid())
		m_pEvent->SetParent(m_pNameRefControl->GetValue());
	
	bool bStartIsNull = !m_pDatationControl->IsStartActivated();
	bool bEndIsNull = !m_pDatationControl->IsEndActivated();
	m_pEvent->SetDatation(FDatation(bStartIsNull ? FDate() : m_pDatationControl->GetStartDate(), bEndIsNull ? FDate() : m_pDatationControl->GetEndDate()));

	m_pLocationListControl->CopyLocation(m_pEvent->GetLocation());

	m_pRoleControl->Save(*m_pEvent);
	m_pTagControl->Save(*m_pEvent);

	m_pEvent->Save();
}

void FEventWindow::OnSave(wxCommandEvent& event)
{
	Save();
	m_pSaveButton->Enable(m_pEvent->GetKey() > 0);
}

void FEventWindow::OnNew(wxCommandEvent& event)
{
	Save();
	m_pSaveButton->Enable(m_pEvent->GetKey() > 0);
}


