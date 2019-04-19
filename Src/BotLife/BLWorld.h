#ifndef __BOTLIFE_BLWORLD_H__
#define __BOTLIFE_BLWORLD_H__

#include "Utils.h"
#include "GridBase.h"
#include "Map/BLSquare.h"
#include "Map/BLMap.h"

class Canvas;
class CanvasBase;
class BLBot;
class BLProp;
class Path;

class BLTiles;
class BLMap;
class BLApp;

class IBObject;
class IBPath;
class IBVector2;
class BLObject;

class BLWorld
{
	public:
		BLWorld(BLApp& app, Canvas& canva, int w, int h, const char* tilesname);
		~BLWorld();

		typedef GridBase<BLSquare> BLGrid;

		const Canvas& GetCanvas() const { return m_oCanva; }
		Canvas& GetCanvas() { return m_oCanva; }
		BLApp& GetApp() { return m_oBLApp; }

		uint GetWidth() const { return m_pMap->GetWidth(); }
		uint GetHeight() const { return m_pMap->GetHeight(); }
		uint GetGridSize() const { return m_iGrid; }

		const BLGrid& GetGrid() const { return m_pMap->GetGrid(); }
		BLGrid& GetGrid() { return m_pMap->GetGrid(); }

		const BLSquare* GetMouseCase();

		bool TestPath(const Path& oPath) const;

		const BLBot& GetBot() const { return *m_pBot; }
		BLBot& GetBot() { return *m_pBot; }

		vector<BLProp*> GetProps();
		void GetProps(vector<BLProp*>& Props);

		void CenterMap(int x, int y);

		void Update(float dt);
		void Draw() const;
		void DrawDebug() const;
		void DrawDebugObject(class BLObject* pObj) const;
		void DrawDebugPath(const class BLPath& oPath) const;
		void DrawDebugObj(const class BLObject& oObj) const;
		void DrawDebugPos(const class BLVector2& oPos) const;

		bool IsDraging() const { return m_bDraging; }
		void StartDrag();
		void UpdateDrag();
		void StopDrag();

	private:
		BLApp& m_oBLApp;
		Canvas& m_oCanva;

		BLTiles* m_pTiles;
		BLMap* m_pMap;

		uint m_iGrid;
		//uint m_iWidth;
		//uint m_iHeight;

		bool m_bDraging;
		int m_iStartDragX;
		int m_iStartDragY;

		BLBot* m_pBot;
};

#endif
