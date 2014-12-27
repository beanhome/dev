
#ifndef __WIDGETCOMMON_H__
#define __WIDGETCOMMON_H__


namespace SideEnum
{
	enum Type
	{
		Left,
		Right,
		Top,
		Bottom,
		Num
	};

	static char* ToString[Num] = 
	{
		"Left",
		"Right",
		"Top",
		"Bottom"
	};
}

namespace WidgetDimState
{
	enum Type
	{
		Unknown,
		Process,
		Valid,
		Invalid,
		Num
	};

	static char* ToString[Num] =
	{
		"Unknow",
		"Process",
		"Valid",
		"Invalid"
	};
}

namespace WidgetReference
{
	enum Type
	{
		Parent,
		Self,
		Brother,
		Child,
		Num
	};

	static char* ToString[Num] =
	{
		"Parent",
		"Self",
		"Brother",
		"Child"
	};
}

namespace WidgetSelfReference
{
	enum Type
	{
		Auto,
		Fix,
		Num
	};

	static char* ToString[Num] =
	{
		"Auto",
		"Fix"
	};

}

#endif


