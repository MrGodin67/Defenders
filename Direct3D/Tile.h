#pragma once
#include "Sprite.h"
#include "SpriteSheet.h"


#include "Rect.h"
class Tile
{
private:
	Sprite m_image;
	bool m_passable;
private:
	static float ms_width;
	static float ms_height;
public:
	Tile();
	Tile(SpriteSheet* image,const int& imageIndex, const Vec2f& pos, bool passable);
	void draw(class Graphics& gfx,class Camera& cam);
	bool Passable() { return m_passable; }
	void Passable(bool canPass) { m_passable = canPass; }
public:
	static void SetWidthHeight(const float& w, const float& h);
	static float Height();
	static float Width();
};