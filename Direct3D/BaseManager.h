#pragma once
#include "Bases.h"
#include "includes.h"
#include "SpriteSheet.h"

class BaseManager
{
	std::unique_ptr<SpriteSheet> m_images;
	std::vector<Base> m_bases;
	Base* m_selectedBase = nullptr;
public:
	BaseManager() {}
	BaseManager(std::wstring imageFile,float clipWidth,float clipHeight);
	void Draw(class Graphics& gfx, class Camera& cam);
	void Update(const float& dt);
	void AddBase(Vec2i pos, int imageIndex);
	SpriteSheet* Images();
	void OnMouseClick(const Vec2i& mouse);
};