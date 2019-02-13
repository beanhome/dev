#include "BLPath.h"

BLPath::BLPath(const string& name)
	: BLObject(name)
	, Path()
	, m_iCurrentStep(0)
{
}

BLPath::BLPath(const string& name, const Vector2& start, const deque<Vector2>& oPath)
	: BLObject(name)
	, Path(start, oPath)
	, m_iCurrentStep(0)
{

}

BLPath::~BLPath()
{
}

void BLPath::FormatData() const
{
	//m_sData = FormatString("(%d)", GetLength());
}

void BLPath::Print() const
{
	LOG("Path %s ", m_sName.c_str());
	Path::Print();
}

void BLPath::ResetStep()
{
	m_iCurrentStep = 0;
}

bool BLPath::NextStep()
{
	m_iCurrentStep++;
	
	return (m_iCurrentStep < GetLength());
}

Vector2 BLPath::GetCurrentStep() const
{
	return operator[](m_iCurrentStep);
}

