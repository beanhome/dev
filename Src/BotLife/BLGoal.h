#ifndef __BLGOAL_H__
#define __BLGOAL_H__

#include "Utils.h"
#include "World/IBObject.h"


class BLGoal
{
	public:
		BLGoal(class IBPlanner& oPlanner, const char* fact_name);
		BLGoal(class IBPlanner& oPlanner, const char* fact_name, const class BLObject* pObject);
		BLGoal(class IBPlanner& oPlanner, const char* fact_name, const class BLObject* pObject1, const class BLObject* pObject2);
		BLGoal(class IBPlanner& oPlanner, const char* fact_name, const class BLObject* pObject1, const class BLObject* pObject2, const class BLObject* pObject3);
		BLGoal(const BLGoal& Original);

		virtual ~BLGoal();

		const string& GetName() const;

		const class IBFact* GetFact() const;

		vector<class IBObject> GetIBObjects() const;

		void AddObject(const class BLObject* oObject) { m_aObjects.push_back(oObject);  }

	private:
		class IBPlanner& m_oPlanner;
		class IBFact* m_pFact;
		vector<const class BLObject*> m_aObjects;
};



#endif
