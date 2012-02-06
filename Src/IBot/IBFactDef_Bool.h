#ifndef __IBFACTDEF_BOOL_H__
#define __IBFACTDEF_BOOL_H__

#include "Utils.h"

#include "IBFactDataDef.h"

class IBFactDef_Bool : public IBFactDataDef
{
	public:
		IBFactDef_Bool();
		virtual ~IBFactDef_Bool();

		IBF_Result			Test(void* pUserData) { return (*((bool*)pUserData) ? IBF_OK : IBF_FAIL); } 

	private:
};

#endif
