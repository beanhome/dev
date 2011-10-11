#ifndef ANT_H_
#define ANT_H_

#include "Utils.h"
#include "Vector2.h"

class Ant
{
	public:
		Ant(int x, int y, int iPlayer);
		Ant(Vector2 loc, int iPlayer);

		const Vector2& GetLocation() const { return m_vLoc; }
		int GetPlayer() const { return m_iPlayer; }

#ifdef MYDEBUG
		void Draw(uint x, uint y, uint w, uint h, int iTurn, bool bSelect) const;
		void PrintInfo(sint16& x, sint16& y, sint16 yl) const;
#endif

	private:
		Vector2 m_vLoc;
		int m_iPlayer;
};

#endif //ANT_H_
