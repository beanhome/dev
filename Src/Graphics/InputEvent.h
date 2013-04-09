#ifndef __INPUTEVENT_H__
#define __INPUTEVENT_H__

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

	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_0,
	
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

	MOUSE_LEFT,
	MOUSE_MIDDLE,
	MOUSE_RIGHT,

	EKeyboardKey_Max
};

class InputEvent
{
	public:
		InputEvent();
		virtual ~InputEvent();

		//virtual InputEvent& operator=(const InputEvent& src) = 0;

		virtual bool IsQuit() const = 0;
		virtual bool IsMouse() const = 0;
		virtual bool IsKeyboard() const = 0;
		
		virtual EMouseEvent GetMouseEvent() const = 0;
		virtual bool GetMouseMove(sint32& x, sint32& y) const = 0;

		virtual EKeyboardEvent GetKeyboardEvent() const = 0;
		virtual EKeyboardKey GetKeyboardKey() const = 0;

	private:
};


#endif // __INPUTEVENT_H__

