#include "Path.h"

Path::Path()
{
}

Path::Path(const Vector2& start, vector<Vector2> oPath)
	: m_vStart(start)
	, m_vTarget(oPath.size() > 0 ? oPath[oPath.size()-1] : start)
	, m_aPath(oPath)
{}


vector<Vector2> Path::GetListInverse() const
{
	vector<Vector2> oPath;
	oPath.resize(m_aPath.size());

	if (m_aPath.size() > 0)
	{
		for (uint i=0 ; i<m_aPath.size()-1 ; ++i)
			oPath[i] = m_aPath[m_aPath.size()-i-2];
		oPath[oPath.size()-1] = m_vStart;
	}

	return oPath;
}

Path Path::GetInverse() const
{
	vector<Vector2> oPath;
	oPath.resize(m_aPath.size());

	if (m_aPath.size() > 0)
	{
		for (uint i=0 ; i<m_aPath.size()-1 ; ++i)
			oPath[i] = m_aPath[m_aPath.size()-i-2];
		oPath[oPath.size()-1] = m_vStart;
	}

	return Path(m_vTarget, oPath);
}



bool operator==(const Path& a, const Path& b)
{
	return (a.GetStart() == b.GetStart()
	     && a.GetTarget() == b.GetTarget()
		 && a.GetList() == b.GetList());
}

bool operator!=(const Path& a, const Path& b)
{
	return !operator==(a, b);
}

bool operator<(const Path& a, const Path& b)
{
	return (a.GetStart() < b.GetStart()
		|| (a.GetStart() == b.GetStart() && a.GetList().size() < b.GetList().size())
		|| (a.GetStart() == b.GetStart() && a.GetList().size() == b.GetList().size() && a.GetTarget() < b.GetTarget()));
}

bool operator<=(const Path& a, const Path& b)
{
	return (operator==(a, b) || operator<(a, b));
}

bool operator>(const Path& a, const Path& b)
{
	return !operator<=(a, b);
}

bool operator>=(const Path& a, const Path& b)
{
	return !operator<(a, b);
}

