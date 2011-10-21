#ifndef ANT_H_
#define ANT_H_

#include "Utils.h"
#include "Vector2.h"
#include "Path.h"

class World;

enum Role
{
	None,
	Explore,
	Guard,
	Protect,
	Loot,
	Attack,
	Flee,

	Role_MAX
};

class Ant
{
	public:
		Ant(int x, int y, int iPlayer);
		Ant(Vector2 loc, int iPlayer);

		const Vector2&	GetLocation() const { return m_vLoc; }
		int				GetPlayer() const { return m_iPlayer; }
		const Path&		GetPath() const { return m_oPath; }
		Path&			GetPath() { return m_oPath; }
		void			SetPath(const Path& oPath) { m_oPath = oPath; }
		Role			GetRole() const { return m_eRole; }
		void			SetRole(Role eRole) { m_eRole = eRole; }

		void			TestAnts(const World& oWorld);

#ifdef MYDEBUG
		void			Draw(uint x, uint y, uint w, uint h, int iTurn, bool bSelect) const;
		void			PrintInfo(sint16& x, sint16& y, sint16 yl) const;
#endif

	private:
		Vector2			m_vLoc;
		int				m_iPlayer;

		Role			m_eRole;
		Path			m_oPath;

		vector<Vector2> m_aEnemyAnts;
		vector<Vector2> m_aAllieAnts;

		static const char* s_Role[Role_MAX];
};

#endif //ANT_H_
