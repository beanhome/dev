#include "FRoleWindow.h"
#include "FSQLClient.h"
#include "FApp.h"
#include "Config.h"
#include "Utils.h"
#include "FQuery.h"
#include "wx/wx.h" 
#include "FNewRoleDialog.h"


BEGIN_EVENT_TABLE(FRoleWindow, wxScrolledWindow)
	EVT_LISTBOX_DCLICK( ID_TopRoleListDirect,		FRoleWindow::OnSelectRoleFromTopDirect)
	EVT_LISTBOX_DCLICK( ID_TopRoleListIndirect,		FRoleWindow::OnSelectRoleFromTopIndirect)
	EVT_LISTBOX_DCLICK( ID_TopRoleListExclude,		FRoleWindow::OnSelectRoleFromTopExclude)
	EVT_BUTTON( ID_TopRoleAddBtn,					FRoleWindow::OnTopListAddBtn)
	EVT_BUTTON( ID_TopRoleDelBtn,					FRoleWindow::OnTopListDelBtn)

	EVT_LISTBOX( ID_RoleList,						FRoleWindow::OnSelectRole)
	EVT_BUTTON( ID_RoleAddBtn,						FRoleWindow::OnNewBtn)
	EVT_BUTTON( ID_RoleDelBtn,						FRoleWindow::OnDelBtn)

	EVT_LISTBOX_DCLICK( ID_BotRoleListDirect,		FRoleWindow::OnSelectRoleFromBotDirect)
	EVT_LISTBOX_DCLICK( ID_BotRoleListIndirect,		FRoleWindow::OnSelectRoleFromBotIndirect)
	EVT_LISTBOX_DCLICK( ID_BotRoleListExclude,		FRoleWindow::OnSelectRoleFromBotExclude)
	EVT_BUTTON( ID_BotRoleAddBtn,					FRoleWindow::OnBotListAddBtn)
	EVT_BUTTON( ID_BotRoleDelBtn,					FRoleWindow::OnBotListDelBtn)
END_EVENT_TABLE();

FRoleWindow::FRoleWindow(wxWindow* pParent, wxWindowID id)
	: wxScrolledWindow(pParent, id)
{
	wxBoxSizer* pSizer = new wxBoxSizer( wxHORIZONTAL );
	{
		wxBoxSizer* pTopRoleSizer = new wxBoxSizer( wxVERTICAL );
		{
			wxStaticBoxSizer* pTopRoleDirectSizer = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Direct Upper Role"));
			{
				m_pTopRoleDirect = new wxListBox(this, ID_TopRoleListDirect, wxDefaultPosition, wxSize(150, 100));
				pTopRoleDirectSizer->Add(m_pTopRoleDirect, 0, 0, 0);

				m_pTopRoleDelBtn = new wxButton(this, ID_TopRoleDelBtn, wxT("Remove"));
				pTopRoleDirectSizer->Add(m_pTopRoleDelBtn, 0, wxEXPAND | wxTOP, 5);
			}
			pTopRoleSizer->Add(pTopRoleDirectSizer);

			wxStaticBoxSizer* pTopRoleIndirectSizer = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Indirect Upper Role"));
			{
				m_pTopRoleIndirect = new wxListBox(this, ID_TopRoleListIndirect, wxDefaultPosition, wxSize(150, 100));
				pTopRoleIndirectSizer->Add(m_pTopRoleIndirect, 0, 0, 0);

				//m_pTopRoleDelBtn = new wxButton(this, ID_TopRoleDelBtn, wxT("Remove"));
				//pTopRoleIndirectSizer->Add(m_pTopRoleDelBtn, 0, wxEXPAND | wxTOP, 5);
			}
			pTopRoleSizer->Add(pTopRoleIndirectSizer);

			wxStaticBoxSizer* pTopRoleExcludeSizer = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Excude Upper Role"));
			{
				m_pTopRoleExclude = new wxListBox(this, ID_TopRoleListExclude, wxDefaultPosition, wxSize(150, 100));
				pTopRoleExcludeSizer->Add(m_pTopRoleExclude, 0, 0, 0);

				m_pTopRoleAddBtn = new wxButton(this, ID_TopRoleAddBtn, wxT("Add"));
				pTopRoleExcludeSizer->Add(m_pTopRoleAddBtn, 0, wxEXPAND | wxTOP, 5);
			}
			pTopRoleSizer->Add(pTopRoleExcludeSizer);
		}
		pSizer->Add(pTopRoleSizer, 0, wxRIGHT, 5);

		wxStaticBoxSizer* pRoleSizer = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Chosen Role"));
		{
			m_pRoleList = new wxListBox(this, ID_RoleList, wxDefaultPosition, wxSize(150, 344));
			pRoleSizer->Add(m_pRoleList, 0, 0, 0);

			m_pRoleAddBtn = new wxButton(this, ID_RoleAddBtn, wxT("New"));
			pRoleSizer->Add(m_pRoleAddBtn, 0, wxEXPAND | wxTOP, 5);

			m_pRoleDelBtn = new wxButton(this, ID_RoleDelBtn, wxT("Delete"));
			pRoleSizer->Add(m_pRoleDelBtn, 0, wxEXPAND | wxTOP, 5);
		}
		pSizer->Add(pRoleSizer, 0, wxRIGHT, 5);

		wxBoxSizer* pBotRoleSizer = new wxBoxSizer( wxVERTICAL );
		{
			wxStaticBoxSizer* pBotRoleDirectSizer = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Direct Lower Role"));
			{
				m_pBotRoleDirect = new wxListBox(this, ID_BotRoleListDirect, wxDefaultPosition, wxSize(150, 100));
				pBotRoleDirectSizer->Add(m_pBotRoleDirect, 0, 0, 0);

				m_pBotRoleDelBtn = new wxButton(this, ID_BotRoleDelBtn, wxT("Remove"));
				pBotRoleDirectSizer->Add(m_pBotRoleDelBtn, 0, wxEXPAND | wxTOP, 5);
			}
			pBotRoleSizer->Add(pBotRoleDirectSizer);

			wxStaticBoxSizer* pBotRoleIndirectSizer = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Indirect Lower Role"));
			{
				m_pBotRoleIndirect = new wxListBox(this, ID_BotRoleListIndirect, wxDefaultPosition, wxSize(150, 100));
				pBotRoleIndirectSizer->Add(m_pBotRoleIndirect, 0, 0, 0);

				//m_pBotRoleDelBtn = new wxButton(this, ID_BotRoleDelBtn, wxT("Remove"));
				//pBotRoleIndirectSizer->Add(m_pBotRoleDelBtn, 0, wxEXPAND | wxTOP, 5);
			}
			pBotRoleSizer->Add(pBotRoleIndirectSizer);

			wxStaticBoxSizer* pBotRoleExcludeSizer = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Exclude Lower Role"));
			{
				m_pBotRoleExclude = new wxListBox(this, ID_BotRoleListExclude, wxDefaultPosition, wxSize(150, 100));
				pBotRoleExcludeSizer->Add(m_pBotRoleExclude, 0, 0, 0);

				m_pBotRoleAddBtn = new wxButton(this, ID_BotRoleAddBtn, wxT("Add"));
				pBotRoleExcludeSizer->Add(m_pBotRoleAddBtn, 0, wxEXPAND | wxTOP, 5);
			}
			pBotRoleSizer->Add(pBotRoleExcludeSizer);
		}
		pSizer->Add(pBotRoleSizer, 0);

	}
	UpdateRoleList();

	SetScrollbars(10, 10, 50, 50);
	ShowScrollbars(wxSHOW_SB_DEFAULT, wxSHOW_SB_DEFAULT);
	SetSizerAndFit(pSizer);
	Layout();
}

FRoleWindow::~FRoleWindow()
{
}

void FRoleWindow::UpdateRoleList()
{
	m_pRoleList->Clear();
	PGresult* pResult;
	if (FApp::s_oSQLClient.Query(FQ_ALLROLES, &pResult))
	{
		int iTuplesCount = PQntuples(pResult);
		for (int i=0 ; i<iTuplesCount ; ++i)
		{
			wxString sRole = wxString(PQgetvalue(pResult, i, 0), wxConvISO8859_1);
			m_pRoleList->Append(sRole);
		}
	}
	FApp::s_oSQLClient.Clear(pResult);

	if (m_sCurrentRole.length() > 0)
	{
		int id = m_pRoleList->FindString(wxString(m_sCurrentRole.c_str(), wxConvISO8859_1));
		if (id != wxNOT_FOUND)
			m_pRoleList->Select(id);
		else
			m_sCurrentRole.clear();
	}
}

void FRoleWindow::UpdateTopRoleList()
{
	m_pTopRoleDirect->Clear();
	m_pTopRoleIndirect->Clear();
	m_pTopRoleExclude->Clear();

	if (m_sCurrentRole.length() > 0)
	{
		PGresult* pResult;
		string SQuery = FormatString(FQ_TOP_ROLES, m_sCurrentRole.c_str(), m_sCurrentRole.c_str(), m_sCurrentRole.c_str());
		if (FApp::s_oSQLClient.Query(SQuery, &pResult))
		{
			int iTuplesCount = PQntuples(pResult);
			for (int i=0 ; i<iTuplesCount ; ++i)
			{
				int col = wxNOT_FOUND;

				col = PQfnumber(pResult, "role");
				assert(col != wxNOT_FOUND);
				wxString sRole = wxString(PQgetvalue(pResult, i, col), wxConvISO8859_1);

				col = PQfnumber(pResult, "direct");
				assert(col != wxNOT_FOUND);
				bool bDirect = (PQgetvalue(pResult, i, col)[0] == 't');

				col = PQfnumber(pResult, "indirect");
				assert(col != wxNOT_FOUND);
				bool bIndirect = (PQgetvalue(pResult, i, col)[0] == 't');

				if (bDirect)
					m_pTopRoleDirect->Append(sRole);
				else if (bIndirect)
					m_pTopRoleIndirect->Append(sRole);
				else
					m_pTopRoleExclude->Append(sRole);
			}
		}
		FApp::s_oSQLClient.Clear(pResult);
	}
}

void FRoleWindow::UpdateBotRoleList()
{
	m_pBotRoleDirect->Clear();
	m_pBotRoleIndirect->Clear();
	m_pBotRoleExclude->Clear();

	if (m_sCurrentRole.length() > 0)
	{
		PGresult* pResult;
		string SQuery = FormatString(FQ_SUB_ROLES, m_sCurrentRole.c_str(), m_sCurrentRole.c_str(), m_sCurrentRole.c_str());
		if (FApp::s_oSQLClient.Query(SQuery, &pResult))
		{
			int iTuplesCount = PQntuples(pResult);
			for (int i=0 ; i<iTuplesCount ; ++i)
			{
				int col = wxNOT_FOUND;

				col = PQfnumber(pResult, "role");
				assert(col != wxNOT_FOUND);
				wxString sRole = wxString(PQgetvalue(pResult, i, col), wxConvISO8859_1);

				col = PQfnumber(pResult, "direct");
				assert(col != wxNOT_FOUND);
				bool bDirect = (PQgetvalue(pResult, i, col)[0] == 't');

				col = PQfnumber(pResult, "indirect");
				assert(col != wxNOT_FOUND);
				bool bIndirect = (PQgetvalue(pResult, i, col)[0] == 't');

				if (bDirect)
					m_pBotRoleDirect->Append(sRole);
				else if (bIndirect)
					m_pBotRoleIndirect->Append(sRole);
				else
					m_pBotRoleExclude->Append(sRole);
			}
		}
		FApp::s_oSQLClient.Clear(pResult);
	}
}

void FRoleWindow::DoSelectFromList(wxListBox* pList)
{
	int id = pList->GetSelection();
	assert(id != -1);

	m_sCurrentRole = string(pList->GetString(id).mb_str(wxConvISO8859_1));

	UpdateRoleList();
	UpdateTopRoleList();
	UpdateBotRoleList();
}


void FRoleWindow::OnSelectRole(wxCommandEvent& event)
{
	m_sCurrentRole = string(m_pRoleList->GetString(m_pRoleList->GetSelection()).mb_str(wxConvISO8859_1));

	UpdateTopRoleList();
	UpdateBotRoleList();
}

void FRoleWindow::OnSelectRoleFromTopDirect(wxCommandEvent& event)
{
	DoSelectFromList(m_pTopRoleDirect);
}

void FRoleWindow::OnSelectRoleFromTopIndirect(wxCommandEvent& event)
{
	DoSelectFromList(m_pTopRoleIndirect);
}

void FRoleWindow::OnSelectRoleFromTopExclude(wxCommandEvent& event)
{
	DoSelectFromList(m_pTopRoleExclude);
}

void FRoleWindow::OnSelectRoleFromBotDirect(wxCommandEvent& event)
{
	DoSelectFromList(m_pBotRoleDirect);
}

void FRoleWindow::OnSelectRoleFromBotIndirect(wxCommandEvent& event)
{
	DoSelectFromList(m_pBotRoleIndirect);
}

void FRoleWindow::OnSelectRoleFromBotExclude(wxCommandEvent& event)
{
	DoSelectFromList(m_pBotRoleExclude);
}


void FRoleWindow::OnTopListAddBtn(wxCommandEvent& event)
{
	if (m_sCurrentRole.length() == 0)
		return;

	int id = m_pTopRoleExclude->GetSelection();
	if (id != -1)
	{
		string sRole = string(m_pTopRoleExclude->GetString(id).mb_str(wxConvISO8859_1));
		FApp::s_oSQLClient.Query("GRANT \"" + m_sCurrentRole + "\" TO \"" + sRole + "\" ;");
		UpdateTopRoleList();
	}
}

void FRoleWindow::OnTopListDelBtn(wxCommandEvent& event)
{
	if (m_sCurrentRole.length() == 0)
		return;

	int id = m_pTopRoleDirect->GetSelection();
	if (id != -1)
	{
		string sRole = string(m_pTopRoleDirect->GetString(id).mb_str(wxConvISO8859_1));
		FApp::s_oSQLClient.Query("REVOKE \"" + m_sCurrentRole + "\" FROM \"" + sRole + "\" ;");
		UpdateTopRoleList();
	}
}

void FRoleWindow::OnBotListAddBtn(wxCommandEvent& event)
{
	if (m_sCurrentRole.length() == 0)
		return;

	int id = m_pBotRoleExclude->GetSelection();
	if (id != -1)
	{
		string sRole = string(m_pBotRoleExclude->GetString(id).mb_str(wxConvISO8859_1));
		FApp::s_oSQLClient.Query("GRANT \"" + sRole + "\" TO \"" + m_sCurrentRole + "\" ;");
		UpdateBotRoleList();
	}
}

void FRoleWindow::OnBotListDelBtn(wxCommandEvent& event)
{
	if (m_sCurrentRole.length() == 0)
		return;

	int id = m_pBotRoleDirect->GetSelection();
	if (id != -1)
	{
		string sRole = string(m_pBotRoleDirect->GetString(id).mb_str(wxConvISO8859_1));
		FApp::s_oSQLClient.Query("REVOKE \"" + sRole + "\" FROM \"" + m_sCurrentRole + "\" ;");
		UpdateBotRoleList();
	}
}

void FRoleWindow::OnNewBtn(wxCommandEvent& event)
{
	FNewRoleDialog oDialog(this, wxID_ANY, wxT("New Role"), wxDefaultPosition, wxDefaultSize, FNewRoleDialog::EM_NewUser);

	if (oDialog.ShowModal() == wxID_OK)
	{
		m_sCurrentRole = oDialog.GetRoleName();

		UpdateRoleList();
		UpdateTopRoleList();
		UpdateBotRoleList();
	}
}

void FRoleWindow::OnDelBtn(wxCommandEvent& event)
{
	if (wxMessageBox(wxT("Do you realy want to delete this role ?"), wxT("Confirmation"), wxYES_NO, this) ==  wxYES)
	{
		FApp::s_oSQLClient.Query("DROP ROLE \"" + m_sCurrentRole + "\"");

		UpdateRoleList();
		m_pTopRoleDirect->Clear();
		m_pTopRoleExclude->Clear();
		m_pBotRoleDirect->Clear();
		m_pBotRoleExclude->Clear();
	}
}


