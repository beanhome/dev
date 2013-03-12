#ifndef __BOTLIFE_BLTiles_H__
#define __BOTLIFE_BLTiles_H__

#include "Utils.h"
#include "GridBase.h"
#include "Color.h"
#include "BLMap.h"

class GEngine;
class Canvas;
class CanvasBase;
class ImageResource;

union TileKey
{
	uint32 val;

	struct  
	{
		uint8 BR;
		uint8 BL;
		uint8 TR;
		uint8 TL;
	};

	TileKey() : val(0) { }
	TileKey(uint32 v) : val(v) { }
	TileKey(CaseType t) : BR(t), BL(t), TR(t), TL(t) { }
	TileKey(CaseType tl, CaseType tr, CaseType bl, CaseType br) : BR(br), BL(bl), TR(tr), TL(tl) { }
};

bool operator<(const TileKey& a, const TileKey& b);

class BLTiles
{
	public:
		BLTiles(const GEngine& ge, const char* name);
		~BLTiles();

	public:
		void ReadFile();
		void WriteFile() const;

		int GetTilesWidth() const { return m_iTileSizeX; }
		int GetTilesHeight() const { return m_iTileSizeY; }
		int GetTilesCount() const { return m_iTileCountX * m_iTileCountY;}

		void DrawTile(const CanvasBase& canvas, CaseType tl, CaseType tr, CaseType bl, CaseType br, int x, int y, int w, int h) const;
		void DrawTile(const CanvasBase& canvas, int id, int x, int y, int w, int h) const;

		int Find(CaseType type) const;
		int Find(CaseType tl, CaseType tr, CaseType bl, CaseType br) const;
		TileKey Find(int id) const;

		void Add(TileKey oKey, int id);
		void Del(int id);

	private:
		ImageResource*	m_pTiles;
		string			m_sPath;

		int m_iTileCountX;
		int m_iTileCountY;
		int m_iTileSizeX;
		int m_iTileSizeY;
		int m_iTileOffsetX;
		int m_iTileOffsetY;

	public:
		typedef multimap<TileKey, int> TilesCornerMap;
		typedef pair<TileKey, int> TilesCornerPair;
		TilesCornerMap m_aTilesCorner;

		typedef map<int, TileKey> TilesIdMap;
		typedef pair<int, TileKey> TilesIdPair;
		TilesIdMap m_aTilesId;
};


#endif
