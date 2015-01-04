
#ifndef __WIMAGE_H__
#define __WIMAGE_H__

#include "Widget.h"

class ImageResource;

class WImage : public Widget
{
public:
	struct Desc
	{
		const char* sPath;
		Desc(const char* path) : sPath(path) {}
	};

public:
	WImage(CanvasBase& oParent, WImage::Desc oDesc, sint32 id = -1, const string& sName = "unknow");
	WImage(Widget& oParent, WImage::Desc oDesc, sint32 id = -1, const string& sName = "unknow");
	void Init();

	~WImage();

public:
	sint32 GetAutoWidth() override;
	sint32 GetAutoHeight() override;

	void Draw() const override;

private:
	Desc m_oDesc;
	ImageResource* m_pImageResource;

};

#endif

