#include "ItemSelector.h"
#include "Graphics.h"
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
	
	for (int r = 0; r < 2; r++)
	{
		
		for (int c = 0; c < 2; c++)
		{
			const int index = r * 2 + c;
			m_bases(r,c) = Base(Locator::ImageManager->GetImage("bases"),
				index,48.0f,48.0f,Vec2i((int)x,(int)y),30.0f);
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

}



void ItemsSelector::Draw(Graphics & gfx)
{
	gfx.DrawFilledScreenRectangle(border.ToD2D(), D2D1::ColorF(0.1f, 0.2f, 0.0f, 0.40f));
	gfx.DrawSprite(D2D1::Matrix3x2F::Identity(), border.ToD2D(), Locator::ImageManager->GetImage("hud")->GetTexture());

	for (int c = 0; c < m_bases.numElements(); c++)
	{
		m_bases(c).Draw(gfx);
		gfx.DrawRectangle(D2D1::Matrix3x2F::Identity(), m_bases(c).GetAABB().ToD2D(), D2D1::ColorF(1.0f, 1.0f, 1.0f, 0.20f));
		
	}
	if (m_selectedBase)
	{
		DrawItems(gfx);
	}
	
}

bool ItemsSelector::OnMouseClick(const Vec2i& mouse,bool isControlKey)
{
	baseItemSelected = false;
	
	for (int c = 0; c < m_bases.numElements(); c++)
	{
			if (m_bases(c).GetAABB().Contains(mouse))
			{
				 m_selectedBase = &m_bases(c);
				 if(isControlKey)
				    baseItemSelected = true;
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
	if (!baseItemSelected)
		m_selectedBase = nullptr;
}

Base * ItemsSelector::CurrentSelectedBase()
{
	return m_selectedBase;
}

bool ItemsSelector::PointIn(const int & x, const int & y)
{
	return border.Contains(Vec2i(x,y));
}

void ItemsSelector::DrawItems(Graphics & gfx)
{
	int index = m_selectedBase->NumUinitTypes();
	RectF rect = m_selectedBase->GetAABB();
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
}


