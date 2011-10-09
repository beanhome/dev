#ifndef GRID_H
#define GRID_H

#include "Utils.h"

struct Square;

class Grid;

class GridArray
{
	friend class Grid;

	private:
		GridArray();
		~GridArray();

		void Init(int size, Square* pBuff);

	public:
		Square& operator[](int x);

	private:
		int m_iSize;

		Square* m_pBuffer;
};


class Grid
{
	public:
		Grid();
		~Grid();

		void Init(uint iWidth, uint iHeight);

		GridArray& operator[](int x);

	private:
		Square* m_pBuffer;
		GridArray* m_aGridArray;

		uint m_iWidth;
		uint m_iHeight;
};

#endif //GRID_H
