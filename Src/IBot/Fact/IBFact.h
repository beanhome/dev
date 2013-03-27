#ifndef __IBFACT_H__
#define __IBFACT_H__

#include "Utils.h"

#include "IBFactDef.h"

class IBAction;
class IBPlanner;
class IBObject;

typedef set<IBFact*>	FactSet;
typedef set<IBAction*>	ActionSet;

class IBFact
{
	public:
		friend class IBPlanner;
		friend class IBAction;

	protected:
		IBFact(IBFactDef* pDef, const vector<IBObject*>& aUserData);
		virtual ~IBFact();

	public:
		IBFactDef*					GetFactDef() const { return m_pDef; }

		bool						HasCauseAction() const { return (m_aCauseAction.size() > 0); }
		void						RemoveCauseAction(IBAction* pAction) { m_aCauseAction.erase(pAction); }
		void						AddCauseAction(IBAction* pAction) { m_aCauseAction.insert(pAction); }
		const ActionSet&			GetCauseAction() const { return m_aCauseAction; }

		void						SetEffectAction(IBAction* pAction) { m_pEffectAction = pAction; }
		IBAction*					GetEffectAction() const { return m_pEffectAction; }
		bool						HasEffectAction() const { return (m_pEffectAction != NULL); }

		const vector<IBObject*>&	GetUserData() const { return m_aUserData; }
		const vector<IBObject*>&	GetVariables() const { return m_aUserData; }
		IBObject*					GetVariable(uint i) const { ASSERT(i<m_aUserData.size()); return m_aUserData[i]; }
		//IBObject*					GetVariable(uint i) { ASSERT(i<m_aUserData.size()); return m_aUserData[i]; }
		void						SetVariable(uint i, IBObject* pVar);

		bool						IsReadyToDelete() const;
		void						PrepareToDelete();
		bool						IsMarkToDelete() const { return m_bToDelete; }

		bool						IsTrue() const { return Test() == IBF_OK; }
		float						Evaluate() const;

		IBAction*					GetBestCauseAction(float& fMinEval) const;
		IBAction*					GetBestCauseAction() const { float fEval; return GetBestCauseAction(fEval); }

		IBF_Result 					Resolve(IBPlanner* pPlanner);
		void						ResolveVariable() { return m_pDef->ResolveVariable(m_aUserData); }

	public:
		static bool	RemoveAndDelete(IBFact* pFact) { if (pFact->IsReadyToDelete()) { delete pFact; return true; } else { return false; } }


	public:
		IBF_Result					Test() const { return m_pDef->Test(m_aUserData); }

	protected:
		IBFactDef*					m_pDef;
		vector<IBObject*>			m_aUserData;
		ActionSet					m_aCauseAction;
		IBAction*					m_pEffectAction;
		bool						m_bToDelete;
};

#endif
