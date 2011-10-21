#ifndef __INPUTEVENT_H__
#define __INPUTEVENT_H__

union SDL_Event;

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
};

enum EKeyboardEvent
{
	EKeyboardEvent_Error = -1,

	KeyUp,
	KeyDown
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
};

class InputEvent
{
	public:
		InputEvent();
		~InputEvent();

		bool IsQuit() const;
		bool IsMouse() const;
		bool IsKeyboard() const;
		
		EMouseEvent GetMouseEvent() const;
		bool GetMouseMove(uint16& x, uint16& y) const;

		EKeyboardEvent GetKeyboardEvent() const;
		EKeyboardKey GetKeyboardKey() const;

		SDL_Event* GetSDLEvent() { return m_pSDLEvent; }

	private:
		SDL_Event* m_pSDLEvent;
};


#endif // __INPUTEVENT_H__

