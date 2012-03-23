#ifndef __IBFACT_H__
#define __IBFACT_H__

#include "Utils.h"

#include "IBFactDef.h"

class IBFact
{
	public:
		IBFact();
		virtual ~IBFact();

		virtual bool		IsTrue() = 0;

	public:
		virtual IBF_Result	Test() = 0;

	private:
};

typedef set<IBFact*>	FactSet;

#endif
