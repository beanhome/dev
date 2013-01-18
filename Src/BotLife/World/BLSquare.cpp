#include "BLSquare.h"

BLSquare::BLSquare()
	: m_iType(0)
	, m_pProp(NULL)
{}

bool BLSquare::IsBlock() const
{
	return (m_iType == 1);
}
