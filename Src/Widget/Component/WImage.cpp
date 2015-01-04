// WImage.cpp

#include "GEngine.h"
#include "WImage.h"
#include "Image.h"

WImage::WImage(CanvasBase& oParent, WImage::Desc oDesc, sint32 id, const string& sName)
	: Widget(oParent, id, sName)
	, m_oDesc(oDesc)
{
	Init();
}

WImage::WImage(Widget& oParent, WImage::Desc oDesc, sint32 id, const string& sName)
	: Widget(oParent, id, sName)
	, m_oDesc(oDesc)
{
	Init();
}

void WImage::Init()
{
	string sPath= FormatString("%s%s", DATA_DIR, m_oDesc.sPath);
	m_pImageResource = GetGEngine()->GetImageResource(sPath.c_str());
}


WImage::~WImage()
{
}


void WImage::Draw() const
{
	DrawImage(*m_pImageResource, GetWidth()/2, GetHeight()/2, GetWidth(), GetHeight(), 0, 0, m_pImageResource->GetWidth(), m_pImageResource->GetHeight());

	Widget::Draw();
}

sint32 WImage::GetAutoWidth()
{
	return m_pImageResource->GetWidth();

}

sint32 WImage::GetAutoHeight()
{
	return m_pImageResource->GetHeight();
}
