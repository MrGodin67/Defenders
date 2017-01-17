#pragma once
#include "includes.h"
#include "vec2.h"
class MenuInterface
{
protected:
	bool gameStarted = false;
public:
	struct Button
	{
		RectF frame;
		int id;
		bool drawFrame;
		bool enabled = true;
		WCHAR* text;
	};
	MenuInterface() {};
	virtual ~MenuInterface() {}
	virtual void Draw(class Graphics& gfx) = 0;
	virtual int OnMouseClick(Vec2i& mouse) = 0;
	virtual int OnMouseOver(Vec2i& mouse) = 0;

	bool GameStarted() { return gameStarted; }
	void GameStarted(bool val) { gameStarted = val; }
};