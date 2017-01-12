
#include "Tile.h"
#include "Graphics.h"
#include "Camera.h"

float Tile::ms_width = 0.0f;
float Tile::ms_height = 0.0f;

Tile::Tile()
	:m_image(nullptr, -1, 0, 0, {0.0f,0.0f})
{
}

Tile::Tile(SpriteSheet * image, const int & imageIndex, const Vec2f & pos, bool passable)
	:m_image(image,imageIndex,ms_width,ms_height,pos),
	m_passable(passable)
{
}

void Tile::draw(Graphics & gfx,Camera& cam)
{
	m_image.TransformToCamera(cam.GetPos());
	m_image.Draw(gfx);
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
