#include "IBCost.h"

IBCost IBCost::MaxCost(FLT_MAX, INT32_MAX);
float IBCost::fFactCoeff = 1.f;
float IBCost::fActionCoeff = 1.f;


IBCost::IBCost()
	: m_fActionCost(0.f)
	, m_iFactCost(0)
{
	UpdateText();
}

IBCost::IBCost(const IBCost& other)
	: m_fActionCost(other.m_fActionCost)
	, m_iFactCost(other.m_iFactCost)
{
	UpdateText();
}

IBCost::IBCost(float fActionCost, sint32 iFactCost)
	: m_fActionCost(fActionCost)
	, m_iFactCost(iFactCost)
{
	UpdateText();
}

void IBCost::Reset()
{
	m_fActionCost = 0.f;
	m_iFactCost = 0;
	UpdateText();
}


bool IBCost::operator==(const IBCost& other) const
{
	return (m_fActionCost == other.m_fActionCost && m_iFactCost == other.m_iFactCost);
}

bool IBCost::operator!=(const IBCost& other) const
{
	return (m_fActionCost != other.m_fActionCost ||m_iFactCost != other.m_iFactCost);
}

bool IBCost::operator<(const IBCost& other) const
{
	return GetUniCost() < other.GetUniCost();
}

bool IBCost::operator<=(const IBCost& other) const
{
	return GetUniCost() <= other.GetUniCost();
}

bool IBCost::operator>(const IBCost& other) const
{
	return GetUniCost() > other.GetUniCost();
}

bool IBCost::operator>=(const IBCost& other) const
{
	return GetUniCost() >= other.GetUniCost();
}

IBCost IBCost::operator+(const IBCost& other) const
{
	IBCost out(*this);
	out += other;
	out.UpdateText();
	return out;
}

IBCost& IBCost::operator+=(const IBCost& other)
{
	if (other.m_fActionCost == FLT_MAX)
		m_fActionCost = FLT_MAX;
	else if (m_fActionCost != FLT_MAX)
		m_fActionCost += other.m_fActionCost;

	if (other.m_iFactCost == INT32_MAX)
		m_iFactCost = INT32_MAX;
	else if (m_iFactCost != INT32_MAX)
		m_iFactCost += other.m_iFactCost;
	
	UpdateText();

	return *this;
}


float IBCost::GetActionCost() const
{
	return m_fActionCost;
}

sint32 IBCost::GetFactCost() const
{
	return m_iFactCost;
}

float IBCost::GetUniCost() const
{
	return (float)m_iFactCost * fFactCoeff + m_fActionCost * fActionCoeff;
}

void IBCost::SetCost(float fActionCost, sint32 iFactCost)
{
	m_fActionCost = fActionCost;
	m_iFactCost = iFactCost;
	UpdateText();
}

void IBCost::SetActionCost(float fActionCost)
{
	m_fActionCost = fActionCost;
	UpdateText();
}

void IBCost::SetFactCost(sint32 iFactCost)
{
	m_iFactCost = iFactCost;
	UpdateText();
}

const string& IBCost::GetText() const
{
	return m_sText;
}


void IBCost::UpdateText()
{
	string sFact = (m_iFactCost == INT32_MAX ? "inf " : FormatString("%d ", m_iFactCost));
	string sAction = (m_fActionCost == FLT_MAX? "inf" : FormatString("%.1f", m_fActionCost));
	m_sText = sFact + sAction;
}



