#pragma once

#include "includes.h"
#include "Rect.h"
class Entity
{
public:
	
	virtual void Update(const float& dt) = 0;
	virtual void Draw(class Graphics& gfx) = 0;
	virtual RectF GetAABB() = 0;
	virtual Vec2f GetCenter() = 0;
	
	
};