#pragma once
#include "includes.h"
#include "Rect.h"
#include "Vec2.h"
#include "D2D1Texture.h"
#include "Locator.h"
#include "MenuBase.h"
class MainMenu : public MenuInterface
{
	
	Button Buttons[3];
	int lastOver = -1;
	int numButtons = 3;
	RectF border;

public:
	MainMenu(Vec2f screenCenter,float width,float height);
	~MainMenu();
	virtual void Draw(class Graphics& gfx)override;
	virtual _MenuReturn OnMouseClick(Vec2i& mouse)override;
	virtual _MenuReturn OnMouseOver(Vec2i& mouse)override;
	
};

