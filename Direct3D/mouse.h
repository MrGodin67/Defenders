#pragma once

#include <windows.h>
#include "Vec2.h"

class alignas(16) SimpleMouseServer
{
	friend class SimpleMouse;
protected:
	int m_X;
	int m_Y;
	bool m_leftBtnDown = false;
	bool m_rightBtnDown = false;
	bool m_middleBtnDown = false;

public:
	SimpleMouseServer() {}
public:
	
	bool OnMouseMove(WPARAM state, int x, int y)
	{
		
		m_X = x;
		m_Y = y;
		
		return true;
	}
	bool OnMouseDown(WPARAM state, int x, int y)
	{
		
		if ((state & MK_LBUTTON) != 0)
		{
			m_leftBtnDown = true;
		}
		if ((state & MK_RBUTTON) != 0)
		{
			m_rightBtnDown = true;
		}
		if ((state & MK_MBUTTON) != 0)
		{
			m_middleBtnDown = true;
		}
		
		return true;
	}
	bool OnMouseUp(WPARAM state, int x, int y)
	{
		
		if ((state & MK_LBUTTON) == 0)
		{
			m_leftBtnDown = false;
		}
		if ((state & MK_RBUTTON) == 0)
		{
			m_rightBtnDown = false;
		}
		if ((state & MK_MBUTTON) == 0)
		{
			m_middleBtnDown = false;
		}
		return true;
	}
	
};

class alignas(16) SimpleMouse
{
	SimpleMouseServer& server;
	bool m_LBD = false;
	bool m_MBD = false;
	bool m_RBD = false;
public:
	SimpleMouse(SimpleMouseServer& sm)
		:
		server(sm)
	{
		
	}
	
	bool LeftBtnClick()
	{
		if (!m_LBD && server.m_leftBtnDown)
		{
			return (m_LBD = true);
		}
		m_LBD = server.m_leftBtnDown;
		return false;
	}
	bool RightBtnClick()
	{
		if (!m_RBD && server.m_rightBtnDown)
		{
			return (m_RBD = true);
		}
		m_RBD = server.m_rightBtnDown;
		return false;
	}
	bool MiddleBtnClick()
	{
		if (!m_MBD && server.m_middleBtnDown)
		{
			return (m_MBD = true);
		}
		m_MBD = server.m_middleBtnDown;
		return false;
	}
	bool LeftBtnDown() { return server.m_leftBtnDown; }
	bool RightBtnDown() { return server.m_rightBtnDown; }
	bool MiddleBtnDown() { return server.m_middleBtnDown; }
	
	Vec2i MousePos() { return Vec2i(server.m_X, server.m_Y); }
};