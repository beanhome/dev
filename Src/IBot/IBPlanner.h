#ifndef __IBPLANNER_H__
#define __IBPLANNER_H__

#include "Utils.h"
#include "IBFactLibrary.h"
#include "IBActionLibrary.h"
#include "IBFact.h"

class IBFactDef;

class IBPlanner
{
	public:
		IBPlanner();
		virtual ~IBPlanner();

	public:
		void					InitFactLibrary();
		void					InitActionLibrary();

		void					AddGoal(const string& name);
		void					AddGoal(const string& name, void* pUserData);
		void					AddGoal(const string& name, void* pUserData1, void* pUserData2);
		void					AddGoal(const string& name, void* pUserData1, void* pUserData2, void* pUserData3);

		IBFactDef*				GetFactDef(const string& name) { return m_oFactLibrary.GetFactDef(name); }

		int						Step();

	private:
		IBFactLibrary			m_oFactLibrary;
		IBActionLibrary			m_oActionLibrary;

		set<IBFactDef*>			m_aGoalsDef;
		
		FactSet					m_aGoals;
};

#endif
