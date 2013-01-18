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

void IBFact::SetVariable(uint i, void* pVar)
{
	ASSERT(i<m_aUserData.size());
	m_aUserData[i] = pVar;

	if (m_pCauseAction != NULL)
		m_pCauseAction->ResolvePostCondVariable();
}



bool IBFact::Resolve(IBPlanner* pPlanner)
{
	IBF_Result res = Test();
	//LOG("Result : %d\n", res);

	if (m_pCauseAction != NULL && m_pCauseAction->Resolve(pPlanner) == IBAction::IBA_Destroy)
	{
		delete m_pCauseAction;
		m_pCauseAction = NULL;
	}

	switch (res)
	{
		case IBF_OK:
			return true;
			break;

		case IBF_FAIL:
			if (m_pCauseAction == NULL)
			{
				pPlanner->FindActionToResolve(this);
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


