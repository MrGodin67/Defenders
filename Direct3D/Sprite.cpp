#include "Sprite.h"
#include "Graphics.h"
Sprite::Sprite(SpriteSheet* image, int imageIndex, float width, float height, Vec2f pos)
	:m_image(image),m_imageIndex(imageIndex),m_width(width),m_height(height),m_pos(pos)
{
	m_drawRect = { pos.x,pos.y,pos.x + m_width,pos.y + m_height };
}

void Sprite::Update(const float & dt)
{
	
}

void Sprite::Draw(Graphics & gfx)
{
	if (m_image)
	{
		D2D1_POINT_2F p = { m_drawRect.left + (m_width / 2),m_drawRect.top + (m_height / 2) };
		gfx.DrawSprite(D2D1::Matrix3x2F::Rotation(m_angle, p),
			m_drawRect.ToD2D(), m_image->GetTexture(),
			&m_image->GetClippedImage(m_imageIndex).ToD2D());
	}
}

RectF Sprite::GetAABB()
{
	return m_drawRect;
}

void Sprite::TransformToCamera(Vec2f & pos)
{
	float x = m_pos.x + -pos.x;
	float y = m_pos.y + -pos.y;
	m_drawRect = { x,y,x + m_width,y + m_height };
}

Vec2f Sprite::GetCenter()
{
	return Vec2f();
}

Vec2f Sprite::GetPosition()
{
	return m_pos;
}

void Sprite::SetTexture(SpriteSheet * image, int imageIndex, float width, float height)
{
	m_width = width;
	m_height = height;
	m_image = image;
	m_imageIndex = imageIndex;
}


