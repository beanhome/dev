
#ifndef __WTEXT_H__
#define __WTEXT_H__

#include "Utils.h"
#include "Widget.h"

class ImageResource;
class FontResource;

class WText : public Widget
{
public:
	struct Desc
	{
		const char* sFontPath;

		uint16 size;

		ETextAlign eAlign;

		uint8 r;
		uint8 g;
		uint8 b;

		string sText;

		Desc(const string& _sText, uint16 _size = 12, ETextAlign _eAlign = LeftTop, uint8 _r = 128, uint8 _g = 128, uint8 _b = 128, const char* _sFontPath="")
			: sText(_sText), size(_size), eAlign(_eAlign), r(_r), g(_g), b(_b), sFontPath(_sFontPath)
		{}
	};

public:
	WText(CanvasBase& oParent, WText::Desc oDesc, sint32 id = -1, const string& sName = "unknow");
	WText(Widget& oParent, WText::Desc oDesc, sint32 id = -1, const string& sName = "unknow");
	void Init();

	~WText();

public:
	sint32 GetAutoWidth() override;
	sint32 GetAutoHeight() override;

	void Draw() const override;

protected:
	void OnDimensionChanged(SideEnum::Type eSide) override;
	virtual void OnTextChanged();

private:
	void SliceText();

protected:
	Desc m_oDesc;
	FontResource* m_pFont;

	vector<string> m_aLine;
	vector<string> m_aDrawLine;

};

#endif

