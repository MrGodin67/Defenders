#pragma once

#include "includes.h"
#include "SpriteSheet.h"
#include "Sprite.h"
#include "Table.h"

class ItemsSelector
{
	
public:
	struct Item
	{
	
		int type = 0;
		int imageIndex = -1;
		RectF frame;
		RectF progressBar;
		float buildTime;
		float timer;
		int  selectIndex;
		bool selected = false;
		bool active = false;
		bool built;
		int  cost;
		bool sell;
		int  sellValue;
		int  numberAvaliable;
		
		Item() {};
	

	};
public:
	ItemsSelector() {}
	ItemsSelector(Vec2f& screenSize,float height);
	void  SetSprites(std::string name, SpriteSheet* image);
	void Draw(class Graphics& gfx);
	bool OnMouseClick(const Vec2i& mouse, Item& item);
	bool BaseItemSelected();
	void BaseItemSelected(bool val);
private:
	SpriteSheet* spriteSheet;
	RectF border;
	bool PointIn(const int& x, const int& y);
	bool baseItemSelected = false;
	Table<Item> m_bases;
	Table<Item> m_items;
	std::unordered_map<std::string, SpriteSheet*> m_images;
};