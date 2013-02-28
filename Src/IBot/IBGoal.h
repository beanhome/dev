#ifndef __IBGOAL_H__
#define __IBGOAL_H__

#include "Utils.h"

class IBObject;

class IBGoal
{
	public:
		IBGoal(const char* name);
		IBGoal(const char* name, IBObject* pUserData);
		IBGoal(const char* name, IBObject* pUserData1, IBObject* pUserData2);
		IBGoal(const char* name, IBObject* pUserData1, IBObject* pUserData2, IBObject* pUserData3);

		IBGoal(const string& name);
		IBGoal(const string& name, IBObject* pUserData);
		IBGoal(const string& name, IBObject* pUserData1, IBObject* pUserData2);
		IBGoal(const string& name, IBObject* pUserData1, IBObject* pUserData2, IBObject* pUserData3);

		~IBGoal() {};

		const string& GetName() const { return m_sName; }
		string GetData() const;
		const vector<IBObject*>& GetUserData() const { return m_aUserData; }

	private:
		string					m_sName;
		vector<IBObject*>		m_aUserData;
};



#endif
