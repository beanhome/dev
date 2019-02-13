#include "IBObject.h"

IBObject::IBObject()
	: m_sName()
	, m_pUserData(nullptr)
{
}

IBObject::IBObject(const char* name, void* data)
	: m_sName(name)
	, m_pUserData(data)
{
}

IBObject::IBObject(const string& name, void* data)
	: m_sName(name)
	, m_pUserData(data)
{
}


IBObject::~IBObject()
{
}

bool IBObject::operator==(const IBObject& other) const
{
	return (m_pUserData == other.m_pUserData);
}

bool IBObject::operator!=(const IBObject& other) const
{
	return !(this->operator==(other));
}

const string& IBObject::GetName() const
{
	return m_sName;
}

void	 IBObject::SetName(const string& name)
{
	m_sName = name;
}

void* IBObject::GetUserData() const
{
	return m_pUserData;
}
void IBObject::SetUserData(void* UserData)
{
	m_pUserData = UserData;
}

void IBObject::Print() const
{
	LOG("Object : %s", m_sName.c_str());

	LOG("\n");
}
