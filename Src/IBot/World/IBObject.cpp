#include "IBObject.h"


IBObject::IBObject(const string& name, bool bInstance)
	: m_sName(name)
	, m_sData("")
	, m_bInstance(bInstance)
	, m_pFactOwner(NULL)
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
