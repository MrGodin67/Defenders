#include "Bases.h"
#include "Graphics.h"
#include "Camera.h"
Base::Base(Animation::RenderDesc& desc, std::vector<int> indices, float interval,
	std::string imageName, float constructionTime, _BaseTypes type, std::vector<Tile*>& buildingExitPoints)
	:Sprite(desc,indices,interval,imageName),
	m_type(type),
	m_buildingExitPoints(buildingExitPoints)
{
	StatusRect::StatusRectDesc status_desc = StatusRect::StatusRectDesc(desc.drawRect,1.0f,D2D1::ColorF(1.0f,1.0f,1.0f));
	m_status = LifeRect(status_desc, 100.0f, 8.0f);
	m_buildClock.timer = 0.0f;
	m_buildClock.buildTime = constructionTime;
	
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
}

bool Base::UpdateBuilds(const float & dt)
{
	m_Completedbuilds.clear();
	float dt1 = dt;
	for (size_t i = 0; i < m_UnitsUnderConstruction.size(); i++)
	{
		if (m_UnitsUnderConstruction[i].Update(dt1))
		{
			m_Completedbuilds.push_back(m_UnitsUnderConstruction[i].type);
			m_UnitsUnderConstruction.erase(m_UnitsUnderConstruction.begin() + i);
			i--;
		}
	}

	// return true if size is greater than 0
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


