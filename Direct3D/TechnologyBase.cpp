#include "TechnologyBase.h"

TechnologyBase::TechnologyBase()
{}

TechnologyBase::TechnologyBase(Animation::RenderDesc & desc, std::vector<int> indices, std::string imageName,
	std::vector<Tile*>& buildingExitPoints)
	:
	Base(desc, indices, 0.0f, imageName, constructTime, baseFactory,buildingExitPoints)
{}


TechnologyBase::~TechnologyBase()
{
}

std::wstring TechnologyBase::GetText()
{
	std::wstring str = L"Technology Research Facility\nCost "+ std::to_wstring(500);
	return str;
}

void TechnologyBase::Update(const float & dt)
{
	float deltaTime = dt;
	m_buildClock.Update(deltaTime);
	m_status.UpdateHealth(m_buildClock.timer);
}
