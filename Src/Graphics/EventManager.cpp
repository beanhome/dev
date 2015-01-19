#include "Utils.h"

#include "EventManager.h"
#include "GEngine.h"

EKeyboardKey EventManager::s_eMouseToKey[EMouseEvent_MAX] = 
{
	EKeyboardKey_Error,  /* MouseMove */
	MOUSE_LEFT,   /* LeftUp */
	MOUSE_LEFT,   /* LeftDown */
	MOUSE_MIDDLE, /* MiddleUp */
	MOUSE_MIDDLE, /* MiddleDown */
	MOUSE_RIGHT,  /* RightUp */
	MOUSE_RIGHT,  /* RightDown */
	MOUSE_WHEELUP,  /* WheelUpUp */
	MOUSE_WHEELUP,  /* WheelUpDown */
	MOUSE_WHEELDOWN,  /* WheelDownUp */
	MOUSE_WHEELDOWN,  /* WheelDownDown */
};

EKeyboardEvent EventManager::s_eMouseToEvent[EMouseEvent_MAX] = 
{
	EKeyboardEvent_Error,  /* MouseMove */
	KeyUp,    /* LeftUp */
	KeyDown,  /* LeftDown */
	KeyUp,    /* MiddleUp */
	KeyDown,  /* MiddleDown */
	KeyUp,    /* RightUp */
	KeyDown,  /* RightDown */
	KeyUp,    /* WheelUpUp */
	KeyDown,  /* WheelUpDown */
	KeyUp,    /* WheelDownUp */
	KeyDown,  /* WheelDownDown */
};


EventManager::EventManager(GEngine& ge)
	: m_oEngine(ge)
{
}

EventManager::~EventManager()
{
}

void EventManager::Update(float dt)
{
	//LOG("EventManager::Update\n");

	for (uint i=0 ; i<EKeyboardKey_Max ; ++i)
	{
		VirtualKey& oKey = m_aVirtualKey[i];
		switch (oKey.m_eState)
		{
			case KeyUp:			oKey.m_eState = KeyUp;		oKey.m_fDuration += dt;	break;
			case KeyDown:		oKey.m_eState = KeyDown;	oKey.m_fDuration += dt;	break;
			case KeyPressed:	oKey.m_eState = KeyDown;	oKey.m_fDuration = 0.f;	break;
			case KeyReleased:	oKey.m_eState = KeyUp;		oKey.m_fDuration = 0.f;	break;
			case KeyRepeat:		oKey.m_eState = KeyRepeat;	oKey.m_fDuration += dt;	break;
		}

		if (oKey.m_eState == KeyDown && oKey.m_fDuration > 0.5f
		 || oKey.m_eState == KeyRepeat && oKey.m_fDuration > 0.1f)
		{
			oKey.m_eState = KeyRepeat;
			oKey.m_fDuration = 0.f;

			CustomEvent oRepeatEvent(KeyRepeat, (EKeyboardKey)i, oKey.m_cChar);
			m_oEngine.ReceiveEvent(&oRepeatEvent);
		}
	}

	Event* pEvent = m_oEngine.CreateEvent();

	while (m_oEngine.PollEvent(pEvent))
	{
		if (pEvent->IsKeyboard())
		{
			EKeyboardKey eKey = pEvent->GetKeyboardKey();
			EKeyboardEvent eEvent = pEvent->GetKeyboardEvent();
			
			if (eKey == EKeyboardKey_Error)
				continue;

			if (eEvent == EKeyboardEvent_Error)
				continue;

			VirtualKey& oKey = m_aVirtualKey[eKey];

			switch (oKey.m_eState)
			{
				case KeyUp:			oKey.m_eState = (eEvent == KeyDown ? KeyPressed	: KeyUp);			break;
				case KeyDown:		oKey.m_eState = (eEvent == KeyDown ? KeyRepeat	: KeyReleased);		break;
				case KeyPressed:	oKey.m_eState = (eEvent == KeyDown ? KeyDown	: KeyReleased);		break;
				case KeyReleased:	oKey.m_eState = (eEvent == KeyDown ? KeyPressed	: KeyUp);			break;
				case KeyRepeat:		oKey.m_eState = (eEvent == KeyDown ? KeyRepeat	: KeyReleased);		break;
			}

			oKey.m_cChar = pEvent->GetKeyboardChar();
		}

		if (pEvent->IsMouse())
		{
			pEvent->GetMouseMove(m_iMouseX, m_iMouseY);

			VirtualKey& oKey = m_aVirtualKey[s_eMouseToKey[pEvent->GetMouseEvent()]];
			EKeyboardEvent& oEvent = s_eMouseToEvent[pEvent->GetMouseEvent()];

			switch (oKey.m_eState)
			{
				case KeyUp:			oKey.m_eState = (oEvent == KeyDown ? KeyPressed	: KeyUp);			break;
				case KeyDown:		oKey.m_eState = (oEvent == KeyDown ? KeyRepeat	: KeyReleased);		break;
				case KeyPressed:	oKey.m_eState = (oEvent == KeyDown ? KeyDown	: KeyReleased);		break;
				case KeyReleased:	oKey.m_eState = (oEvent == KeyDown ? KeyPressed	: KeyUp);			break;
				case KeyRepeat:		oKey.m_eState = (oEvent == KeyDown ? KeyRepeat	: KeyReleased);		break;
			}
		}

		m_oEngine.ReceiveEvent(pEvent);
	}

	delete pEvent;
}


