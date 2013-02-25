#ifndef __BOTLIFE_BLSQUARE_H__
#define __BOTLIFE_BLSQUARE_H__

#include "Utils.h"
#include "GridBase.h"

class Canvas;
class CanvasBase;
class BLBot;
class BLProp;
class Path;

enum TilesType
{
	TT_DWater,
	TT_DWater_LWater,
	TT_LWater,
	TT_LWater_LDirt,
	TT_LDirt,
	TT_LDirt_DDirt,
	TT_LDirt_LGrass,
	TT_LDirt_Stone,
	TT_DDirt,
	TT_Stone,
	TT_LGrass,
	TT_LGrass_DGrass,
	TT_LGrass_Tree,
	TT_DGrass,
	TT_Tree,

	TilesType_MAX
};

class BLSquare
{
	public:
		BLSquare();

		TilesType GetTilesType() const { return m_eTilesType; }
		void SetTilesType(TilesType type) { m_eTilesType = type;}

		int GetTilesId() const { return m_TilesId; }
		void SetTilesId(int id) { m_TilesId = id; }

		void SetProp(BLProp* pProp);
		const BLProp* GetProp() const { return m_pProp; }

		virtual bool IsBlock() const;
		virtual bool IsTempBlock() const;

	private:
		TilesType	m_eTilesType;
		int			m_TilesId;
		BLProp*		m_pProp;

	public:
		static const bool s_bIsBloc[TilesType_MAX];
		static const bool s_bIsFullGround[TilesType_MAX];
};

#endif