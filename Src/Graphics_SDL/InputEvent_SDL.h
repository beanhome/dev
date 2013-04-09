#ifndef __INPUTEVENT_SDL_H__
#define __INPUTEVENT_SDL_H__

#include "InputEvent.h"

union SDL_Event;

class InputEvent_SDL : public InputEvent
{
	public:
		InputEvent_SDL();
		virtual ~InputEvent_SDL();

		InputEvent_SDL& operator=(const InputEvent_SDL& src);

		bool IsQuit() const;
		bool IsMouse() const;
		bool IsKeyboard() const;
		
		EMouseEvent GetMouseEvent() const;
		bool GetMouseMove(sint32& x, sint32& y) const;

		EKeyboardEvent GetKeyboardEvent() const;
		EKeyboardKey GetKeyboardKey() const;

		SDL_Event* GetSDLEvent() { return m_pSDLEvent; }

	private:
		SDL_Event* m_pSDLEvent;
};


#endif // __INPUTEVENT_SDL_H__

