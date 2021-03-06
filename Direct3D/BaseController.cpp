#include "BaseController.h"
#include "Camera.h"
#include "CommandBase.h"
#include "FactoryBase.h"
#include "TechnologyBase.h"
#include "RepairBase.h"
#include "WorldGrid.h"
#include "Tile.h"
#include "InputManager.h"
#include "EntityManager.h"


BaseController::BaseController(WorldGrid& grid,InputManager& input,Camera& cam,Vec2f & screenSize, float height)
	:m_grid(grid),m_input(input),m_cam(cam)
{
	m_border.left = 0.0f;
	m_border.top = screenSize.y - height;
	m_border.right = screenSize.x;
	m_border.bottom = screenSize.y - 1.0f;
	Animation::RenderDesc hud_desc;
	hud_desc.drawRect = m_border.ToD2D();
	hud_desc.clipRect = { 0.0f,0.0f,256.0f,128.0f };
	hud_desc.image = Locator::ImageManager->GetImage("hud")->GetTexture();
	m_hud = Animation(hud_desc);

	float cWidth = 48.0f;
	float toffset = 28.0f;
	float loffset = 20.0f;
	float x = m_border.left + loffset;
	float y = m_border.top + toffset;
	Animation::RenderDesc desc;
	// create Items to render and select
	for (int i = 0; i < 4; i++)
	{
		TextureManager::ImageClip clip = Locator::ImageManager->GetClip("bases", i);
		desc.drawRect = { x,y,x + cWidth,y + cWidth };
		desc.clipRect = clip.rect.ToD2D();
		desc.image = clip.bitmap;
		std::vector<int> ind;
		switch (i)
		{
		case 0:
			ind.push_back(0);
			m_bases.emplace_back(desc, ind, (_BaseTypes)i);
			m_bases.back().defaultText = L"Command and Control Center \nCost 200";
			break;
		case 1:
			ind = { 1,2,3,4 };
			m_bases.emplace_back(desc, ind, (_BaseTypes)i);
			m_bases.back().defaultText = L"Unit Creation Facility \nCost 600";
			break;
		case 2:
			ind = { 5,6 };
			m_bases.emplace_back(desc, ind, (_BaseTypes)i);
			m_bases.back().defaultText = L"Technology Research Facility \nCost 700";
			break;
		case 3:
			m_bases.emplace_back(desc, ind, (_BaseTypes)i);
			m_bases.back().defaultText = L"Unit Repair Facility \nCost 550";
			break;
		}

		x += (cWidth +2.0f);
	}



	x += cWidth + loffset;


	RectF textPlace = RectF(m_border.left + loffset, y-50.0f, (m_border.left + loffset) + (4 * 48.0f),y-32.0f );
	float yInc = 26.0f;
	
	m_text["credits"] = TextSprite(Locator::TextManager->GetFormat("Tahoma14"),
		textPlace, L"Credit: [ 1000 ]", D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f), D2D1::ColorF(0.0f, 0.5f, 0.5f, 0.8f), true);
	textPlace = RectF(x, y, x + 250.0f, y + 75.0f);

	m_text["dataDisplay"] = TextSprite(Locator::TextManager->GetFormat("Tahoma14"),
		textPlace, L"Unit Data : ", D2D1::ColorF(0.0f, 1.0f, 0.0f, 1.0f), D2D1::ColorF(0.0f, 0.0f, 1.0f, 0.2f), false);

	StatusRect::StatusRectDesc sdesc;
	sdesc.drawRect = { 0.0f,0.0f,64.0f,64.0f };
	sdesc.color = { 0.0f,1.0f,0.0f,1.0f };
	sdesc.alphaBlend = 0.8f;
	sdesc.drawFilled = true;
	for (int c = 0; c < 4; c++)
	{
		m_basePlacementTiles.emplace_back(sdesc);
	}

}
void BaseController::Draw(Graphics & gfx)
{
	for (int c = 0; c < m_bases.size(); c++)
	{
		if (m_bases[c].base)
			m_bases[c].base->Draw(m_cam);
	}
	gfx.DrawFilledScreenRectangle(m_border.ToD2D(), D2D1::ColorF(0.1f, 0.6f, 0.0f, 0.4f));

	for (int c = 0; c < m_bases.size(); c++)
	{
		m_bases[c].Draw(gfx);
		
	}
	gfx.Rasterize(m_hud.GetDrawable());
	
	Locator::TextManager->GetFormat("Tahoma14")->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);

	if (m_selectedBase)
	{
		if (m_selectedBase->base){
			m_text["dataDisplay"].UpdateText(m_selectedBase->base->GetText());
		}
		else{m_text["dataDisplay"].UpdateText(m_selectedBase->defaultText);
		}
		m_text["dataDisplay"].Draw(gfx);
	}
	Locator::TextManager->GetFormat("Tahoma14")->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

	m_text["credits"].UpdateText(L"Credit :" + std::to_wstring(credits));
	m_text["credits"].Draw(gfx);
	Locator::TextManager->GetFormat("Tahoma14")->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	if (m_basePlacementTiles.size() <= 0)
		return;
	D2D1_COLOR_F color;

	if (m_newBaseCreation)
	{
		D2D1_RECT_F rect = m_basePlacementTiles[0].GetRenderDesc().drawRect;
		rect.right = rect.left + 128.0f;
		rect.bottom = rect.top + 128.0f;
		D2D1_MATRIX_3X2_F mat = D2D1::Matrix3x2F::Translation({ -m_cam.GetPos().x,-m_cam.GetPos().y });
		gfx.DrawSprite(mat,
			rect,
			Locator::ImageManager->GetImage("bases")->GetTexture(),
			&Locator::ImageManager->GetImage("bases")->GetClippedImage((int)m_selectedBase->type).ToD2D()
		);
	
		for (int d = 0; d < m_basePlacementTiles.size(); d++)
		{
			m_cam.Rasterize(m_basePlacementTiles[d].GetDrawable());

		}
	}
}
void BaseController::Update(const float & dt, UnitManager* unitMgr)
{
	// temp for testing credits
	static float creditMoneyMaker = 0.0f;
	creditMoneyMaker += dt;
	if (creditMoneyMaker >= 1.0f)
	{
		credits++;
		creditMoneyMaker = 0.0f;
	}
	HandleInput();
	if (m_newBaseCreation)
	{
		//** GET PLACEMENT TILES HERE **
		m_grid.SetBasePlacementTiles(m_input.MousePosition(),m_basePlacementTiles);
	}
	for (size_t i = 0; i < 4; i++)
	{
		if (m_bases[i].base)
		{
			Base* base = m_bases[i].base.get();
			if (base)
			{
				base->UpdateBuilds(dt);
				if (base->UnitsReady())
				{
					std::vector<_EntityType> ent = base->CompletedBuilds();
					for (size_t j = 0; j < ent.size(); j++)
					{
						Vec2f pp = base->GetNextAvaliableExitPosition();
						
						pp /= 64.0f;
						unitMgr->AddPlayerUnit(ent[j], Vec2i(pp));
					}
					Locator::SoundEngine->AddToQueue("newunitsavailable");
					//Locator::SoundEngine->Play("newunitsavailable");
				}
			}
		}
	}
}
bool BaseController::CreateNewBase(Vec2f placementPt)
{
	if (!m_selectedBase)
		return false;
	
	if (!m_selectedBase->base)
	{
		m_newBaseCreation = false;
		placementPt = m_cam.ConvertToWorldSpace(placementPt);
		Animation::RenderDesc desc;
		std::vector<int> indices;
		TextureManager::ImageClip clip = Locator::ImageManager->GetClip("bases", (int)m_selectedBase->type);
		indices.push_back((int)m_selectedBase->type);
		
		desc.clipRect = clip.rect.ToD2D();
		desc.image = clip.bitmap;
		Tile tile;
		std::vector<Tile*>buildingExitPoints;
		if (m_grid.SetBase(Vec2i(placementPt),tile, buildingExitPoints))
		{
			desc.drawRect = tile.GetRect().ToD2D();
			desc.drawRect.right = desc.drawRect.left + 128.0f;
			desc.drawRect.bottom = desc.drawRect.top + 128.0f;
			switch (m_selectedBase->type)
			{
			case _BaseTypes::baseCommand:

				m_selectedBase->base = std::make_unique<CommandBase>(desc, indices, "bases", buildingExitPoints);
				break;
			case _BaseTypes::baseFactory:
				m_selectedBase->base = std::make_unique<FactoryBase>(desc, indices, "bases", buildingExitPoints);
				break;
			case _BaseTypes::baseTechnology:
				m_selectedBase->base = std::make_unique<TechnologyBase>(desc, indices, "bases", buildingExitPoints);
				break;
			case _BaseTypes::baseRepair:
				m_selectedBase->base = std::make_unique<RepairBase>(desc, indices, "bases", buildingExitPoints);
				break;
			default:
				return false;
				break;
			}
			Locator::SoundEngine->AddToQueue("constructionstarted");
			//Locator::SoundEngine->Play("constructionstarted");
			m_selectedBase->base->SetSelected(true);
			return true;
		}
	}
	return false;
}
void BaseController::HandleBaseSelection(BaseItem & base)
{
	if (base.base)
	{
		if (base.base->GetRect().Contains(m_cam.ConvertToWorldSpace(m_input.MousePosition())))
		{
			if (m_selectedBase)
			{
				m_selectedBase->selected = false;
				if (m_selectedBase->base)
					m_selectedBase->base->SetSelected(false);

			}
			// assign pointer new selected base
			m_selectedBase = &base;
			m_selectedBase->selected = true;


			if (m_selectedBase->base)
			{
				m_selectedBase->base->SetSelected(true);
			}
			return;
		}
	}
	if (base.image.PointIn(Vec2f(m_input.MousePosition())))
	{
		// set prevous, if any, selected to false
		if (m_selectedBase)
		{
			m_selectedBase->selected = false;
			if (m_selectedBase->base)
				m_selectedBase->base->SetSelected(false);

		}
		// assign pointer new selected base
		m_selectedBase = &base;
		m_selectedBase->selected = true;
		if (!m_selectedBase->base)
			m_newBaseCreation = m_input.KeyPress(VK_CONTROL);

		if (m_selectedBase->base)
		{
			m_selectedBase->base->SetSelected(true);
		}

		Locator::SoundEngine->Play("select");
		
	}
}
void BaseController::HandleItemSelection()
{
	if (!m_newBaseCreation)
	{

		if (m_selectedBase)
		{
			if (!m_selectedBase->base)
				return;
			if (!m_selectedBase->base->Active())
			{
				return;
			}
			if (m_selectedBase->base->ActiveBuilds() > 0)
				return;
			for (size_t j = 0; j < m_selectedBase->children.size(); j++)
			{
				// check bases child nodes to see if we selected an item
				if (m_input.KeyPress(VK_CONTROL))// only if key is presses as well
				{
					if (m_selectedBase->children[j].image.PointIn(Vec2f(m_input.MousePosition())))
					{

						if (CanBuy(m_selectedBase->children[j].cost))
						{
							m_selectedBase->base->ConstructNewUnit(m_selectedBase->children[j].type, 6.0f);

							
							return;
						}
					}
				}
			}

		}
	}
}
void BaseController::HandleInput()
{

	// static variables that keep their value
	static bool leftMouseClick = false;
	static bool rightMouseClick = false;
	


	
	bool controlKey = m_input.KeyPress(VK_CONTROL);
	bool shiftKey = m_input.KeyPress(VK_SHIFT);
	bool F1Key = m_input.KeyPress(VK_F1);
	bool F2Key = m_input.KeyPress(VK_F2);
	bool F3Key = m_input.KeyPress(VK_F3);
	bool F4Key = m_input.KeyPress(VK_F4);

	if (F1Key)
	{
		if (m_selectedBase)
		{
			m_selectedBase->selected = false;
			m_selectedBase = &m_bases[0];
			m_selectedBase->selected = true;
		}
	}
	if (F2Key)
	{
		if (m_selectedBase)
		{
			m_selectedBase->selected = false;
			m_selectedBase = &m_bases[1];
			m_selectedBase->selected = true;
		}
	}
	if (F3Key)
	{
		if (m_selectedBase)
		{
			m_selectedBase->selected = false;
			m_selectedBase = &m_bases[2];
			m_selectedBase->selected = true;
		}
	}
	if (F4Key)
	{
		if (m_selectedBase)
		{
			m_selectedBase->selected = false;
			m_selectedBase = &m_bases[3];
			m_selectedBase->selected = true;
		}
	}
	Keyboard::Event e_kbd = m_input.GetKeyboardEvent();
	unsigned char numKey[8] = { '1','2','3','4','5','6','7','8' };
	if (m_selectedBase)
	{
		if (m_selectedBase->base )
		{
			if (m_selectedBase->base->Active()&& m_selectedBase->base->ActiveBuilds() == 0)
			{
				for (int c = 0; c < 8; c++)
				{
					if ((e_kbd.GetCode() == numKey[c]) && e_kbd.IsRelease())
					{
						if (c < m_selectedBase->children.size())
						{
							if (CanBuy(m_selectedBase->children[c].cost))
							{
								m_selectedBase->base->ConstructNewUnit(m_selectedBase->children[c].type, 6.0f);
							}
							break;
						}
					}
				}
			}
		}
	}

	// if leftMouseClick = false and leftBitton is down
	if (!leftMouseClick && m_input.LeftMouseDown())
	{
		if (m_newBaseCreation)
		{
			CreateNewBase(m_input.MousePosition());
			return;
		}
		for (size_t i = 0; i < m_bases.size(); i++)
		{		
			HandleBaseSelection(m_bases[i]);
		}
		HandleItemSelection();
	}

	// set to current state
	leftMouseClick = m_input.LeftMouseDown();
	rightMouseClick = m_input.RightMouseDown();
	
}
bool BaseController::CanBuy(int cost)
{
	if (credits - cost >= 0)
		credits -= cost;
	else
	{
		Locator::SoundEngine->AddToQueue("notenoughcredit");
		//Locator::SoundEngine->Play("notenoughcredit",0.25f);
		return false;
	}
	return true;
}
