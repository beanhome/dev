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
	, m_bQuit(false)
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

	while (m_oEngine.PollEvent())
	{
		m_bQuit = m_oEngine.GetEvent().IsQuit();

		if (m_oEngine.GetEvent().IsResize())
		{
			sint32 w, h;
			m_oEngine.GetEvent().GetResizeEvent(w, h);
			m_oEngine.Resize((uint16)w, (uint16)h);
		}

		if (m_oEngine.GetEvent().IsKeyboard())
		{
			EKeyboardEvent& oKey = m_aVirtualKey[m_oEngine.GetEvent().GetKeyboardKey()];
			switch (oKey)
			{
				case KeyUp:			oKey = (m_oEngine.GetEvent().GetKeyboardEvent() == KeyDown ? KeyPressed : KeyUp);			break;
				case KeyDown:		oKey = (m_oEngine.GetEvent().GetKeyboardEvent() == KeyDown ? KeyRepeat : KeyReleased);		break;
				case KeyPressed:	oKey = (m_oEngine.GetEvent().GetKeyboardEvent() == KeyDown ? KeyDown : KeyReleased);		break;
				case KeyReleased:	oKey = (m_oEngine.GetEvent().GetKeyboardEvent() == KeyDown ? KeyPressed : KeyUp);			break;
				case KeyRepeat:		oKey = (m_oEngine.GetEvent().GetKeyboardEvent() == KeyDown ? KeyRepeat : KeyReleased);		break;
			}
		}

		if (m_oEngine.GetEvent().IsMouse())
		{
			m_oEngine.GetEvent().GetMouseMove(m_iMouseX, m_iMouseY);

			EKeyboardEvent& oKey = m_aVirtualKey[s_eMouseToKey[m_oEngine.GetEvent().GetMouseEvent()]];

			switch (oKey)
			{
				case KeyUp:			oKey = (s_eMouseToEvent[m_oEngine.GetEvent().GetMouseEvent()] == KeyDown ? KeyPressed : KeyUp);			break;
				case KeyDown:		oKey = (s_eMouseToEvent[m_oEngine.GetEvent().GetMouseEvent()] == KeyDown ? KeyRepeat : KeyReleased);		break;
				case KeyPressed:	oKey = (s_eMouseToEvent[m_oEngine.GetEvent().GetMouseEvent()] == KeyDown ? KeyDown : KeyReleased);			break;
				case KeyReleased:	oKey = (s_eMouseToEvent[m_oEngine.GetEvent().GetMouseEvent()] == KeyDown ? KeyPressed : KeyUp);			break;
				case KeyRepeat:		oKey = (s_eMouseToEvent[m_oEngine.GetEvent().GetMouseEvent()] == KeyDown ? KeyRepeat : KeyReleased);		break;
			}
		}
	}
}


