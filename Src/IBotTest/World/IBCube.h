#ifndef __IBCUBE_H__
#define __IBCUBE_H__

#include "Utils.h"

class IBCube
{
	public:
		IBCube();
		IBCube(const string& name);
		virtual ~IBCube();

		const string& GetName() const { return m_sName; }
		void SetName(const string& name) { m_sName = name; }

		void PutCube(IBCube* pCube);
		void TakeCube();
		
		bool IsFree() const { return (m_pTopCube == NULL); }
		bool HasCube(IBCube* pCube) const { return (m_pTopCube == pCube); }
		const IBCube* GetTopCube() const { return m_pTopCube; }

		void  Print() const;

	private:
		string  m_sName;
		IBCube* m_pTopCube;
};

#endif
