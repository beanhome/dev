#ifndef __BOTLIFE_BLMAP_H__
#define __BOTLIFE_BLMAP_H__

#include "Utils.h"
#include "GridBase.h"
#include "Color.h"

class Canvas;
class CanvasBase;
class ImageResource;
class BLTiles;

enum CaseType
{
	DarkWater	, // -> LightWater
	LightWater	, // -> LightDirt
	LightDirt	, // -> DarkDirt, LightGrass, Stone
	DarkDirt	, // -> nil
	Stone		, // -> nil
	LightGrass	, // -> DarkGrass, Tree
	DarkGrass	, // -> nil
	Tree		, // -> nil

	CaseType_MAX
};

class BLZone
{
	public:
		BLZone();
		~BLZone();

		void Clear();

		void AddType(CaseType type) { m_aTypeCount[type]++; m_iMax++; }
		int GetCount(CaseType type) const { return m_aTypeCount[type]; }
		int GetMax() const { return m_iMax; }
		CaseType GetMajorType(CaseType eTypeToSkip = CaseType_MAX) const;

		bool IsLand() const { return (GetLandCount() == m_iMax); }
		bool IsWater() const { return (GetWaterCount() == m_iMax); }
		bool IsDirt() const { return (GetDirtCount() == m_iMax); }
		bool IsGrass() const { return (GetGrassCount() == m_iMax); }
		bool IsGround() const { return (GetGroundCount() == m_iMax); }

		int GetLandCount() const { return (GetCount(LightDirt) + GetCount(DarkDirt) + GetCount(Stone) + GetCount(LightGrass) + GetCount(DarkGrass) + GetCount(Tree)); }
		int GetWaterCount() const { return (GetCount(LightWater) + GetCount(DarkWater)); }
		int GetDirtCount() const { return (GetCount(LightDirt) + GetCount(DarkDirt)); }
		int GetGrassCount() const { return (GetCount(LightGrass) + GetCount(DarkGrass)); }
		int GetGroundCount() const { return (GetCount(LightDirt) + GetCount(DarkDirt)+ GetCount(LightGrass) + GetCount(DarkGrass)); }
		int GetBlockCount() const { return (GetCount(LightWater) + GetCount(DarkWater) + GetCount(Stone) + GetCount(Tree)); }

	private:
		int m_aTypeCount[CaseType_MAX];
		int m_iMax;
};


class BLMap
{
	public:
		BLMap(uint w, uint h, const BLTiles& oTiles);
		~BLMap();

	public:
		uint GetWidth() const { return m_iWidth; }
		uint GetHeight() const { return m_iHeight; }

		void ConvertTypeToTiles();
		void Debug() const;
		void Display(const CanvasBase& Canvas) const;

		void Step(int step);

		bool IsLand(CaseType val) const { return !IsWater(val); }
		bool IsWater(CaseType val) const { return (val == LightWater || val == DarkWater); }
		bool IsDirt(CaseType val) const { return (val == LightDirt || val == DarkDirt); }
		bool IsGrass(CaseType val) const { return (val == LightGrass || val == DarkGrass); }
		bool IsGround(CaseType val) const { return (val == LightDirt || val == DarkDirt || val == LightGrass || val == DarkGrass); }
		bool IsBlock(CaseType val) const { return (val == Tree || val == Stone); }

	private:
		uint m_iWidth;
		uint m_iHeight;

		GridBase<CaseType> m_oTypeMap;
		GridBase<CaseType> m_oTmp;
		GridBase<int> m_oTilesMap;

		const BLTiles& m_oTiles;

	public:
		static Color s_oColor[CaseType_MAX];
		static float s_fRep[CaseType_MAX];
		static const char* s_sCaseType[CaseType_MAX];
};

#endif