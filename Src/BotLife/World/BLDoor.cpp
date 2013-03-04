#include "BLDoor.h"
#include "GUtils.h"



BLDoor::BLDoor(BLWorld& oWorld, const string& name, Dir eDir, const Vector2& pos)
	: BLProp_FB(oWorld, name, DATA_DIR "/Test/Door.png", 1, 4, pos)
	, m_eDir(eDir)
{
	SetCurrent((eDir)*2);
	m_bIsBlock = false;
	m_bIsPickable = false;
	m_bIsMovable = false;
}


BLDoor::~BLDoor()
{
}

