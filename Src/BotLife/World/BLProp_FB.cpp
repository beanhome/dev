#include "BLProp_FB.h"
#include "Canvas.h"
#include "Image.h"
#include "BLWorld.h"
#include "GEngine.h"
#include "ImageFlipBook.h"



BLProp_FB::BLProp_FB(BLWorld& oWorld, const string& name, const char* img, uint16 row, uint16 col, const Vector2& pos)
	: BLProp(oWorld, name, pos)
{
	const Canvas& oCanvas = m_oWorld.GetCanvas();
	m_pImage = new ImageFlipBook(oCanvas, oCanvas.GetGEngine()->GetImageResource(img), row, col);

	SetPos(pos);
	m_oWorld.GetGrid().GetCase(pos).SetProp(this);
}


BLProp_FB::~BLProp_FB()
{
	delete m_pImage;
}

void BLProp_FB::SetCurrent(sint16 i)
{
	ImageFlipBook* ifb = static_cast<ImageFlipBook*>(m_pImage);
	ifb->SetCurrent(i);
}
