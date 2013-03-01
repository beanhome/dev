#ifndef __IBOBJECT_H__
#define __IBOBJECT_H__

#include "Utils.h"

class IBFact;

class IBObject
{
	public:
		IBObject(const string& name, bool bInstance = false);
		virtual ~IBObject();

		const string&		GetName() const { return m_sName; }
		void				SetName(const string& name) { m_sName = name; }

		const string&		GetData() const { FormatData(); return m_sData; }

		bool				IsInstance() const { return m_bInstance; }
		void				SetOwner(IBFact* pFactOwner) { m_pFactOwner = pFactOwner; }
		IBFact*				GetOwner() const { return m_pFactOwner; }

		void				Print() const;

	protected:
		virtual void		FormatData() const = 0;

	protected:
		string				m_sName;
		mutable string		m_sData;
		bool				m_bInstance;
		IBFact*				m_pFactOwner;
};

#endif
