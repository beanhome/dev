#ifndef __BOTLIFE_BLSQUARE_H__
#define __BOTLIFE_BLSQUARE_H__

#include "Utils.h"
#include "GridBase.h"

class Canvas;
class CanvasBase;
class BLBot;
class BLProp;
class Path;

class BLSquare
{
	public:
		BLSquare();

		int GetType() const { return m_iType; }
		void SetType(int type) { m_iType = type;}

		void SetProp(BLProp* pProp);
		const BLProp* GetProp() const { return m_pProp; }

		virtual bool IsBlock() const;
		virtual bool IsTempBlock() const;

	private:
		int m_iType;
		BLProp* m_pProp;
};

#endif