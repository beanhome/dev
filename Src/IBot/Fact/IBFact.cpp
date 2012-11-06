#include "IBFact.h"
#include "Action/IBActionDef.h"
#include "IBPlanner.h"

#include "Utils.h"

#include "CanvasBase.h"

IBFact::IBFact(IBFactDef* pDef, vector<void*> aUserData)
	: m_pDef(pDef)
	, m_aUserData(aUserData)
	, m_pCauseAction(NULL)
	, m_pEffectAction(NULL)
{
}

IBFact::~IBFact()
{

}



bool IBFact::Resolve(IBPlanner* pPlanner)
{
	IBF_Result res = Test();
	//LOG("Result : %d\n", res);

	switch (res)
	{
		case IBF_OK:
			if (m_pCauseAction != NULL)
			{
				delete m_pCauseAction;
				m_pCauseAction = NULL;
			}
			return true;
			break;

		case IBF_FAIL:
			if (!HasCauseAction())
			{
				pPlanner->FindActionToResolve(this);
			}
			else
			{
				return GetCauseAction()->Resolve(pPlanner);
			}
			break;

		case IBF_UNKNOW:
			// Find variable object
			// ...
			if (false) { LOG("prout"); }
			break;
	}

	return false;
}


void IBFact::Print(int tab) const
{
	m_pDef->Print(m_aUserData, tab);

	for (int i=0 ; i<tab ; ++i) LOG("\t");
	LOG(IBF_ResultString[Test()]);
	LOG("\n");

	if (m_pCauseAction != NULL)
	{
		m_pCauseAction->Print(tab+1);
	}
}

void IBFact::Draw(CanvasBase& canva, int& x, int& y) const
{
	int w = 128;
	int h = 18;
	int sq_size = 10;

	if (m_pEffectAction != NULL)
	{
		int space = 64;

		canva.DrawLine(x, y, x-space, y, Color(255, 255, 255));

		x -= space;
		canva.DrawRect(x-sq_size, y-sq_size/2, sq_size, sq_size, Color(128, 255, 255));
		x -= sq_size;
		x -= w/2;
	}

	canva.DrawRect(x-w/2, y-h/2, w, h, Color(128, 255, 255));
	canva.Print(x, y, canva.GetPrintFont(), h-6, Center, 128, 255, 255, "%s", m_pDef->GetName().c_str());

	if (m_pCauseAction != NULL)
	{
		x -= w/2;
		canva.DrawRect(x-sq_size, y-sq_size/2, sq_size, sq_size, Color(128, 255, 255));
		x -= sq_size;
		m_pCauseAction->Draw(canva, x, y, this);
	}
}
