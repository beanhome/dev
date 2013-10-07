#ifndef __BLPROP_H__
#define __BLPROP_H__

#include "Utils.h"
#include "BLObject.h"

class BLWorld;
class Image;
class ImageResource;

class BLProp : public BLObject
{
	public:
		BLProp(BLWorld& oWorld, const string& name, const Vector2& pos = Vector2(0,0));
		virtual ~BLProp();
	
		virtual IBObject* Clone() const { return new BLProp(*this); }

		virtual void			SetPos(const Vector2& p);
		void					SetLoc(float x, float y);

		void					SetVisible(bool bVisible = true) { m_bVisible = bVisible; }

		virtual bool			IsBlock() const { return false; }
		virtual bool			IsPickable() const { return false; }
		virtual bool			IsMovable() const { return false; }

		const ImageResource*	GetImageResource() const;
		void					Draw() const;

		virtual	void			FormatData() const { m_sData = m_sName; }

	protected:
		BLWorld&				m_oWorld;
		bool					m_bVisible;
		Image*					m_pImage;
};

#endif
