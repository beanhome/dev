#ifndef __IBACTIONLIBRARY_H__
#define __IBACTIONLIBRARY_H__

#include "Utils.h"

class IBActionDef;

typedef map<string, IBActionDef*>  ActionDefMap;
typedef pair<string, IBActionDef*>  ActionDefPair;

class IBActionLibrary
{
	public:
		IBActionLibrary();
		virtual ~IBActionLibrary();

		void					RegisterActionDef(const string& name, IBActionDef* pActionDef);

		IBActionDef*			GetActionDef(const string& name);

	protected:

	private:
		ActionDefMap			m_oMap;
};

#endif
