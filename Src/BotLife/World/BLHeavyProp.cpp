#include "BLHeavyProp.h"


BLHeavyProp::BLHeavyProp(BLWorld& oWorld, const string& name, const char* img, const Vector2& pos)
	: BLProp_SI(oWorld, name, img, pos)
{
	m_bIsBlock = true;
	m_bIsPickable = false;
	m_bIsMovable = true;
}

BLHeavyProp::~BLHeavyProp()
{
}

