#ifndef __IBACTION_H__
#define __IBACTION_H__

#include "Utils.h"

class IBFact;
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
		
		set<IBFact*>			m_aPreCond;
		set<IBFact*>			m_aPostCond;
};

#endif
