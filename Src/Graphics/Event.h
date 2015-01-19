#ifndef __EVENT_H__
#define __EVENT_H__

enum EMouseEvent
{
	EMouseEvent_Error = -1,

	MouseMove,
	LeftUp,
	LeftDown,
	MiddleUp,
	MiddleDown,
	RightUp,
	RightDown,
	WheelUpUp,
	WheelUpDown,
	WheelDownUp,
	WheelDownDown,

	EMouseEvent_MAX
};

enum EKeyboardEvent
{
	EKeyboardEvent_Error = -1,

	KeyUp,
	KeyDown,
	KeyPressed,
	KeyReleased,
	KeyRepeat,
};

enum EKeyboardKey
{
	EKeyboardKey_Error = -1,

	KEY_0,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	
	KEY_A,
	KEY_B,
	KEY_C,
	KEY_D,
	KEY_E,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_I,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_M,
	KEY_N,
	KEY_O,
	KEY_P,
	KEY_Q,
	KEY_R,
	KEY_S,
	KEY_T,
	KEY_U,
	KEY_V,
	KEY_W,
	KEY_X,
	KEY_Y,
	KEY_Z,

	KEY_SPACE,
	KEY_PERIOD,
	KEY_COMMA,
	KEY_EXLAIM,
	KEY_QUESTION,
	KEY_COLON,
	KEY_SEMICOLON,
	KEY_QUOTE,
	KEY_QUOTEDBL,
	KEY_HASH,
	KEY_DOLLAR,
	KEY_AMPERSAND,

	KEY_LPAREN,
	KEY_RPAREN,
	KEY_ASTERISK,
	KEY_PLUS,
	KEY_MINUS,
	KEY_SLASH,
	KEY_BACKSLASH,

	KEY_EQUALS,
	KEY_LESS,
	KEY_GREATER,

	KEY_AT,
	KEY_LBRACKET,
	KEY_RBRACKET,
	KEY_CARET,
	KEY_UNDERSCORE,
	KEY_BACKQUOTE,
	
	KEY_ENTER,
	KEY_BACKSPACE,
	KEY_TAB,
	KEY_LMAJ,
	KEY_RMAJ,
	KEY_LCTRL,
	KEY_RCTRL,
	KEY_ALT,
	KEY_ALTGR,

	KEY_UP,
	KEY_RIGHT,
	KEY_DOWN,
	KEY_LEFT,
	
	KEY_INSERT,
	KEY_DELETE,
	KEY_HOME,
	KEY_END,
	KEY_PAGEUP,
	KEY_PAGEDOWN,
	
	KEY_ESC,

	KEY_F1,
	KEY_F2,
	KEY_F3,
	KEY_F4,
	KEY_F5,
	KEY_F6,
	KEY_F7,
	KEY_F8,
	KEY_F9,
	KEY_F10,
	KEY_F11,
	KEY_F12,
	KEY_F13,
	KEY_F14,
	KEY_F15,

	KEY_NUMLOCK,
	KEY_CAPSLOCK,
	KEY_SCROLLOCK,

	MOUSE_LEFT,
	MOUSE_MIDDLE,
	MOUSE_RIGHT,
	MOUSE_WHEELUP,
	MOUSE_WHEELDOWN,

	EKeyboardKey_Max
};

class Event
{
	public:
		Event();
		virtual ~Event();

		//virtual Event& operator=(const Event& src) = 0;

		virtual bool IsQuit() const = 0;
		virtual bool IsMouse() const = 0;
		virtual bool IsKeyboard() const = 0;
		virtual bool IsResize() const = 0;

		virtual EMouseEvent GetMouseEvent() const = 0;
		virtual bool GetMouseMove(sint32& x, sint32& y) const = 0;

		virtual void GetResizeEvent(sint32& w, sint32& h) const = 0;

		virtual EKeyboardEvent GetKeyboardEvent() const = 0;
		virtual EKeyboardKey GetKeyboardKey() const = 0;

		virtual uint16 GetKeyboardChar() const;
public:
		static const char s_KeyToChar[EKeyboardKey_Max];
};

class CustomEvent : public Event
{
	public:
		CustomEvent(EKeyboardEvent eEvent, EKeyboardKey eKey, uint16 cChar)
			: m_eKeyboardEvent(eEvent)
			, m_eKeyboardKey(eKey)
			, m_cChar(cChar)
			, m_eMouseEvent(EMouseEvent_Error)
		{}

		CustomEvent(EMouseEvent eEvent, sint32 x=0, sint32 y=0)
			: m_eKeyboardEvent(EKeyboardEvent_Error)
			, m_eKeyboardKey(EKeyboardKey_Error)
			, m_cChar(0)
			, m_eMouseEvent(eEvent)
			, m_iMouseX(x)
			, m_iMouseY(y)
		{}

		bool IsQuit() const { return false; }
		bool IsMouse() const { return (m_eMouseEvent != EMouseEvent_Error); }
		bool IsKeyboard() const { return (m_eKeyboardEvent != EKeyboardEvent_Error); }
		bool IsResize() const { return false; }

		EMouseEvent GetMouseEvent() const { return m_eMouseEvent; }
		bool GetMouseMove(sint32& x, sint32& y) const { x = m_iMouseX; y = m_iMouseY; return IsMouse(); }

		void GetResizeEvent(sint32& w, sint32& h) const {  }

		EKeyboardEvent GetKeyboardEvent() const { return m_eKeyboardEvent; }
		EKeyboardKey GetKeyboardKey() const  { return m_eKeyboardKey; }
		uint16 GetKeyboardChar() const  { return m_cChar; }

	private:
		EKeyboardEvent m_eKeyboardEvent;
		EKeyboardKey m_eKeyboardKey;
		uint16 m_cChar;

		EMouseEvent m_eMouseEvent;

		sint32 m_iMouseX, m_iMouseY;
};


#endif // __EVENT_H__

