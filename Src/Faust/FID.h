#ifndef FID_H
#define FID_H

#define ID_START 1

enum ID
{
	ID_MainMenu = ID_START,
	ID_MainMenu_AddView,
	ID_MainMenu_AddEvent,
	ID_MainMenu_AddUser,
	ID_MainMenu_EditUser,
	ID_MainMenu_EditRole,
	ID_MainMenu_AddPlayer,
	ID_MainMenu_AddPerso,
	ID_MainMenu_Logout,
	ID_MainMenu_Exit,

	ID_MainFrame_NoteBook,
	ID_NoteBook_CloseTab,

	ID_ViewWindow,
	ID_EventWindow,
	ID_RoleWindow,

	ID_Bt_Research,
	ID_Bt_Apply,

	ID_MAX
};

#endif