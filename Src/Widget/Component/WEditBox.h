
#ifndef __WEDITBOX_H__
#define __WEDITBOX_H__

#include "Utils.h"
#include "WSimpleWindow.h"
#include "WText.h"

class ImageResource;

class WEditBox : public WSimpleWindow
{
public:
	struct Desc
	{
		const char* sImgPath;
		sint32 iChildArea_Margin;

		WText::Desc oTextDesc;

		Desc(const char* _sImgPath, sint32 margin, const string& _sInitText, uint16 _size = 12, ETextAlign _eAlign = LeftTop, uint8 _r = 255, uint8 _g = 255, uint8 _b = 255, const char* _sFontPath="")
			: sImgPath(_sImgPath), iChildArea_Margin(margin), oTextDesc(_sInitText, _size, _eAlign, _r, _g, _b, _sFontPath)
		{}
	};

public:
	WEditBox(CanvasBase& oParent, WEditBox::Desc oDesc, sint32 id = -1, const string& sName = "unknow");
	WEditBox(Widget& oParent, WEditBox::Desc oDesc, sint32 id = -1, const string& sName = "unknow");
	void Init();

	~WEditBox();

private:
	Desc m_oDesc;
	sint32 m_iIndex;
};

#endif
