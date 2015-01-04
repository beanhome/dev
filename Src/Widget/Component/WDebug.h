
#ifndef __WDEBUG_H__
#define __WDEBUG_H__

#include "Widget.h"

class WDebug : public Widget
{
public:
	struct Desc
	{
	};

public:
	WDebug(CanvasBase& oParent, const Desc& oDesc, sint32 id = -1, const string& sName = "unknow");
	WDebug(Widget& oParent, const Desc& oDesc, sint32 id = -1, const string& sName = "unknow");

	~WDebug();

public:

	void Draw() const override;

private:

	static Color s_oStateColor[WidgetDimState::Num];
};

#endif

