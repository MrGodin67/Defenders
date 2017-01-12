#include "MainMenu.h"
#include "Graphics.h"


MainMenu::MainMenu(Vec2f screenCenter, float width, float height)
{
	border = RectF(screenCenter.x - (width * 0.5f),
		screenCenter.y - (height * 0.5f),
		screenCenter.x + (width * 0.5f),
		screenCenter.y + (height * 0.5f));
	Buttons[0].frame = RectF(border.left+340.0f,
		border.top + 245.0f,
		border.left + 460.0f,
		border.top + 280.0f);
	Buttons[1].frame = RectF(border.left + 340.0f,
		border.top + 285.0f,
		border.left + 460.0f,
		border.top + 322.0f);
	Buttons[2].frame = RectF(border.left + 340.0f,
		border.top + 324.0f,
		border.left + 460.0f,
		border.top + 365.0f);

	for (int c = 0; c < 3; c++)
		Buttons[c].id = c;
	texture = std::make_unique<D2D1Texture>(Locator::RenderTarget, L"media\\menuBack.png");
	assert(texture);
}


MainMenu::~MainMenu()
{
}

void MainMenu::Draw(Graphics & gfx)
{
	gfx.DrawSprite(D2D1::Matrix3x2F::Identity(), border.ToD2D(), texture->GetBitmap());
	gfx.DrawRectangle(D2D1::Matrix3x2F::Identity(), border.ToD2D(), D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f));
	
}

int MainMenu::OnMouseClick(int x, int y)
{
	for (int c = 0; c < 3; c++)
	{
		if (Buttons[c].frame.Contains(Vec2i(x, y)))
		{
			return Buttons[c].id;
		}
		
	}
	return -1;
}
