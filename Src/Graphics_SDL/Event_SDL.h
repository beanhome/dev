#ifndef __EVENT_SDL_H__
#define __EVENT_SDL_H__

#include "Event.h"

union SDL_Event;

class Event_SDL : public Event
{
	public:
		Event_SDL();
		virtual ~Event_SDL();

		Event_SDL& operator=(const Event_SDL& src);

		bool IsQuit() const;
		bool IsMouse() const;
		bool IsKeyboard() const;
		bool IsResize() const;
		
		EMouseEvent GetMouseEvent() const;
		bool GetMouseMove(sint32& x, sint32& y) const;

		EKeyboardEvent GetKeyboardEvent() const;
		EKeyboardKey GetKeyboardKey() const;

		void GetResizeEvent(sint32& w, sint32& h) const;

		SDL_Event* GetSDLEvent() { return m_pSDLEvent; }

	private:
		SDL_Event* m_pSDLEvent;
};


#endif // __EVENT_SDL_H__

