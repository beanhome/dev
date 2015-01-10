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
};


EventManager::EventManager(GEngine& ge)
	: m_oEngine(ge)
{
	for (uint i=0 ; i<EKeyboardKey_Max ; ++i)
	{
		m_aVirtualKey[i] = KeyUp;
	}
}

EventManager::~EventManager()
{
}

void EventManager::Update()
{
	//LOG("EventManager::Update\n");

	for (uint i=0 ; i<EKeyboardKey_Max ; ++i)
	{
		EKeyboardEvent& oKey = m_aVirtualKey[i];
		switch (oKey)
		{
			case KeyUp:			oKey = KeyUp;		break;
			case KeyDown:		oKey = KeyDown;		break;
			case KeyPressed:	oKey = KeyDown;		break;
			case KeyReleased:	oKey = KeyUp;		break;
			case KeyRepeat:		oKey = KeyDown;		break;
		}
	}

	Event* pEvent = m_oEngine.CreateEvent();

	while (m_oEngine.PollEvent(pEvent))
	{
		if (pEvent->IsKeyboard())
		{
			EKeyboardEvent& oKey = m_aVirtualKey[pEvent->GetKeyboardKey()];
			EKeyboardEvent oEvent = pEvent->GetKeyboardEvent();

			switch (oKey)
			{
				case KeyUp:			oKey = (oEvent == KeyDown ? KeyPressed	: KeyUp);			break;
				case KeyDown:		oKey = (oEvent == KeyDown ? KeyRepeat	: KeyReleased);		break;
				case KeyPressed:	oKey = (oEvent == KeyDown ? KeyDown		: KeyReleased);		break;
				case KeyReleased:	oKey = (oEvent == KeyDown ? KeyPressed	: KeyUp);			break;
				case KeyRepeat:		oKey = (oEvent == KeyDown ? KeyRepeat	: KeyReleased);		break;
			}
		}

		if (pEvent->IsMouse())
		{
			pEvent->GetMouseMove(m_iMouseX, m_iMouseY);

			EKeyboardEvent& oKey = m_aVirtualKey[s_eMouseToKey[pEvent->GetMouseEvent()]];
			EKeyboardEvent& oEvent = s_eMouseToEvent[pEvent->GetMouseEvent()];

			switch (oKey)
			{
				case KeyUp:			oKey = (oEvent == KeyDown ? KeyPressed	: KeyUp);			break;
				case KeyDown:		oKey = (oEvent == KeyDown ? KeyRepeat	: KeyReleased);		break;
				case KeyPressed:	oKey = (oEvent == KeyDown ? KeyDown		: KeyReleased);		break;
				case KeyReleased:	oKey = (oEvent == KeyDown ? KeyPressed	: KeyUp);			break;
				case KeyRepeat:		oKey = (oEvent == KeyDown ? KeyRepeat	: KeyReleased);		break;
			}
		}

		m_oEngine.ReceiveEvent(pEvent);
	}

	delete pEvent;
}


