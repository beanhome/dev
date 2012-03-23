#ifndef __IBFACT1_H__
#define __IBFACT1_H__

#include "Utils.h"

#include "IBFact.h"
#include "IBFactDef1.h"


class IBFact1 : public IBFact
{
	public:
		IBFact1(IBFactDef1* pDef, void* pUserData);
		virtual ~IBFact1();

		bool				IsTrue() { return Test() == IBF_OK; }

	protected:
		IBF_Result			Test() { return m_pDef->Test(m_pUserData); }

	private:
		IBFactDef1*			m_pDef;
		void*				m_pUserData;
};

#endif
