#ifndef __EVENTMANAGER_H__
#define __EVENTMANAGER_H__

#include "Utils.h"

#include "Event.h"

class GEngine;

class EventManager
{
	public:
		EventManager(GEngine& ge);
		~EventManager();

		void					Update();
		
		EKeyboardEvent			GetVirtualKey(EKeyboardKey eKey) const { return m_aVirtualKey[eKey]; }

		sint32					GetMouseX() const { return m_iMouseX; }
		sint32					GetMouseY() const { return m_iMouseY; }

	private:
		GEngine& m_oEngine;

		EKeyboardEvent m_aVirtualKey[EKeyboardKey_Max];

		sint32							m_iMouseX;
		sint32							m_iMouseY;

		static EKeyboardKey s_eMouseToKey[EMouseEvent_MAX];
		static EKeyboardEvent s_eMouseToEvent[EMouseEvent_MAX];

};


#endif // __EVENTMANAGER_H__

