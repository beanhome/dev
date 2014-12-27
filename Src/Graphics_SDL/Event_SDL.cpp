#include "SDL.h"

#include "Utils.h"
#include "Event_SDL.h"


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
				case SDL_BUTTON_LEFT:	return LeftDown;
				case SDL_BUTTON_MIDDLE:	return MiddleDown;
				case SDL_BUTTON_RIGHT:	return RightDown;
				default: return EMouseEvent_Error;
			}
		}

		case SDL_MOUSEBUTTONUP:
		{
			switch (m_pSDLEvent->button.button)
			{
				case SDL_BUTTON_LEFT:	return LeftUp;
				case SDL_BUTTON_MIDDLE:	return MiddleUp;
				case SDL_BUTTON_RIGHT:	return RightUp;
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
	switch (m_pSDLEvent->key.keysym.sym)
	{
		case SDLK_UP:			return KEY_UP;
		case SDLK_RIGHT:		return KEY_RIGHT;
		case SDLK_DOWN:			return KEY_DOWN;
		case SDLK_LEFT:			return KEY_LEFT;
		case SDLK_SPACE:		return KEY_SPACE;

		case SDLK_INSERT:		return KEY_INSERT;
		case SDLK_DELETE:		return KEY_DELETE;
		case SDLK_HOME:			return KEY_HOME;
		case SDLK_END:			return KEY_END;
		case SDLK_PAGEUP:		return KEY_PAGEUP;
		case SDLK_PAGEDOWN:		return KEY_PAGEDOWN;

		case SDLK_RETURN:		return KEY_ENTER;
		case SDLK_ESCAPE:		return KEY_ESC;

		case SDLK_F1:			return KEY_F1;
		case SDLK_F2:			return KEY_F2;
		case SDLK_F3:			return KEY_F3;
		case SDLK_F4:			return KEY_F4;

		default:				return EKeyboardKey_Error;
	}
}

void Event_SDL::GetResizeEvent(sint32& w, sint32& h) const
{
	w = m_pSDLEvent->resize.w;
	h = m_pSDLEvent->resize.h;
}
