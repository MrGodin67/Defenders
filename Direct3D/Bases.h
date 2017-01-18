#pragma once
#include "Sprite.h"
#include "SpriteSheet.h"
#include "Locator.h"

class Base
{
	Sprite m_image;
	bool m_active = false;
	bool m_building = false;
	bool m_buildingComplete = false;
	bool m_underConstruction = false;
	_EntityType m_unitTypes[4];
	_EntityType  m_currentBuildType = none;
	int m_imageIndex;
	int m_numUnitTypes = 0;
	float m_build_Timer = 0.0f;
	float m_buildTime = 0.0f;
	float m_constuction_Timer = 0.0f;
	float m_constuctionTime = 0.0f;
	float m_width;
public:
	Base() :m_image(0, 0, 0, 0, Vec2f(0,0), none) {}
	Base(SpriteSheet* image, int imageIndex, float w, float h,Vec2i pos,
		float constuctionTime);

	void SetBuildTypes(_EntityType a, _EntityType b, _EntityType c, _EntityType d, int numTypes);
	_EntityType* UnitTypes();
	int ImageIndex() {return m_imageIndex;}
	void Update(const float& dt);
	void Draw(class Graphics& gfx, class Camera&);
	void Draw(class Graphics& gfx);
	int NumUinitTypes() { return m_numUnitTypes; }

	RectF GetAABB();
};