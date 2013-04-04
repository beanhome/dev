#include "BLMap.h"
#include "CanvasBase.h"
#include "Canvas.h"
#include "BLTiles.h"
#include "BLSquare.h"
//#include "Timer.h"
#include "World/BLProp.h"

BLZone::BLZone()
{
	Clear();
}

BLZone::~BLZone()
{
}

void BLZone::Clear()
{
	for (uint i=0 ; i<CaseType_MAX ; ++i)
	{
		m_aTypeCount[i] = 0;
	}
	m_iMax = 0;
}

CaseType BLZone::GetMajorType(CaseType eTypeToSkip) const
{
	CaseType majortype = CaseType_MAX;
	int majorcount = -1;

	for (uint i=0 ; i<CaseType_MAX ; ++i)
	{
		int count = m_aTypeCount[i] - (eTypeToSkip == i ? 1 : 0);
		if (majortype == CaseType_MAX || majorcount < count)
		{
			majortype = (CaseType)i;
			majorcount = count;
		}
	}

	return majortype;
}



Color BLMap::s_oColor[CaseType_MAX] =
{
	Color(4, 52, 112),	// DarkWater, // -> LightWater
	Color(4, 56, 116),	// LightWater, // -> LightDirt
	Color(110, 65, 1),	// LightDirt, // -> DarkDirt, LightGrass, Stone
	Color(96, 56, 0),	// DarkDirt, // -> nil
	Color(100, 100, 100),	// Stone, // -> nil
	Color(42, 85, 12),	// LightGrass, // -> DarkGrass, Tree
	Color(34, 76, 8),	// DarkGrass, // -> nil
	Color(3, 63, 1)		// Tree, // -> nil
};

float BLMap::s_fRep[CaseType_MAX] = 
{
	0.00f,	// DarkWater, // -> LightWater
	0.34f,	// LightWater, // -> LightDirt
	0.17f,	// LightDirt, // -> DarkDirt, LightGrass, Stone
	0.00f,	// DarkDirt, // -> nil
	0.05f,	// Stone, // -> nil
	0.15f,	// LightGrass, // -> DarkGrass, Tree
	0.0f,	// DarkGrass, // -> nil
	0.33f,	// Tree, // -> nil
};

const char* BLMap::s_sCaseType[CaseType_MAX] =
{
	"DarkWater",
	"LightWater",
	"LightDirt",
	"DarkDirt",
	"Stone",
	"LightGrass",
	"DarkGrass",
	"Tree",
};

const TilesType BLMap::s_sFullCaseToTile[CaseType_MAX] = 
{
	TT_DWater,
	TT_LWater,
	TT_LDirt,
	TT_DDirt,
	TT_Stone,
	TT_LGrass,
	TT_DGrass,
	TT_Tree,
};

const char* BLMap::s_sTilesType[TilesType_MAX] =
{
	"DarkWater"	,
	"DarkWater To LightWater",
	"LightWater",
	"LightWater To LightDirt",
	"LightDirt",
	"LightDirt To DarkDirt",
	"LightDirt To Light Grass",
	"LightDirt To Stone",
	"DarkDirt",
	"Stone",
	"LightGrass",
	"LightGrass To DarkGrass",
	"LightGrass To Tree",
	"DarkGrass",
	"Tree",
};


BLMap::BLMap(uint w, uint h, const BLTiles& oTiles)
	: m_iWidth(w)
	, m_iHeight(h)
	, m_oTypeMap(false, true)
	, m_oTypeMapTmp(false, true)
	, m_oTilesMap(false, true)
	, m_oTiles(oTiles)
{
	m_oTypeMap.Init(m_iWidth+1, m_iHeight+1);
	m_oTypeMapTmp.Init(m_iWidth+1, m_iHeight+1);
	m_oTilesMap.Init(m_iWidth, m_iHeight);

	for (uint i=0 ; i<m_oTilesMap.GetWidth() ; ++i)
	{
		for (uint j=0 ; j<m_oTilesMap.GetHeight() ; ++j)
		{
			m_oTilesMap[i][j].SetPos(i, j);
		}
	}

	for (uint i=1 ; i<CaseType_MAX ; ++i)
	{
		s_fRep[i] += s_fRep[i-1];
	}

	LOG("Repartition : \n");
	for (uint i=0 ; i<CaseType_MAX ; ++i)
	{
		LOG("Rep %d : %f\n", i, s_fRep[i]);
	}

	for (uint i=0 ; i<m_oTypeMap.GetWidth() ; ++i)
	{
		for (uint j=0 ; j<m_oTypeMap.GetHeight() ; ++j)
		{
			float rnd = (float)rand() / (float)RAND_MAX;
			for (int k=0 ; k<CaseType_MAX ; ++k)
			{
				if (rnd<s_fRep[k])
				{
					m_oTypeMap[i][j] = (CaseType)k;
					break;
				}
			}
		}
	}
}

BLMap::~BLMap()
{
}

void BLMap::Generate()
{
	for (uint i=0 ; i<20 ; ++i)
	{
		Step(i);
	}

	ConvertTypeToTiles();
}

void BLMap::RandomFullGroundLoc(int& i, int& j) const
{
	vector<int> id;
	id.reserve(m_oTilesMap.GetWidth() * m_oTilesMap.GetHeight() / 4);

	for (uint k=0 ; k<m_oTilesMap.GetWidth() * m_oTilesMap.GetHeight() ; ++k)
	{
		if (! BLSquare::s_bIsBloc[m_oTilesMap.GetCase(k).GetTilesType()])
			id.push_back(k);
	}

	m_oTilesMap.GetCoord(id[Rand(id.size()-1)], i, j);
}


const BLSquare& BLMap::GetTilesCase(int i, int j) const
{
	return m_oTilesMap.GetCase(i, j);
}


void BLMap::Debug() const
{
	LOG("  *****  BLMap  *****  \n");
	for (uint j=0 ; j<m_oTypeMap.GetHeight() ; ++j)
	{
		for (uint i=0 ; i<m_oTypeMap.GetWidth() ; ++i)
		{
			LOG("%d", m_oTypeMap[i][j]);
		}
		LOG("\n");
	}
}

void BLMap::Step(int step)
{
	m_oTypeMapTmp = m_oTypeMap;

	uint w = m_oTypeMapTmp.GetWidth();
	uint h = m_oTypeMapTmp.GetHeight();

	for (uint i=0 ; i<w ; ++i)
	{
		for (uint j=0 ; j<h ; ++j)
		{
			BLZone zone;
			CaseType type = m_oTypeMapTmp.GetCase(i, j);
			for (int k=(int)i-1 ; k<=(int)i+1 ; ++k)
			{
				for (int l=(int)j-1 ; l<=(int)j+1 ; ++l)
				{
					if (k>=0 && k<(int)w && l>=0 && l<(int)h)
					{
						zone.AddType(m_oTypeMapTmp.GetCase(k, l));
					}
				}
			}

			if (step == 0)
			{
				if (i<2 || j<2 || i>=w-2 || j>=h-2)
				//if (zone.GetMax() < 9)
				{
					m_oTypeMap.GetCase(i, j) = LightWater;// (zone.IsWater() ? DarkWater : LightWater);
				}
			}
			else if (step < 5)
			{
				if (zone.GetWaterCount() > Rand(3,5))
				{
					m_oTypeMap.GetCase(i, j) = LightWater;
				}
				else if (IsWater(type) && zone.GetLandCount() > Rand(3,5))
				{
					m_oTypeMap.GetCase(i, j) = LightDirt;
				}
				else if (IsLand(type) && zone.GetCount(Tree) > Rand(3,4))
				{
					m_oTypeMap.GetCase(i, j) = Tree;
				}
				else
				{
					if (zone.GetCount(type) == 1)
						m_oTypeMap.GetCase(i, j) = zone.GetMajorType();
				}
			}
			else if (step < 8)
			{
				if (IsLand(type) && zone.GetWaterCount() > 0)
				{
					m_oTypeMap.GetCase(i, j) = LightDirt;
				}
				else if (IsLand(type) && type != Stone && zone.GetCount(Stone) > 0)
				{
					m_oTypeMap.GetCase(i, j) = LightDirt;
				}
				else if (zone.IsDirt())
				{
					m_oTypeMap.GetCase(i, j) = (Rand(2) == 0 ? LightDirt : Stone);
				}
				else if (IsDirt(type) && zone.GetWaterCount() == 0)
				{
					m_oTypeMap.GetCase(i, j) = LightGrass;
				}
				else if (type == Tree && zone.GetDirtCount() > 0)
				{
					m_oTypeMap.GetCase(i, j) = LightGrass;
				}
			}
			else if (step < 12)
			{
				if (IsGrass(type) && zone.GetDirtCount() >= 3 && zone.GetCount(Tree) == 0 && Rand(2) == 0)
				{
					m_oTypeMap.GetCase(i, j) = LightDirt;
				}
			}
			else if (step < 17)
			{
				if (zone.IsWater() && Rand(2) == 0)
				{
					m_oTypeMap.GetCase(i, j) = DarkWater;
				}
				else if (zone.IsGrass() && Rand(2) == 0)
				{
					m_oTypeMap.GetCase(i, j) = DarkGrass;
				}
				else if (zone.IsDirt() && Rand(2) == 0)
				{
					m_oTypeMap.GetCase(i, j) = DarkDirt;
				}
				//else
				//{
				//	if (zone.GetCount(type) == 1)
				//		m_oMap.GetCase(i, j) = zone.GetMajorType();
				//}
			}
		}
	}
}

TilesType BLMap::CaseToTile(int id) const
{
	return CaseToTile(m_oTiles.Find(id));
}


TilesType BLMap::CaseToTile(const TileKey& tiles) const
{
	if (tiles.TL == tiles.TR && tiles.TL == tiles.BL && tiles.TL == tiles.BR)
	{
		return s_sFullCaseToTile[tiles.TL];
	}
	else if ((tiles.TL == DarkWater || tiles.TR == DarkWater || tiles.BL == DarkWater || tiles.BR == DarkWater)
		&&   (tiles.TL == LightWater || tiles.TR == LightWater || tiles.BL == LightWater || tiles.BR == LightWater))
	{
		return TT_DWater_LWater;
	}
	else if ((tiles.TL == LightWater || tiles.TR == LightWater || tiles.BL == LightWater || tiles.BR == LightWater)
		&&   (tiles.TL == LightDirt || tiles.TR == LightDirt || tiles.BL == LightDirt || tiles.BR == LightDirt))
	{
		return TT_LWater_LDirt;
	}
	else if ((tiles.TL == LightDirt || tiles.TR == LightDirt || tiles.BL == LightDirt || tiles.BR == LightDirt)
		&&   (tiles.TL == DarkDirt || tiles.TR == DarkDirt || tiles.BL == DarkDirt || tiles.BR == DarkDirt))
	{
		return TT_LDirt_DDirt;
	}
	else if ((tiles.TL == LightDirt || tiles.TR == LightDirt || tiles.BL == LightDirt || tiles.BR == LightDirt)
		&&   (tiles.TL == LightGrass || tiles.TR == LightGrass || tiles.BL == LightGrass || tiles.BR == LightGrass))
	{
		return TT_LDirt_LGrass;
	}
	else if ((tiles.TL == LightDirt || tiles.TR == LightDirt || tiles.BL == LightDirt || tiles.BR == LightDirt)
		&&   (tiles.TL == Stone || tiles.TR == Stone || tiles.BL == Stone || tiles.BR == Stone))
	{
		return TT_LDirt_Stone;
	}
	else if ((tiles.TL == LightGrass || tiles.TR == LightGrass || tiles.BL == LightGrass || tiles.BR == LightGrass)
		&&   (tiles.TL == DarkGrass || tiles.TR == DarkGrass || tiles.BL == DarkGrass || tiles.BR == DarkGrass))
	{
		return TT_LGrass_DGrass;
	}
	else if ((tiles.TL == LightGrass || tiles.TR == LightGrass || tiles.BL == LightGrass || tiles.BR == LightGrass)
		&&   (tiles.TL == Tree || tiles.TR == Tree || tiles.BL == Tree || tiles.BR == Tree))
	{
		return TT_LGrass_Tree;
	}

	return TilesType_MAX;
}

void BLMap::ConvertTypeToTiles()
{
	for (uint i=0 ; i<m_oTypeMap.GetWidth()-1 ; ++i)
	{
		for (uint j=0 ; j<m_oTypeMap.GetHeight()-1 ; ++j)
		{
			CaseType tl = m_oTypeMap.GetCase(i, j);
			CaseType tr = m_oTypeMap.GetCase(i+1, j);
			CaseType bl = m_oTypeMap.GetCase(i, j+1);
			CaseType br = m_oTypeMap.GetCase(i+1, j+1);

			m_oTilesMap.GetCase(i, j).SetTilesId(m_oTiles.Find(tl, tr, bl, br));
			m_oTilesMap.GetCase(i, j).SetTilesType(CaseToTile(TileKey(tl, tr, bl, br)));
		}
	}
}


void BLMap::Display(const CanvasBase& Canvas) const
{
	for (uint i=0 ; i<m_oTilesMap.GetWidth() ; ++i)
	{
		for (uint j=0 ; j<m_oTilesMap.GetHeight() ; ++j)
		{
			int w = m_oTiles.GetTilesWidth();
			int h = m_oTiles.GetTilesHeight();
			int x = i*w;
			int y = j*h;

			const BLSquare& sq = m_oTilesMap.GetCase(i, j);

			m_oTiles.DrawTile(Canvas, sq.GetTilesId() , x, y, w, h);
		}
	}
	for (uint i=0 ; i<m_oTilesMap.GetWidth() ; ++i)
	{
		for (uint j=0 ; j<m_oTilesMap.GetHeight() ; ++j)
		{
			const BLSquare& sq = m_oTilesMap.GetCase(i, j);
			if (sq.GetProp() != NULL)
				sq.GetProp()->Draw();
			//Canvas.DrawFillRect(i*32, j*32, 32, 32, s_oColor[m_oMap.GetCase(i, j)]);
			//Canvas.Print(x, y, Canvas.GetPrintFont(), w/2, Center, 0, 0, 0, "%d", m_oMap.GetCase(i, j));
		}
	}
}

