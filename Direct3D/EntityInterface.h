#pragma once

#include "includes.h"
#include "Rect.h"

enum _EntityType
{
	drone,
	fighter,
	artillary,
	radar,
	miner,
	none
};
class Entity
{
	_EntityType m_type = none;
public:
	Entity() {}
	Entity(_EntityType type)
		:m_type(type) {}
	_EntityType Type() { return m_type; };
	virtual void Update(const float& dt) = 0;
	virtual void Draw(class Graphics& gfx) = 0;
	virtual RectF GetAABB() = 0;
	virtual Vec2f GetCenter() = 0;
	virtual void TransformToCamera(Vec2f& pos) {};
	
	
};