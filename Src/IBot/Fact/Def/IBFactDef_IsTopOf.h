#ifndef __IBFACTDEF_ISTOPOF_BOOL_H__
#define __IBFACTDEF_ISTOPOF_BOOL_H__

#include "Utils.h"

#include "Fact/IBFactDef2.h"

class IBFactDef_IsTopOf : public IBFactDef2
{
	public:
		IBFactDef_IsTopOf();
		virtual ~IBFactDef_IsTopOf();

		IBF_Result			Test(void* pUserData1, void* pUserData2);

	private:
};

#endif
