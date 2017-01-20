
#include "Tile.h"
#include "Graphics.h"
#include "Camera.h"

float Tile::ms_width = 0.0f;
float Tile::ms_height = 0.0f;

Tile::Tile(Animation::RenderDesc& desc,bool passable)
	:Animation(desc),m_passable(passable)
{
}



void Tile::Draw(Camera& cam)
{
	cam.Rasterize(GetDrawable());
	
	

	D2D1_COLOR_F color = D2D1::ColorF(0.08f, 0.08f, 0.08f, m_colorAlphaBlend);
	//gfx.DrawFilledScreenRectangle(m_visibleRect.ToD2D(), color);
}

RectF Tile::GetRect()
{
	return RectF(m_renderDesc.drawRect.left,
		m_renderDesc.drawRect.top,
		m_renderDesc.drawRect.right,
		m_renderDesc.drawRect.bottom);
}

Vec2f Tile::GetWorldPosition()
{
	return Vec2f(m_renderDesc.drawRect.left + 2.0f, m_renderDesc.drawRect.top + 2.0f);
}

void Tile::SetVisibleColorAlpha(float alpha)
{
	if(alpha < m_colorAlphaBlend)
	   m_colorAlphaBlend = alpha;
}

float Tile::GetVisibleColorAplha()
{
	return m_colorAlphaBlend;
}



void Tile::SetWidthHeight(const float & w, const float & h)
{
	ms_width = w;
	ms_height = h;
}

float Tile::Height()
{
	return ms_height;
}

float Tile::Width()
{
	return ms_width;
}
