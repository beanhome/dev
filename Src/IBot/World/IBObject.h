#ifndef __IBOBJECT_H__
#define __IBOBJECT_H__

#include "Utils.h"

class IBObject
{
	public:
		IBObject();
		IBObject(const char* name, void* data);
		IBObject(const string& name, void* data);

		virtual ~IBObject();

		bool operator==(const IBObject& other) const;
		bool operator!=(const IBObject& other) const;

		const string&			GetName() const;
		void					SetName(const string& name);

		void*					GetUserData() const;
		void					SetUserData(void* UserData);

		void					Print() const;

	protected:
		string					m_sName;
		void*					m_pUserData;
};

#endif
