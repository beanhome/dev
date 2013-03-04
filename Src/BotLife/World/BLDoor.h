#ifndef __BLDoor_H__
#define __BLDoor_H__

#include "Utils.h"
#include "BLProp_FB.h"

class BLWorld;
class Image;
class ImageResource;

class BLDoor : public BLProp_FB
{
	public:
		enum Dir
		{
			Horiz,
			Verti
		};

	public:
		BLDoor(BLWorld& oWorld, const string& name, Dir eDir, const Vector2& pos = Vector2(0,0));
		virtual ~BLDoor();

		void Open() { SetState(true); }
		void Close() { SetState(false); }
		bool IsOpen() const { return m_bOpen; }

		virtual bool IsTempBlock() const { return !m_bOpen; }

	private:
		void SetState(bool bOpen) { m_bOpen = bOpen; SetCurrent((m_eDir*2) + m_bOpen); }

	protected:
		Dir m_eDir;
		bool m_bOpen;
};

#endif
