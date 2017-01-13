#pragma once
#include "Sprite.h"
#include "SpriteSheet.h"
#include "Locator.h"
enum UnitTypes
{
	scout,
	fighter,
	radar,
	drone,
	none
};
class Base
{
	Sprite m_image;
	bool m_active = false;
	bool m_building = false;
	bool m_buildingComplete = false;
	bool m_underConstruction = false;
	UnitTypes m_unitTypes = none;
	UnitTypes m_currentBuildType = none;
	float m_build_Timer = 0.0f;
	float m_buildTime = 0.0f;
	float m_constuction_Timer = 0.0f;
	float m_constuctionTime = 0.0f;
	float m_width;
public:
	Base(SpriteSheet* image, int imageIndex, float w, float h,Vec2i pos,
		float constuctionTime);
	void Update(const float& dt);
	void Draw(class Graphics& gfx, class Camera&);
};