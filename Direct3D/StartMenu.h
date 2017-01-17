#pragma once
#include "includes.h"
#include "Rect.h"
#include "Vec2.h"
#include "D2D1Texture.h"
#include "Locator.h"
#include "menuBase.h"
class StartMenu : public MenuInterface
{
	struct DrawRects
	{
		RectF pos;
		RectF clip;
		WCHAR* text;
	};
	Button Buttons[6];
	int numButtons = 6;
	DrawRects UnitRects[4];
	DrawRects BaseRects[4];
	RectF border;
	int lastOver = -1;
	std::vector<std::unique_ptr<D2D1Texture>> m_textures;
	
public:
	StartMenu(Vec2f screenCenter, float width, float height);
	~StartMenu();
	virtual void Draw(class Graphics& gfx)override;
	virtual int OnMouseClick(Vec2i& mouse)override;
	virtual int OnMouseOver(Vec2i& mouse)override;

	void DrawMap(class Graphics& gfx);
	void DrawUnits(class Graphics& gfx);
	void DrawBases(class Graphics& gfx);
};