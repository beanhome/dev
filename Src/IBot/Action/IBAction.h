#ifndef __IBACTION_H__
#define __IBACTION_H__

#include "Utils.h"
#include "Types.h"
#include "Fact/IBFact.h"
#include "World/IBObject.h"
#include "IBCost.h"

class IBAction
{
	public:
		friend class IBPlanner;
		friend class IBFact;
		friend class IBNode;
		friend class IBActionLibrary;

	protected:
		IBAction(const class IBActionDef* pDef, class IBFact* pPostCond, IBPlanner* pPlanner);
		IBAction(const class IBAction* pOrig);
		virtual ~IBAction();

	public:
		void						Create();
		void						Destroy();
		void						CloneWithVar(const string& sVarName, const IBObject& oVarObj);
		void						CloneWithVar(const string& sVarName, const IBObject& oVarObj, const PotentialVarMap& aPotentialVarMap);


		IBA_State					GetState() const { return m_eState; }
		void						SetState(IBA_State state) { m_eState = state; }

		const VarMap&				GetVariables() const { return m_aVariables; }
		const IBObject*				GetVariable(const string& name) const;
		void						SetVariable(const string& var_name, const IBObject& obj);
		void						SetVariable(const string& var_name, const string& obj_name, void* user_data);

		bool						IsResolved() const;

		void						AddPotentialVariable(const string& var_name, const string& obj_name, void* user_data);
		void						GetPotentialVariable(const string& var_name, vector<IBObject>& aObj) const;
		uint32						GetPotentialVariableCount(const string& var_name) const;

		template <class T>
		T*							GetVariable(const string& name) const;

		const class IBActionDef*	GetDef() const { return m_pDef; }

		const vector<IBFact*>&		GetPostCond() const { return m_aPostCond; }
		const vector<IBFact*>&		GetAdditionnalPostCond() const { return m_aAdditionalPostCond; }
		IBNode*				GetPreNode() const { return m_pPreNode;  }

		void*						GetUserData() { return m_pUserData; }
		void						SetUserData(void* pUserData) { m_pUserData = pUserData; }

		IBPlanner*					GetPlanner();

		void						Update();
		//void							Step();
		//void							Resolve();

		void						ResolveVariableFromPostCond(const IBFact* pPostCond);
		bool						CheckVariables() const;
		void						FinalizeCreation();

		bool						IsChildOf(const IBFact* pFact) const;

		void						Start();
		void						Interrupt();

		float						GetCost() const;
		float						GetTotalCost() const;

	protected:
		const class IBActionDef*	m_pDef;
		class IBPlanner*			m_pPlanner;

		IBA_State					m_eState;

		VarMap						m_aVariables;
		PotentialVarMap				m_aPotentialVariables;

		IBNode*				m_pPostNode;
		IBNode*				m_pPreNode;
		vector<IBFact*>				m_aPostCond; // ref to Node
		vector<IBFact*>				m_aAdditionalPostCond;

		void*						m_pUserData;
};

template <class T>
T* IBAction::GetVariable(const string& name) const
{
	const IBObject* Obj = GetVariable(name);
	return (Obj != nullptr ? (T*)Obj->GetUserData() : nullptr);
}


#endif
