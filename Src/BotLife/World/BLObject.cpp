#include "BLObject.h"
#include "Vector2.h"


BLObject::BLObject(const string& name)
	: m_sName(name)
{
}

BLObject::~BLObject()
{
}

void BLObject::Print() const
{
	LOG("Object : %s", GetName().c_str());
	LOG("\n");
}
