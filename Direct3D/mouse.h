#pragma once

#include <windows.h>
#include <DirectXMath.h>
#include <d3d11.h>
using namespace DirectX;
class alignas(16) SimpleMouseServer
{
	friend class SimpleMouse;
protected:
	float m_X;
	float m_Y;
	float m_lastX;
	float m_lastY;
	float m_deltaX;
	float m_deltaY;
	bool m_leftBtnDown = false;
	bool m_rightBtnDown = false;
	bool m_middleBtnDown = false;

public:
	SimpleMouseServer() {}
public:
	
	bool OnMouseMove(WPARAM state, int x, int y)
	{
		m_deltaX = m_deltaY = 0.0f;
		if ((state & MK_LBUTTON) != 0)
		{
			// Make each pixel correspond to a quarter of a degree.
			m_deltaX = XMConvertToRadians(0.25f*static_cast<float>(x - m_lastX));
			m_deltaY = XMConvertToRadians(0.25f*static_cast<float>(y - m_lastY));
			
		
		}
		m_X = (float)x;
		m_Y = (float)y;
		m_lastX = (float)x;
		m_lastY = (float)y;
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
	XMFLOAT2 MouseDelta() { return XMFLOAT2(m_deltaX, m_deltaY); }
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
	
	XMFLOAT2 Position()
	{
		return XMFLOAT2(server.m_lastX, server.m_lastY);
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
	XMFLOAT2 Delta() { return server.MouseDelta(); }
	XMFLOAT2 MousePos() { return XMFLOAT2(server.m_X, server.m_Y); }
};