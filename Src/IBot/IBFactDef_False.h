#ifndef __IBFACTDEF_FALSE_H__
#define __IBFACTDEF_FALSE_H__

#include "Utils.h"

#include "IBFactDef0.h"

class IBFactDef_False : public IBFactDef0
{
	public:
		IBFactDef_False();
		virtual ~IBFactDef_False();

		IBF_Result			Test() { return IBF_FAIL; }
};

#endif
