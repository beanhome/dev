#ifndef __IBACTIONLIBRARY_H__
#define __IBACTIONLIBRARY_H__

#include "Utils.h"

typedef map<string, class IBActionDef*>  ActionDefMap;
typedef pair<string, class IBActionDef*>  ActionDefPair;
typedef set<class IBActionDef*>  ActionDefSet;

class IBActionLibrary
{
	public:
		IBActionLibrary();
		virtual ~IBActionLibrary();

		void						RegisterActionDef(const string& name, class IBActionDef* pActionDef);

		class IBActionDef*		GetActionDef(const string& name) const;
		class IBActionDef*		FindActionDef(const string& factname) const;
		//class IBAction*			FindActionDef(class IBFact* pFact) const;

		const ActionDefSet&		GetAllActionDef() const;

	protected:

	private:
		ActionDefMap			m_oMap;
		ActionDefSet			m_oSet;
};

#endif
