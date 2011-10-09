#ifndef FMAINFRAME_H
#define FMAINFRAME_H

#include "wx/wx.h" 
#include "wx/notebook.h"
#include "Config.h"
#include "Utils.h"
#include "FEvent.h"

class FMainFrame: public wxFrame
{
	public:
		FMainFrame(const wxString& title, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize); 

		void NewViewPage();
		void NewViewPage(const wxString& filename);
		void NewEventPage(uint key = 0);
		void NewRolePage();

		//FEvent& GetEvent(uint id);
		//void RegisterEvent(const FEvent& oEvent);
		//void UnregisterEvent(const FEvent& oEvent);
		//void UnregisterEvent(uint id);

		void UpdateEvent();

	public:
		enum ID
		{
			ID_AddView,
			ID_AddEvent,
			ID_AddUser,
			ID_EditUser,
			ID_EditRole,
			ID_AddPlayer,
			ID_AddPerso,
			ID_ParseFile,
			ID_CloseTab,

			ID_Logout,
			ID_Exit,

			ID_NoteBook,
			ID_NoteBook_CloseTab,

			ID_ViewWindow,
			ID_EventWindow,
			ID_RoleWindow,

			ID_FMainFrame_MAX
		};
		DECLARE_EVENT_TABLE()

		void OnMenuCreateView(wxCommandEvent& event);
		void OnMenuCreateEvent(wxCommandEvent& event);
		void OnMenuCreateUser(wxCommandEvent& event);
		void OnMenuEditRole(wxCommandEvent& event);
		void OnMenuEditUser(wxCommandEvent& event);
		void OnMenuCreatePlayer(wxCommandEvent& event);
		void OnMenuCreatePerso(wxCommandEvent& event);
		void OnMenuParseFile(wxCommandEvent& event);
		void OnMenuLogout(wxCommandEvent& event);
		void OnMenuCloseTab(wxCommandEvent& event);
		void OnQuit(wxCommandEvent& event);

		void OnNoteBookChange(wxNotebookEvent& event);
		void OnNoteBookRightClick(wxMouseEvent& event);
		void OnNoteBookCloseTab(wxCommandEvent& event);

	private:
		wxMenuBar*			m_pMenuBar;
		wxToolBar*			m_pToolBar;
		wxMenu*				m_pMainMenu;
		wxNotebook*			m_pNoteBook;

		int					m_iClickTabId;

		DECLARE_CLASS(FMainFrame)
};

#endif