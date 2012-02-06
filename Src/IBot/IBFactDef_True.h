#ifndef __IBFACTDEF_TRUE_H__
#define __IBFACTDEF_TRUE_H__

#include "Utils.h"

#include "IBFactDef.h"

class IBFactDef_True : public IBFactDef
{
	public:
		IBFactDef_True();
		virtual ~IBFactDef_True();

		IBF_Result			Test() { return IBF_OK; }
};

#endif
