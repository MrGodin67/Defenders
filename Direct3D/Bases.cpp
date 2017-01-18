#include "Bases.h"
#include "Graphics.h"
#include "Camera.h"
Base::Base(SpriteSheet * image, int imageIndex, float w, float h,Vec2i pos,
	float constuctionTime)
	:m_image(image,imageIndex,w,h,Vec2f(pos),none),
	m_underConstruction(true),
	m_constuctionTime(constuctionTime),
	m_width(w),
	m_imageIndex(imageIndex)
{
	
}

void Base::SetBuildTypes(_EntityType a, _EntityType b, _EntityType c, _EntityType d,int numTypes)
{
	m_unitTypes[0] = a;
	m_unitTypes[1] = b;
	m_unitTypes[2] = c;
	m_unitTypes[3] = d;
	m_numUnitTypes = numTypes;

}

_EntityType * Base::UnitTypes()
{
	return &m_unitTypes[0];
}

void Base::Update(const float & dt)
{
	if (m_underConstruction)
	{
		if ((m_constuction_Timer += dt) > m_constuctionTime)
		{
			m_underConstruction = false;
			m_active = true;
			Locator::SoundEngine->Play("constructioncomplete");
		}
	}
	if (m_building)
	{
		if ((m_build_Timer += dt) > m_buildTime)
		{
			m_buildingComplete = true;
			m_building = false;
		}
	}
}

void Base::Draw(Graphics & gfx, Camera &cam)
{
	
	m_image.TransformToCamera(cam.GetPos());
	m_image.Draw(gfx);
	if (m_underConstruction)
	{
		float percent = m_constuction_Timer / m_constuctionTime;
		RectF dr(m_image.GetAABB().left, m_image.GetAABB().top - 8.0f,
			m_image.GetAABB().left + (m_width * percent), m_image.GetAABB().top + 6.0f);

		gfx.DrawFilledScreenRectangle(dr.ToD2D(), D2D1::ColorF(0.0f, 1.0f, 0.0f, 1.0f));
		gfx.DrawFilledScreenRectangle(m_image.GetAABB().ToD2D(), D2D1::ColorF(0.9f, 0.0f, 0.0f, 0.2f));

	}
}

void Base::Draw(Graphics & gfx)
{
	
	m_image.Draw(gfx);
	
}

RectF Base::GetAABB()
{
	return m_image.GetAABB();
}
