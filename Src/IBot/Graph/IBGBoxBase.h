#ifndef __IBGBOXBASE_H__
#define __IBGBOXBASE_H__

#include "Utils.h"
//#include "Color.h"
#include "Canvas.h"
#include "Vector2.h"

class CanvasBase;

class IBGBox;
class Color;

class IBGBoxBase
{
	public:
		IBGBoxBase(CanvasBase& parent);

		sint16 GetX() const { return (sint16)m_oCanvas.GetPosX(); }
		sint16 GetY() const { return (sint16)m_oCanvas.GetPosY(); }
		sint16 GetW() const { return (sint16)m_oCanvas.GetWidth(); }
		sint16 GetH() const { return (sint16)m_oCanvas.GetHeight(); }

		void SetX(sint16 _x) { m_oCanvas.SetPosX(_x); }
		void SetY(sint16 _y) { m_oCanvas.SetPosY(_y); }
		void SetW(sint16 _w) { m_oCanvas.SetWidth(_w); }
		void SetH(sint16 _h) { m_oCanvas.SetHeight(_h); }

		sint16 GetLeft() const { return GetX(); }
		sint16 GetRight() const { return GetX() + GetW(); }
		sint16 GetTop() const { return GetY(); }
		sint16 GetBottom() const { return GetY() + GetH(); }
		sint16 GetMidW() const { return GetX() + GetW()/2; }
		sint16 GetMidH() const { return GetY() + GetH()/2; }

		sint16 GetScreenX() const { return (sint16)m_oCanvas.GetScreenPosX(); }
		sint16 GetScreenY() const { return (sint16)m_oCanvas.GetScreenPosY(); }

		const CanvasBase& GetCanvas() const { return m_oCanvas; }
		CanvasBase& GetCanvas() { return m_oCanvas; }
		
		/*
		Vector2 GetTopLeft() const { return Vector2(GetX(), GetY()); }
		Vector2 GetTopMiddle() const { return Vector2(GetX() + GetW()/2, GetY()); }
		Vector2 GetTopRight() const { return Vector2(GetX() + GetW(), GetY()); }
		Vector2 GetMiddleLeft() const { return Vector2(GetX(), GetY()+GetH()/2); }
		Vector2 GetMiddle() const { return Vector2(GetX() + GetW()/2, GetY()+GetH()/2); }
		Vector2 GetMiddleRight() const { return Vector2(GetX() + GetW(), GetY()+GetH()/2); }
		Vector2 GetBottomLeft() const { return Vector2(GetX(), GetY()+GetH()); }
		Vector2 GetBottomMiddle() const { return Vector2(GetX() + GetW()/2, GetY()+GetH()); }
		Vector2 GetBottomRight() const { return Vector2(GetX() + GetW(), GetY()+GetH()); }
		*/

		virtual void	Resize() = 0;
		virtual void	Draw() const = 0;
		
		void			DrawFrame(const Color& color) const;

	protected:
		Canvas		m_oCanvas;
};

#endif
