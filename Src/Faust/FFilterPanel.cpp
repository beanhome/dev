#include "FFilterPanel.h"
#include "Config.h"
#include "Utils.h"
#include "FQuery.h"
#include "FApp.h"
#include "wx/datetime.h"
#include "FCalendarDialog.h"
#include "FDatationControl.h"
#include "FLocationControl.h"
#include "FRoleControlView.h"
#include "FTagControl.h"
#include "FNameRefControl.h"

BEGIN_EVENT_TABLE(FFilterPanel, wxScrolledWindow)
END_EVENT_TABLE()


FFilterPanel::FFilterPanel(wxWindow *parent, wxWindowID id)
	: wxScrolledWindow(parent, id, wxDefaultPosition, wxDefaultSize, wxScrolledWindowStyle | wxBORDER_SIMPLE)
{
	//SetBackgroundColour(wxColour(0x0000FF00));

	wxBoxSizer* pSizer = new wxBoxSizer(wxVERTICAL);

	m_pRoleControl = new FRoleControlView(this, wxID_ANY, wxString(wxT("Roles : ")));
	pSizer->Add(m_pRoleControl, 0, wxLEFT|wxRIGHT|wxTOP, 5);

	wxStaticBoxSizer* pNameSizer = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Name : "));
	{
		m_pNameRegExp = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(150, -1));
		pNameSizer->Add(m_pNameRegExp);
	}
	pSizer->Add(pNameSizer, 0, wxLEFT|wxRIGHT|wxTOP, 5);

	m_pNameRefControl = new FNameRefControl(this, wxID_ANY, wxString(wxT("Reference : ")));
	pSizer->Add(m_pNameRefControl, 0, wxLEFT|wxRIGHT|wxTOP, 5);

	m_pDatationControl = new FDatationControl(this, wxID_ANY, wxString(wxT("Datation : ")));
	pSizer->Add(m_pDatationControl, 0, wxLEFT|wxRIGHT|wxTOP, 5);

	m_pLocationControl = new FLocationControl(this, wxID_ANY, wxString(wxT("Location : ")));
	pSizer->Add(m_pLocationControl, 0, wxLEFT|wxRIGHT|wxTOP, 5);

	m_pTagControl = new FTagControl(this, wxID_ANY, wxString(wxT("Tags : ")));
	pSizer->Add(m_pTagControl, 0, wxLEFT|wxRIGHT|wxTOP, 5);

	m_pLastEventControl = new FDatationControl(this, wxID_ANY, wxT("Last update : "), wxDefaultPosition, wxDefaultSize, true);
	pSizer->Add(m_pLastEventControl, 0, wxLEFT|wxRIGHT|wxTOP, 5);

	pSizer->AddSpacer(5);
	SetScrollbars(10, 10, 50, 50);
	ShowScrollbars(wxSHOW_SB_NEVER, wxSHOW_SB_DEFAULT);
	SetSizer(pSizer);
	SetSizeHints(160 + 10 + 16, wxDefaultCoord);
	Layout();
}



string FFilterPanel::GetQuery() const
{
	std::vector<string> aConditions;
	string sQuery = FQ_EVENT_BEGIN;

	sQuery += m_pLocationControl->GetJoinQuery();
	sQuery += m_pRoleControl->GetJoinQuery();
	sQuery += m_pTagControl->GetJoinQuery();

	string sParent = m_pNameRefControl->GetValue();
	if (sParent.length() > 0)
	{
		aConditions.push_back(FormatString(FQ_EVENT_COND_PARENT, sParent.c_str(), sParent.c_str()));
	}

	string sNameRegExt = string(m_pNameRegExp->GetValue().mb_str(wxConvISO8859_1));
	if (sNameRegExt.length() > 0)
	{
		aConditions.push_back(FormatString(FQ_EVENT_COND_NAMEREGEXP, sNameRegExt.c_str()));
	}

	if (m_pDatationControl->IsActivated())
	{
		if (! m_pDatationControl->IsStartActivated() && ! m_pDatationControl->IsEndActivated())
		{
			aConditions.push_back(FQ_EVENT_COND_DATE_NULL);
		}
		else
		{
			if (m_pDatationControl->IsStartActivated())
				aConditions.push_back(FormatString(FQ_EVENT_COND_DATE_START, m_pDatationControl->GetStartDate().GetFormated()));

			if (m_pDatationControl->IsEndActivated())
				aConditions.push_back(FormatString(FQ_EVENT_COND_DATE_END, m_pDatationControl->GetEndDate().GetFormated()));
		}
	}

	if (m_pLastEventControl->IsActivated())
	{
		if (m_pLastEventControl->IsStartActivated())
			aConditions.push_back(FormatString(FQ_EVENT_COND_LAST_START, m_pLastEventControl->GetStartDate().GetFormated()));

		if (m_pLastEventControl->IsEndActivated())
			aConditions.push_back(FormatString(FQ_EVENT_COND_LAST_END, m_pLastEventControl->GetEndDate().GetFormated()));
	}

	for (uint i=0 ; i<aConditions.size() ; ++i)
	{
		sQuery += (i==0 ? "WHERE " : "AND ");
		sQuery += aConditions[i] + " ";
	}

	sQuery += FQ_EVENT_END;

	return sQuery;
}
