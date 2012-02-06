#ifndef __IBACTIONDEF_H__
#define __IBACTIONDEF_H__

#include "Utils.h"

class IBPlanner;
class IBFactDef;

class IBActionDef
{
	public:
		IBActionDef(IBPlanner* pPlanner);
		virtual ~IBActionDef();

		virtual void		Define() = 0;

		void AddPreCondition(const string& name);
		void AddPostCondition(const string& name);

	private:
		IBPlanner*				m_pPlanner;

		vector<IBFactDef*>		m_aPreCondDef;
		vector<IBFactDef*>		m_aPostCondDef;

};

#endif
