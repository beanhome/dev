#ifndef __IBFACT_H__
#define __IBFACT_H__

#include "Utils.h"

#include "IBFactDef.h"

class IBAction;
class IBPlanner;

class IBFact
{
	public:
		IBFact(IBFactDef* pDef, vector<void*> aUserData);
		~IBFact();

		IBFactDef*					GetFactDef() const { return m_pDef; }

		void						SetCauseAction(IBAction* pAction) { m_pCauseAction = pAction; }
		IBAction*					GetCauseAction() const { return m_pCauseAction; }
		bool						HasCauseAction() const { return (m_pCauseAction != NULL); }
		void						RemoveCauseAction(const IBAction* pAction) { if (m_pCauseAction == pAction) m_pCauseAction = NULL; }

		void						SetEffectAction(IBAction* pAction) { m_pEffectAction = pAction; }
		IBAction*					GetEffectAction() const { return m_pEffectAction; }
		bool						HasEffectAction() const { return (m_pEffectAction != NULL); }

		const vector<void*>&		GetUserData() const { return m_aUserData; }
		const vector<void*>&		GetVariables() const { return m_aUserData; }
		void*						GetVariable(uint i) const { ASSERT(i<m_aUserData.size()); return m_aUserData[i]; }
		//void*						GetVariable(uint i) { assert(i<m_aUserData.size()); return m_aUserData[i]; }
		void						SetVariable(uint i, void* pVar);

		bool						IsTrue() const { return Test() == IBF_OK; }

		bool						Resolve(IBPlanner* pPlanner);
		void						ResolveVariable() { return m_pDef->ResolveVariable(m_aUserData); }

	public:
		IBF_Result					Test() const { return m_pDef->Test(m_aUserData); }

	protected:
		IBFactDef*					m_pDef;
		vector<void*>				m_aUserData;
		IBAction*					m_pCauseAction;
		IBAction*					m_pEffectAction;
};

typedef set<IBFact*>	FactSet;

#endif
