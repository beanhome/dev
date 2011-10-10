#include "Grid.h"
#include "Utils.h"

#include "Square.h"



GridArray::GridArray()
{

}

GridArray::~GridArray()
{

}

void GridArray::Init(int size, Square* pBuff)
{
	m_iSize = size;
	m_pBuffer = pBuff;
}

Square& GridArray::operator[](int i)
{
	while (i<0) i += m_iSize;
	while (i>=m_iSize) i -= m_iSize;

	return m_pBuffer[i];
}

const Square& GridArray::operator[](int i) const
{
	while (i<0) i += m_iSize;
	while (i>=m_iSize) i -= m_iSize;

	return m_pBuffer[i];
}


Grid::Grid()
	: m_pBuffer(NULL)
	, m_aGridArray(NULL)
	, m_iWidth(0)
	, m_iHeight(0)
{
}

Grid::~Grid()
{
	if (m_pBuffer != NULL)
		delete [] m_pBuffer;

	if (m_aGridArray != NULL)
		delete [] m_aGridArray;
}

GridArray& Grid::operator[](int x)
{
	ASSERT(m_pBuffer != NULL);

	while (x<0) x += m_iWidth;
	while ((uint)x>=m_iWidth) x -= m_iWidth;

	return m_aGridArray[x];
}

const GridArray& Grid::operator[](int x) const
{
	ASSERT(m_pBuffer != NULL);

	while (x<0) x += m_iWidth;
	while ((uint)x>=m_iWidth) x -= m_iWidth;

	return m_aGridArray[x];
}


void Grid::Init(uint iWidth, uint iHeight)
{
	if (m_pBuffer != NULL)
		delete [] m_pBuffer;

	if (m_aGridArray != NULL)
		delete [] m_aGridArray;

	m_iWidth = iWidth;
	m_iHeight = iHeight;
	m_pBuffer = new Square[iWidth * iHeight];
	m_aGridArray = new GridArray[iWidth];

	for (uint x=0 ; x<iWidth ; ++x)
	{
		m_aGridArray[x].Init(iHeight, m_pBuffer + x * m_iHeight);
	}
}

void Grid::NewTurn()
{
	for (uint x=0 ; x<m_iWidth ; ++x)
	{
		for (uint y=0 ; y<m_iHeight; ++y)
		{
			m_aGridArray[x][y].NewTurn();
		}
	}

}


