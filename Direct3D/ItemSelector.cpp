#include "ItemSelector.h"
#include "Graphics.h"
ItemsSelector::ItemsSelector(Vec2f& screenSize, float height)
{
	border.left = 0.0f;
	border.top = screenSize.y - height;
	border.right = screenSize.x;
	border.bottom = screenSize.y-1.0f;
	m_bases.resize(2, 2);
	m_items.resize(4, 4);

	m_bases(0, 0).buildTime = 30.0f;
	m_bases(0, 0).cost = 100;
	m_bases(0, 0).active = true;
	m_bases(0, 0).built = false;
	m_bases(0, 0).frame = RectF(border.left + 1.0f, border.top + 1.0f, (border.left + 1.0f) + 63.0f, (border.top + 1.0f) + 63.0f);
	m_bases(0, 0).imageIndex = 0;
	m_bases(0, 0).numberAvaliable = 1;
	m_bases(0, 0).progressBar = m_bases(0, 0).frame;
	m_bases(0, 0).selected = false;
	
	m_bases(0, 1).buildTime = 30.0f;
	m_bases(0, 1).cost = 100;
	m_bases(0, 1).active = true;
	m_bases(0, 1).built = false;
	m_bases(0, 1).frame = RectF((border.left + 1.0f)+63.0f, border.top + 1.0f, (border.left + 1.0f) + (2.0f*63.0f), (border.top + 1.0f) + 63.0f);
	m_bases(0, 1).imageIndex = 1;
	m_bases(0, 1).numberAvaliable = 1;
	m_bases(0, 1).progressBar = m_bases(0, 1).frame;
	m_bases(0, 1).selected = true;

	m_bases(1, 0).buildTime = 30.0f;
	m_bases(1, 0).cost = 100;
	m_bases(1, 0).active = true;
	m_bases(1, 0).built = false;
	m_bases(1, 0).frame = RectF(border.left + 1.0f, (border.top + 1.0f) + 63.0f, (border.left + 1.0f) + 63.0f, (border.top + 1.0f) + (2.0f*63.0f));
	m_bases(1, 0).imageIndex = 2;
	m_bases(1, 0).numberAvaliable = 1;
	m_bases(1, 0).progressBar = m_bases(0, 0).frame;
	m_bases(1, 0).selected = false;

	m_bases(1, 1).buildTime = 30.0f;
	m_bases(1, 1).cost = 100;
	m_bases(1, 1).active = true;
	m_bases(1, 1).built = false;
	m_bases(1, 1).frame = RectF((border.left + 1.0f) + (63.0f), (border.top + 1.0f) + (63.0f), (border.left + 1.0f) + (2.0f*63.0f), (border.top + 1.0f) + (2.0f*63.0f));
	m_bases(1, 1).imageIndex = 3;
	m_bases(1, 1).numberAvaliable = 1;
	m_bases(1, 1).progressBar = m_bases(0, 0).frame;
	m_bases(1, 1).selected = false;
	float newX = m_bases(1, 1).frame.right + 1.0f;

}

void ItemsSelector::SetSprites(std::string name, SpriteSheet * image)
{
	m_images[name] = image;
}

void ItemsSelector::Draw(Graphics & gfx)
{
	gfx.DrawFilledScreenRectangle(border.ToD2D(),D2D1::ColorF(0.0f, 0.0f, 0.0f, 1.0f));
	gfx.DrawRectangle(D2D1::Matrix3x2F::Identity(), border.ToD2D(), D2D1::ColorF(1.0f, 0.0f, 0.0f, 1.0f));
	for (int c = 0; c < m_bases.numElements(); c++)
	{
		gfx.DrawSprite(D2D1::Matrix3x2F::Identity(),
			m_bases(c).frame.ToD2D(), m_images["base"]->GetTexture(), &m_images["base"]->GetClippedImage(m_bases(c).imageIndex).ToD2D());
		if(m_bases(c).active)
			gfx.DrawRectangle(D2D1::Matrix3x2F::Identity(), m_bases(c).frame.ToD2D(), D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f));
		else
			gfx.DrawFilledScreenRectangle( m_bases(c).frame.ToD2D(), D2D1::ColorF(0.2f, 0.2f, 0.8f, 0.8f));

	}
	
}

bool ItemsSelector::OnMouseClick(const Vec2i& mouse, Item& item)
{
	baseItemSelected = false;
	for (int c = 0; c < m_bases.numElements(); c++)
	{
		if (m_bases(c).active && !m_bases(c).built)
		{
			if (m_bases(c).frame.Contains(mouse))
			{
				
				m_bases(c).selected = baseItemSelected = true;
				m_bases(c).built = true;
				item = m_bases(c);
				return true;
			}
		}
		
	}
	item = Item();
	return false;
}

bool ItemsSelector::BaseItemSelected()
{
	return baseItemSelected;
}

void ItemsSelector::BaseItemSelected(bool val)
{
	baseItemSelected = val;
}

bool ItemsSelector::PointIn(const int & x, const int & y)
{
	return border.Contains(Vec2i(x,y));
}


