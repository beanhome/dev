#include "FRoleControlComp.h"
#include "Utils.h"
#include "Config.h"
#include "FQuery.h"
#include "FApp.h"

BEGIN_EVENT_TABLE(FRoleControlComp, FRoleControl)
END_EVENT_TABLE()


FRoleControlComp::FRoleControlComp(wxWindow *parent, wxWindowID id, const wxString& sLabel)
	: FRoleControl(parent, id, sLabel)
{
	wxStaticBoxSizer* pSizer = new wxStaticBoxSizer(wxVERTICAL, this, sLabel);

	FRoleControl::Create(pSizer);

	SetSizeHints(160, -1, 160, -1);
	SetSizerAndFit(pSizer);
	Layout();
}

