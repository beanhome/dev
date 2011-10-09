#ifndef FLOCATIONDIALOG_H
#define FLOCATIONDIALOG_H

#include "wx/wx.h" 
#include "Config.h"
#include "Utils.h"
#include "FLocation.h"
#include "FLocationControl.h"

class FLocationControl;

class FLocationDialog : public wxDialog
{
	public:
		FLocationDialog(wxWindow *parent, wxWindowID id);

		const FLocation& GetLocation() const { return m_pLocationControl->GetLocation(); }
		void SetLocation(const FLocation& oLoc) { m_pLocationControl->SetLocation(oLoc); }

		DECLARE_EVENT_TABLE()

	private:
		FLocationControl*		m_pLocationControl;

};

#endif