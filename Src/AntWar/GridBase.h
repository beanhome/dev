#ifndef GRIDBASE_H
#define GRIDBASE_H

#include "Utils.h"
#include "Vector2.h"

enum EDirection
{
	North,
	Est,
	South,
	West,

	EDirection_MAX
};

template<typename TCase>
class GridBase;

template<typename TCase>
class GridArray
{
	friend class GridBase<TCase>;

	private:
		GridArray() {}
		~GridArray() {}

		void Init(int size, TCase* pBuff)
		{
			m_iSize = size;
			m_pBuffer = pBuff;
		}

	public:
		TCase& operator[](int i)
		{
			while (i<0) i += m_iSize;
			while (i>=m_iSize) i -= m_iSize;
			return m_pBuffer[i];
		}

		const TCase& operator[](int i) const
		{
			while (i<0) i += m_iSize;
			while (i>=m_iSize) i -= m_iSize;
			return m_pBuffer[i];
		}

	private:
		int m_iSize;

		TCase* m_pBuffer;
};

template<typename TCase>
class GridBase
{
	public:
		GridBase()
			: m_pBuffer(NULL)
			, m_aGridArray(NULL)
			, m_iWidth(0)
			, m_iHeight(0)
		{}

		~GridBase()
		{
			if (m_pBuffer != NULL)		delete [] m_pBuffer;
			if (m_aGridArray != NULL)	delete [] m_aGridArray;
		}


		uint GetWidth() const { return m_iWidth; }
		uint GetHeight() const { return m_iHeight; }
		uint GetSize() const { return m_iWidth * m_iHeight; }

		void Init(uint iWidth, uint iHeight)
		{
			if (m_pBuffer != NULL)
				delete [] m_pBuffer;

			if (m_aGridArray != NULL)
				delete [] m_aGridArray;

			m_iWidth = iWidth;
			m_iHeight = iHeight;
			m_pBuffer = new TCase[iWidth * iHeight];
			m_aGridArray = new GridArray<TCase>[iWidth];

			for (uint x=0 ; x<iWidth ; ++x)
			{
				m_aGridArray[x].Init(iHeight, m_pBuffer + x * m_iHeight);
			}
		}

		void Normalize(Vector2& pos) const
		{
			Normalize(pos.x, pos.y);
		}

		void Normalize(int& i, int& j) const
		{
			while (i<0) i += m_iWidth;
			while ((uint)i>=m_iWidth) i -= m_iWidth;
			while (j<0) j += m_iHeight;
			while ((uint)j>=m_iHeight) j -= m_iHeight;
		}

		uint GetIndex(int i, int j) const
		{
			Normalize(i, j);
			return i * GetHeight() + j;
		}

		uint GetIndex(Vector2 pos) const
		{
			return GetIndex(pos.x, pos.y);
		}

		Vector2 GetCoord(uint id) const
		{
			ASSERT(id < m_iWidth * m_iHeight);
			Vector2 pos;
			GetCoord(id, pos.x, pos.y);
			return pos;
		}

		void GetCoord(uint id, int& i, int& j) const
		{
			i = id / GetHeight();
			j = id % GetHeight();

			Normalize(i, j);
		}

		void GetCoord(uint id, Vector2& pos) const
		{
			pos = GetCoord(id);
		}

		Vector2 GetCoord(const Vector2& pos, EDirection dir) const
		{
			static const Vector2 vMove[EDirection_MAX] = { Vector2(0, -1), Vector2(1, 0), Vector2(0, 1), Vector2(-1, 0) };
			Vector2 out(pos.x + vMove[dir].x, pos.y + vMove[dir].y);
			Normalize(out);
			return out;
		}

		const TCase&	GetCase(uint id) const							{ ASSERT(id < m_iWidth * m_iHeight); return m_pBuffer[id]; }
		TCase&			GetCase(uint id)								{ ASSERT(id < m_iWidth * m_iHeight); return m_pBuffer[id]; }
		const TCase&	GetCase(int i, int j) const						{ return operator[](i)[j]; }
		TCase&			GetCase(int i, int j)							{ return operator[](i)[j]; }
		const TCase&	GetCase(const Vector2& pos) const				{ return GetCase(pos.x, pos.y); }
		TCase&			GetCase(const Vector2& pos)						{ return GetCase(pos.x, pos.y); }
		const TCase&	GetCase(int i, int j, EDirection dir) const		{ return GetCase(GetCoord(Vector2(i, j), dir)); }
		TCase&			GetCase(int i, int j, EDirection dir)			{ return GetCase(GetCoord(Vector2(i, j), dir)); }

		GridArray<TCase>& operator[](int x)
		{
			ASSERT(m_pBuffer != NULL);

			while (x<0) x += m_iWidth;
			while ((uint)x>=m_iWidth) x -= m_iWidth;

			return m_aGridArray[x];
		}

		const GridArray<TCase>& operator[](int x) const
		{
			ASSERT(m_pBuffer != NULL);

			while (x<0) x += m_iWidth;
			while ((uint)x>=m_iWidth) x -= m_iWidth;

			return m_aGridArray[x];
		}

		const TCase& operator[](const Vector2& coord) const
		{
			return GetCase(coord);
		}

		TCase& operator[](const Vector2& coord)
		{
			return GetCase(coord);
		}

		int DistanceSq(const Vector2 &loc1, const Vector2 &loc2)
		{
			uint d1 = abs(loc1.x-loc2.x);
			uint d2 = abs(loc1.y-loc2.y);
			int dr = min<uint>(d1, m_iWidth-d1);
			int dc = min<uint>(d2, m_iHeight-d2);
			return (dr*dr + dc*dc);
		}

	private:
		TCase* m_pBuffer;
		GridArray<TCase>* m_aGridArray;

		uint m_iWidth;
		uint m_iHeight;
};

#endif //GRID_H
