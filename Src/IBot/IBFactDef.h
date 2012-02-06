#ifndef __IBFACTDEF_H__
#define __IBFACTDEF_H__

#include "Utils.h"

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

	public:
		virtual IBF_Result			Test() = 0;

	private:
		
};

#endif
