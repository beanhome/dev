#ifndef __IBFACTDEF_BOOL_H__
#define __IBFACTDEF_BOOL_H__

#include "Utils.h"

#include "Fact/IBFactDef.h"

class IBFactDef_Bool : public IBFactDef
{
	public:
		IBFactDef_Bool(const string& name, IBPlanner* pPlanner);
		virtual ~IBFactDef_Bool();

		//virtual string				GetVariableData(uint i) const override;
		virtual IBF_Result			Test(const class IBFact* pFact) const override;


	private:
};

#endif
