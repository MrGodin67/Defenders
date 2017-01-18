#pragma once
#include "Bases.h"
#include "includes.h"
#include "SpriteSheet.h"

class BaseManager
{
	
	std::vector<Base> m_bases;
	Base* m_selectedBase = nullptr;
public:
	BaseManager() {}
	
	void Draw(class Graphics& gfx, class Camera& cam);
	void Update(const float& dt);
	void AddBase(Vec2i pos, int imageIndex);
	void OnMouseClick(const Vec2i& mouse);
};