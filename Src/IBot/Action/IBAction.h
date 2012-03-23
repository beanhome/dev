#ifndef __IBACTION_H__
#define __IBACTION_H__

#include "Utils.h"
#include "Fact/IBFact.h"

class IBActionDef;

class IBAction
{
	public:
		IBAction();
		virtual ~IBAction();

		bool Test();

		virtual void			Execute() {}

	private:
		IBActionDef*			m_pDef;
		
		FactSet					m_aPreCond;
		FactSet					m_aPostCond;
};

#endif
