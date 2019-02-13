#include "BLSquare.h"
#include "World/BLProp.h"



const bool BLSquare::s_bIsBloc[TilesType_MAX] =
{
	/* TT_DWater */           true,  
	/* TT_DWater_LWater */	  true,  
	/* TT_LWater */			  true,  
	/* TT_LWater_LDirt */	  true, 
	/* TT_LDirt */			  false, 
	/* TT_LDirt_DDirt */		  false, 
	/* TT_LDirt_LGrass */	  false, 
	/* TT_LDirt_Stone */		  true, 
	/* TT_DDirt */			  false, 
	/* TT_Stone */			  true,  
	/* TT_LGrass */			  false, 
	/* TT_LGrass_DGrass */	  false, 
	/* TT_LGrass_Tree */		  true, 
	/* TT_DGrass */			  false, 
	/* TT_Tree */			  true,  
};

const bool BLSquare::s_bIsFullGround[TilesType_MAX] =
{
	/* TT_DWater */           false, 
	/* TT_DWater_LWater */	  false, 
	/* TT_LWater */			  false, 
	/* TT_LWater_LDirt */	  false, 
	/* TT_LDirt */			  true,  
	/* TT_LDirt_DDirt */		  true,  
	/* TT_LDirt_LGrass */	  true,  
	/* TT_LDirt_Stone */		  false, 
	/* TT_DDirt */			  true,  
	/* TT_Stone */			  false, 
	/* TT_LGrass */			  true,  
	/* TT_LGrass_DGrass */	  true,  
	/* TT_LGrass_Tree */		  false, 
	/* TT_DGrass */			  true,  
	/* TT_Tree */			  false, 
};


BLSquare::BLSquare()
	: m_vPos("xy")
	, m_eTilesType(TilesType_MAX)
	, m_pProp(NULL)
{
}

BLSquare::BLSquare(const BLVector2& pos)
	: m_vPos(pos)
	, m_eTilesType(TilesType_MAX)
	, m_pProp(NULL)
{
}

BLSquare::~BLSquare()
{
	if (m_pProp != NULL)
		delete m_pProp;
}

void BLSquare::SetPos(const BLVector2& pos)
{
	m_vPos = pos;
}

void BLSquare::SetPos(int i, int j)
{
	m_vPos.x = i;
	m_vPos.y = j;
	m_vPos.SetName(FormatString("%d,%d", m_vPos.x, m_vPos.y));
}

void BLSquare::SetProp(BLProp* pProp)
{
	m_pProp = pProp;
}


bool BLSquare::IsBlock(BLProp* ignore) const
{
	return (IsPermBlock() || IsTempBlock());
}

bool BLSquare::IsPermBlock(BLProp* ignore) const
{
	return (s_bIsBloc[m_eTilesType]);
}

bool BLSquare::IsTempBlock(BLProp* ignore) const
{
	return (m_pProp != NULL && m_pProp != ignore && m_pProp->IsBlock());
}

