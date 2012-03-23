#ifndef __IBFACT0_H__
#define __IBFACT0_H__

#include "Utils.h"

#include "IBFact.h"

#include "IBFactDef.h"

class IBFact0 : public IBFact
{
	public:
		IBFact0(IBFactDef* pDef);
		virtual ~IBFact0();

		bool				IsTrue() { return Test() == IBF_OK; }

	protected:
		IBF_Result			Test() { return m_pDef->Test(); }

	private:
		IBFactDef*			m_pDef;
};

#endif
