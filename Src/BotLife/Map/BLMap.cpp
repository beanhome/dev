#include "BLMap.h"
#include "CanvasBase.h"
#include "Canvas.h"
#include "BLTiles.h"

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


BLMap::BLMap(uint w, uint h, const BLTiles& oTiles)
	: m_iWidth(w)
	, m_iHeight(h)
	, m_oTypeMap(false)
	, m_oTmp(false)
	, m_oTiles(oTiles)
{
	m_oTypeMap.Init(m_iWidth+1, m_iHeight+1);
	m_oTmp.Init(m_iWidth+1, m_iHeight+1);
	m_oTilesMap.Init(m_iWidth, m_iHeight);

	for (uint i=1 ; i<CaseType_MAX ; ++i)
	{
		s_fRep[i] += s_fRep[i-1];
	}

	LOG("Repartition : \n");
	for (uint i=0 ; i<CaseType_MAX ; ++i)
	{
		LOG("Rep %d : %f\n", i, s_fRep[i]);
	}

	for (uint i=0 ; i<m_iWidth+1 ; ++i)
	{
		for (uint j=0 ; j<m_iHeight+1 ; ++j)
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

void BLMap::Debug() const
{
	LOG("  *****  BLMap  *****  \n");
	for (uint j=0 ; j<m_iHeight+1 ; ++j)
	{
		for (uint i=0 ; i<m_iWidth+1 ; ++i)
		{
			LOG("%d", m_oTypeMap[i][j]);
		}
		LOG("\n");
	}
}

void BLMap::Step(int step)
{
	m_oTmp = m_oTypeMap;

	uint w = m_iWidth+1;
	uint h = m_iHeight+1;

	for (uint i=0 ; i<w ; ++i)
	{
		for (uint j=0 ; j<h ; ++j)
		{
			BLZone zone;
			CaseType type = m_oTmp.GetCase(i, j);
			for (int k=(int)i-1 ; k<=(int)i+1 ; ++k)
			{
				for (int l=(int)j-1 ; l<=(int)j+1 ; ++l)
				{
					if (k>=0 && k<(int)w && l>=0 && l<(int)h)
					{
						zone.AddType(m_oTmp.GetCase(k, l));
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

void BLMap::ConvertTypeToTiles()
{
	for (uint i=0 ; i<m_iWidth ; ++i)
	{
		for (uint j=0 ; j<m_iHeight ; ++j)
		{
			CaseType tl = m_oTypeMap.GetCase(i, j);
			CaseType tr = m_oTypeMap.GetCase(i+1, j);
			CaseType bl = m_oTypeMap.GetCase(i, j+1);
			CaseType br = m_oTypeMap.GetCase(i+1, j+1);

			m_oTilesMap.GetCase(i, j) = m_oTiles.Find(tl, tr, bl, br);
		}
	}
}


void BLMap::Display(const CanvasBase& Canvas) const
{
	for (uint i=0 ; i<m_iWidth ; ++i)
	{
		for (uint j=0 ; j<m_iHeight ; ++j)
		{
			int w = m_oTiles.GetTilesWidth();
			int h = m_oTiles.GetTilesHeight();
			int x = i*w;
			int y = j*h;

			m_oTiles.DrawTile(Canvas, m_oTilesMap.GetCase(i, j) , x, y, w, h);
			//Canvas.DrawFillRect(i*32, j*32, 32, 32, s_oColor[m_oMap.GetCase(i, j)]);
			//Canvas.Print(x, y, Canvas.GetPrintFont(), w/2, Center, 0, 0, 0, "%d", m_oMap.GetCase(i, j));
		}
	}
}

