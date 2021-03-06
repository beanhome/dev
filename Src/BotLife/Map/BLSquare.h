#ifndef __BOTLIFE_BLSQUARE_H__
#define __BOTLIFE_BLSQUARE_H__

#include "Utils.h"
#include "GridBase.h"
#include "World/BLVector2.h"

#undef GetProp

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
		BLSquare(const BLVector2& pos);
		virtual ~BLSquare();

		const BLVector2& GetPos() const { return m_vPos; }
		void SetPos(const BLVector2& pos);
		void SetPos(int i, int j);

		TilesType GetTilesType() const { return m_eTilesType; }
		void SetTilesType(TilesType type) { m_eTilesType = type;}

		int GetTilesId() const { return m_TilesId; }
		void SetTilesId(int id) { m_TilesId = id; }

		void SetProp(BLProp* pProp);
		const BLProp* GetProp() const { return m_pProp; }
		BLProp* GetProp() { return m_pProp; }

		bool IsFree(BLProp* ignore = NULL) const { return (!IsBlock(ignore) && (m_pProp == NULL || m_pProp == ignore)); }
		virtual bool IsBlock(BLProp* ignore = NULL) const;
		virtual bool IsPermBlock(BLProp* ignore = NULL) const;
		virtual bool IsTempBlock(BLProp* ignore = NULL) const;

	private:
		BLVector2	m_vPos;
		TilesType	m_eTilesType;
		int			m_TilesId;
		BLProp*		m_pProp;

	public:
		static const bool s_bIsBloc[TilesType_MAX];
		static const bool s_bIsFullGround[TilesType_MAX];
};

#endif
