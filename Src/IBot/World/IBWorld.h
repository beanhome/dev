#ifndef __IBWORLD_H__
#define __IBWORLD_H__

#include "Utils.h"
#include "IBTable.h"
#include "IBCube.h"

class IBWorld
{
	public:
		IBWorld();
		virtual ~IBWorld();

		void Init();

		IBCube* GetCubeA() { return &m_oCubes[0]; }
		IBCube* GetCubeB() { return &m_oCubes[1]; }
		IBCube* GetCubeC() { return &m_oCubes[2]; }

		const IBCube* GetCubeA() const { return &m_oCubes[0]; }
		const IBCube* GetCubeB() const { return &m_oCubes[1]; }
		const IBCube* GetCubeC() const { return &m_oCubes[2]; }

		const vector<IBCube>& GetCubes() const { return m_oCubes; }
		vector<IBCube>& GetCubes() { return m_oCubes; }

		void MoveCubeFromTableToCube(IBCube* pCube, IBCube* pDestCube);
		void MoveCubeFromCubeToCube(IBCube* pCube, IBCube* pOrigCube, IBCube* pDestCube);
		void MoveCubeFromCubeToTable(IBCube* pCube, IBCube* pOrigCube);

		bool IsCubeOnTable(IBCube* pCube);
		bool IsCubeOnCube(IBCube* pCube1, IBCube* pCube2);

		void Print() const;

	private:
		IBTable			m_oTable;

		vector<IBCube>	m_oCubes;
};

#endif
