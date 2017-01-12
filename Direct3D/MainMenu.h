#pragma once
#include "includes.h"
#include "Rect.h"
#include "Vec2.h"
#include "D2D1Texture.h"
#include "Locator.h"
class MainMenu
{
	struct Button
	{
		RectF frame;
		int id;
	};
	Button Buttons[3];
	
	RectF border;
	std::unique_ptr<D2D1Texture> texture;
public:
	MainMenu(Vec2f screenCenter,float width,float height);
	~MainMenu();
	void Draw(class Graphics& gfx);
	int OnMouseClick(int x, int y);
	
};

