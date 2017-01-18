#pragma once

#include "includes.h"
#include "SpriteSheet.h"
#include "Sprite.h"
#include "Table.h"
#include "Bases.h"

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
	ItemsSelector() 
	{
	}
	~ItemsSelector() {}
	ItemsSelector(Vec2f& screenSize,float height);
	void Draw(class Graphics& gfx);
	bool OnMouseClick(const Vec2i& mouse,bool isControlKey);
	bool BaseItemSelected();
	void BaseItemSelected(bool val);
	Base* CurrentSelectedBase();
	
private:
	RectF border;
	bool PointIn(const int& x, const int& y);
	void DrawItems(class Graphics& gfx);
	bool baseItemSelected = false;
	Table<Base> m_bases;
	Base* m_selectedBase = nullptr;
	Table<Item> m_items;
	
};