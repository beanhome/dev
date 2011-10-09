#include "FEditPanel.h"
#include "Config.h"
#include "Utils.h"
#include "FQuery.h"
#include "FApp.h"
#include "FDatationControl.h"
#include "FLocationListControl.h"
#include "FRoleControlEdit.h"
#include "FTagControlEdit.h"
#include "FEvent.h"
#include "FNameRefControl.h"

BEGIN_EVENT_TABLE(FEditPanel, wxScrolledWindow)
END_EVENT_TABLE()


FEditPanel::FEditPanel(wxWindow *parent, wxWindowID id)
	: wxScrolledWindow(parent, id, wxDefaultPosition, wxDefaultSize, wxScrolledWindowStyle | wxBORDER_SIMPLE)
{
	//SetBackgroundColour(0x00000055);
	wxBoxSizer* pSizer = new wxBoxSizer(wxVERTICAL);

	m_pNameRef = new FNameRefControl(this, wxID_ANY, wxT("Reference : "));
	pSizer->Add(m_pNameRef, 0, wxLEFT|wxRIGHT|wxTOP, 5);

	m_pRoleControl = new FRoleControlEdit(this, wxID_ANY, wxString(wxT("Roles : ")));
	pSizer->Add(m_pRoleControl, 0, wxLEFT|wxRIGHT|wxTOP, 5);

	//m_pDatationControl = new FDatationControl(this, wxID_ANY, wxString(wxT("Datation : ")));
	//pSizer->Add(m_pDatationControl, 0, wxLEFT|wxRIGHT|wxTOP, 5);

	m_pLocationControl = new FLocationListControl(this, wxID_ANY, wxString(wxT("Location : ")), wxDefaultPosition, wxDefaultSize, true);
	pSizer->Add(m_pLocationControl, 0, wxLEFT|wxRIGHT|wxTOP, 5);

	m_pTagControl = new FTagControlEdit;
	m_pTagControl->Create(this, wxID_ANY, wxString(wxT("Tags : ")));
	pSizer->Add(m_pTagControl, 0, wxLEFT|wxRIGHT|wxTOP, 5);

	pSizer->AddSpacer(5);

	SetScrollbars(10, 10, 50, 50);
	ShowScrollbars(wxSHOW_SB_NEVER, wxSHOW_SB_DEFAULT);
	SetSizer(pSizer);
	SetSizeHints(160 + 10 + 16, wxDefaultCoord);
	Layout();
}

void FEditPanel::ClearSelection()
{
	m_pNameRef->SetValue("");
	m_pRoleControl->ClearSelection();
	m_pTagControl->ClearSelection();
	m_pLocationControl->ClearLocation();
}

void FEditPanel::UpdateComp(vector<FEvent*> aEvent)
{
	SelectCountRoleMap aRole;
	SelectCountTagMap aTag;
	SelectCountLocMap aLoc;

	int iParent = -1;

	for (uint i=0 ; i<aEvent.size() ; ++i)
	{
		FEvent& oEvent = *(aEvent[i]);

		if (iParent == -1 && oEvent.GetParent() != 0)
			iParent = oEvent.GetParent();
		else if (iParent > 0 && iParent != oEvent.GetParent())
			iParent = 0;
			
		// Role
		oEvent.PushRoleToSelection(aRole);

		// Tag
		oEvent.PushTagToSelection(aTag);

		// Loc
		oEvent.PushLocationToSelection(aLoc);
	}

	string sParent;
	if (iParent > 0)
	{
		PGresult* pResult;
		FApp::s_oSQLClient.Query(FormatString("SELECT name FROM \"Event\" WHERE id = %d;", iParent), &pResult);
		assert(PQntuples(pResult) == 1);
		sParent = PQgetvalue(pResult, 0, 0);
		FApp::s_oSQLClient.Clear(pResult);
	}
	m_pNameRef->SetValue(sParent);


	UpdateRoleSelection(aRole, aEvent.size());
	UpdateTagSelection(aTag, aEvent.size());
	UpdateLocationSelection(aLoc, aEvent.size());
}


void FEditPanel::ApplyModif(FEvent& oEvent)
{
	oEvent.SetParent(m_pNameRef->GetValue());

	m_pTagControl->ApplyModif(oEvent);
	m_pRoleControl->ApplyModif(oEvent);
}


void FEditPanel::UpdateRoleSelection(SelectCountRoleMap aRoles, int iSelectionCount)
{
	m_pRoleControl->ClearSelection();
	for (SelectCountRoleMap::iterator it = aRoles.begin() ; it != aRoles.end() ; ++it)
	{
		if (it->second == 0)
			m_pRoleControl->SetSelection(it->first, EUnselect);
		else if (it->second == iSelectionCount)
			m_pRoleControl->SetSelection(it->first, ESelect);
		else
			m_pRoleControl->SetSelection(it->first, EUndefined);
	}
}

void FEditPanel::UpdateTagSelection(SelectCountTagMap aTags, int iSelectionCount)
{
	m_pTagControl->ClearSelection();
	for (SelectCountTagMap::iterator it = aTags.begin() ; it != aTags.end() ; ++it)
	{
		if (it->second == 0)
			m_pTagControl->SetSelection(it->first, EUnselect);
		else if (it->second == iSelectionCount)
			m_pTagControl->SetSelection(it->first, ESelect);
		else
			m_pTagControl->SetSelection(it->first, EUndefined);
	}
}

void FEditPanel::UpdateLocationSelection(SelectCountLocMap aLocations, int iSelectionCount)
{
	m_pLocationControl->ClearLocation();
	for (SelectCountLocMap::iterator it = aLocations.begin() ; it != aLocations.end() ; ++it)
	{
		if (it->second == iSelectionCount)
			m_pLocationControl->AddLocation(it->first);
	}
}

