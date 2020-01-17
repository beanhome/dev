#ifndef __IBWORLD_H__
#define __IBWORLD_H__

#include "Utils.h"
#include "IBTable.h"
#include "IBCube.h"

class IBCubeWorld
{
	public:
		IBCubeWorld();
		virtual ~IBCubeWorld();

		void Init(const char* sInit);
		IBCube* CreateCube(const string& name);
		IBCube* GetCube(const string& name);

		const vector<IBCube*>& GetCubes() const { return m_oCubes; }
		vector<IBCube*>& GetCubes() { return m_oCubes; }

		const IBTable& GetTable() const { return m_oTable; }


		void MoveCubeFromTableToCube(IBCube* pCube, IBCube* pDestCube);
		void MoveCubeFromCubeToCube(IBCube* pCube, IBCube* pOrigCube, IBCube* pDestCube);
		void MoveCubeFromCubeToTable(IBCube* pCube, IBCube* pOrigCube);

		bool IsCubeOnTable(IBCube* pCube);
		bool IsCubeOnCube(IBCube* pCube1, IBCube* pCube2);

		void Print() const;
		void Draw(class CanvasBase& oWorldCanva) const;

	private:
		IBTable			m_oTable;

		vector<IBCube*>	m_oCubes;
};

#endif
