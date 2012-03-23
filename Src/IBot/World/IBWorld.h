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

		IBCube* GetCube1() { return &m_oCube1; }
		IBCube* GetCube2() { return &m_oCube2; }
		IBCube* GetCube3() { return &m_oCube3; }

		void MoveCubeFromTableToCube(IBCube* pCube, IBCube* pDestCube);
		void MoveCubeFromCubeToCube(IBCube* pCube, IBCube* pOrigCube, IBCube* pDestCube);
		void MoveCubeFromCubeToTable(IBCube* pCube, IBCube* pOrigCube);

		bool IsCubeOnTable(IBCube* pCube);
		bool IsCubeOnCube(IBCube* pCube1, IBCube* pCube2);

	private:
		IBTable		m_oTable;
		IBCube		m_oCube1;
		IBCube		m_oCube2;
		IBCube		m_oCube3;
};

#endif
