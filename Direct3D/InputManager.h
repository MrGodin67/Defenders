#pragma once

#include "mouse.h"
#include "keyboard.h"

class InputManager
{
	Mouse& m_mouse;
	Keyboard& m_keyboard;
public:
	InputManager(Mouse& m,Keyboard& kbd)
		:m_mouse(m),m_keyboard(kbd)
	{}

	Mouse::Event GetMouseEvent() { return m_mouse.Read(); }
	Keyboard::Event GetKeyboardEvent() { return m_keyboard.ReadKey(); }
	/*bool MouseLeftClick() { return m_mouse.LeftBtnClick(); }
	bool MouseRightClick() { return m_mouse.RightBtnClick(); }
	bool MouseMiddleClick() { return m_mouse.MiddleBtnClick(); }
	bool MouseLeftDown() { return m_mouse.LeftBtnDown(); }
	bool MouseRightDown() { return m_mouse.RightBtnDown(); }
	bool MouseMiddleDown() { return m_mouse.MiddleBtnDown(); }*/
	bool KeyPress(unsigned char key) { return m_keyboard.KeyIsPressed(key); }
	bool AnyKeyPressed() { return !m_keyboard.CharIsEmpty(); }
	//Vec2i GetMousePos() { return m_mouse.MousePos(); }
	
};