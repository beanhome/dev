#include "FMainFrame.h"
#include "FFilterPanel.h"
#include "FResultPanel.h"
#include "FSQLClient.h"
#include "FApp.h"
#include "FViewWindow.h"
#include "wx/notebook.h"
#include "FEventWindow.h"
#include "FNewRoleDialog.h"
#include "FRoleWindow.h"
//#include "../../Project_2008/Faust/vcproj/resource.h"

BEGIN_EVENT_TABLE(FMainFrame, wxFrame)
	EVT_MENU(ID_AddView,			FMainFrame::OnMenuCreateView)
	EVT_MENU(ID_AddEvent,			FMainFrame::OnMenuCreateEvent)
	EVT_MENU(ID_AddUser,			FMainFrame::OnMenuCreateUser)
	EVT_MENU(ID_EditUser,			FMainFrame::OnMenuEditUser)
	EVT_MENU(ID_EditRole,			FMainFrame::OnMenuEditRole)
	EVT_MENU(ID_AddPlayer,			FMainFrame::OnMenuCreatePlayer)
	EVT_MENU(ID_AddPerso,			FMainFrame::OnMenuCreatePerso)
	EVT_MENU(ID_ParseFile,			FMainFrame::OnMenuParseFile)
	EVT_MENU(ID_Logout,				FMainFrame::OnMenuLogout)
	EVT_MENU(ID_CloseTab,			FMainFrame::OnMenuCloseTab)
	EVT_MENU(ID_Exit,				FMainFrame::OnQuit)
	EVT_NOTEBOOK_PAGE_CHANGED(ID_NoteBook,  FMainFrame::OnNoteBookChange)
	EVT_MENU(ID_NoteBook_CloseTab, FMainFrame::OnNoteBookCloseTab)
END_EVENT_TABLE();

IMPLEMENT_CLASS(FMainFrame, wxFrame);

FMainFrame::FMainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxFrame((wxFrame *)NULL, -1, title, pos, size)
	, m_pMenuBar(NULL)
	, m_pMainMenu(NULL)
	, m_pNoteBook(NULL)
{
	SetIcon(wxIcon(IMG_PATH(View, png), wxBITMAP_TYPE_PNG));

	// Menu
	m_pMenuBar = new wxMenuBar();
	m_pMainMenu = new wxMenu();
	m_pMainMenu->Append(ID_AddView, wxT("Add View"));
	if (FApp::s_oSQLClient.IsWriter())
	{
		m_pMainMenu->Append(ID_AddEvent, wxT("Add Event"));
		m_pMainMenu->Append(ID_AddUser, wxT("Add User"));
		m_pMainMenu->Append(ID_EditUser, wxT("Edit User"));
		m_pMainMenu->Append(ID_EditRole, wxT("Edit Role"));
		m_pMainMenu->Append(ID_ParseFile, wxT("Parse File"));
		//m_pMainMenu->Append(ID_MainMenu_AddPlayer, wxT("Add Player"));
		//m_pMainMenu->Append(ID_MainMenu_AddPerso, wxT("Add Perso"));
	}
	m_pMainMenu->Append(ID_Logout, wxT("Logout"));
	m_pMainMenu->Append(ID_Exit, wxT("Quit"));
	m_pMenuBar->Append(m_pMainMenu, wxT("Main"));
	SetMenuBar(m_pMenuBar);

	m_pToolBar = new wxToolBar(this, wxID_ANY);
	//m_pToolBar->AddTool(ID_AddView, wxT("View"), wxBitmap(IMG_PATH(View, png), wxBITMAP_TYPE_PNG), wxT("New View Page"));
	//m_pToolBar->AddTool(ID_AddEvent, wxT("New"), wxBitmap(IMG_PATH(Add, png), wxBITMAP_TYPE_PNG), wxT("New Event"));
	//m_pToolBar->AddTool(ID_ParseFile, wxT("File"), wxBitmap(IMG_PATH(Parse, png), wxBITMAP_TYPE_PNG), wxT("Parse File"));
	//m_pToolBar->AddTool(ID_CloseTab, wxT("Close Tab"), wxBitmap(IMG_PATH(Close, png), wxBITMAP_TYPE_PNG), wxT("Close Tab"));
	//m_pToolBar->AddTool(ID_Logout, wxT("Logout"), wxBitmap(IMG_PATH(Logout, png), wxBITMAP_TYPE_PNG), wxT("Logout"));
	m_pToolBar->Realize();
	SetToolBar(m_pToolBar);

	m_pNoteBook = new wxNotebook(this, ID_NoteBook);

	NewViewPage();
	//NewRolePage();
	//NewEventPage();
	
	// Sizer
	wxBoxSizer* pSizer = new wxBoxSizer(wxVERTICAL);
	pSizer->Add(m_pNoteBook, 1, wxEXPAND);
	SetSizer(pSizer);
	SetSizeHints(640, 480);
	SetSize(1000, 560);
	Layout();

	m_pNoteBook->Connect(wxEVT_RIGHT_UP, wxMouseEventHandler(FMainFrame::OnNoteBookRightClick), NULL, this);
}

void FMainFrame::NewViewPage()
{
	Freeze();
	FViewWindow* pViewWindow = new FViewWindow(m_pNoteBook, ID_ViewWindow);
	m_pNoteBook->AddPage(pViewWindow, wxT("View"), true);
	Thaw();
}

void FMainFrame::NewViewPage(const wxString& filename)
{
	Freeze();
	FViewWindow* pViewWindow = new FViewWindow(m_pNoteBook, ID_ViewWindow);
	m_pNoteBook->AddPage(pViewWindow, wxT("View"), true);
	pViewWindow->ParseFile(filename);
	Thaw();
}

void FMainFrame::NewEventPage(uint key)
{
	Freeze();
	bool bFound = false;
	for (uint i=0 ; i<m_pNoteBook->GetPageCount() ; ++i)
	{
		wxString sName = m_pNoteBook->GetPageText(i);
		if (sName == wxString(wxT("Event"), wxConvISO8859_1))
		{
			wxWindow* pPage = m_pNoteBook->GetPage(i);

			FEventWindow* pEventPage = wxDynamicCast(pPage, FEventWindow);
			if (pEventPage->GetKey() == key)
			{
				m_pNoteBook->SetSelection(i);
				bFound = true;
			}
		}
	}

	if (bFound == false)
	{
		FEventWindow* pEventWindow = new FEventWindow(m_pNoteBook, ID_EventWindow, key);
		m_pNoteBook->AddPage(pEventWindow, wxT("Event"), true);
	}
	Thaw();
}

void FMainFrame::NewRolePage()
{
	Freeze();
	FRoleWindow* pRoleWindow = new FRoleWindow(m_pNoteBook, ID_RoleWindow);
	m_pNoteBook->AddPage(pRoleWindow, wxT("Role"), true);
	Thaw();
}

/*
FEvent& FMainFrame::GetEvent(uint id)
{
	EventMap::iterator it = m_aEventMap.find(id);
	assert(it != m_aEventMap.end());

	return it->second;
}

void FMainFrame::RegisterEvent(const FEvent& oEvent)
{
	EventMap::iterator it = m_aEventMap.find(oEvent.GetKey());
	if (it == m_aEventMap.end())
	{
		pair<EventMap::iterator, bool> res;
		res = m_aEventMap.insert(EventPair(oEvent.GetKey(), oEvent));
		assert(res.second);
		it = res.first;
	}
	else
	{
		it->second = oEvent;
	}

	it->second.AddRef();
}

void FMainFrame::UnregisterEvent(const FEvent& oEvent)
{
	UnregisterEvent(oEvent.GetKey());
}

void FMainFrame::UnregisterEvent(uint id)
{
	EventMap::iterator it = m_aEventMap.find(id);
	assert(it != m_aEventMap.end());

	if (it->second.RemRef() == 0)
		m_aEventMap.erase(it);
}
*/

void FMainFrame::UpdateEvent()
{
	wxWindow* pCurrent = m_pNoteBook->GetCurrentPage();

	wxString sName = m_pNoteBook->GetPageText(m_pNoteBook->GetSelection());

	if (sName == wxString("View", wxConvISO8859_1))
	{
		FViewWindow* pViewWindow = wxDynamicCast(pCurrent, FViewWindow);
		assert(pViewWindow != NULL);
		pViewWindow->UpdateEvent();
	}
	else if (sName == wxString("Event", wxConvISO8859_1))
	{
		FEventWindow* pEventWindow = wxDynamicCast(pCurrent, FEventWindow);
		assert(pEventWindow != NULL);
		if (pEventWindow->GetKey() > 0)
			pEventWindow->Load();
	}
}



void FMainFrame::OnMenuCreateView(wxCommandEvent& event)
{
	NewViewPage();
}

void FMainFrame::OnMenuCreateEvent(wxCommandEvent& event)
{
	NewEventPage();
}

void FMainFrame::OnMenuEditRole(wxCommandEvent& event)
{
	NewRolePage();
}

void FMainFrame::OnMenuCreateUser(wxCommandEvent& event)
{
	FNewRoleDialog oDialog(this, wxID_ANY, wxT("New User"), wxDefaultPosition, wxDefaultSize, FNewRoleDialog::EM_NewUser);
	oDialog.ShowModal();
}

void FMainFrame::OnMenuEditUser(wxCommandEvent& event)
{
	FNewRoleDialog oDialog(this, wxID_ANY, wxT("Edit User"), wxDefaultPosition, wxDefaultSize, FNewRoleDialog::EM_EditUser);
	oDialog.ShowModal();
}

void FMainFrame::OnMenuCreatePlayer(wxCommandEvent& event)
{
}

void FMainFrame::OnMenuCreatePerso(wxCommandEvent& event)
{
}

void FMainFrame::OnMenuParseFile(wxCommandEvent& event)
{
	wxString filename = wxFileSelector("Choose a file to open");
	if ( !filename.empty() )
	{
		NewViewPage(filename);
	}
}

void FMainFrame::OnMenuLogout(wxCommandEvent& event)
{
	FApp* pApp = wxDynamicCast(wxTheApp, FApp);
	pApp->Logout();
}

void FMainFrame::OnMenuCloseTab(wxCommandEvent& event)
{
	if (m_pNoteBook->GetPageCount() > 1)
	{
		m_pNoteBook->DeletePage(m_pNoteBook->GetSelection());
		UpdateEvent();
	}
}


void FMainFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	Close(true);
}

void FMainFrame::OnNoteBookChange(wxNotebookEvent& event)
{
	UpdateEvent();
}

void FMainFrame::OnNoteBookRightClick(wxMouseEvent& event)
{
	if (m_pNoteBook != NULL)
	{
		m_iClickTabId = m_pNoteBook->HitTest(event.GetPosition());

		wxMenu* pMenu = new wxMenu;
		pMenu->Append(ID_NoteBook_CloseTab, wxT("Close"));

		PopupMenu(pMenu, event.GetPosition());
	}
}

void FMainFrame::OnNoteBookCloseTab(wxCommandEvent& event)
{
	if (m_pNoteBook->GetPageCount() > 1)
	{
		m_pNoteBook->DeletePage(m_iClickTabId);
		UpdateEvent();
	}
}

