

#include <windows.h>
#include "Direct3DWindow.h"
#include "Game.h"
#include "SimpleTimer.h"
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	Direct3DWindow D3D11Window(SCREEN_WIDTH, SCREEN_HEIGHT);
	Game app(D3D11Window);
	SimpleTimer timer;
	timer.Reset();
	bool ok = true;
	while (ok)
	{
		ok = D3D11Window.ProcessMessage();
		if (ok)
		{
			timer.Update();
			ok = app.Play(timer.Time());
		}
	};
	D3D11Window.Shutdown();
	return 0;
}