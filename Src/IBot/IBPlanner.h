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
		IBPlanner(void* pOwner);
		virtual ~IBPlanner();

		friend class IBPlannerGraph;

	public:
		virtual void			InitFactLibrary();
		virtual void			InitActionLibrary();

		void					AddGoal(const string& name);
		void					AddGoal(const string& name, IBObject* pUserData);
		void					AddGoal(const string& name, IBObject* pUserData1, IBObject* pUserData2);
		void					AddGoal(const string& name, IBObject* pUserData1, IBObject* pUserData2, IBObject* pUserData3);

		void					AddPreCond(IBAction* pAction, const string& name);
		void					AddPreCond(IBAction* pAction, const string& name, IBObject* pUserData);
		void					AddPreCond(IBAction* pAction, const string& name, IBObject* pUserData1, IBObject* pUserData2);
		void					AddPreCond(IBAction* pAction, const string& name, IBObject* pUserData1, IBObject* pUserData2, IBObject* pUserData3);

		IBFactDef*				GetFactDef(const string& name) { return m_oFactLibrary.GetFactDef(name); }

		int						Step();

		int						FindActionToResolve(IBFact* pFact);

		void*					GetOwner() const { return m_pOwner; }
		const FactSet&			GetGoals() const { return m_aGoals; }
		//FactSet&				GetGoals() { return m_aGoals; }


	protected:
		IBFactLibrary			m_oFactLibrary;
		IBActionLibrary			m_oActionLibrary;

	private:
		void*					m_pOwner;
		set<IBFactDef*>			m_aGoalsDef;
		
		FactSet					m_aGoals;
};

#define REGISTER_FACT(a) m_oFactLibrary.RegisterFactDef(#a, new a(#a, this))
#define REGISTER_FACT_NAMED(a, s) m_oFactLibrary.RegisterFactDef(s, new a(s, this))
#define REGISTER_ACTION(a) m_oActionLibrary.RegisterActionDef(#a, new a(#a, this))
#define REGISTER_ACTION_NAMED(a, s) m_oActionLibrary.RegisterActionDef(s, new a(s, this))


#endif
