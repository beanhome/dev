#include "IBCube.h"


IBCube::IBCube()
	: m_pTopCube(NULL)
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

