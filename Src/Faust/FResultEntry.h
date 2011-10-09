#ifndef FRESULTENTRY_H
#define FRESULTENTRY_H

#include "wx/wx.h" 
#include "libpq-fe.h"
#include "Config.h"
#include "Utils.h"
#include "FEvent.h"

class FResultEntry : public wxPanel
{
	public:
		FResultEntry(wxWindow *parent, FEvent* pEvent); 
		~FResultEntry();

		void UpdateEvent();
		bool ApplyToEvent();

		void Select(bool bSelect);
		void DoSelect(bool bSelect); // interne

		FEvent* GetEvent() const { return m_pEvent; }

		enum
		{
			ID_Select,
			ID_Edit,
			ID_Delete
		};

	public:
		DECLARE_EVENT_TABLE()

		void OnEnterWindow(wxMouseEvent& event);
		void OnLeaveWindow(wxMouseEvent& event);
		void OnRightClick(wxMouseEvent& event);
		void OnLeftClick(wxMouseEvent& event);
		void OnLeftDClick(wxMouseEvent& event);
		void OnEdit(wxCommandEvent& event);
		void OnDelete(wxCommandEvent& event);
		void OnSelect(wxCommandEvent& event);

	private:
		void Edit();
		void Delete();

	private:
		FEvent* const	m_pEvent;

		wxCheckBox*		m_pSelectCheckBox;

		wxTextCtrl*		m_pDebugText;
		wxTextCtrl*		m_pNameText;
		wxTextCtrl*		m_pStartDateText;
		wxTextCtrl*		m_pEndDateText;
		wxTextCtrl*		m_pDescText;

		bool			m_bSelected;
		wxColor			m_oBGColor;
		wxColor			m_oBGColorSelected;
};

#endif