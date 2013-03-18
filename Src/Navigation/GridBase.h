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

	CardDirCount,

	NorthEst = 4,
	SouthEst,
	SouthWest,
	NorthWest,

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

class GridOp
{
	public:
		GridOp(bool bNormalize = false, bool bDiagMode = false)
			: m_iWidth(0)
			, m_iHeight(0)
			, m_bNormalized(bNormalize)
			, m_bDiagMode(bDiagMode)
		{}

		GridOp& operator=(const GridOp& grid)
		{
			Init(grid.m_iWidth, grid.m_iHeight);
			m_bNormalized = grid.m_bNormalized;
			return *this;
		}

		bool IsNormalized() const { return m_bNormalized; }
		bool IsDiagMode() const { return m_bDiagMode; }

		uint GetWidth() const { return m_iWidth; }
		uint GetHeight() const { return m_iHeight; }
		uint GetSize() const { return m_iWidth * m_iHeight; }

		void Init(uint iWidth, uint iHeight)
		{
			m_iWidth = iWidth;
			m_iHeight = iHeight;
		}

		void Normalize(Vector2& pos) const
		{
			Normalize(pos.x, pos.y);
		}

		void Normalize(int& i, int& j) const
		{
			ASSERT(m_bNormalized);
			while (i<0) i += m_iWidth;
			while ((uint)i>=m_iWidth) i -= m_iWidth;
			while (j<0) j += m_iHeight;
			while ((uint)j>=m_iHeight) j -= m_iHeight;
		}

		uint GetIndex(int i, int j) const
		{
			if (m_bNormalized)
				Normalize(i, j);
			
			ASSERT(i>=0 && i<(int)m_iWidth);
			ASSERT(j>=0 && j<(int)m_iHeight);

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

			if (m_bNormalized)
				Normalize(i, j);
		}

		void GetCoord(uint id, Vector2& pos) const
		{
			pos = GetCoord(id);
		}

		bool GetCoord(const Vector2& pos, EDirection dir, Vector2& out) const
		{
			static const Vector2 vMove[EDirection_MAX] = { Vector2(0, -1), Vector2(1, 0), Vector2(0, 1), Vector2(-1, 0), Vector2(1, -1), Vector2(1, 1), Vector2(-1, 1), Vector2(-1, -1) };
			out = Vector2(pos.x + vMove[dir].x, pos.y + vMove[dir].y);

			if (m_bNormalized)
				Normalize(out);

			return (out.x>=0 && out.x<(int)m_iWidth && out.y>=0 && out.y<(int)m_iHeight);
		}

		/*
		Vector2 GetCoord(const Vector2& pos, EDirection dir) const
		{
			static const Vector2 vMove[EDirection_MAX] = { Vector2(0, -1), Vector2(1, 0), Vector2(0, 1), Vector2(-1, 0), Vector2(1, -1), Vector2(1, 1), Vector2(-1, 1), Vector2(-1, -1) };
			Vector2 out(pos.x + vMove[dir].x, pos.y + vMove[dir].y);
			Normalize(out);
			return out;
		}
		*/
		int Distance(const Vector2 &loc1, const Vector2 &loc2) const
		{
			return Distance(loc1, loc2, m_bDiagMode);
		}

		int Distance(const Vector2 &loc1, const Vector2 &loc2, bool bDiagMode) const
		{
			int d1 = abs(loc1.x-loc2.x);
			int d2 = abs(loc1.y-loc2.y);

			return (bDiagMode ? std::min<int>(d1, d2) + abs(d1-d2) : d1 + d2);
		}

		EDirection GetDirection(const Vector2 &startLoc, const Vector2 &targetLoc) const
		{
			int iHori = targetLoc.x - startLoc.x;
			int iVert = targetLoc.y - startLoc.y;

			if (iHori > (int)m_iWidth / 2)
				iHori -= m_iWidth;

			if (iHori < -((int)m_iWidth) / 2)
				iHori += m_iWidth;

			if (iVert > (int)m_iHeight / 2)
				iVert -= m_iHeight;

			if (iVert < -((int)m_iHeight) / 2)
				iVert += m_iHeight;

			if (abs(iHori) > abs(iVert))
			{
				return (iHori > 0 ? Est : West);
			}
			else
			{
				return (iVert > 0 ? South : North);
			}
		}

	protected:
		uint m_iWidth;
		uint m_iHeight;

		bool m_bNormalized;
		bool m_bDiagMode;

};

template<typename TCase>
class GridBase : public GridOp
{
	public:
		GridBase(bool bNormalize = false, bool bDiagMode = false)
			: GridOp(bNormalize, bDiagMode)
			, m_pBuffer(NULL)
			, m_aGridArray(NULL)
		{}

		~GridBase()
		{
			if (m_pBuffer != NULL)		delete [] m_pBuffer;
			if (m_aGridArray != NULL)	delete [] m_aGridArray;
		}

		GridBase& operator=(const GridBase& grid)
		{
			Init(grid.m_iWidth, grid.m_iHeight);
			int size = sizeof(TCase);
			int len = m_iWidth*m_iHeight;
			memcpy(m_pBuffer, grid.m_pBuffer, sizeof(TCase) * m_iWidth*m_iHeight);
			return *this;
		}

		void Init(uint iWidth, uint iHeight)
		{
			GridOp::Init(iWidth, iHeight);

			if (m_pBuffer != NULL)
				delete [] m_pBuffer;

			if (m_aGridArray != NULL)
				delete [] m_aGridArray;

			m_pBuffer = new TCase[iWidth * iHeight];
			m_aGridArray = new GridArray<TCase>[iWidth];

			for (uint x=0 ; x<iWidth ; ++x)
			{
				m_aGridArray[x].Init(iHeight, m_pBuffer + x * m_iHeight);
			}
		}

		bool			IsCoordValid(int i, int j) const				{ return (m_bNormalized || (i>=0 && i<(int)m_iWidth && j>=0 && j<(int)m_iHeight)); }
		bool			IsCoordValid(const Vector2& pos) const			{ return IsCoordValid(pos.x, pos.y); }

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
			ASSERT(m_bNormalized || (x>=0 && x<(int)m_iWidth));

			while (x<0) x += m_iWidth;
			while ((uint)x>=m_iWidth) x -= m_iWidth;

			return m_aGridArray[x];
		}

		const GridArray<TCase>& operator[](int x) const
		{
			ASSERT(m_pBuffer != NULL);
			ASSERT(m_bNormalized || (x>=0 && x<(int)m_iWidth));

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

	private:
		TCase* m_pBuffer;
		GridArray<TCase>* m_aGridArray;
};

#endif //GRID_H
