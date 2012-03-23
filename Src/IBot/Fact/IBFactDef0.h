#ifndef __IBFACTDEF0_H__
#define __IBFACTDEF0_H__

#include "Utils.h"
#include "IBFactDef.h"

class IBFactDef0 : public IBFactDef
{
	public:
		IBFactDef0();
		virtual ~IBFactDef0();

		IBFact* Instanciate();
		IBFact* Instanciate(void* pUserData1) { assert(false); return NULL; }
		IBFact* Instanciate(void* pUserData1, void* pUserData2) { assert(false); return NULL; }
		IBFact* Instanciate(void* pUserData1, void* pUserData2, void* pUserData3) { assert(false); return NULL; }

	public:
		//virtual IBF_Result			Test() = 0;

	private:
		
};

#endif
