#ifndef __IBPATH_H__
#define __IBPATH_H__

#include "Utils.h"
#include "World\IBObject.h"
#include "Path.h"

class IBPath : public IBObject, public Path
{
	public:
		IBPath();
		IBPath(const string& name);
		IBPath(const Vector2& start, const deque<Vector2>& oPath);
		IBPath(const string& name, const Vector2& start, const deque<Vector2>& oPath);
		virtual ~IBPath();
		
		virtual void  Print() const;

	private:
};

#endif