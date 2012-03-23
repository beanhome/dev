#ifndef __IBFACTDEF2_H__
#define __IBFACTDEF2_H__

#include "Utils.h"

#include "IBFactDef1.h"

class IBFactDef2 : public IBFactDef1
{
	public:
		IBFactDef2();
		virtual ~IBFactDef2();

		IBFact* Instanciate() { assert(false); return NULL; }
		IBFact* Instanciate(void* pUserData1) { assert(false); return NULL; }
		IBFact* Instanciate(void* pUserData1, void* pUserData2);
		IBFact* Instanciate(void* pUserData1, void* pUserData2, void* pUserData3) { assert(false); return NULL; }

		virtual IBF_Result			Test() { assert(false); return IBF_FAIL; }
		virtual IBF_Result			Test(void* pUserData) { assert(false); return IBF_FAIL; }
		virtual IBF_Result			Test(void* pUserData1, void* pUserData2) = 0;

	private:
};

#endif
