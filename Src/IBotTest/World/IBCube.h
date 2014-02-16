#ifndef __IBCUBE_H__
#define __IBCUBE_H__

#include "Utils.h"
#include "World\IBObject.h"

class IBCube : public IBObject
{
	public:
		IBCube(const string& name);
		virtual ~IBCube();

		virtual IBObject* Clone() const { return new IBCube(*this); }

		void PutCube(IBCube* pCube);
		void TakeCube();
		
		bool IsFree() const { return (m_pTopCube == NULL); }
		bool HasCube(IBCube* pCube) const { return (m_pTopCube == pCube); }
		const IBCube* GetTopCube() const { return m_pTopCube; }

		void  Print() const;

	protected:
		virtual void		FormatData() const;


	private:
		IBCube* m_pTopCube;
};

#endif
