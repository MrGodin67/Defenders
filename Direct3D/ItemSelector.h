#pragma once

#include "includes.h"
#include "Sprite2.h"
#include "Graphics.h"
#include "bases.h"
class ItemsSelector
{
	// Items
	struct BaseItem
	{
		Base* base = nullptr;
		Animation image;
		bool selected = false;
		size_t numItems;
		
		std::vector<Animation> children;
		BaseItem(Animation::RenderDesc& desc, std::vector<int> itemIndices)
			:
			image(desc),
			numItems(itemIndices.size()),
			selected(false)
		{
			
			float x = desc.drawRect.left;
			float y = desc.drawRect.bottom + 4.0f;
			float w = 32.0f;
			for (int i = 0; i< numItems; i++)
			{
				TextureManager::ImageClip clip = Locator::ImageManager->GetClip("player_units", itemIndices[i]);
				Animation::RenderDesc desc;
				desc.clipRect = clip.rect.ToD2D();
				desc.drawRect = { x,y,x + w,y + w };
				desc.image = clip.bitmap;
				x += (w + 6.0f);
				children.emplace_back(desc);
			}
		}
		void Draw(Graphics& gfx)
		{
			
			if (selected)
			{
				gfx.DrawFilledScreenRectangle(image.GetRenderDesc().drawRect, D2D1::ColorF(0.0f, 1.0f, 0.4f, 0.4f));
				gfx.DrawRectangle(D2D1::Matrix3x2F::Identity(), image.GetRenderDesc().drawRect, D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f));
				gfx.Rasterize(image.GetDrawable());
				for (size_t i = 0; i < numItems; i++)
				{
					gfx.DrawFilledScreenRectangle(children[i].GetRenderDesc().drawRect, D2D1::ColorF(0.0f, 1.0f, 0.4f, 0.4f));
					gfx.Rasterize(children[i].GetDrawable());
					gfx.DrawRectangle(D2D1::Matrix3x2F::Identity(), children[i].GetRenderDesc().drawRect, D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f));
				}
			}else
				gfx.Rasterize(image.GetDrawable());
		};
	};
	int m_credits = 1000;
	std::vector<BaseItem> m_bases;
	
	Animation m_hud;
public:
	
	
	
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
	void SetBaseIntoWorld(RectF pos);
	//Base* CurrentSelectedBase();
	void Update(const float& dt);
	
private:
	RectF border;
	bool PointIn(const int& x, const int& y);
	void DrawItems(class Graphics& gfx);
	bool baseItemSelected = false;
	
	int m_numBasesInWorld = 0;
	std::wstring m_creditString;
	std::wstring m_unitString;
	std::wstring m_baseString;

	std::unordered_map<std::string, TextSprite> m_text;
	
	
};