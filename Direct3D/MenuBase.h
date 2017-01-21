#pragma once
#include "includes.h"
#include "vec2.h"

enum _MenuReturn
{
	startGame,
	resumeGame,
	newGame,
	exitGame,
	backGame,
	pausedGame,
	Invalid
};
class MenuInterface
{
protected:
	bool gameStarted = false;
public:
	struct Button
	{
		RectF frame;
		_MenuReturn id;
		bool drawFrame;
		bool enabled = true;
		WCHAR* text;
	};
	MenuInterface() {};
	virtual ~MenuInterface() {}
	virtual void Draw(class Graphics& gfx) = 0;
	virtual _MenuReturn OnMouseClick(Vec2i& mouse) = 0;
	virtual _MenuReturn OnMouseOver(Vec2i& mouse) = 0;

	bool GameStarted() { return gameStarted; }
	void GameStarted(bool val) { gameStarted = val; }
};