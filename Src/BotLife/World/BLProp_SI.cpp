#include "BLProp_SI.h"
#include "Canvas.h"
#include "Image.h"
#include "BLWorld.h"
#include "GEngine.h"



BLProp_SI::BLProp_SI(BLWorld& oWorld, const string& name, const char* img, const Vector2& pos)
	: BLProp(oWorld, name, pos)
{
	const Canvas& oCanvas = m_oWorld.GetCanvas();
	m_pImage = new Image(oCanvas, oCanvas.GetGEngine()->GetImageResource(img));

	SetPos(pos);
}


BLProp_SI::~BLProp_SI()
{
	delete m_pImage;
}
