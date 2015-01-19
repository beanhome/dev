// WEditText.cpp


#include "GEngine.h"
#include "WEditText.h"
#include "Image.h"
#include "Event.h"

WEditText::WEditText(CanvasBase& oParent, WEditText::Desc oDesc, sint32 id, const string& sName)
	: WText(oParent, oDesc, id, sName)
	, m_bEdit(false)
{
	Init();
}

WEditText::WEditText(Widget& oParent, WEditText::Desc oDesc, sint32 id, const string& sName)
	: WText(oParent, oDesc, id, sName)
	, m_bEdit(false)
{
	Init();
}

void WEditText::Init()
{
	WText::Init();

	m_iLineIndex = 0;
	m_iCharIndex = 0;
}


WEditText::~WEditText()
{
}

void WEditText::SetLineIndex(sint32 iIndex)
{
	m_iLineIndex = 0;
	m_iCharIndex = iIndex;

	for (uint32 i=0 ; i<m_aLine.size() ; ++i)
	{
		if (m_iCharIndex > (sint32)m_aLine[i].length())
		{
			m_iCharIndex -= m_aLine[i].length();
		}
		else
		{
			m_iLineIndex = i;
			break;
		}
	}
}

sint32 WEditText::GetLineIndex() const
{
	sint32 iIndex = 0;

	for (sint32 i=0 ; i<m_iLineIndex ; ++i)
		iIndex += m_aLine[i].length();

	iIndex += m_iCharIndex;

	return iIndex;
}

void WEditText::ToLeft()
{
	if (m_iCharIndex == 0)
	{
		if (m_iLineIndex != 0)
		{
			m_iLineIndex--;
			m_iCharIndex = m_aLine[m_iLineIndex].length();
			if (m_aLine[m_iLineIndex][m_iCharIndex-1] == '\n')
				m_iCharIndex--;
		}
	}
	else
	{
		m_iCharIndex--;
	}
}

void WEditText::ToRight()
{
	if (m_iCharIndex >= m_aLine[m_iLineIndex].length()
	 || m_aLine[m_iLineIndex][m_iCharIndex] == '\n')
	{
		if (m_iLineIndex != m_aLine.size()-1)
		{
			m_iLineIndex++;
			m_iCharIndex = 0;
		}
	}
	else
	{
		m_iCharIndex++;
	}
}

void WEditText::ToUp()
{
	if (m_iLineIndex > 0)
	{
		m_iLineIndex--;
		m_iCharIndex = std::min<sint32>(m_iCharIndex, m_aLine[m_iLineIndex].length());
	}
}

void WEditText::ToDown()
{
	if (m_iLineIndex < (sint32)m_aLine.size()-1)
	{
		m_iLineIndex++;
		m_iCharIndex = std::min<sint32>(m_iCharIndex, m_aLine[m_iLineIndex].length());
	}
}

void WEditText::ToHome()
{
	m_iCharIndex = 0;
}

void WEditText::ToEnd()
{
	m_iCharIndex = m_aLine[m_iLineIndex].length();
	if (m_aLine[m_iLineIndex][m_iCharIndex-1] == '\n')
		m_iCharIndex--;
}



void WEditText::Draw() const
{
	WText::Draw();

	if (!m_bEdit)
		return;

	uint16 w = GetWidth();
	uint16 h = GetHeight();
	sint32 tx, ty, lw, lh, ltw, lth;
	uint16 th = m_pFont->GetLineSkip()*(m_aDrawLine.size()-1) + m_pFont->GetSize();

	TextSize(lw, lh, m_oDesc.sFontPath, m_oDesc.size, m_aDrawLine[m_iLineIndex].c_str());

	switch (m_oDesc.eAlign)
	{
		case LeftTop:		tx = 0;			ty = 0;			/*ty = 0;		*/	break;
		case LeftCenter:	tx = 0;			ty = (h-th)/2;	/*ty = h/2-th/2;*/	break;
		case LeftBottom:	tx = 0;			ty = h - th;	/*ty = h-th;	*/	break;
		case CenterTop:		tx = w/2-lw/2;	ty = 0;			/*ty = 0;		*/	break;
		case Center:		tx = w/2-lw/2;	ty = (h-th)/2;	/*ty = h/2-th/2;*/	break;
		case CenterBottom:	tx = w/2-lw/2;	ty = h - th;	/*ty = h-th;	*/	break;
		case RightTop:		tx = w-lw;		ty = 0;			/*ty = 0;		*/	break;
		case RightCenter:	tx = w-lw;		ty = (h-th)/2;	/*ty = h/2-th/2;*/	break;
		case RightBottom:	tx = w-lw;		ty = h - th;	/*ty = h-th;	*/	break;
	}

	TextSize(ltw, lth, m_oDesc.sFontPath, m_oDesc.size, m_aDrawLine[m_iLineIndex].substr(0, m_iCharIndex).c_str());

	sint32 ly = ty + (m_iLineIndex*m_pFont->GetLineSkip());
	sint32 lx = std::max<sint32>(0, tx + ltw - 1);

	DrawLine(lx, ly, lx, ly+lth-1, m_oDesc.r, m_oDesc.g, m_oDesc.b);
}

void WEditText::OnFocusEnter()
{
	m_bEdit = true;
}

void WEditText::OnFocusExit()
{
	m_bEdit = false;
}

void WEditText::CatchEvent(Event* pEvent)
{
	if (pEvent->IsKeyboard() && (pEvent->GetKeyboardEvent() == KeyDown || pEvent->GetKeyboardEvent() == KeyRepeat))
	{
		sint32 iIndex = GetLineIndex();

		switch (pEvent->GetKeyboardKey())
		{
			case KEY_RIGHT:	ToRight();	break;
			case KEY_LEFT:	ToLeft();	break;
			case KEY_UP:	ToUp();		break;
			case KEY_DOWN:	ToDown();	break;
			case KEY_HOME:	ToHome();	break;
			case KEY_END:	ToEnd();	break;
			
			case KEY_DELETE:
				m_oDesc.sText.erase(iIndex, 1);
				OnTextChanged();
				break;

			case KEY_BACKSPACE:
				if (iIndex > 0)
				{
					iIndex--;
					m_oDesc.sText.erase(iIndex, 1);
					OnTextChanged();
					SetLineIndex(iIndex);
					if (m_aLine[m_iLineIndex][m_iCharIndex-1] == '\n')
						m_iCharIndex--;
				}
				break;

			case KEY_ENTER:
				m_oDesc.sText.insert(iIndex++, 1, '\n');
				OnTextChanged();
				SetLineIndex(iIndex);
				ToRight();
				break;

			default:
			{
				char ch = (char)pEvent->GetKeyboardChar(); // TODO unicode
				if (isprint(ch))
				{
					m_oDesc.sText.insert(iIndex++, 1, ch);
					OnTextChanged();
					SetLineIndex(iIndex);
				}
			}
		}

		{
			string str = m_oDesc.sText;

			for (uint i=0 ; i<str.length() ; ++i)
				if (str[i] == '\n')
					str[i]='*';

			iIndex = GetLineIndex();

			LOG("_%s_%s_\n", str.substr(0, iIndex).c_str(), str.substr(iIndex, str.length() - iIndex).c_str());
		}
	}
}

void WEditText::OnTextChanged()
{
	//sint32 iIndex = GetLineIndex();

	WText::OnTextChanged();

	//SetLineIndex(iIndex);
}

