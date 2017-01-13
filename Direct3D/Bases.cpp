#include "Bases.h"
#include "Graphics.h"
#include "Camera.h"
Base::Base(SpriteSheet * image, int imageIndex, float w, float h,Vec2i pos,
	float constuctionTime)
	:m_image(image,imageIndex,w,h,Vec2f(pos)),
	m_underConstruction(true),
	m_constuctionTime(constuctionTime),
	m_width(w)
{
	Locator::SoundEngine->Play("constructionstarted");
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

	}
}
