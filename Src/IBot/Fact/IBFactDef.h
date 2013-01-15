#ifndef __IBFACTDEF_H__
#define __IBFACTDEF_H__

#include "Utils.h"

class IBFact;
class IBPlanner;

enum IBF_Result
{
	IBF_OK,
	IBF_FAIL,
	IBF_UNKNOW,

	IBF_Result_MAX
};

extern char* IBF_ResultString[IBF_Result_MAX];

class IBFactDef
{
	public:
		IBFactDef(const string& name, uint iDegree, IBPlanner* pPlanner);
		virtual ~IBFactDef();

		const string&				GetName() const { return m_sName; }
		uint						GetDegree() const { return m_iDegree; }

		IBFact*						Instanciate() { vector<void*> aUserData; return Instanciate(aUserData); }
		IBFact*						Instanciate(vector<void*> aUserData);

		// Must return state of the fact: true or false
		IBF_Result					Test() { vector<void*> aUserData; return Test(aUserData); }
		virtual IBF_Result			Test(const vector<void*>& aUserData) = 0;
		
		// Find adequate object to match with the fact for the variables unfilled
		virtual void				ResolveVariable(vector<void*>& aUserData) {}

		virtual void				Print(const vector<void*>& aUserData, int tab) const;

	private:
		string						m_sName;
		uint						m_iDegree;
	
	protected:
		IBPlanner*					m_pPlanner;
};

#endif
