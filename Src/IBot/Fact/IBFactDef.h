#ifndef __IBFACTDEF_H__
#define __IBFACTDEF_H__

#include "Utils.h"

class IBFact;

enum IBF_Result
{
	IBF_OK,
	IBF_FAIL
};

class IBFactDef
{
	public:
		IBFactDef();
		virtual ~IBFactDef();

		virtual IBFact* Instanciate() = 0;
		virtual IBFact* Instanciate(void* pUserData1) = 0;
		virtual IBFact* Instanciate(void* pUserData1, void* pUserData2) = 0;
		virtual IBFact* Instanciate(void* pUserData1, void* pUserData2, void* pUserData3) = 0;

	public:
		virtual IBF_Result			Test() = 0;

	private:
		
};

#endif
