#pragma once

#include "includes.h"
#include "Bases.h"
#include "Graphics.h"

class Camera;
class BaseController
{
public:
	struct ChildType
	{
		Animation image;
		_EntityType type;
		int cost;
		ChildType(Animation::RenderDesc& desc, _EntityType t, int cost)
			:
			image(desc),
			type(t),
			cost(cost){}

	};
	struct BaseItem
	{
		std::unique_ptr<Base> base;
		Animation image;
		bool selected = false;
		size_t numItems;
		WCHAR* defaultText = L"\0";
		int selectedChildIndex = -1;
		_BaseTypes type = _BaseTypes::baseInvalid;
		std::vector<ChildType> children;
		BaseItem(Animation::RenderDesc& desc, std::vector<int> itemIndices, _BaseTypes type)
			:
			image(desc),
			numItems(itemIndices.size()),
			selected(false),
			type(type)
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
				int cost = itemIndices[i] * 100;
				if (cost == 0)cost = 100;
				children.emplace_back(desc,(_EntityType)itemIndices[i],cost);
			}
		}
		void Draw(Graphics& gfx)
		{

			if (selected)
			{
				gfx.DrawFilledScreenRectangle(image.GetRenderDesc().drawRect, D2D1::ColorF(0.0f, 1.0f, 0.4f, 0.4f));
				gfx.DrawRectangle(D2D1::Matrix3x2F::Identity(), image.GetRenderDesc().drawRect, D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f));
				gfx.Rasterize(image.GetDrawable());
				if (base)
				{
					for (size_t i = 0; i < numItems; i++)
					{
						gfx.DrawFilledScreenRectangle(children[i].image.GetRenderDesc().drawRect, D2D1::ColorF(0.0f, 1.0f, 0.4f, 0.4f));
						gfx.Rasterize(children[i].image.GetDrawable());
						gfx.DrawRectangle(D2D1::Matrix3x2F::Identity(), children[i].image.GetRenderDesc().drawRect, D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f));
					}
				}
			}
			else
			{
				
				gfx.Rasterize(image.GetDrawable());
			}
		};
	};
public:
	BaseController(class WorldGrid& grid, class InputManager& input,class Camera& cam,Vec2f& screenSize, float height);
	~BaseController() {}
	void Draw(Graphics& gfx);
	void Update(const float& dt,class UnitManager* unitMgr);
	Base* SelectedNewBase() { return m_selectedNewBase; }
private:
	class Camera& m_cam;
	class WorldGrid& m_grid;
	class InputManager& m_input;
	class UnitManager* m_unitManager;
	std::vector<BaseItem> m_bases;
	std::unordered_map<std::string, TextSprite> m_text;
	RectF m_border;
	Animation m_hud;
	BaseItem* m_selectedBase = nullptr;
	bool m_newBaseCreation = false;
	int credits = 2300;
	Base* m_selectedNewBase = nullptr;
	std::vector<StatusRect> m_basePlacementTiles;
private:
	bool CreateNewBase(Vec2f placementPt);
	void HandleBaseSelection(BaseItem& base);
	void HandleItemSelection();
	void HandleInput();
	bool CanBuy(int cost);
};