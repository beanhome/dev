#include "FLocationDialog.h"
#include "Config.h"
#include "Utils.h"
#include "FQuery.h"
#include "FApp.h"
#include "wx\datetime.h"
#include "wx\calctrl.h"
#include "FDatation.h"

BEGIN_EVENT_TABLE(FLocationDialog, wxDialog)
END_EVENT_TABLE()


FLocationDialog::FLocationDialog(wxWindow *parent, wxWindowID id)
	: wxDialog(parent, id, wxT("Add Location"), wxDefaultPosition, wxSize(200,200))
{
	wxBoxSizer* pSizer = new wxBoxSizer(wxVERTICAL);

	m_pLocationControl = new FLocationControl(this, wxID_ANY, wxString(wxT("Location")), true);
	pSizer->Add(m_pLocationControl);

	wxSizer* pButtonSizer = CreateButtonSizer(wxOK | wxCANCEL);

	pSizer->Add(pButtonSizer, 0, wxEXPAND | wxALL, 5);

	SetSizerAndFit(pSizer);
	Layout();
}





