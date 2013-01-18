#include "BLProp.h"
#include "Canvas.h"
#include "Image.h"
#include "BLWorld.h"
#include "GEngine.h"



BLProp::BLProp(BLWorld& oWorld, const string& name, const Vector2& pos)
	: BLObject(name, pos)
	, m_oWorld(oWorld)
	, m_bVisible(true)
{
	const Canvas& oCanvas = m_oWorld.GetCanvas();

	m_pImage = new Image(oCanvas, oCanvas.GetGEngine()->GetImageResource(DATA_DIR "/Test/Mine.png"));
	m_pImage->SetPos(GetPos().x * m_oWorld.GetGridSize() + m_oWorld.GetGridSize()/2, GetPos().y * m_oWorld.GetGridSize() + m_oWorld.GetGridSize()/2);
}


BLProp::~BLProp()
{
	delete m_pImage;
}

const ImageResource* BLProp::GetImageResource() const
{
	return m_pImage->GetResource();
}


void BLProp::Draw()
{
	if (m_bVisible)
		m_pImage->Draw();
}


