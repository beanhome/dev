#ifndef __IBFACTDATADEF_H__
#define __IBFACTDATADEF_H__

#include "Utils.h"

#include "IBFactDef.h"

class IBFactDataDef : public IBFactDef
{
	public:
		IBFactDataDef();
		virtual ~IBFactDataDef();

		virtual IBF_Result			Test() { assert(false); return IBF_FAIL; }
		virtual IBF_Result			Test(void* pUserData) = 0;

	private:
};

#endif
