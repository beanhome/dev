#ifndef __BOTLIFE_BLWORLD_H__
#define __BOTLIFE_BLWORLD_H__

#include "Utils.h"
#include "GridBase.h"
#include "World\BLSquare.h"

class Canvas;
class CanvasBase;
class BLBot;
class BLProp;
class Path;

class BLWorld
{
	public:
		BLWorld(Canvas& canva, uint grid);
		~BLWorld();

		typedef GridBase<BLSquare> BLGrid;

		const Canvas& GetCanvas() const { return m_oCanva; }

		uint GetWidth() const { return m_iWidth; }
		uint GetHeight() const { return m_iHeight; }
		uint GetGridSize() const { return m_iGrid; }

		const BLGrid& GetGrid() const { return m_oGrid; }
		BLGrid& GetGrid() { return m_oGrid; }

		bool TestPath(const Path& oPath) const;

		const BLBot& GetBot() const { return *m_pBot; }

		void Update(float dt);
		void Draw() const;

	private:
		Canvas& m_oCanva;

		BLGrid m_oGrid;

		uint m_iGrid;
		uint m_iWidth;
		uint m_iHeight;

		BLBot* m_pBot;

		BLProp* m_pProp;
};

#endif