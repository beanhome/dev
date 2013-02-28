#ifndef __IBOBJECT_H__
#define __IBOBJECT_H__

#include "Utils.h"

class IBObject
{
	public:
		IBObject();
		IBObject(const string& name);
		virtual ~IBObject();

		const string&		GetName() const { return m_sName; }
		void				SetName(const string& name) { m_sName = name; }

		const string&		GetData() const { FormatData(); return m_sData; }

		void				Print() const;

	protected:
		virtual void		FormatData() const = 0;

	protected:
		string				m_sName;
		mutable string		m_sData;
};

#endif
