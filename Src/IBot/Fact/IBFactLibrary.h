#ifndef __IBFACTLIBRARY_H__
#define __IBFACTLIBRARY_H__

#include "Utils.h"

typedef map<string, class IBFactDef*>  FactDefMap;
typedef pair<string, class IBFactDef*>  FactDefPair;

class IBFactLibrary
{
	public:
		IBFactLibrary();
		virtual ~IBFactLibrary();

		void					RegisterFactDef(const string& name, class IBFactDef* pFactDef);

		class IBFactDef*		GetFactDef(const string& name) const;

	protected:

	private:
		FactDefMap			m_oMap;
};

#endif
