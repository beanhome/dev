#include "BLProp.h"
#include "Canvas.h"
#include "Image.h"
#include "BLWorld.h"
#include "GEngine.h"



BLProp::BLProp(BLWorld& oWorld, const string& name, const Vector2& pos)
	: BLObject(name, pos)
	, m_oWorld(oWorld)
	, m_bVisible(true)
	, m_pImage(NULL)
	, m_bIsBlock(false)
	, m_bIsPickable(false)
	, m_bIsMovable(false)
{
	SetPos(pos);
	m_oWorld.GetGrid().GetCase(pos).SetProp(this);
}


BLProp::~BLProp()
{
}


void BLProp::SetPos(const Vector2& p)
{
	BLObject::SetPos(p);

	SetLoc(GetPos().x * m_oWorld.GetGridSize() + m_oWorld.GetGridSize()/2, GetPos().y * m_oWorld.GetGridSize() + m_oWorld.GetGridSize()/2);
}

void BLProp::SetLoc(float x, float y)
{
	if (m_pImage != NULL)
		m_pImage->SetPos((sint16)x, (sint16)y);
}



const ImageResource* BLProp::GetImageResource() const
{
	return (m_pImage != NULL ? m_pImage->GetResource() : NULL);
}

void BLProp::Draw() const
{
	if (m_bVisible && m_pImage != NULL)
		m_pImage->Draw();
}


