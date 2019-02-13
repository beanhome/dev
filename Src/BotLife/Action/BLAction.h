#ifndef __BLACTION_H__
#define __BLACTION_H__

#include "Action/IBAction.h"

class BLAction : public IBAction
{
public:
	BLAction(const class IBActionDef* pDef, class IBFact* pPostCond, IBPlanner* pPlanner);
	BLAction(const class IBAction* pOrig);
	~BLAction();

	void AddOwnedObject(class BLObject* pObject);

private:
	vector<class BLObject*> m_aOwnedObjects;
};

#endif