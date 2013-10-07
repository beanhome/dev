#ifndef __IBPLANNER_H__
#define __IBPLANNER_H__

#include "Utils.h"
#include "Fact/IBFactLibrary.h"
#include "Fact/IBFact.h"
#include "Action/IBActionLibrary.h"

class IBFactDef;

class IBGoal;

class IBPlanner
{
	public:
		IBPlanner(void* pOwner);
		virtual ~IBPlanner();

	public:
		virtual IBAction*		InstanciateAction(IBActionDef* pDef, IBFact* pPostCond1);
		virtual IBFact*			InstanciateFact(IBFactDef* pDef, const vector<IBObject*>& aUserData, IBAction* pEffectAction);

		void					AddGoal(const string& name);
		void					AddGoal(const string& name, IBObject* pUserData);
		void					AddGoal(const string& name, IBObject* pUserData1, IBObject* pUserData2);
		void					AddGoal(const string& name, IBObject* pUserData1, IBObject* pUserData2, IBObject* pUserData3);

		void					AddGoal(const IBGoal& goal);

		void					RemGoal(IBFact* goal);

		void					AddPreCond(IBAction* pAction, const string& name);
		void					AddPreCond(IBAction* pAction, const string& name, IBObject* pUserData);
		void					AddPreCond(IBAction* pAction, const string& name, IBObject* pUserData1, IBObject* pUserData2);
		void					AddPreCond(IBAction* pAction, const string& name, IBObject* pUserData1, IBObject* pUserData2, IBObject* pUserData3);

		IBFactDef*				GetFactDef(const string& name) { return m_oFactLibrary.GetFactDef(name); }

		int						Step(bool bExecute = true, bool bCleanGoal = true);
		const IBAction*			GetCurrentAction() const { return m_pCurrentAction; }
		void					SetCurrentAction(const IBAction* pAction) { m_pCurrentAction = pAction; }

		int						FindActionToResolve(IBFact* pFact);
		IBFact*					FindEqualFact_TopBottom(IBFact* pFact, const IBFact* pInstigator) const;

		void*					GetOwner() const { return m_pOwner; }
		const FactSet&			GetGoals() const { return m_aGoals; }
		//FactSet&				GetGoals() { return m_aGoals; }


	protected:
		IBFactLibrary			m_oFactLibrary;
		IBActionLibrary			m_oActionLibrary;

	private:
		void*					m_pOwner;
		
	protected:
		const IBAction*			m_pCurrentAction;
		FactSet					m_aGoals;

	public:
		static float			s_fMaxActionDelay;
};

#define REGISTER_FACT(a) m_oFactLibrary.RegisterFactDef(#a, new a(#a, this))
#define REGISTER_FACT_NAMED(a, s) m_oFactLibrary.RegisterFactDef(s, new a(s, this))
#define REGISTER_ACTION(a) m_oActionLibrary.RegisterActionDef(#a, new a(#a, this))
#define REGISTER_ACTION_NAMED(a, s) m_oActionLibrary.RegisterActionDef(s, new a(s, this))


#endif
