#ifndef __IBFACTDEF1_H__
#define __IBFACTDEF1_H__

#include "Utils.h"

#include "IBFactDef.h"

class IBFactDef1 : public IBFactDef
{
	public:
		IBFactDef1();
		virtual ~IBFactDef1();

		IBFact* Instanciate() { assert(false); return NULL; }
		IBFact* Instanciate(void* pUserData1);
		IBFact* Instanciate(void* pUserData1, void* pUserData2) { assert(false); return NULL; }
		IBFact* Instanciate(void* pUserData1, void* pUserData2, void* pUserData3) { assert(false); return NULL; }

		virtual IBF_Result			Test() { assert(false); return IBF_FAIL; }
		virtual IBF_Result			Test(void* pUserData) = 0;

	private:
};

#endif
