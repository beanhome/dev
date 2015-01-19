
#ifndef __WSIMPLEWINDOW_H__
#define __WSIMPLEWINDOW_H__

#include "Widget.h"

class ImageResource;

class WSimpleWindow : public Widget
{
public:
	struct Desc
	{
		const char* sPath;
		sint32 iChildArea_Margin;

		Desc(const char* _sPath, sint32 m)
			: sPath(_sPath), iChildArea_Margin(m)
		{}
	};

public:
	WSimpleWindow(CanvasBase& oParent, WSimpleWindow::Desc oDesc, sint32 id = -1, const string& sName = "unknow");
	WSimpleWindow(Widget& oParent, WSimpleWindow::Desc oDesc, sint32 id = -1, const string& sName = "unknow");
	void Init();

	~WSimpleWindow();

public:
	sint32 GetAutoWidth() override;
	sint32 GetAutoHeight() override;

	void Draw() const override;

	Widget* GetChild(uint32 id) override;
	const Widget* GetChild(uint32 id) const override;

protected:
	virtual Widget* GetParentRef() { return (m_pChildArea != NULL ? m_pChildArea : this); }
	void InsertChild(Widget* pChild) override;

private:
	void DrawPart(ImageResource* res, sint32 x, sint32 y, uint16 w, uint16 h) const;

protected:
	Widget* m_pChildArea;

private:
	Desc m_oDesc;
	ImageResource* m_pImageResource;
};

#endif

