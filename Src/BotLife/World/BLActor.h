#ifndef __BLACTOR_H__
#define __BLACTOR_H__

#include "Utils.h"
#include "BLObject.h"
#include "Vector2.h"

class BLActor : public BLObject
{
	public:
		BLActor(const string& name);
		BLActor(const string& name, const Vector2& pos);
		virtual ~BLActor();

		virtual BLObject* Clone() const { return new BLActor(*this); }

		virtual const Vector2& GetPos() const { return m_vPos; }
		virtual Vector2& GetPos() { return m_vPos; }
		virtual void SetPos(const Vector2& p) { m_vPos = p; }

		void  Print() const;

	protected:
		Vector2 m_vPos;
};

#endif
