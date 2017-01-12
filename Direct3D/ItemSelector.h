#pragma once

#include "includes.h"
#include "SpriteSheet.h"
#include "Sprite.h"

class ItemsSelector
{
	SpriteSheet* spriteSheet;
	RectF border;
public:
	class Item
	{
		Sprite sprite;
		int selectIndex;
		bool selected;
		int cost;
		bool sell;
		int sellValue;
	public:
		Item();

	};
public:
	ItemsSelector(SpriteSheet* image, float screenW, float screenH, float height);
	void Draw(class Graphics& gfx);
};