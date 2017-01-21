#pragma once
#include "includes.h"
#include "Rect.h"
#include "Vec2.h"
#include "D2D1Texture.h"
#include "TextureManager.h"
#include "menuBase.h"
class StartMenu : public MenuInterface
{
	struct DrawRects
	{
		TextureManager::ImageClip clip;
		RectF pos;
		RectF textPos;
		WCHAR* text;
	};

	Button Buttons[8];
	int numButtons = 8;
	DrawRects UnitRects[5];
	DrawRects BaseRects[4];
	DrawRects TechRects[3];
	DrawRects HowTo;
	RectF border;
	int lastOver = -1;

	
public:
	StartMenu(Vec2f screenCenter, float width, float height);
	~StartMenu();
	virtual void Draw(class Graphics& gfx)override;
	virtual _MenuReturn OnMouseClick(Vec2i& mouse)override;
	virtual _MenuReturn OnMouseOver(Vec2i& mouse)override;

	void DrawMap(class Graphics& gfx);
	void DrawUnits(class Graphics& gfx);
	void DrawBases(class Graphics& gfx);
	void DrawObjectives(class Graphics& gfx);
	void DrawTechnology(class Graphics& gfx);
	void DrawHowTo(class Graphics& gfx);
};