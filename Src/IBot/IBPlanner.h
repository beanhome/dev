#ifndef __IBPLANNER_H__
#define __IBPLANNER_H__

#include "Utils.h"
#include "Fact/IBFactLibrary.h"
#include "Fact/IBFact.h"
#include "Action/IBActionLibrary.h"

class IBFactDef;

class IBPlannerGraph;

class IBPlanner
{
	public:
		IBPlanner();
		virtual ~IBPlanner();

		friend class IBPlannerGraph;

	public:
		virtual void			InitFactLibrary();
		virtual void			InitActionLibrary();

		void					AddGoal(const string& name);
		void					AddGoal(const string& name, void* pUserData);
		void					AddGoal(const string& name, void* pUserData1, void* pUserData2);
		void					AddGoal(const string& name, void* pUserData1, void* pUserData2, void* pUserData3);

		IBFactDef*				GetFactDef(const string& name) { return m_oFactLibrary.GetFactDef(name); }

		int						Step();

		int						FindActionToResolve(IBFact* pFact);

		const FactSet&			GetGoals() const { return m_aGoals; }


	protected:
		IBFactLibrary			m_oFactLibrary;
		IBActionLibrary			m_oActionLibrary;

	private:
		set<IBFactDef*>			m_aGoalsDef;
		
		FactSet					m_aGoals;
};

#define REGISTER_FACT(a) m_oFactLibrary.RegisterFactDef(#a, new a(#a))
#define REGISTER_ACTION(a) m_oActionLibrary.RegisterActionDef(#a, new a(#a, this))


#endif
