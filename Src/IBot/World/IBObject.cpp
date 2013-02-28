#include "IBObject.h"


IBObject::IBObject()
	: m_sName("")
	, m_sData("")
{
}

IBObject::IBObject(const string& name)
	: m_sName(name)
	, m_sData("")
{
}

IBObject::~IBObject()
{
}


void IBObject::Print() const
{
	LOG("Object : %s", m_sName.c_str());

	LOG("\n");
}
