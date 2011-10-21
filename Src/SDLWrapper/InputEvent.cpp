#include "Utils.h"

#include "InputEvent.h"

#include "SDL.h"

InputEvent::InputEvent()
	: m_pSDLEvent(new SDL_Event)
{
}

InputEvent::~InputEvent()
{
	delete m_pSDLEvent;
}

bool InputEvent::IsQuit() const
{
	return (m_pSDLEvent->type == SDL_QUIT);
}

bool InputEvent::IsMouse() const
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

bool InputEvent::IsKeyboard() const
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

EMouseEvent InputEvent::GetMouseEvent() const
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

bool InputEvent::GetMouseMove(uint16& x, uint16& y) const
{
	if (m_pSDLEvent->type != SDL_MOUSEMOTION)
		return false;

	x = m_pSDLEvent->motion.x;
	y = m_pSDLEvent->motion.y;

	return true;
}


EKeyboardEvent InputEvent::GetKeyboardEvent() const
{
	switch (m_pSDLEvent->type)
	{
		case SDL_KEYDOWN:		return KeyDown;
		case SDL_KEYUP:			return KeyUp;

		default:
			return EKeyboardEvent_Error;
	}
}

EKeyboardKey InputEvent::GetKeyboardKey() const
{
	switch (m_pSDLEvent->key.keysym.sym)
	{
		case SDLK_UP:			return KEY_UP;
		case SDLK_RIGHT:		return KEY_RIGHT;
		case SDLK_DOWN:			return KEY_DOWN;
		case SDLK_LEFT:			return KEY_LEFT;
		case SDLK_SPACE:		return KEY_SPACE;
		
		case SDLK_F1:			return KEY_F1;
		case SDLK_F2:			return KEY_F2;
		case SDLK_F3:			return KEY_F3;
		case SDLK_F4:			return KEY_F4;

		default:				return EKeyboardKey_Error;
	}
}
