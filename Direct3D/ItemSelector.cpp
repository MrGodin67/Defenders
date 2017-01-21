#include "ItemSelector.h"
#include "Graphics.h"
#include "Camera.h"
#include "Animation.h"
#include "Locator.h"
ItemsSelector::ItemsSelector(Vec2f& screenSize, float height)
{
	border.left = 0.0f;
	border.top = screenSize.y - height;
	border.right = screenSize.x;
	border.bottom = screenSize.y-1.0f;
	Animation::RenderDesc hud_desc;
	hud_desc.drawRect = border.ToD2D();
	hud_desc.clipRect = { 0.0f,0.0f,256.0f,128.0f };
	hud_desc.image = Locator::ImageManager->GetImage("hud")->GetTexture();
	m_hud = Animation(hud_desc);

	float cWidth = 48.0f;
	float toffset = 20.0f;
	float loffset = 20.0f;
	float x = border.left + loffset;
	float y = border.top + toffset;
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
			m_bases.emplace_back(desc,ind );
			break;
		case 1:
			ind = {1,2,3,4};
			m_bases.emplace_back(desc, ind);
			break;
		case 2:
			ind = {5,6};
			m_bases.emplace_back(desc, ind);
			break;
		case 3:
			m_bases.emplace_back(desc, ind);
			break;
		}
		
		x += cWidth;
	}
	
	

	x = border.left + loffset;
	y = border.top + toffset + 56.0f;
	
	RectF textPlace = RectF(border.right - 250.0f, border.top + toffset, border.right - loffset, (border.top + toffset) + 24.0f);
	float yInc = 26.0f;
	m_text["credits"] = TextSprite(Locator::TextManager->GetFormat("Tahoma14"),
		textPlace,L"Credit: [ 1000 ]", D2D1::ColorF(0.0f, 1.0f, 0.0f, 1.0f), D2D1::ColorF(0.0f, 0.0f, 1.0f, 0.2f), false);
		m_text["dataDisplay"] = TextSprite(Locator::TextManager->GetFormat("Tahoma14"),
		textPlace, L"Unit Data : ", D2D1::ColorF(0.0f, 1.0f, 0.0f, 1.0f), D2D1::ColorF(0.0f, 0.0f, 1.0f, 0.2f), false);

	
}

void ItemsSelector::Draw(Graphics & gfx)
{
	gfx.DrawFilledScreenRectangle(border.ToD2D(), D2D1::ColorF(0.1f, 0.6f, 0.0f, 0.4f));
	gfx.Rasterize(m_hud.GetDrawable());
	for (int c = 0; c < m_bases.size(); c++)
	{
		m_bases[c].Draw(gfx);
	}
	
}

bool ItemsSelector::OnMouseClick(const Vec2i& mouse,bool isControlKey)
{
	baseItemSelected = false;
	bool select = false;
	for (int c = 0; c < m_bases.size(); c++)
	{
		m_bases[c].selected = false;
		if (m_bases[c].image.PointIn(Vec2f(mouse)))
			{
				 
				 if(isControlKey)
				    baseItemSelected = true;
				 m_bases[c].selected = true;
				 select = true;
				 Locator::SoundEngine->Play("select");
				
			}
		
		
	}
	
	return select;
}

bool ItemsSelector::BaseItemSelected()
{
	return baseItemSelected;
}

void ItemsSelector::BaseItemSelected(bool val)
{
	baseItemSelected = val;
	
}

void ItemsSelector::SetBaseIntoWorld(RectF pos)
{
	
}

void ItemsSelector::Update(const float & dt)
{
	
}

bool ItemsSelector::PointIn(const int & x, const int & y)
{
	return border.Contains(Vec2i(x,y));
}

void ItemsSelector::DrawItems(Graphics & gfx)
{
	/*int index = m_selectedBase->NumUinitTypes();
	RectF rect = m_basePlaces[m_selectedBase->ImageIndex()].pos;;
	_EntityType* ent = m_selectedBase->UnitTypes();
	for (int c = 0; c < 6; c++)
	{
		m_items(0, c).frame.left = rect.left;
		m_items(0, c).frame.right = rect.left + 32.0f;
		rect.left += 32.0f;
	}
	TextureManager::ImageClip imageData;
	for (int c = 0; c < index; c++)
	{
		imageData = Locator::ImageManager->GetClip("player_units", (int)*ent);

		gfx.DrawSprite(D2D1::Matrix3x2F::Identity(), m_items(0, c).frame.ToD2D(),
			imageData.bitmap,&imageData.rect.ToD2D());

		gfx.DrawRectangle(D2D1::Matrix3x2F::Identity(), m_items(0, c).frame.ToD2D(), D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.20f));

		ent++;
	}
	gfx.DrawRectangle(D2D1::Matrix3x2F::Identity(), m_basePlaces[m_selectedBase->ImageIndex()].pos.ToD2D(), D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.20f));
	m_text["dataDisplay"].UpdateText(m_selectedBase->GetText());
	m_text["dataDisplay"].Draw(gfx);*/
}


