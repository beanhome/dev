#include "IBPath.h"


IBPath::IBPath()
{
}

IBPath::IBPath(const string& name)
	: IBObject(name)
	, Path()
{
}

IBPath::IBPath(const Vector2& start, const deque<Vector2>& oPath)
	: IBObject()
	, Path(start, oPath)
{

}

IBPath::IBPath(const string& name, const Vector2& start, const deque<Vector2>& oPath)
	: IBObject(name)
	, Path(start, oPath)
{

}




IBPath::~IBPath()
{
}

void IBPath::FormatData() const
{
	m_sData = FormatString("(%d)", GetLength());
}

void IBPath::Print() const
{
	LOG("Path %s ", m_sName.c_str());
	Path::Print();
}
