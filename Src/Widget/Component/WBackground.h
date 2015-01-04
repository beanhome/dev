
#ifndef __WBACKGROUND_H__
#define __WBACKGROUND_H__

#include "Widget.h"

class WBackground : public Widget
{
public:
	struct Desc
	{
		const char* sPath;
		Desc(const char* path) : sPath(path) {}
	};

public:
	WBackground(CanvasBase& oParent, const Desc& oDesc, sint32 id = -1, const string& sName = "unknow");
	WBackground(Widget& oParent, const Desc& oDesc, sint32 id = -1, const string& sName = "unknow");
	void Init();

	~WBackground();

public:

	void Draw() const override;

private:
	Desc m_oDesc;
	ImageResource* m_pImageResource;
};

#endif

