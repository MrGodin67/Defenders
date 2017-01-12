#pragma once

#include "mouse.h"
#include "Chilikeyboard.h"

class InputManager
{
	SimpleMouse& m_mouse;
	Keyboard& m_keyboard;
public:
	InputManager(SimpleMouse& m,Keyboard& kbd)
		:m_mouse(m),m_keyboard(kbd)
	{}

	bool MouseLeftClick() { return m_mouse.LeftBtnClick(); }
	bool MouseRightClick() { return m_mouse.RightBtnClick(); }
	bool MouseMiddleClick() { return m_mouse.MiddleBtnClick(); }
	bool MouseLeftDown() { return m_mouse.LeftBtnDown(); }
	bool MouseRightDown() { return m_mouse.RightBtnDown(); }
	bool MouseMiddleDown() { return m_mouse.MiddleBtnDown(); }
	bool KeyPress(unsigned char key) { return m_keyboard.KeyIsPressed(key); }
	bool AnyKeyPressed() { return !m_keyboard.CharIsEmpty(); }
	XMFLOAT2 GetMouseDelta() { return m_mouse.Delta(); }
	XMFLOAT2 GetMousePos() { return m_mouse.MousePos(); }
};