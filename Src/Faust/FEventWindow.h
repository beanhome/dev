#ifndef FEVENTWINDOW_H
#define FEVENTWINDOW_H

#include "wx/wx.h" 
#include "Config.h"
#include "Utils.h"
#include "FEvent.h"

class FDatationControl;
class FLocationListControl;
class FRoleControlEdit;
class FTagControlEdit;
class FNameRefControl;

class FEventWindow: public wxPanel
{
	public:
		FEventWindow(wxWindow* pParent, wxWindowID id, uint key = 0); 
		~FEventWindow();

		uint GetKey() const { return m_pEvent->GetKey(); }

		void Load();
		void Save();

	public:
		enum
		{
			ID_Role,
			ID_Tag,
			ID_Save,
			ID_New
		};

		DECLARE_EVENT_TABLE()
		void OnSave(wxCommandEvent& event);
		void OnNew(wxCommandEvent& event);

	private:
		FEvent*	const			m_pEvent;

		wxBoxSizer*				m_pSizer;

		wxStaticText*			m_pNameText;
		wxTextCtrl*				m_pNameControl;

		FNameRefControl*		m_pNameRefControl;

		wxStaticText*			m_pDescText;
		wxTextCtrl*				m_pDescControl;

		FDatationControl*		m_pDatationControl;

		FLocationListControl*	m_pLocationListControl;

		FRoleControlEdit*		m_pRoleControl;

		FTagControlEdit*		m_pTagControl;
		
		wxButton*				m_pSaveButton;
		wxButton*				m_pNewButton;
};

#endif