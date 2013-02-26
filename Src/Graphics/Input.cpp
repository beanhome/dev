#include "Utils.h"

#include "Input.h"
#include "GEngine.h"

EKeyboardKey Input::s_eMouseToKey[EMouseEvent_MAX] = 
{
	EKeyboardKey_Error,  /* MouseMove */
	MOUSE_LEFT,   /* LeftUp */
	MOUSE_LEFT,   /* LeftDown */
	MOUSE_MIDDLE, /* MiddleUp */
	MOUSE_MIDDLE, /* MiddleDown */
	MOUSE_RIGHT,  /* RightUp */
	MOUSE_RIGHT,  /* RightDown */
};

EKeyboardEvent Input::s_eMouseToEvent[EMouseEvent_MAX] = 
{
	EKeyboardEvent_Error,  /* MouseMove */
	KeyUp,    /* LeftUp */
	KeyDown,  /* LeftDown */
	KeyUp,    /* MiddleUp */
	KeyDown,  /* MiddleDown */
	KeyUp,    /* RightUp */
	KeyDown,  /* RightDown */
};


Input::Input(GEngine& ge)
	: m_oEngine(ge)
	, m_bQuit(false)
{
	for (uint i=0 ; i<EKeyboardKey_Max ; ++i)
	{
		m_aVirtualKey[i] = KeyUp;
	}
}

Input::~Input()
{
}

void Input::Update()
{
	//LOG("Input::Update\n");

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
		m_bQuit = m_oEngine.GetInputEvent().IsQuit();

		if (m_oEngine.GetInputEvent().IsKeyboard())
		{
			EKeyboardEvent& oKey = m_aVirtualKey[m_oEngine.GetInputEvent().GetKeyboardKey()];
			switch (oKey)
			{
				case KeyUp:			oKey = (m_oEngine.GetInputEvent().GetKeyboardEvent() == KeyDown ? KeyPressed : KeyUp);			break;
				case KeyDown:		oKey = (m_oEngine.GetInputEvent().GetKeyboardEvent() == KeyDown ? KeyRepeat : KeyReleased);		break;
				case KeyPressed:	oKey = (m_oEngine.GetInputEvent().GetKeyboardEvent() == KeyDown ? KeyDown : KeyReleased);		break;
				case KeyReleased:	oKey = (m_oEngine.GetInputEvent().GetKeyboardEvent() == KeyDown ? KeyPressed : KeyUp);			break;
				case KeyRepeat:		oKey = (m_oEngine.GetInputEvent().GetKeyboardEvent() == KeyDown ? KeyRepeat : KeyReleased);		break;
			}
		}

		if (m_oEngine.GetInputEvent().IsMouse())
		{
			m_oEngine.GetInputEvent().GetMouseMove(m_iMouseX, m_iMouseY);

			EKeyboardEvent& oKey = m_aVirtualKey[s_eMouseToKey[m_oEngine.GetInputEvent().GetMouseEvent()]];

			switch (oKey)
			{
				case KeyUp:			oKey = (s_eMouseToEvent[m_oEngine.GetInputEvent().GetMouseEvent()] == KeyDown ? KeyPressed : KeyUp);			break;
				case KeyDown:		oKey = (s_eMouseToEvent[m_oEngine.GetInputEvent().GetMouseEvent()] == KeyDown ? KeyRepeat : KeyReleased);		break;
				case KeyPressed:	oKey = (s_eMouseToEvent[m_oEngine.GetInputEvent().GetMouseEvent()] == KeyDown ? KeyDown : KeyReleased);			break;
				case KeyReleased:	oKey = (s_eMouseToEvent[m_oEngine.GetInputEvent().GetMouseEvent()] == KeyDown ? KeyPressed : KeyUp);			break;
				case KeyRepeat:		oKey = (s_eMouseToEvent[m_oEngine.GetInputEvent().GetMouseEvent()] == KeyDown ? KeyRepeat : KeyReleased);		break;
			}
		}
	}
}


