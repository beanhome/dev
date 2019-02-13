#ifndef __IBFACTDEF_H__
#define __IBFACTDEF_H__

#include "Utils.h"
#include "Types.h"

class IBFactDef
{
	public:
		IBFactDef(const string& name, uint iDegree, class IBPlanner* pPlanner);
		virtual ~IBFactDef();

		const string&				GetName() const;
		uint							GetDegree() const;

		const string&				GetVariableName(uint i) const;
		//virtual string				GetVariableData(uint i) const = 0;

		class IBFact*				Instanciate(bool bInverted) const;
		class IBFact*				Instanciate(bool bInverted, class IBWorldChange* pWorldChange) const;
		class IBFact*				Instanciate(bool bInverted, class IBWorldChange* pWorldChange, const vector<IBObject>& aUserData) const;

		// Must return state of the fact: true or false
		virtual IBF_Result			Test(const class IBFact* pFact) const = 0;

	protected:
		void							AddVariable(const string& name);


	private:
		string						m_sName;
		uint							m_iDegree;
		vector<string>				m_aVarNames;
	
	protected:
		class IBPlanner*				m_pPlanner;
};

#endif
