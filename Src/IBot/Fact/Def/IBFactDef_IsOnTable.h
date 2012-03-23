#ifndef __IBFACTDEF_ISONTABLE_BOOL_H__
#define __IBFACTDEF_ISONTABLE_BOOL_H__

#include "Utils.h"

#include "Fact/IBFactDef1.h"

class IBFactDef_IsOnTable : public IBFactDef1
{
	public:
		IBFactDef_IsOnTable();
		virtual ~IBFactDef_IsOnTable();

		IBF_Result	Test(void* pUserData2);

	private:
};

#endif
