#ifndef PATH_H
#define PATH_H

#include "Utils.h"
#include "Vector2.h"

class Path
{
	public:
		Path();
		Path(const Vector2& start, vector<Vector2> oPath);

		const Vector2& GetStart() const { return m_vStart; }
		const Vector2& GetTarget() const { return m_vTarget; }

		void SetStart(const Vector2& start) { m_vStart = start; } 
		void SetTarget(const Vector2& target) { m_vTarget = target; } 

		int GetLength() const { return m_aPath.size(); }
		const vector<Vector2>& GetList() const { return m_aPath; }
		vector<Vector2>& GetList() { return m_aPath; }
		vector<Vector2> GetListInverse() const;
		Path GetInverse() const;

		void PushTarget(const Vector2& pos) { m_aPath.push_back(m_vTarget = pos); }

		Vector2 operator[](int i) const { ASSERT(i<(int)m_aPath.size()); return m_aPath[i]; }

	private:
		Vector2				m_vStart;
		Vector2				m_vTarget;

		vector<Vector2>		m_aPath;
};

bool operator==(const Path& a, const Path& b);
bool operator!=(const Path& a, const Path& b);
bool operator<(const Path& a, const Path& b);
bool operator<=(const Path& a, const Path& b);
bool operator>(const Path& a, const Path& b);
bool operator>=(const Path& a, const Path& b);

struct ltpath_start
{
	bool operator()(const Path& a, const Path& b)
	{
		return (a.GetStart() < b.GetStart()
			|| (a.GetStart() == b.GetStart() && a.GetList().size() < b.GetList().size()));
	}
};

#endif //PATH_H
