#include "FLocationControl.h"
#include "Config.h"
#include "Utils.h"
#include "FQuery.h"
#include "FApp.h"

BEGIN_EVENT_TABLE(FLocationControl, wxPanel)
	EVT_CHECKBOX	( ID_Activate,				FLocationControl::OnActivate)
END_EVENT_TABLE()

const char* FLocationControl::s_sLabelName[] = { "Country ", "City ", "District ", "Street ", "Address " };


FLocationControl::FLocationControl(wxWindow *parent, wxWindowID id, const wxString& sLabel, bool bCreate)
	: wxPanel(parent, id)
	, m_pActivateCheckBox(NULL)
{
	wxStaticBoxSizer* pStaticBoSizer = new wxStaticBoxSizer(wxHORIZONTAL, this, sLabel);
	wxFlexGridSizer* pSizer = new wxFlexGridSizer(3);

	int iTextWidth = 47;
	int iComboBoxWidth = 100;
	int iButtonBoxWidth = 30;
	int iButtonBoxHeight = -1;

	if (!bCreate)
	{
		// Activate CheckBox
		wxStaticText* pActivateText = new wxStaticText(this, wxID_ANY, wxString(wxT("Activate")), wxDefaultPosition, wxSize(iTextWidth, -1));
		pSizer->Add(pActivateText, 0, wxALIGN_CENTER_VERTICAL | wxBOTTOM, 3);

		m_pActivateCheckBox = new wxCheckBox(this, ID_Activate, wxT(""), wxDefaultPosition, wxDefaultSize);
		pSizer->Add(m_pActivateCheckBox, 0, wxLEFT | wxBOTTOM, 3);
		pSizer->Add(NULL, 0, 0, 0);
	}


	for (uint i=0 ; i<ELocElem_MAX ; ++i)
	{
		m_oEntry[i].m_pName = new wxStaticText(this, wxID_ANY, wxString(s_sLabelName[i], wxConvISO8859_1), wxDefaultPosition, wxSize(iTextWidth, -1));
		pSizer->Add(m_oEntry[i].m_pName, 0, wxALIGN_CENTER_VERTICAL);
		m_oEntry[i].m_pComboBox = new wxChoice(this, ID_ChoiceList + i, wxDefaultPosition, wxSize(iComboBoxWidth, -1));
		pSizer->Add(m_oEntry[i].m_pComboBox, 0, wxLEFT, 3);
		m_oEntry[i].m_pCreateBtn = new wxButton(this, ID_CreateBtn + i, wxT("Add"), wxDefaultPosition, wxSize(iButtonBoxWidth, iButtonBoxHeight));
		m_oEntry[i].m_pCreateBtn->Show(bCreate);
		pSizer->Add(m_oEntry[i].m_pCreateBtn, 0, wxLEFT, 3);

		m_oEntry[i].m_pComboBox->Connect(ID_ChoiceList + i, wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(FLocationControl::OnEntryChange), NULL, this);
		m_oEntry[i].m_pCreateBtn->Connect(ID_CreateBtn + i, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FLocationControl::OnClickCreate), NULL, this);
	}

	pStaticBoSizer->Add(pSizer);

	SetSizeHints(bCreate ? 200 : 160, -1, bCreate ? 200 : 160, -1);
	SetSizerAndFit(pStaticBoSizer);
	Layout();

	if (m_oLocation.GetKey() == 0)
	{
		UpdateList(0);

		for (uint i=0 ; i<ELocElem_MAX ; ++i)
			m_oEntry[i].Enable(i == 0);
	}
	else
	{
		SetLocation(m_oLocation);
	}

	if (m_pActivateCheckBox != NULL)
	{
		m_pActivateCheckBox->SetValue(false);
		Activate(false);
	}
}

FLocationControl::~FLocationControl()
{

}

bool FLocationControl::IsActivated() const
{
	return (m_pActivateCheckBox == NULL || m_pActivateCheckBox->IsChecked());
}

void FLocationControl::Activate(bool bActivate)
{
	for (uint i=0 ; i<ELocElem_MAX ; ++i)
		m_oEntry[i].Enable(bActivate && (i == 0 || !m_oEntry[i].IsNull()));
}

void FLocationControl::SetLocation(const FLocation& oLocation)
{
	m_oLocation = oLocation;

	for (uint i=0 ; i<ELocElem_MAX ; ++i)
		SetEntry(i, oLocation.GetValue(i));
}



void FLocationControl::UpdateList(uint id)
{
	m_oEntry[id].m_pComboBox->Clear();

	PGresult* pResult;

	string sQuery = FormatString("SELECT DISTINCT %s FROM \"Location\" ", FLocation::s_scolName[id]);

	for (uint i=0 ; i<id+1 ; ++i)
	{
		sQuery += (i==0 ? "WHERE " : "AND ");

		if (i==id)
		{
			sQuery += FormatString("%s IS NOT NULL ", FLocation::s_scolName[i]);
		}
		else
		{
			sQuery += FormatString("%s = '%s' ", FLocation::s_scolName[i], m_oEntry[i].m_sValue.c_str());
		}
	}
	sQuery += ";";

	if (FApp::s_oSQLClient.Query(sQuery, &pResult))
	{
		m_oEntry[id].m_pComboBox->Append(wxT(""));

		int iTuplesCount = PQntuples(pResult);
		for (int i=0 ; i<iTuplesCount ; ++i)
		{
			m_oEntry[id].m_pComboBox->Append(wxString(PQgetvalue(pResult, i, 0), wxConvISO8859_1));
		}
	}
	FApp::s_oSQLClient.Clear(pResult);
}

string FLocationControl::GetJoinQuery() const
{
	if (IsActivated())
		return m_oLocation.GetJoinQuery();

	return string();
}


void FLocationControl::UpdateID()
{
	m_oLocation.UpdateID();
}


void FLocationControl::SetEntry(uint eid, const string& sValue)
{
	m_oEntry[eid].m_sValue = sValue;
	int id = m_oEntry[eid].m_pComboBox->FindString(wxString(sValue.c_str(), wxConvISO8859_1));
	if (id != wxNOT_FOUND)
		m_oEntry[eid].m_pComboBox->SetSelection(id);

	DoLocChange(eid);
}

void FLocationControl::DoLocChange(uint id)
{
	bool bEnable = (m_oEntry[id].m_sValue.length() > 0);

	m_oLocation.SetValue(id, m_oEntry[id].m_sValue);

	for (uint i=id+1 ; i<ELocElem_MAX ; ++i)
		m_oLocation.SetValue(i, ""); 

	UpdateID();

	if (id+1 < ELocElem_MAX)
		m_oEntry[id+1].Enable(bEnable);

	for (uint i=id+2 ; i<ELocElem_MAX ; ++i)
		m_oEntry[i].Enable(false);

	if (bEnable && id+1 < ELocElem_MAX)
		UpdateList(id + 1);
}

void FLocationControl::OnActivate(wxCommandEvent& event)
{
	Activate(IsActivated());
}

void FLocationControl::OnEntryChange(wxCommandEvent& event)
{
	uint id = event.GetId() - ID_ChoiceList;
	m_oEntry[id].m_sValue = string(m_oEntry[id].m_pComboBox->GetString(m_oEntry[id].m_pComboBox->GetSelection()).mb_str(wxConvISO8859_1));
	DoLocChange(id);
}


void FLocationControl::OnClickCreate(wxCommandEvent& event)
{
	uint eid = event.GetId() - ID_CreateBtn;
	
	wxTextEntryDialog oDialog(this, wxString(wxT("New ")) + wxString(s_sLabelName[eid], wxConvISO8859_1));
	if (oDialog.ShowModal() == wxID_OK)
	{
		int id = m_oEntry[eid].m_pComboBox->FindString(oDialog.GetValue());
		if (id != wxNOT_FOUND)
		{
			m_oEntry[eid].m_pComboBox->SetSelection(id);
		}
		else
		{
			string sValue(oDialog.GetValue().mb_str(wxConvISO8859_1));

			string sQuery = "INSERT INTO \"Location\" ";
			sQuery += "(";
			for (uint i=0 ; i<eid+1 ; ++i)
			{
				if (i!=0)
					sQuery += ",";
				sQuery += string(FLocation::s_scolName[i]);
			}
			sQuery += ") ";
			sQuery += "VALUES ";
			sQuery += "(";
			for (uint i=0 ; i<eid ; ++i)
			{
				if (i!=0)
					sQuery += ", ";
				sQuery += "'" + m_oEntry[i].m_sValue + "'";
			}
			sQuery += string(eid > 0 ? ", " : "") + "'" + sValue + "'";
			sQuery += ");";

			FApp::s_oSQLClient.Query(sQuery);
			UpdateList(eid);
			SetEntry(eid, sValue);
		}
	}
}


