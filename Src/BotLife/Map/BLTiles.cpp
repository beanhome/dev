#include "BLTiles.h"
#include "CanvasBase.h"
#include "Canvas.h"
#include "GEngine.h"

bool operator<(const TileKey& a, const TileKey& b)
{
	return (a.val < b.val);
}

BLTiles::BLTiles(const GEngine& ge, const char* name)
	: m_pTiles(NULL)
	, m_iTileCountX(0)
	, m_iTileCountY(0)
	, m_iTileSizeX(0)
	, m_iTileSizeY(0)
	, m_iTileOffsetX(0)
	, m_iTileOffsetY(0)
{
	string path = FormatString("%sBotLife/%s.png", DATA_DIR, name);

	m_pTiles = ge.GetImageResource(path.c_str());

	m_sPath = FormatString("%sBotLife/%s.blt", DATA_DIR, name);

	ReadFile();

	/*
	m_iTileCountX = 19;
	m_iTileCountY = 20;
	m_iTileSizeX = 32;
	m_iTileSizeY = 32;
	m_iTileOffsetX = 33;
	m_iTileOffsetY = 33;

	Add(DarkWater, 327);
	Add(LightWater, 319);
	Add(LightDirt, 334);
	Add(DarkDirt, 341);
	Add(Stone, 172);
	Add(LightGrass, 351);
	Add(DarkGrass, 364);
	Add(Tree, 135);
	*/
}

BLTiles::~BLTiles()
{
	WriteFile();
}


void BLTiles::ReadFile()
{
	struct
	{
		TileKey key;
		int val;
	} oData;

	FILE* pFile;
	fopen_s(&pFile, m_sPath.c_str(), "rb");

	fread_s(&m_iTileCountX, sizeof(m_iTileCountX), sizeof(m_iTileCountX), 1, pFile);
	fread_s(&m_iTileCountY, sizeof(m_iTileCountY), sizeof(m_iTileCountY), 1, pFile);
	fread_s(&m_iTileSizeX, sizeof(m_iTileSizeX), sizeof(m_iTileSizeX), 1, pFile);
	fread_s(&m_iTileSizeY, sizeof(m_iTileSizeY), sizeof(m_iTileSizeY), 1, pFile);
	fread_s(&m_iTileOffsetX, sizeof(m_iTileOffsetX), sizeof(m_iTileOffsetX), 1, pFile);
	fread_s(&m_iTileOffsetY, sizeof(m_iTileOffsetY), sizeof(m_iTileOffsetY), 1, pFile);

	int count = 0;

	while ((count = fread_s(&oData, sizeof(oData), sizeof(oData), 1, pFile)) == 1)
	{
		m_aTilesCorner.insert(TilesCornerPair(oData.key, oData.val));
		m_aTilesId.insert(TilesIdPair(oData.val, oData.key));
	}

	fclose(pFile);
}

void BLTiles::WriteFile() const
{
	FILE* pFile;
	fopen_s(&pFile, m_sPath.c_str(), "wb+");

	fwrite(&m_iTileCountX, sizeof(m_iTileCountX), 1, pFile);
	fwrite(&m_iTileCountY, sizeof(m_iTileCountY), 1, pFile);
	fwrite(&m_iTileSizeX, sizeof(m_iTileSizeX), 1, pFile);
	fwrite(&m_iTileSizeY, sizeof(m_iTileSizeY), 1, pFile);
	fwrite(&m_iTileOffsetX, sizeof(m_iTileOffsetX), 1, pFile);
	fwrite(&m_iTileOffsetY, sizeof(m_iTileOffsetY), 1, pFile);

	for (TilesIdMap::const_iterator it = m_aTilesId.begin() ; it!=m_aTilesId.end() ; ++it)
	{
		int id = it->first;
		uint32 key = it->second.val;
		CHECK(fwrite(&key, sizeof(uint32), 1, pFile) == 1, "Error fwrite %d\n", id);
		CHECK(fwrite(&id, sizeof(int), 1, pFile) == 1, "Error fwrite %d\n", id);
	}

	fclose(pFile);
}

int BLTiles::Find(CaseType type) const
{
	int count = m_aTilesCorner.count(type);
	if (count == 0)
		return -1;

	count = Rand(count);

	TilesCornerMap::const_iterator it = m_aTilesCorner.lower_bound(type);
	for (int i=1 ; i<count ; ++i)
		++it;
	
	return it->second;
}

int BLTiles::Find(CaseType tl, CaseType tr, CaseType bl, CaseType br) const
{
	int count = m_aTilesCorner.count(TileKey(tl, tr, bl, br));
	if (count == 0)
		return -1;

	count = Rand(count);

	TilesCornerMap::const_iterator it = m_aTilesCorner.lower_bound(TileKey(tl, tr, bl, br));
	for (int i=1 ; i<count ; ++i)
		++it;

	return it->second;
}

TileKey BLTiles::Find(int id) const
{
	TilesIdMap::const_iterator it = m_aTilesId.find(id);
	return (it != m_aTilesId.end() ? it->second : -1);
}

void BLTiles::Add(TileKey oKey, int id)
{
	m_aTilesCorner.insert(TilesCornerPair(oKey, id));
	m_aTilesId.insert(TilesIdPair(id, oKey));
}

void BLTiles::Del(int id)
{
	for (TilesCornerMap::iterator it = m_aTilesCorner.begin() ; it!=m_aTilesCorner.end() ; ++it)
	{
		if (it->second == id)
		{
			m_aTilesCorner.erase(it);
			break;
		}
	}

	m_aTilesId.erase(id);
}

void BLTiles::DrawTile(const CanvasBase& canvas, CaseType tl, CaseType tr, CaseType bl, CaseType br, int x, int y, int w, int h) const
{
	DrawTile(canvas, Find(tl, tr, bl, br), x, y, w, h);
}

void BLTiles::DrawTile(const CanvasBase& canvas, int id, int x, int y, int w, int h) const
{
	int i = id%m_iTileCountX;
	int j = id/m_iTileCountX;
	canvas.DrawImage(*m_pTiles, x+w/2, y+h/2, w, h, i * m_iTileOffsetX, j * m_iTileOffsetY, m_iTileSizeX, m_iTileSizeY);
}
