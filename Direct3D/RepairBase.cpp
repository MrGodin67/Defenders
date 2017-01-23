#include "RepairBase.h"



RepairBase::RepairBase()
{
}
RepairBase::RepairBase(Animation::RenderDesc & desc, std::vector<int> indices, std::string imageName,
	std::vector<Tile*>& buildingExitPoints)
	:
	Base(desc, indices, 0.0f, imageName, constructTime, baseFactory,buildingExitPoints)
{}


RepairBase::~RepairBase()
{
}

std::wstring RepairBase::GetText()
{
	std::wstring str = L"Unit Re-Construction Facility\nCost " + std::to_wstring(500);
	return str;
}

void RepairBase::Update(const float & dt)
{
	float deltaTime = dt;
	m_buildClock.Update(deltaTime);
	m_status.UpdateHealth(m_buildClock.timer);
}
