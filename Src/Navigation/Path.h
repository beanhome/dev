#ifndef PATH_H
#define PATH_H

#include "Utils.h"
#include "Vector2.h"

class Path
{
	public:
		Path();
		Path(const Vector2& start, const deque<Vector2>& oPath);
		Path(const Path& oOrig);

		void Clear() { m_bInitialized = false; m_aPath.clear(); }

		const Vector2& GetStart() const { return m_vStart; }
		const Vector2& GetTarget() const { return m_aPath.back(); }

		void PushBack(const Vector2& pos);
		void PushFront(const Vector2& pos);

		const Vector2& GetFirstStep() const;
		const Vector2& PopFront();

		uint GetLength() const { return (uint)m_aPath.size(); }
		const deque<Vector2>& GetList() const { return m_aPath; }
		//deque<Vector2> GetListInverse() const;
		//Path GetInverse() const;



		Vector2 operator[](int i) const { ASSERT(i<(int)m_aPath.size()); return m_aPath[i]; }

	private:
		bool				m_bInitialized;
		Vector2				m_vStart;
		deque<Vector2>		m_aPath;
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
			|| (a.GetStart() == b.GetStart() && a.GetLength() < b.GetLength()));
	}
};

#endif //PATH_H
