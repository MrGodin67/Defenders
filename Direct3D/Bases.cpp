#include "Bases.h"
#include "Graphics.h"
#include "Camera.h"
Base::Base(Animation::RenderDesc& desc, std::vector<int> indices, float interval,
	std::string imageName, _EntityType type,float constructionTime)
	:Sprite(desc,indices,interval,imageName,type),
	m_underConstruction(false),
	m_constuctionTime(constructionTime),
	m_width(desc.drawRect.right - desc.drawRect.left)
{
	
}

void Base::SetPosition(Vec2f pos,float w,float h)
{
	m_underConstruction = true;
	m_constuction_Timer = 0.0f;
	m_width = w; 
	m_position = pos;
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
	if (m_buildingUnit)
	{
		if ((m_build_Timer += dt) > m_buildTime)
		{
			m_buildingComplete = true;
			m_buildingUnit = false;
		}
	}
}

void Base::Draw(Graphics & gfx, Camera &cam)
{
	
	cam.Rasterize(GetDrawable());
	
	if (m_underConstruction)
	{
		RectF rect = GetRect();
		float percent = m_constuction_Timer / m_constuctionTime;
		RectF dr(rect.left, rect.top - 8.0f,
			rect.left + (m_width * percent), rect.top + 6.0f);

		gfx.DrawFilledScreenRectangle(dr.ToD2D(), D2D1::ColorF(0.0f, 1.0f, 0.0f, 1.0f));
		gfx.DrawFilledScreenRectangle(rect.ToD2D(), D2D1::ColorF(0.9f, 0.0f, 0.0f, 0.2f));

	}
}

void Base::Draw(Graphics & gfx)
{
	
	
	
}

std::wstring Base::GetText()
{
	std::wstring Text;
	if (!m_active)
	{
		Text += L"Cost " + std::to_wstring(m_cost) + L"\n";
	}
	
	if (m_underConstruction)
	{
		Text += L"Under Constuction [ " + std::to_wstring((int)((m_constuction_Timer / m_constuctionTime) * 100.0f)) + L" ]% complete\n";
	}
	for (int c = 0; c < m_numUnitTypes; c++)
	{
		switch (m_unitTypes[c])
		{
		case _EntityType::drone:
			Text += L"Drone : " + std::to_wstring(m_cost) + L" credits\n";
			break;
		case _EntityType::fighter:
			Text += L"Fighter : " + std::to_wstring(m_cost) + L" credits\n";
			break;
		case _EntityType::artillary:
			Text += L"Artillary : " + std::to_wstring(m_cost) + L" credits\n";
			break;
		case _EntityType::radar:
			Text += L"Radar: " + std::to_wstring(m_cost) + L" credits\n";
			break;
		case _EntityType::turret:
			Text += L"Turret: " + std::to_wstring(m_cost) + L" credits\n";
			break;
		case _EntityType::tech:
			Text += L"Technology: " + std::to_wstring(m_cost) + L" credits\n";
			break;
		case _EntityType::data:
			Text += L"Data Storage: " + std::to_wstring(m_cost) + L" credits\n";
			break;
		}
	}
	
	//= L"Base Data :\n Cost " + std::to_wstring(100);
	return Text;
}


