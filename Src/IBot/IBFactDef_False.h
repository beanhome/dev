#ifndef __IBFACTDEF_FALSE_H__
#define __IBFACTDEF_FALSE_H__

#include "Utils.h"

#include "IBFactDef.h"

class IBFactDef_False : public IBFactDef
{
	public:
		IBFactDef_False();
		virtual ~IBFactDef_False();

		IBF_Result			Test() { return IBF_FAIL; }
};

#endif
