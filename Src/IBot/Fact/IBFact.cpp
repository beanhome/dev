#include "IBFact.h"
#include "Action/IBActionDef.h"
#include "IBPlanner.h"

#include "Utils.h"

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


