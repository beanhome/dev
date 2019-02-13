#include "BLGoal.h"
#include "IBPlanner.h"
#include "Fact/IBFact.h"
#include "Fact/IBFactDef.h"
#include "World/IBObject.h"
#include "World/BLObject.h"

BLGoal::BLGoal(class IBPlanner& oPlanner, const char* name)
	: m_oPlanner(oPlanner)
	, m_pFact(nullptr)
{
	vector<IBObject> aObjects;
	m_pFact = m_oPlanner.InstanciateFact(name, false, aObjects, nullptr);
}

BLGoal::BLGoal(class IBPlanner& oPlanner, const char* name, const class BLObject* pObject)
	: m_oPlanner(oPlanner)
	, m_pFact(nullptr)
{
	vector<IBObject> aObjects;
	aObjects.push_back(IBObject(pObject->GetName(), (void*)pObject));
	m_pFact = m_oPlanner.InstanciateFact(name, false, aObjects, nullptr);
}

BLGoal::BLGoal(class IBPlanner& oPlanner, const char* name, const class BLObject* pObject1, const class BLObject* pObject2)
	: m_oPlanner(oPlanner)
	, m_pFact(nullptr)
{
	vector<IBObject> aObjects;
	aObjects.push_back(IBObject(pObject1->GetName(), (void*)pObject1));
	aObjects.push_back(IBObject(pObject2->GetName(), (void*)pObject2));
	m_pFact = m_oPlanner.InstanciateFact(name, false, aObjects, nullptr);
}

BLGoal::BLGoal(class IBPlanner& oPlanner, const char* name, const class BLObject* pObject1, const class BLObject* pObject2, const class BLObject* pObject3)
	: m_oPlanner(oPlanner)
	, m_pFact(nullptr)
{
	vector<IBObject> aObjects;
	aObjects.push_back(IBObject(pObject1->GetName(), (void*)pObject1));
	aObjects.push_back(IBObject(pObject2->GetName(), (void*)pObject2));
	aObjects.push_back(IBObject(pObject3->GetName(), (void*)pObject3));
	m_pFact = m_oPlanner.InstanciateFact(name, false, aObjects, nullptr);
}

BLGoal::BLGoal(const BLGoal& oOriginal)
	: m_oPlanner(oOriginal.m_oPlanner)
	, m_pFact(nullptr)
{
	m_pFact = (oOriginal.m_pFact != nullptr ? oOriginal.m_pFact->Clone() : nullptr);

	m_aObjects.resize(oOriginal.m_aObjects.size());
	for (uint32 i = 0; i < m_aObjects.size(); ++i)
	{
		m_aObjects[i] = oOriginal.m_aObjects[i]->Clone();

		for (VarMap::const_iterator it = oOriginal.m_pFact->GetVariables().begin(); it != oOriginal.m_pFact->GetVariables().end(); ++it)
		{
			if (it->second.GetUserData() == oOriginal.m_aObjects[i])
			{
				m_pFact->SetVariable(it->first, IBObject(m_aObjects[i]->GetName(), (void*)m_aObjects[i]));
				break;
			}
		}
	}
}

BLGoal::~BLGoal()
{
	for (const class BLObject* pObj : m_aObjects)
		delete pObj;

	delete m_pFact;
}

const string& BLGoal::GetName() const
{
	return m_pFact->GetFactDef()->GetName();
}

const class IBFact* BLGoal::GetFact() const
{
	return m_pFact;
}

vector<class IBObject> BLGoal::GetIBObjects() const
{
	vector<class IBObject> aIBObjects;
	aIBObjects.reserve(m_aObjects.size());

	for (const class BLObject* pObj : m_aObjects)
		aIBObjects.push_back(IBObject(pObj->GetName(), (void*)pObj));

	return aIBObjects;
}

/*
string BLGoal::GetData() const
{
	string sData = "(";

	for (uint i=0 ; i<m_aUserData.size() ; ++i)
	{
		sData += m_aUserData[i]->GetData();

		if (i<m_aUserData.size()-1)
			sData += ", ";
	}

	sData += ")";

	return sData;
}
*/