#ifndef FCALENDARDIALOG_H
#define FCALENDARDIALOG_H

#include "wx/wx.h" 
#include "Config.h"
#include "Utils.h"
#include "wx/calctrl.h"
#include "FDatation.h"

class FCalendarDialog : public wxDialog
{
	public:
		FCalendarDialog(wxWindow *parent, wxWindowID id); 

		const FDate& GetDate() const { return m_oDate; }
		void SetDate(const FDate& oDate) { m_oDate = oDate; UpdateTextDate(); UpdateSlider(); UpdateCalendar(); }

	public:
		enum
		{
			ID_TextEntry,
			ID_Slider,
			ID_CalEntry,
		};

		DECLARE_EVENT_TABLE()

		void OnTextDateChange(wxCommandEvent& event);
		void OnYearSlide(wxCommandEvent& event);
		void OnCalendarChange(wxCalendarEvent& event);

	private:
		void UpdateTextDate();
		void UpdateSlider();
		void UpdateCalendar();

	private:
		wxTextCtrl*			m_pDateEntry;

		wxSlider*			m_pYearSlider;

		wxCalendarCtrl*		m_pCalendarEntry;

		FDate				m_oDate;
};

#endif