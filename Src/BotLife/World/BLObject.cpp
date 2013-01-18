#include "BLObject.h"


BLObject::BLObject()
	: IBObject()
	, m_vPos("Pos")
{
}

BLObject::BLObject(const string& name)
	: IBObject(name)
	, m_vPos("Pos")
{
}

BLObject::BLObject(const Vector2& pos)
	: IBObject()
	, m_vPos("Pos", pos)
{
}

BLObject::BLObject(const string& name, const Vector2& pos)
	: IBObject(name)
	, m_vPos("Pos", pos)
{
}


BLObject::~BLObject()
{
}


void BLObject::Print() const
{
	LOG("Object : %s (%d %d)", GetName().c_str(), m_vPos.x, m_vPos.y);
	LOG("\n");
}
