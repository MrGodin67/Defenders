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

	float cWidth = 48.0f;
	float toffset = 20.0f;
	float loffset = 20.0f;
	float x = border.left + loffset;
	float y = border.top + toffset;
	//for (int r = 0; r < 2; r++)
	//{
	//	//float x = border.left + loffset;
	//	//SpriteSheet* image, int imageIndex, float w, float h, Vec2i pos,
	//	//	float constuctionTime
	//	for (int c = 0; c < 2; c++)
	//	{
	//		m_bases(r,c) = Base(.buildTime = 30.0f;
	//		m_bases(r, c).cost = 100;
	//		m_bases(r, c).active = true;
	//		m_bases(r, c).built = false;
	//		m_bases(r, c).frame = RectF(x,y,x+cWidth,y+cWidth);
	//		m_bases(r, c).imageIndex = r * 2 + c;
	//		m_bases(r, c).numberAvaliable = 1;
	//		m_bases(r, c).progressBar = m_bases(r, c).frame;
	//		m_bases(r, c).selected = false;
	//		x += cWidth;
	//	}
	//	//y += cWidth;
	//}


	//
	//float newX = m_bases(1, 1).frame.right + 1.0f;

	hud_display = std::make_unique<D2D1Texture>(Locator::RenderTarget, L"media\\hud.png");

}

void ItemsSelector::SetSprites(std::string name, SpriteSheet * image)
{
	m_images[name] = image;
}

void ItemsSelector::Draw(Graphics & gfx)
{
	gfx.DrawSprite(D2D1::Matrix3x2F::Identity(), border.ToD2D(), hud_display->GetBitmap());

	/*for (int c = 0; c < m_bases.numElements(); c++)
	{
		gfx.DrawSprite(D2D1::Matrix3x2F::Identity(),
			m_bases(c).frame.ToD2D(), m_images["base"]->GetTexture(), &m_images["base"]->GetClippedImage(m_bases(c).imageIndex).ToD2D());
		if(m_bases(c).active)
			gfx.DrawRectangle(D2D1::Matrix3x2F::Identity(), m_bases(c).frame.ToD2D(), D2D1::ColorF(1.0f, 1.0f, 1.0f, 0.20f));
		
	}
	*/
}

bool ItemsSelector::OnMouseClick(const Vec2i& mouse, Item& item)
{
	baseItemSelected = false;
	/*for (int c = 0; c < m_bases.numElements(); c++)
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
		
	}*/
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


