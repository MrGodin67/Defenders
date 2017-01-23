
#include "FactoryBase.h"

FactoryBase::FactoryBase(Animation::RenderDesc & desc, std::vector<int> indices, std::string imageName,
	std::vector<Tile*>& buildingExitPoints)
	:
	Base(desc, indices, 0.0f, imageName, constructTime, baseFactory,buildingExitPoints)
{}

std::wstring FactoryBase::GetText()
{
	std::wstring str = L"Unit Creation Facility";
	return str;
}

void FactoryBase::Update(const float & dt)
{
	float deltaTime = dt;
	m_buildClock.Update(deltaTime);
	m_status.UpdateHealth(m_buildClock.timer);
}
