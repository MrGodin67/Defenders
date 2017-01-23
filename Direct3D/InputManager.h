#pragma once

#include "mouse.h"
#include "keyboard.h"
#include "Vec2.h"
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
	bool KeyPress(unsigned char key) { return m_keyboard.KeyIsPressed(key); }
	bool AnyKeyPressed() { return !m_keyboard.CharIsEmpty(); }
	bool LeftMouseDown() { return m_mouse.LeftIsPressed(); }
	bool RightMouseDown() { return m_mouse.RightIsPressed(); }
	Vec2i MousePosition() { return Vec2i(m_mouse.GetPosX(),m_mouse.GetPosY()); }
};