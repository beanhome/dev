#include "IBTreeBox_String.h"

#include "Canvas.h"
#include "Color.h"
#include "Utils.h"


IBTreeBox_String::IBTreeBox_String(Canvas& oCanvas, IBTreeBox* pParent)
	: IBTreeBox(oCanvas, pParent)
	, m_pFont(nullptr)
	, m_oColor(Color::White)
{
}

IBTreeBox_String::~IBTreeBox_String()
{
}

void IBTreeBox_String::Draw() const
{
	m_oCanvas.Print(m_iPosX, m_iPosY, m_pFont, ETextAlign::LeftTop, m_oColor, m_sString.c_str());
}

void IBTreeBox_String::ComputeSize()
{
	m_oCanvas.TextSize(m_iWidth, m_iHeight, m_pFont, m_sString.c_str());
}
