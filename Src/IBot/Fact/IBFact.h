#ifndef __IBFACT_H__
#define __IBFACT_H__

#include "Utils.h"

#include "IBFactDef.h"

class IBAction;
class IBPlanner;
class IBObject;

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

		void						SetCauseAction(IBAction* pAction) { m_pCauseAction = pAction; }
		IBAction*					GetCauseAction() const { return m_pCauseAction; }
		bool						HasCauseAction() const { return (m_pCauseAction != NULL); }
		void						RemoveCauseAction(const IBAction* pAction) { if (m_pCauseAction == pAction) m_pCauseAction = NULL; }

		void						SetEffectAction(IBAction* pAction) { m_pEffectAction = pAction; }
		IBAction*					GetEffectAction() const { return m_pEffectAction; }
		bool						HasEffectAction() const { return (m_pEffectAction != NULL); }

		const vector<IBObject*>&	GetUserData() const { return m_aUserData; }
		const vector<IBObject*>&	GetVariables() const { return m_aUserData; }
		IBObject*					GetVariable(uint i) const { ASSERT(i<m_aUserData.size()); return m_aUserData[i]; }
		//IBObject*					GetVariable(uint i) { assert(i<m_aUserData.size()); return m_aUserData[i]; }
		void						SetVariable(uint i, IBObject* pVar);

		bool						IsReadyToDelete() const { return (m_bToDelete && m_pCauseAction == NULL); }
		void						PrepareToDelete();
		bool						IsMarkToDelete() const { return m_bToDelete; }

		bool						IsTrue() const { return Test() == IBF_OK; }

		bool						Resolve(IBPlanner* pPlanner);
		void						ResolveVariable() { return m_pDef->ResolveVariable(m_aUserData); }

	public:
		static bool	RemoveAndDelete(IBFact* pFact) { if (pFact->IsReadyToDelete()) { delete pFact; return true; } else { return false; } }


	public:
		IBF_Result					Test() const { return m_pDef->Test(m_aUserData); }

	protected:
		IBFactDef*					m_pDef;
		vector<IBObject*>			m_aUserData;
		IBAction*					m_pCauseAction;
		IBAction*					m_pEffectAction;
		bool						m_bToDelete;
};

typedef set<IBFact*>	FactSet;

#endif
