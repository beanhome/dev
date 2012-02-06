#ifndef __IBPLANNER_H__
#define __IBPLANNER_H__

#include "Utils.h"
#include "IBFactLibrary.h"
#include "IBActionLibrary.h"

class IBFactDef;
class IBFact;

class IBPlanner
{
	public:
		IBPlanner();
		virtual ~IBPlanner();

		void					InitFactLibrary();
		void					InitActionLibrary();

		void					AddGoal(IBFactDef* def);

		IBFactDef*				GetFactDef(const string& name) { return m_oFactLibrary.GetFactDef(name); }

		int						Step();

	private:
		IBFactLibrary			m_oFactLibrary;
		IBActionLibrary			m_oActionLibrary;

		set<IBFactDef*>			m_aGoalsDef;
		
		set<IBFact*>			m_aGoals;
		
};

#endif
