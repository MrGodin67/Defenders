#include "ItemSelector.h"
#include "Graphics.h"
#include "Camera.h"
#include "Animation.h"
ItemsSelector::ItemsSelector(Vec2f& screenSize, float height)
{
	border.left = 0.0f;
	border.top = screenSize.y - height;
	border.right = screenSize.x;
	border.bottom = screenSize.y-1.0f;
	m_bases.resize(2, 2);
	m_items.resize(1, 6);

	float cWidth = 48.0f;
	float toffset = 20.0f;
	float loffset = 20.0f;
	float x = border.left + loffset;
	float y = border.top + toffset;
	Animation::RenderDesc desc;
	std::vector<int> indices;
	for (int r = 0; r < 2; r++)
	{
		//Animation::RenderDesc& desc, std::vector<int> indices, float interval,
		//std::string imageName, _EntityType type, float constructionTime
		for (int c = 0; c < 2; c++)
		{
			const int index = r * 2 + c;
			indices.clear();
			indices.push_back(index);
			desc.drawRect = D2D1::RectF(x, y, x + 48.0f, y + 48.0f);
			m_bases(r, c) = Base(desc, indices, 0.0f, "bases", none, 15.0f);
		
			m_basePlaces[index].imageIndex = index;
			m_basePlaces[index].owner = nullptr;
			m_basePlaces[index].pos = RectF(x, y, x + 48.0f, y + 48.0f);

			switch (index)
			{
			case 0:
				m_bases(r, c).SetBuildTypes(_EntityType::drone, _EntityType::none, _EntityType::none, _EntityType::none,1);
				break;
			case 1:
				m_bases(r, c).SetBuildTypes(_EntityType::fighter, _EntityType::artillary, _EntityType::radar, _EntityType::turret,4);
				break;
			case 2:
				m_bases(r, c).SetBuildTypes(_EntityType::tech, _EntityType::data, _EntityType::none, _EntityType::none,2);
				break;
			case 3:
				m_bases(r, c).SetBuildTypes(_EntityType::none, _EntityType::none, _EntityType::none, _EntityType::none,0);
				break;
			}
			x += cWidth;
		}
		
	}

	x = border.left + loffset;
	y = border.top + toffset + 56.0f;
	for (int i = 0; i < 6; i++)
	{
		m_items(0, i).frame = { x,y,x + 32.0f,y + 32.0f };
		m_items(0, i).progressBar = m_items(0, i).frame;
		x += 32.0f;
	}
	RectF textPlace = RectF(border.right - 250.0f, border.top + toffset, border.right - loffset, (border.top + toffset) + 24.0f);
	float yInc = 26.0f;
	m_text["credits"] = TextSprite(Locator::TextManager->GetFormat("Tahoma14"),
		textPlace,L"Credit: [ 1000 ]", D2D1::ColorF(0.0f, 1.0f, 0.0f, 1.0f), D2D1::ColorF(0.0f, 0.0f, 1.0f, 0.2f), false);
	textPlace = m_bases(0, 3).GetRect();
	textPlace.left = m_bases(0, 3).GetRect().right + 60.0f; 
	textPlace.right = textPlace.left + 360.0f;
	m_text["dataDisplay"] = TextSprite(Locator::TextManager->GetFormat("Tahoma14"),
		textPlace, L"Unit Data : ", D2D1::ColorF(0.0f, 1.0f, 0.0f, 1.0f), D2D1::ColorF(0.0f, 0.0f, 1.0f, 0.2f), false);

	
}


void ItemsSelector::Draw(Graphics & gfx, Camera& cam)
{
	
	Draw(gfx);
	for (int c = 0; c < m_bases.numElements(); c++)
		m_bases(c).Draw(gfx, cam);
}
void ItemsSelector::Draw(Graphics & gfx)
{
	gfx.DrawFilledScreenRectangle(border.ToD2D(), D2D1::ColorF(0.1f, 0.2f, 0.0f, 0.70f));
	gfx.DrawSprite(D2D1::Matrix3x2F::Identity(), border.ToD2D(), Locator::ImageManager->GetImage("hud")->GetTexture());

	for (int c = 0; c < m_bases.numElements(); c++)
	{
		
		gfx.DrawSprite(D2D1::Matrix3x2F::Identity(), m_basePlaces[c].pos.ToD2D(), Locator::ImageManager->GetImage("bases")->GetTexture(),
			&Locator::ImageManager->GetImage("bases")->GetClippedImage(c).ToD2D());

		gfx.DrawRectangle(D2D1::Matrix3x2F::Identity(), m_basePlaces[c].pos.ToD2D(), D2D1::ColorF(1.0f, 1.0f, 1.0f, 0.20f));
		
	}
	if (m_selectedBase)
	{
		DrawItems(gfx);
	}
	Locator::TextManager->GetFormat("Tahoma14")->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);

	m_text["credits"].Draw(gfx);
	
}

bool ItemsSelector::OnMouseClick(const Vec2i& mouse,bool isControlKey)
{
	baseItemSelected = false;
	
	for (int c = 0; c < m_bases.numElements(); c++)
	{
			if (m_basePlaces[c].pos.Contains(mouse))
			{
				 m_selectedBase = &m_bases(c);
				 if(isControlKey)
				    baseItemSelected = true;

				 Locator::SoundEngine->Play("select");
				 return true;
			}
		
		
	}
	
	return false;
}

bool ItemsSelector::BaseItemSelected()
{
	return baseItemSelected;
}

void ItemsSelector::BaseItemSelected(bool val)
{
	baseItemSelected = val;
	if (val == false)
		m_selectedBase = nullptr;
}

void ItemsSelector::SetBaseIntoWorld(RectF pos)
{
	m_numBasesInWorld++;
	if (m_numBasesInWorld > 4)m_numBasesInWorld = 4;

	m_selectedBase->SetPosition(Vec2f(pos.left, pos.top), 128.0f, 128.0f);
}

Base * ItemsSelector::CurrentSelectedBase()
{
	return m_selectedBase;
}

void ItemsSelector::Update(const float & dt)
{
	for (int c = 0; c < m_bases.numElements(); c++)
		m_bases(c).Update(dt);
}

bool ItemsSelector::PointIn(const int & x, const int & y)
{
	return border.Contains(Vec2i(x,y));
}

void ItemsSelector::DrawItems(Graphics & gfx)
{
	int index = m_selectedBase->NumUinitTypes();
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
	m_text["dataDisplay"].Draw(gfx);
}


