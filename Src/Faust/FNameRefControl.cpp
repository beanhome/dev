#include "FNameRefControl.h"
#include "Config.h"
#include "Utils.h"
#include "FQuery.h"
#include "FApp.h"
#include "FEvent.h"

BEGIN_EVENT_TABLE(FNameRefControl, wxPanel)
	EVT_COMBOBOX(ID_NameRef, OnChangeName)
	EVT_TEXT_ENTER(ID_NameRef, OnSetNameFilter)
END_EVENT_TABLE()


FNameRefControl::FNameRefControl(wxWindow *parent, wxWindowID id, const wxString& sLabel)
	: wxPanel(parent, id)
	, m_pNameRef(NULL)
{
	wxStaticBoxSizer* pSizer = new wxStaticBoxSizer(wxVERTICAL, this, sLabel);
	{
		m_pNameRef = new wxComboBox(this, ID_NameRef, wxEmptyString, wxDefaultPosition, wxSize(150, -1), 0, NULL, wxTE_PROCESS_ENTER);
		pSizer->Add(m_pNameRef, 0, 0, 0);
	}

	SetSizeHints(160, -1, 160, -1);
	SetSizerAndFit(pSizer);
	Layout();
}

string FNameRefControl::GetValue()
{
	return string(m_pNameRef->GetValue().mb_str(wxConvISO8859_1));
}

bool FNameRefControl::IsValid() const
{
	return (m_pNameRef->GetCount() > 0);
}


void FNameRefControl::SetValue(const string& sValue)
{
	m_pNameRef->SetValue(wxString(sValue.c_str(), wxConvISO8859_1));
}



void FNameRefControl::OnSetNameFilter(wxCommandEvent& oEvent)
{
	PGresult* pResult;
	string sName = string(m_pNameRef->GetValue().mb_str(wxConvISO8859_1));
	string sQuery = FormatString("SELECT name FROM \"Event\" WHERE name LIKE '%s'", sName.c_str());
	m_pNameRef->Clear();
	if (FApp::s_oSQLClient.Query(sQuery, &pResult))
	{
		int iTuplesCount = PQntuples(pResult);
		for (int i=0 ; i<iTuplesCount ; ++i)
		{
			wxString sName = wxString(PQgetvalue(pResult, i, 0), wxConvISO8859_1);
			m_pNameRef->Append(sName);
		}
	}
	FApp::s_oSQLClient.Clear(pResult);

	if (m_pNameRef->GetCount() > 0)
		m_pNameRef->SetValue(m_pNameRef->GetString(0));
	else
		m_pNameRef->SetValue(wxString(sName.c_str(), wxConvISO8859_1));

	GetParent()->Refresh();
}

void FNameRefControl::OnChangeName(wxCommandEvent& oEvent)
{

}
