#include "BLAction.h"
#include "World/BLObject.h"

BLAction::BLAction(const class IBActionDef* pDef, class IBFact* pPostCond, IBPlanner* pPlanner)
: IBAction(pDef, pPostCond, pPlanner)
{
}

BLAction::BLAction(const class IBAction* pOrig)
	: IBAction(pOrig)
{
}

BLAction::~BLAction()
{
	for (BLObject* pObj : m_aOwnedObjects)
		delete pObj;
}

void BLAction::AddOwnedObject(class BLObject* pObject)
{
	m_aOwnedObjects.push_back(pObject);
}

