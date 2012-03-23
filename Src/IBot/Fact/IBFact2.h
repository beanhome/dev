#ifndef __IBFACT2_H__
#define __IBFACT2_H__

#include "Utils.h"

#include "IBFact.h"
#include "IBFactDef2.h"

class IBFact2 : public IBFact
{
	public:
		IBFact2(IBFactDef2* pDef, void* pUserData1, void* pUserData2);
		virtual ~IBFact2();

		bool				IsTrue() { return Test() == IBF_OK; }

	protected:
		IBF_Result			Test() { return m_pDef->Test(m_pUserData1, m_pUserData2); }

	private:
		IBFactDef2*			m_pDef;
		void*				m_pUserData1;
		void*				m_pUserData2;
};

#endif
