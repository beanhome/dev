#ifndef __IBFACTDEF_H__
#define __IBFACTDEF_H__

#include "Utils.h"
#include "Types.h"

class IBFactDef
{
	public:
		IBFactDef(const string& name, class IBPlanner* pPlanner);
		virtual ~IBFactDef();

		const string&				GetName() const;
		uint						GetDegree() const;

		const string&				GetVariableName(uint i) const;
		//virtual string				GetVariableData(uint i) const = 0;

		class IBFact*				Instanciate(bool bInverted) const;
		class IBFact*				Instanciate(bool bInverted, class IBWorldChange* pWorldChange) const;
		class IBFact*				Instanciate(bool bInverted, class IBWorldChange* pWorldChange, const vector<IBObject>& aUserData) const;

		// Must return state of the fact: true or false
		virtual IBF_Result			Test(const class IBFact* pFact) const = 0;
		virtual bool				HasSameVariables(const class IBFact* pA, const class IBFact* pB) const;

	protected:
		void						AddVariable(const string& name);

	private:
		string						m_sName;
		vector<string>				m_aVarNames;
	
	protected:
		class IBPlanner*			m_pPlanner;
};

#endif
