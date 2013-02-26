#ifndef __INPUT_H__
#define __INPUT_H__

#include "Utils.h"

#include "InputEvent.h"

class GEngine;

class Input
{
	public:
		Input(GEngine& ge);
		~Input();

		void					Update();
		
		bool					IsQuit() const { return m_bQuit; }

		EKeyboardEvent			GetVirtualKey(EKeyboardKey eKey) const { return m_aVirtualKey[eKey]; }

		sint32					GetMouseX() const { return m_iMouseX; }
		sint32					GetMouseY() const { return m_iMouseY; }

	private:
		GEngine& m_oEngine;
		bool m_bQuit;

		EKeyboardEvent m_aVirtualKey[EKeyboardKey_Max];

		sint32							m_iMouseX;
		sint32							m_iMouseY;

		static EKeyboardKey s_eMouseToKey[EMouseEvent_MAX];
		static EKeyboardEvent s_eMouseToEvent[EMouseEvent_MAX];

};


#endif // __Input_H__

