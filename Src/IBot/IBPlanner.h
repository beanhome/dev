#ifndef __IBPLANNER_H__
#define __IBPLANNER_H__

#include "Utils.h"
#include "Fact/IBFactLibrary.h"
#include "Fact/IBFact.h"
#include "Fact/IBWorldChange.h"
#include "Action/IBActionLibrary.h"

class IBPlanner
{
	public:
		IBPlanner(void* pOwner);
		virtual ~IBPlanner();

	public:
		IBAction*				InstanciateAction(const string& sActionName, IBFact* pPostCond);
		IBFact*					InstanciateFact(const string& sFactName, bool bInverted, const vector<IBObject>& aVariables, IBWorldChange* pWorldChange);
		
		virtual IBAction*		InstanciateAction(const class IBActionDef* pDef, IBFact* pPostCond);
		virtual IBFact*			InstanciateFact(const class IBFactDef* pDef, bool bInverted, const vector<IBObject>& aVariables, IBWorldChange* pWorldChange);

		virtual bool				AreCompatible(const class IBFact* A, const class IBFact* B) const { return true; }

		void						AddGoal(const string& fact_name, bool bTrue);
		void						AddGoal(const string& name, bool bTrue, const vector<IBObject>& aObjects);
		void						AddGoal(const string& fact_name, bool bTrue, const string& sVarName, void* pUserData);
		void						AddGoal(const string& fact_name, bool bTrue, const string& sVarName1, void* pUserData1, const string& sVarName2, void* pUserData2);
		void						AddGoal(const string& fact_name, bool bTrue, const string& sVarName1, void* pUserData1, const string& sVarName2, void* pUserData2, const string& sVarName3, void* pUserData3);

		template<class T1>
		void						AddGoal(const string& fact_name, bool bTrue, T1* pVar1) { AddGoal(fact_name, bTrue, pVar1->GetName(), pVar1); }

		template<class T1, class T2>
		void						AddGoal(const string& fact_name, bool bTrue, T1* pVar1, T2* pVar2) { AddGoal(fact_name, bTrue, pVar1->GetName(), pVar1, pVar2->GetName(), pVar2); }

		template<class T1, class T2, class T3>
		void						AddGoal(const string& fact_name, bool bTrue, T1* pVar1, T2* pVar2, T3* pVar3) { AddGoal(fact_name, bTrue, pVar1->GetName(), pVar1, pVar2->GetName(), pVar2, pVar3->GetName(), pVar3); }

		void						AddGoal(IBFact* goal);
		void						RemGoal(IBFact* goal);

		const IBActionLibrary&	GetActionLibrary() const { return m_oActionLibrary;  }
		class IBFactDef*			GetFactDef(const string& name) { return m_oFactLibrary.GetFactDef(name); }

		int						Step(bool bExecute = true, bool bCleanGoal = true);

		sint32					GetStepCount() const { return m_iStepCount; }

		class IBAction*			GetCurrentAction() const { return m_pCurrentAction; }
		void						SetCurrentAction(IBAction* pAction) { m_pCurrentAction = pAction; m_pBestNode = nullptr; }
		const class IBWorldChange*	GetBestNode() const { return m_pBestNode; }

		void*					GetOwner() const { return m_pOwner; }
		const class IBWorldChange&	GetGoals() const { return m_oGoals; }

	protected:
		void CleanGoal();

	protected:
		IBFactLibrary			m_oFactLibrary;
		IBActionLibrary			m_oActionLibrary;

	private:
		void*					m_pOwner;
		
	protected:
		class IBWorldChange		m_oGoals;
		
		class IBAction*			m_pCurrentAction;
		class IBWorldChange*		m_pBestNode;

		sint32					m_iStepCount;

public:
		static float				s_fMaxActionDelay;
};

#define REGISTER_FACT(a) m_oFactLibrary.RegisterFactDef(#a, new a(#a, this))
#define REGISTER_FACT_NAMED(a, s) m_oFactLibrary.RegisterFactDef(s, new a(s, this))
#define REGISTER_ACTION(a) m_oActionLibrary.RegisterActionDef(#a, new a(#a, this))
#define REGISTER_ACTION_NAMED(a, s) m_oActionLibrary.RegisterActionDef(s, new a(s, this))


#endif
