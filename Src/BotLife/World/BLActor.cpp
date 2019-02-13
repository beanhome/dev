#include "BLActor.h"
#include "Vector2.h"


BLActor::BLActor(const string& name)
	: BLObject(name)
{
}

BLActor::BLActor(const string& name, const Vector2& pos)
	: BLObject(name)
	, m_vPos(pos)
{
}

BLActor::~BLActor()
{
}

void BLActor::Print() const
{
	LOG("Object : %s (%d %d)", GetName().c_str(), m_vPos.x, m_vPos.y);
	LOG("\n");
}
