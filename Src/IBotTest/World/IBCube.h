#ifndef __IBCUBE_H__
#define __IBCUBE_H__

#include "Utils.h"

class IBCube
{
	public:
		IBCube(const string& name);
		virtual ~IBCube();

		const string& GetName() const { return m_sName; }

		void PutCube(IBCube* pCube);
		void TakeCube();
		
		bool IsFree() const { return (m_pTopCube == NULL); }
		bool HasCube(IBCube* pCube) const { return (m_pTopCube == pCube); }
		const IBCube* GetTopCube() const { return m_pTopCube; }

		void Print() const;
		void Draw(class CanvasBase& canva, int i, int j) const;

	private:
		string m_sName;
		IBCube* m_pTopCube;
};

#endif
