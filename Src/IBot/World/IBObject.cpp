#include "IBObject.h"


IBObject::IBObject()
{
}

IBObject::IBObject(const string& name)
: m_sName(name)
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
