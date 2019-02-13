#ifndef __IBFACTDEF_TRUE_H__
#define __IBFACTDEF_TRUE_H__

#include "Utils.h"

#include "Fact/IBFactDef.h"

class IBFactDef_True : public IBFactDef
{
	public:
		IBFactDef_True(const string& name, IBPlanner* pPlanner);
		virtual ~IBFactDef_True();

		//virtual string				GetVariableData(uint i) const override;
		virtual IBF_Result			Test(const class IBFact* pFact) const override;
};

#endif
