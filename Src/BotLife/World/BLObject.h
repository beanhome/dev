#ifndef __BLOBJECT_H__
#define __BLOBJECT_H__

#include "Utils.h"
#include "World\IBObject.h"
#include "World\IBVector2.h"

class BLObject : public IBObject
{
	public:
		BLObject();
		BLObject(const string& name);
		BLObject(const Vector2& pos);
		BLObject(const string& name, const Vector2& pos);
		virtual ~BLObject();

		const IBVector2& GetPos() const { return m_vPos; }
		void SetPos(const Vector2& p) { m_vPos = p; }

		void  Print() const;

	protected:
		IBVector2 m_vPos;
};

#endif
