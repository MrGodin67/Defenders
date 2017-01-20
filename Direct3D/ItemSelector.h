#pragma once

#include "includes.h"
#include "SpriteSheet.h"
#include "Sprite2.h"
#include "Table.h"
#include "Bases.h"
#include "Animation.h"
class ItemsSelector
{
	int m_credits = 1000;
public:
	struct BasePlace
	{
		RectF pos;
		Base* owner;
		int imageIndex;
	};
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
	void Draw(class Graphics& gfx,class Camera& cam);
	bool OnMouseClick(const Vec2i& mouse,bool isControlKey);
	bool BaseItemSelected();
	void BaseItemSelected(bool val);
	void SetBaseIntoWorld(RectF pos);
	Base* CurrentSelectedBase();
	void Update(const float& dt);
	
private:
	RectF border;
	bool PointIn(const int& x, const int& y);
	void DrawItems(class Graphics& gfx);
	bool baseItemSelected = false;
	Table<Base> m_bases;
	Base* m_selectedBase = nullptr;
	Table<Item> m_items;
	BasePlace m_basePlaces[4];
	int m_numBasesInWorld = 0;
	std::wstring m_creditString;
	std::wstring m_unitString;
	std::wstring m_baseString;

	std::unordered_map<std::string, TextSprite> m_text;
	
	
};