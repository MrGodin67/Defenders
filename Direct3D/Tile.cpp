
#include "Tile.h"
#include "Graphics.h"
#include "Camera.h"

float Tile::ms_width = 0.0f;
float Tile::ms_height = 0.0f;

Tile::Tile()
	:m_image(nullptr, -1, 0, 0, {0.0f,0.0f},none)
{
}

Tile::Tile(SpriteSheet * image, const int & imageIndex, const Vec2f & pos, bool passable)
	:m_image(image,imageIndex,ms_width,ms_height,pos,none),
	m_passable(passable)
{
	
}

void Tile::draw(Graphics & gfx,Camera& cam)
{
	
	m_image.TransformToCamera(cam.GetPos());
	m_visibleRect = m_image.GetAABB();
	m_image.Draw(gfx);
	D2D1_COLOR_F color = D2D1::ColorF(0.08f, 0.08f, 0.08f, m_colorAlphaBlend);
	gfx.DrawFilledScreenRectangle(m_visibleRect.ToD2D(), color);
}

RectF Tile::GetRect()
{
	return m_image.GetAABB();
}

Vec2f Tile::GetWorldPosition()
{
	return Vec2f(m_image.GetAABB().left + 2.0f, m_image.GetAABB().top + 2.0f);
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
