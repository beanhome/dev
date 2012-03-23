#ifndef __IBFACTLIBRARY_H__
#define __IBFACTLIBRARY_H__

#include "Utils.h"

class IBFactDef;

typedef map<string, IBFactDef*>  FactDefMap;
typedef pair<string, IBFactDef*>  FactDefPair;

class IBFactLibrary
{
	public:
		IBFactLibrary();
		virtual ~IBFactLibrary();

		void				RegisterFactDef(const string& name, IBFactDef* pFactDef);

		IBFactDef*			GetFactDef(const string& name);

	protected:

	private:
		FactDefMap			m_oMap;
};

#endif
