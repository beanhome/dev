#include "Path.h"
#include "Utils.h"

Path::Path()
	: m_bInitialized(false)
{}

Path::Path(const Vector2& start, const deque<Vector2>& oPath)
	: m_bInitialized(true)
	, m_vStart(start)
	, m_aPath(oPath)
{}

Path::Path(const Path& oOrig)
	: m_bInitialized(oOrig.m_bInitialized)
	, m_vStart(oOrig.m_vStart)
	, m_aPath(oOrig.m_aPath)
{}

void Path::PushBack(const Vector2& pos)
{
	if (m_bInitialized)
	{
		m_aPath.push_back(pos);
	}
	else
	{
		ASSERT(m_aPath.size() == 0);
		m_vStart = pos;
		m_bInitialized = true;
	}
}
void Path::PushFront(const Vector2& pos)
{
	if (m_bInitialized)
	{
		m_aPath.push_front(m_vStart);
		m_vStart = pos;
	}
	else
	{
		ASSERT(m_aPath.size() == 0);
		m_vStart = pos;
		m_bInitialized = true;
	}
}

const Vector2& Path::GetFirstStep() const
{
	ASSERT(m_aPath.size() > 0);
	return *m_aPath.begin();
}

const Vector2& Path::PopFront()
{
	ASSERT(m_aPath.size() > 0);
	m_vStart = *m_aPath.begin();
	m_aPath.pop_front();
	return m_vStart;
}


/*
deque<Vector2> Path::GetListInverse() const
{
	deque<Vector2> oPath;
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
	return Path(m_aPath.back(), GetListInverse());
}
*/

bool Path::InOnPath(const Vector2& pos) const
{
	if (GetStart() == pos)
		return true;

	for (uint i = 0; i < m_aPath.size(); ++i)
	{
		if (m_aPath[i] == pos)
			return true;
	}

	return false;
}

void Path::Print() const
{
	if (!m_bInitialized)
	{
		LOG("Not initialized\n");
	}
	else
	{
		LOG("[(%d %d) ->", m_vStart.x, m_vStart.y);
		for (uint i=0 ; i<m_aPath.size() ; ++i)
		{
			LOG(" (%d %d)", m_aPath[i].x, m_aPath[i].y);
		}
		LOG("]\n");
	}
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
		|| (a.GetStart() == b.GetStart() && a.GetLength() < b.GetLength())
		|| (a.GetStart() == b.GetStart() && a.GetLength() == b.GetLength() && a.GetTarget() < b.GetTarget()));
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

