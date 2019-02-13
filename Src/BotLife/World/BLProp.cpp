#include "BLProp.h"
#include "Canvas.h"
#include "Image.h"
#include "BLWorld.h"
#include "GEngine.h"



BLProp::BLProp(BLWorld& oWorld, const string& name, const Vector2& pos)
	: BLActor(name, pos)
	, m_oWorld(oWorld)
	, m_bVisible(true)
	, m_pImage(NULL)
{
	SetPos(pos);
	m_oWorld.GetGrid().GetCase(pos).SetProp(this);
}


BLProp::~BLProp()
{
}


void BLProp::SetPos(const Vector2& p)
{
	BLActor::SetPos(p);

	SetLoc((float)GetPos().x * m_oWorld.GetGridSize() + m_oWorld.GetGridSize()/2, (float)GetPos().y * m_oWorld.GetGridSize() + m_oWorld.GetGridSize()/2);
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


