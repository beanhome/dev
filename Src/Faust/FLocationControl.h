#ifndef FLocationControl_H
#define FLocationControl_H

#include "wx/wx.h" 
#include "Config.h"
#include "Utils.h"
#include "FLocation.h"

class FLocationControl : public wxPanel
{
	public:
		FLocationControl(wxWindow *parent, wxWindowID id, const wxString& sLabel, bool bCreate = false); 
		~FLocationControl();

		void Activate(bool bActivate);
		bool IsActivated() const;

		const FLocation& GetLocation() const { return m_oLocation; }
		void SetLocation(const FLocation& oLocation);

		string GetJoinQuery() const;

	public:
		enum
		{
			ID_Activate,
			ID_ChoiceList,
			ID_CreateBtn = ID_ChoiceList + ELocElem_MAX
		};

	public:
		DECLARE_EVENT_TABLE()

		void OnActivate(wxCommandEvent& event);

		void OnEntryChange(wxCommandEvent& event);
		void OnClickCreate(wxCommandEvent& event);

	private:
		void SetEntry(uint id, const string& sValue);

		void DoLocChange(uint id);

		void UpdateList(uint id);

		void UpdateID();		

	private:
		struct LocationEntry
		{
			wxStaticText*	m_pName;
			wxChoice*		m_pComboBox;
			wxButton*		m_pCreateBtn;

			string			m_sValue;

			LocationEntry() : m_pName(NULL), m_pComboBox(NULL), m_pCreateBtn(NULL) {}

			void Enable(bool bEnable) { if (m_pComboBox != NULL) m_pComboBox->Enable(bEnable); if (m_pCreateBtn != NULL) m_pCreateBtn->Enable(bEnable); }
			bool IsNull() const { return m_sValue.length() == 0;}

			//const char* GetValue() const { return m_pComboBox != NULL ? m_pComboBox->GetValue().mb_str()}
		};

		wxCheckBox*			m_pActivateCheckBox;

		LocationEntry		m_oEntry[ELocElem_MAX];

		FLocation			m_oLocation;

		static const char* s_sLabelName[ELocElem_MAX];
};

#endif