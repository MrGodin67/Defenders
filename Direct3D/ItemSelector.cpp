#include "ItemSelector.h"
#include "Graphics.h"
ItemsSelector::ItemsSelector(SpriteSheet * image, float screenW, float screenH,  float height)
	:spriteSheet(image)
{
	border.left = 0.0f;
	border.top = screenH - height;
	border.right = screenW;
	border.bottom = screenH;
}

void ItemsSelector::Draw(Graphics & gfx)
{
	gfx.DrawFilledScreenRectangle(border.ToD2D(),D2D1::ColorF(0.0f, 0.0f, 0.0f, 1.0f));
	gfx.DrawRectangle(D2D1::Matrix3x2F::Identity(), border.ToD2D(), D2D1::ColorF(1.0f, 0.0f, 0.0f, 1.0f));
}
