#include "Bases.h"
#include "Graphics.h"
#include "Camera.h"
void Base::UpdateMainBuild(float dt)
{
		if (m_building)
		{
			if (m_buildClock.Update(dt))
			{
				m_building = false;
				m_status.SetMaxValue(0.0f);
				m_buildClock.timer = 0.0f;
				m_status.UpdateHealth(m_buildClock.timer);
				Locator::SoundEngine->Play("constructioncomplete");
			}
			m_status.UpdateHealth(m_buildClock.timer);
		}
	
}
Base::Base(Animation::RenderDesc& desc, std::vector<int> indices, float interval,
	std::string imageName, float constructionTime, _BaseTypes type, std::vector<Tile*>& buildingExitPoints)
	:Sprite(desc,indices,interval,imageName),
	m_type(type),
	m_buildingExitPoints(buildingExitPoints)
{
	StatusRect::StatusRectDesc status_desc = StatusRect::StatusRectDesc(desc.drawRect,1.0f,D2D1::ColorF(1.0f,1.0f,1.0f));
	m_status = LifeRect(status_desc, 20.0f, 8.0f);
	m_buildClock.timer = 0.0f;
	m_buildClock.buildTime = 20.0f;
	m_buildClock.building = true;
	m_building = true;
}

void Base::Draw(Camera & cam)
{
	cam.Rasterize(GetDrawable());
	if(m_selected)
	  cam.Rasterize(m_status.GetDrawable());
}

void Base::ConstructNewUnit(_EntityType type, float buildTime)
{
	
	Locator::SoundEngine->Play("unitrequest",0.35f);
	m_UnitsUnderConstruction.emplace_back(type, buildTime);
	float result = m_status.GetMaxValue();
	result += buildTime;
	m_status.SetMaxValue(result);
}

bool Base::UpdateBuilds(const float & dt)
{
	if (!m_building)
	{
		m_Completedbuilds.clear();
		float dt1 = dt;
		static float d = 0.0f;
		d += dt;
		for (size_t i = 0; i < m_UnitsUnderConstruction.size(); i++)
		{
			if (m_UnitsUnderConstruction[i].Update(dt1))
			{
				m_Completedbuilds.push_back(m_UnitsUnderConstruction[i].type);
				m_UnitsUnderConstruction.erase(m_UnitsUnderConstruction.begin() + i);
				i--;


				//m_status.SetMaxValue(result);
			}
		}
		if (m_UnitsUnderConstruction.size() == 0)
		{
			d = 0.0f;;
			m_status.SetMaxValue(0.0f);
		}
		m_status.UpdateHealth(d);

		// return true if size is greater than 0
		
	}
	else
	{
		UpdateMainBuild(dt);
		return false;
	}
	
	return (m_Completedbuilds.size() > 0);
}

std::vector<_EntityType> Base::CompletedBuilds()
{
	return m_Completedbuilds;
}

Vec2f Base::GetNextAvaliableExitPosition()
{
	for (auto& it : m_buildingExitPoints)
	{
		if (it->Passable())
			return it->GetWorldPosition();
	}

}


