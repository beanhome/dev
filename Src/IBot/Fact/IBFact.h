#ifndef __IBFACT_H__
#define __IBFACT_H__

#include "Utils.h"
#include "World/IBObject.h"
#include "IBCost.h"
#include "Types.h"


class IBFact
{
	public:
		friend class IBPlanner;
		friend class IBAction;
		friend class IBNode;

	protected:
		IBFact(const class IBFactDef* pDef, bool bInverted, const vector<class IBObject>& aVariables, class IBNode* pNodeOwner, IBPlanner* pPlanner);

	public:
		virtual ~IBFact();

	public:
		bool operator==(const IBFact& other) const;
		bool operator!=(const IBFact& other) const;
		bool IsEqual(const IBFact* other) const;
		bool IsOpposite(const IBFact* other) const;
		//bool IsCompatible(const IBFact* other) const;

		IBFact*							Clone() const;
		void							Destroy();

		const IBFactDef*				GetFactDef() const;

		bool							HasCauseAction() const;
		void							RemoveCauseAction(class IBAction* pAction);
		void							AddCauseAction(class IBAction* pAction);
		const ActionSet&				GetCauseAction() const;

		const VarMap&					GetVariables() const;
		const IBObject*					GetVariable(const string& str) const { return GetVariable(str.c_str()); }
		const IBObject*					GetVariable(const char* varname = nullptr) const;
		void							SetVariable(const IBObject& obj);
		void							SetVariable(const string& varname, const IBObject& obj);
		template<class T>
		T*								GetVariable(const char* varname = nullptr) const;

		bool							IsInverted() const { return m_bInverted;  }
		bool							IsTrue() const;
		int								GetCost() const;
		bool							IsImpossible() const;

		bool							IsResolvableBy(const class IBActionDef* pActionDef) const;
		void							Resolve(const IBPlanner* pPlanner);
		void							Update();
		void							ResolveVariableFromCond(const class IBAction* pAction, const struct IBFactCondDef& oCondDef);

	public:
		enum IBF_Result					Test() const;

	protected:
		class IBPlanner*				m_pPlanner;
		const class IBFactDef*			m_pDef;
		bool							m_bInverted;
		VarMap							m_aVariables;
		ActionSet						m_aCauseAction;
		class IBNode*					m_pNodeOwner;
};


template<class T>
T* IBFact::GetVariable(const char* varname) const
{
	const IBObject* var = GetVariable(varname);
	return static_cast<T*>(var != nullptr ? var->GetUserData() : nullptr);
}

#endif
