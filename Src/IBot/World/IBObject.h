#ifndef __IBOBJECT_H__
#define __IBOBJECT_H__

#include "Utils.h"

class IBObject
{
	public:
		IBObject();
		IBObject(const string& name);
		virtual ~IBObject();

		const string& GetName() const { return m_sName; }
		void SetName(const string& name) { m_sName = name; }

		void  Print() const;

	private:
		string  m_sName;
};

#endif
