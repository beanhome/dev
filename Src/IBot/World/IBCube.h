#ifndef __IBCUBE_H__
#define __IBCUBE_H__

#include "Utils.h"

class IBCube
{
	public:
		IBCube();
		virtual ~IBCube();

		void PutCube(IBCube* pCube);
		void TakeCube();
		
		bool IsFree() { return (m_pTopCube == NULL); }
		bool HasCube(IBCube* pCube) { return (m_pTopCube == pCube); }

	private:
		IBCube* m_pTopCube;
};

#endif
