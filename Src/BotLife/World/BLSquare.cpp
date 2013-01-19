#include "BLSquare.h"
#include "BLProp.h"

BLSquare::BLSquare()
	: m_iType(0)
	, m_pProp(NULL)
{
}

void BLSquare::SetProp(BLProp* pProp)
{
	m_pProp = pProp;
}


bool BLSquare::IsBlock() const
{
	return (m_iType == 1 || (m_pProp != NULL && m_pProp->IsBlock()));
}

bool BLSquare::IsTempBlock() const
{
	return (m_pProp != NULL && m_pProp->IsTempBlock());
}
