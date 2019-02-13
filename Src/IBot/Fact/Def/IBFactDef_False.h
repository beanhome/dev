#ifndef __IBFACTDEF_FALSE_H__
#define __IBFACTDEF_FALSE_H__

#include "Utils.h"

#include "Fact/IBFactDef.h"

class IBFactDef_False : public IBFactDef
{
	public:
		IBFactDef_False(const string& name, IBPlanner* pPlanner);
		virtual ~IBFactDef_False();

		//virtual string				GetVariableData(uint i) const override;
		virtual IBF_Result			Test(const class IBFact* pFact) const override;
};

#endif
