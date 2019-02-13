#ifndef __BLOBJECT_H__
#define __BLOBJECT_H__

#include "Utils.h"
#include "Vector2.h"

class BLObject
{
	public:
		BLObject(const string& name);
		virtual ~BLObject();

		virtual BLObject* Clone() const { return new BLObject(*this); }

		const string& GetName() const { return m_sName; }
		void SetName(const string& name) { m_sName = name; }

		void  Print() const;

	protected:
		string m_sName;
};

#endif
