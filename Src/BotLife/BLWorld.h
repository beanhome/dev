#ifndef __BOTLIFE_BLWORLD_H__
#define __BOTLIFE_BLWORLD_H__

#include "Utils.h"
#include "GridBase.h"

class Canvas;
class CanvasBase;
class BLBot;

class BLSquare
{
	public:
		BLSquare() : m_iType(0) {}

		int GetType() const { return m_iType; }
		void SetType(int type) { m_iType = type;}

		virtual bool IsBlock() const { return (m_iType == 1); }

	private:
		int m_iType;
};

class BLWorld
{
	public:
		BLWorld(Canvas& canva, uint grid);
		~BLWorld();

		typedef GridBase<BLSquare> BLGrid;

		uint GetWidth() const { return m_iWidth; }
		uint GetHeight() const { return m_iHeight; }
		uint GetGridSize() const { return m_iGrid; }

		const BLGrid& GetGrid() const { return m_oGrid; }
		BLGrid& GetGrid() { return m_oGrid; }

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
};

#endif