#ifndef FRoleWindow_H
#define FRoleWindow_H

#include "wx/wx.h" 
#include "Config.h"
#include "Utils.h"
#include "FEvent.h"

class FRoleWindow: public wxScrolledWindow
{
	public:
		FRoleWindow(wxWindow* pParent, wxWindowID id); 
		~FRoleWindow();

	public:
		enum
		{
			ID_TopRoleListDirect,
			ID_TopRoleListIndirect,
			ID_TopRoleListExclude,
			ID_TopRoleAddBtn,
			ID_TopRoleDelBtn,

			ID_RoleList,
			ID_RoleAddBtn,
			ID_RoleDelBtn,

			ID_BotRoleListDirect,
			ID_BotRoleListIndirect,
			ID_BotRoleListExclude,
			ID_BotRoleAddBtn,
			ID_BotRoleDelBtn,
		};

		DECLARE_EVENT_TABLE()
		void OnSelectRole(wxCommandEvent& event);
		void OnSelectRoleFromTopDirect(wxCommandEvent& event);
		void OnSelectRoleFromTopIndirect(wxCommandEvent& event);
		void OnSelectRoleFromTopExclude(wxCommandEvent& event);
		void OnSelectRoleFromBotDirect(wxCommandEvent& event);
		void OnSelectRoleFromBotIndirect(wxCommandEvent& event);
		void OnSelectRoleFromBotExclude(wxCommandEvent& event);
		
		void OnTopListAddBtn(wxCommandEvent& event);
		void OnTopListDelBtn(wxCommandEvent& event);
		void OnBotListAddBtn(wxCommandEvent& event);
		void OnBotListDelBtn(wxCommandEvent& event);
		void OnNewBtn(wxCommandEvent& event);
		void OnDelBtn(wxCommandEvent& event);

	private:
		void UpdateRoleList();
		void UpdateTopRoleList();
		void UpdateBotRoleList();

		void DoSelectFromList(wxListBox* pList);

	private:
		string					m_sCurrentRole;

		wxListBox*				m_pTopRoleDirect;
		wxListBox*				m_pTopRoleIndirect;
		wxListBox*				m_pTopRoleExclude;
		wxButton*				m_pTopRoleAddBtn;
		wxButton*				m_pTopRoleDelBtn;

		wxListBox*				m_pRoleList;
		wxButton*				m_pRoleAddBtn;
		wxButton*				m_pRoleDelBtn;

		wxListBox*				m_pBotRoleDirect;
		wxListBox*				m_pBotRoleIndirect;
		wxListBox*				m_pBotRoleExclude;
		wxButton*				m_pBotRoleAddBtn;
		wxButton*				m_pBotRoleDelBtn;

};

#endif