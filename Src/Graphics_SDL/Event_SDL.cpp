#include "SDL.h"

#include "Utils.h"
#include "Event_SDL.h"

const EKeyboardKey Event_SDL::s_eSDLKeyToKeyboardKey[SDLK_LAST] = 
{
#include "Event_SDLKeyToKeyboardKey.h"
};

const SDLKey Event_SDL::s_eKeyboardKeyToSDLKey[EKeyboardKey_Max] =
{
#include "Event_KeyboardKeyToSDLKey.h"
};

Event_SDL::Event_SDL()
	: m_pSDLEvent(new SDL_Event)
{
}

Event_SDL::~Event_SDL()
{
	delete m_pSDLEvent;
}

Event_SDL& Event_SDL::operator=(const Event_SDL& src)
{
	*m_pSDLEvent = *(src.m_pSDLEvent);

	return *this;
}


bool Event_SDL::IsQuit() const
{
	return (m_pSDLEvent->type == SDL_QUIT);
}

bool Event_SDL::IsMouse() const
{
	switch (m_pSDLEvent->type)
	{
		case SDL_MOUSEMOTION:
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
			return true;

		default:
			return false;
	}
}

bool Event_SDL::IsKeyboard() const
{
	switch (m_pSDLEvent->type)
	{
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			return true;

		default:
			return false;
	}
}

bool Event_SDL::IsResize() const
{
	switch (m_pSDLEvent->type)
	{
		case SDL_VIDEORESIZE:
			return true;

		default:
			return false;
	}

}


EMouseEvent Event_SDL::GetMouseEvent() const
{
	switch (m_pSDLEvent->type)
	{
		case SDL_MOUSEMOTION:
			return MouseMove;

		case SDL_MOUSEBUTTONDOWN:
		{
			switch (m_pSDLEvent->button.button)
			{
				case SDL_BUTTON_LEFT:		return LeftDown;
				case SDL_BUTTON_MIDDLE:		return MiddleDown;
				case SDL_BUTTON_RIGHT:		return RightDown;
				case SDL_BUTTON_WHEELUP:	return WheelUpDown;
				case SDL_BUTTON_WHEELDOWN:	return WheelDownDown;
				default: return EMouseEvent_Error;
			}
		}

		case SDL_MOUSEBUTTONUP:
		{
			switch (m_pSDLEvent->button.button)
			{
				case SDL_BUTTON_LEFT:		return LeftUp;
				case SDL_BUTTON_MIDDLE:		return MiddleUp;
				case SDL_BUTTON_RIGHT:		return RightUp;
				case SDL_BUTTON_WHEELUP:	return WheelUpUp;
				case SDL_BUTTON_WHEELDOWN:	return WheelDownUp;
				default: return EMouseEvent_Error;
			}
		}

		default:
			return EMouseEvent_Error;
	}
}

bool Event_SDL::GetMouseMove(sint32& x, sint32& y) const
{
	/*
	if (m_pSDLEvent->type != SDL_MOUSEMOTION)
		return false;

	x = m_pSDLEvent->motion.x;
	y = m_pSDLEvent->motion.y;
	*/

	int get_fX, get_fY;
	uint8 btnstate = SDL_GetMouseState( &get_fX, &get_fY );
	x = get_fX;
	y = get_fY;

	return true;
}


EKeyboardEvent Event_SDL::GetKeyboardEvent() const
{
	switch (m_pSDLEvent->type)
	{
		case SDL_KEYDOWN:		return KeyDown;
		case SDL_KEYUP:			return KeyUp;

		default:
			return EKeyboardEvent_Error;
	}
}

EKeyboardKey Event_SDL::GetKeyboardKey() const
{
	return s_eSDLKeyToKeyboardKey[m_pSDLEvent->key.keysym.sym];
}

void Event_SDL::GetResizeEvent(sint32& w, sint32& h) const
{
	w = m_pSDLEvent->resize.w;
	h = m_pSDLEvent->resize.h;
}

uint16 Event_SDL::GetKeyboardChar() const
{
	return m_pSDLEvent->key.keysym.unicode;
}

