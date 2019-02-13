#include "IBCube.h"
#include "CanvasBase.h"


IBCube::IBCube(const string& name)
	: m_sName(name)
	, m_pTopCube(NULL)
{
}

IBCube::~IBCube()
{
}

void IBCube::PutCube(IBCube* pCube)
{
	assert(m_pTopCube == NULL);
	m_pTopCube = pCube;
}

void IBCube::TakeCube()
{
	m_pTopCube = NULL;
}

void IBCube::Print() const
{
	LOG("Cube : %s", m_sName.c_str());
	if (m_pTopCube != NULL)
		LOG("  support %s", m_pTopCube->GetName().c_str());
	else
		LOG("  free");

	LOG("\n");
}

/*
string IBCube::GetData() const
{
	string Data;
	if (m_pTopCube != NULL)
		Data = " [" + m_pTopCube->GetName() + "]";
	else
		Data = " [free]";

	return Data;
}
*/


void IBCube::Draw(CanvasBase& canva, int i, int j) const
{
	int size = 48;
	int space = 32;
	int line = canva.GetHeight() - size;
	int left_space = 32;

	canva.DrawRect(left_space + space + i*(size + space), line - (size*(j + 1)), size, size, Color(255, 255, 255));
	canva.Print(left_space + space + i*(size + space) + size / 2, line - (size*j) - size / 2, canva.GetPrintFont(), 12, Center, Color(255, 255, 255), "%s", GetName().c_str());

	if (GetTopCube() != NULL)
	{
		GetTopCube()->Draw(canva, i, j + 1);
	}
}
