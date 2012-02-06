#ifndef __IBFACT_H__
#define __IBFACT_H__

#include "Utils.h"

#include "IBFactDef.h"

class IBFact
{
	public:
		IBFact();
		virtual ~IBFact();

		bool				IsTrue() { return Test() == IBF_OK; }

	protected:
		IBF_Result			Test() { return m_pDef->Test(); }

	private:
		IBFactDef*			m_pDef;
};

#endif
