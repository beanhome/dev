#ifndef __IBTABLE_H__
#define __IBTABLE_H__

#include "Utils.h"

class IBCube;

class IBTable
{
	public:
		IBTable();
		virtual ~IBTable();

		void PutCube(IBCube* pCube);
		void TakeCube(IBCube* pCube);
		bool HasCube(IBCube* pCube) const;

		void Print() const;

	private:
		set<IBCube*> m_aCube;
};

#endif
