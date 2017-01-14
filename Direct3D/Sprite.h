#pragma once

#include "includes.h"
#include "Rect.h"
#include "Vec2.h"
#include "EntityInterface.h"
#include "SpriteSheet.h"
class Sprite : public Entity
{
protected:
	SpriteSheet* m_image;
	RectF m_drawRect;
	Vec2f m_pos;
	float m_width;
	float m_height;
	int m_imageIndex;
	float m_angle = 0.0f;
public:
	Sprite(SpriteSheet* image,int imageIndex, float width, float height, Vec2f pos,_EntityType type);

	// Inherited via Entity
	virtual void Update(const float & dt) override;
	virtual void Draw(Graphics & gfx) override;
	virtual RectF GetAABB() override;
	virtual void TransformToCamera(Vec2f& pos);
	virtual Vec2f GetCenter() override;
	virtual Vec2f GetPosition();
	void SetTexture(SpriteSheet* image, int imageIndex,float width,float height);
	
};