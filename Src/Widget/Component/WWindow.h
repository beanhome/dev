
#ifndef __WWINDOW_H__
#define __WWINDOW_H__

#include "Widget.h"

class ImageResource;

namespace WinPart
{
	enum WinPart { TL, TC, TR, CL, CC, CR, BL, BC, BR, Num };
	static const char* ToString[Num] = { "TL", "TC", "TR", "CL", "CC", "CR", "BL", "BC", "BR" };
}

class WWindow : public Widget
{
public:
	struct Desc
	{
		const char* sBasePath;
		const char* sExt;
		sint32 m_iChildArea_LeftMargin;
		sint32 m_iChildArea_RightMargin;
		sint32 m_iChildArea_TopMargin;
		sint32 m_iChildArea_BottomMargin;

		Desc(const char* _sBasePath, const char* _sExt, sint32 alm, sint32 arm, sint32 atm, sint32 abm)
			: sBasePath(_sBasePath), sExt(_sExt), m_iChildArea_LeftMargin(alm), m_iChildArea_RightMargin(arm), m_iChildArea_TopMargin(atm), m_iChildArea_BottomMargin(abm)
		{}
	};

public:
	WWindow(CanvasBase& oParent, WWindow::Desc oDesc, sint32 id = -1, const string& sName = "unknow");
	WWindow(Widget& oParent, WWindow::Desc oDesc, sint32 id = -1, const string& sName = "unknow");
	void Init();

	~WWindow();

public:
	sint32 GetAutoWidth() override;
	sint32 GetAutoHeight() override;

	void Draw() const override;

	Widget* GetChild(uint32 id) override;
	const Widget* GetChild(uint32 id) const override;

protected:
	virtual Widget* GetParentRef() { return m_pChildArea; }
	void InsertChild(Widget* pChild) override;

private:
	void DrawPart(ImageResource* res, sint32 x, sint32 y, uint16 w, uint16 h) const;

private:
	Desc m_oDesc;
	ImageResource* m_pImageResource[WinPart::Num];
	Widget* m_pChildArea;
};

#endif

