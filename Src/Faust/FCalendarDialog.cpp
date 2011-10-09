#include "FCalendarDialog.h"
#include "Config.h"
#include "Utils.h"
#include "FQuery.h"
#include "FApp.h"
#include "wx\datetime.h"
#include "wx\calctrl.h"
#include "FDatation.h"

BEGIN_EVENT_TABLE(FCalendarDialog, wxDialog)
	EVT_TEXT( ID_TextEntry,    FCalendarDialog::OnTextDateChange)
	EVT_SLIDER( ID_Slider,    FCalendarDialog::OnYearSlide)
	EVT_CALENDAR_SEL_CHANGED( ID_CalEntry,    FCalendarDialog::OnCalendarChange)
END_EVENT_TABLE()


FCalendarDialog::FCalendarDialog(wxWindow *parent, wxWindowID id)
	: wxDialog(parent, id, wxT("Calendar"), wxDefaultPosition, wxSize(200,200))
	, m_pDateEntry(NULL)
	, m_pYearSlider(NULL)
	, m_pCalendarEntry(NULL)
	, m_oDate(0,0)
{
	wxBoxSizer* pSizer = new wxBoxSizer(wxVERTICAL);

	m_pDateEntry = new wxTextCtrl(this, ID_TextEntry, wxT(""));
	pSizer->Add(m_pDateEntry, 0, wxEXPAND | wxLEFT|wxRIGHT|wxTOP, 5);

	m_pYearSlider = new wxSlider(this, ID_Slider, 2000, 0, 2050, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL | wxSL_LABELS);
	pSizer->Add(m_pYearSlider, 0, wxEXPAND | wxLEFT|wxRIGHT|wxTOP, 5);

	m_pCalendarEntry = new wxCalendarCtrl(this, ID_CalEntry, wxDefaultDateTime);
	pSizer->Add(m_pCalendarEntry, 0, wxEXPAND | wxLEFT|wxRIGHT|wxTOP, 5);

	wxSizer* pButtonSizer = CreateButtonSizer(wxOK | wxCANCEL);

	pSizer->Add(pButtonSizer, 0, wxEXPAND | wxALL, 5);

	SetSizerAndFit(pSizer);
	Layout();

	m_oDate.SetYear(2000);
	m_oDate.SetMonth(0);
	m_oDate.SetDay(1);

	UpdateTextDate();
	UpdateSlider();
	UpdateCalendar();
}


void FCalendarDialog::OnTextDateChange(wxCommandEvent& WXUNUSED(event))
{
	if (m_pDateEntry != NULL)
	{
		m_oDate = FDate(m_pDateEntry->GetValue().mb_str(wxConvISO8859_1));
		UpdateSlider();
		UpdateCalendar();
	}
}

void FCalendarDialog::OnYearSlide(wxCommandEvent& WXUNUSED(event))
{
	int iYear = m_pYearSlider->GetValue();

	m_oDate.SetYear(iYear);

	UpdateTextDate();
	UpdateCalendar();
}

void FCalendarDialog::OnCalendarChange(wxCalendarEvent& WXUNUSED(event))
{
	const wxDateTime wxDate = m_pCalendarEntry->GetDate();

	m_oDate.SetYear(wxDate.GetYear());
	m_oDate.SetMonth(wxDate.GetMonth());
	m_oDate.SetDay(wxDate.GetDay());

	UpdateTextDate();
	UpdateSlider();
}

void FCalendarDialog::UpdateTextDate()
{
	m_pDateEntry->ChangeValue(wxString(m_oDate.GetFormated(), wxConvISO8859_1));
}

void FCalendarDialog::UpdateSlider()
{
	m_pYearSlider->SetValue(m_oDate.GetYear());
}

void FCalendarDialog::UpdateCalendar()
{
	m_pCalendarEntry->SetDate(wxDateTime(m_oDate.GetDay(), (wxDateTime::Month)m_oDate.GetMonth(), m_oDate.GetYear()));
}



