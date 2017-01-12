
#include "Direct3DWindow.h"

#include <windows.h>

Direct3DWindow::Direct3DWindow()
	:m_mouse(m_mouseServer)
{
	
}

Direct3DWindow::Direct3DWindow(int scrnWidth, int scrnHeight)
	:m_screenWidth(scrnWidth),m_screenHeight(scrnHeight),
	m_mouse(m_mouseServer)
{
	InitializeWindows();
}


Direct3DWindow::Direct3DWindow(const Direct3DWindow& other)
	:m_mouse(m_mouseServer)
{
}


Direct3DWindow::~Direct3DWindow()
{
}





void Direct3DWindow::Shutdown()
{
	// Release the application wrapper object.
	

	// Shutdown the window.
	ShutdownWindows();

	return;
}


bool Direct3DWindow::ProcessMessage()
{
	MSG msg;
	bool ok;


	// Initialize the message structure.
	ZeroMemory(&msg, sizeof(MSG));

	// Loop until there is a quit message from the window or the user.
	ok = true;
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if (msg.message == WM_QUIT)
		{
			ok = false;
		}
	}

	return ok;
}

int Direct3DWindow::ScreenWidth()
{
	return m_screenWidth;
}

int Direct3DWindow::ScreenHeight()
{
	return m_screenHeight;
}

void Direct3DWindow::ScreenHalfExtents(float & x, float & y)
{
	
	x = (float)( m_screenWidth / 2);
	y = (float)( m_screenHeight / 2);
	
}

HWND & Direct3DWindow::WindowHandle()
{
	return m_hwnd;
}


bool Direct3DWindow::Frame()
{
	return true;
}


LRESULT CALLBACK Direct3DWindow::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	switch (umsg)
	{
	case WM_KEYDOWN:
		if (!(lparam & 0x40000000) || m_keyboard.AutorepeatIsEnabled()) // no thank you on the autorepeat
		{
			m_keyboard.OnKeyPressed(static_cast<unsigned char>(wparam));
		}
		break;
	case WM_KEYUP:
		m_keyboard.OnKeyReleased(static_cast<unsigned char>(wparam));
		break;
	case WM_CHAR:
		m_keyboard.OnChar(static_cast<unsigned char>(wparam));
		break;
	case WM_MOUSEMOVE:
		m_mouseServer.OnMouseMove(wparam, GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
		break;
	case WM_RBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_LBUTTONDOWN:
		m_mouseServer.OnMouseDown(wparam, GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
		break;
	case WM_RBUTTONUP:
	case WM_MBUTTONUP:
	case WM_LBUTTONUP:
		m_mouseServer.OnMouseUp(wparam, GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
		break;
	
	}
	return DefWindowProc(hwnd, umsg, wparam, lparam);
}


void Direct3DWindow::InitializeWindows()
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;


	// Get an external pointer to this object.	
	ApplicationHandle = this;

	// Get the instance of this application.
	m_hinstance = GetModuleHandle(NULL);

	// Give the application a name.
	m_applicationName = APPLICATION_NAME;

	// Setup the windows class with default settings.
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	// Register the window class.
	RegisterClassEx(&wc);

	// Determine the resolution of the clients desktop screen.
	int screenWidth2 = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight2 = GetSystemMetrics(SM_CYSCREEN);

	// Setup the screen settings depending on whether it is running in full screen or in windowed mode.
	if (FULL_SCREEN)
	{
		// If full screen set the screen to maximum size of the users desktop and 32bit.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth2;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight2;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Change the display settings to full screen.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// Set the position of the window to the top left corner.
		posX = posY = 0;
		m_screenWidth = screenWidth2;
		m_screenHeight = screenHeight2;
	}
	else
	{
		// If windowed then set it to 800x600 resolution.
		// Place the window in the middle of the screen.
		posX = (GetSystemMetrics(SM_CXSCREEN) - m_screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - m_screenHeight) / 2;
	}


	RECT wr;
	wr.left = (long)posX;
	wr.right = m_screenWidth + wr.left;
	wr.top = (long)posY;
	wr.bottom = m_screenHeight + wr.top;
	AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);
	m_hwnd = CreateWindow(m_applicationName, m_applicationName,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		wr.left, wr.top, wr.right - wr.left, wr.bottom - wr.top,
		nullptr, nullptr, m_hinstance, this);

	// Bring the window up on the screen and set it as main focus.
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

	
	ShowCursor(true);

	return;
}


void Direct3DWindow::ShutdownWindows()
{
	// Show the mouse cursor.
	ShowCursor(true);

	// Fix the display settings if leaving full screen mode.
	if (FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	// Remove the window.
	DestroyWindow(m_hwnd);
	m_hwnd = NULL;

	// Remove the application instance.
	UnregisterClass(m_applicationName, m_hinstance);
	m_hinstance = NULL;

	// Release the pointer to this class.
	ApplicationHandle = NULL;

	return;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch (umessage)
	{
		// Check if the window is being destroyed.
	
	
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}

	// Check if the window is being closed.
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}

	// All other messages pass to the message handler in the system class.
	default:
	{
		return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
	}
	}
	return 0;
}
