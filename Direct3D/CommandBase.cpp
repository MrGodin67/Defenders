
#include "CommandBase.h"

CommandBase::CommandBase(Animation::RenderDesc & desc, std::vector<int> indices, std::string imageName,
	std::vector<Tile*>& buildingExitPoints)
	:
	Base(desc, indices, 0.0f, imageName, constructTime, baseCommand,buildingExitPoints)
{
	m_status.SetMaxValue(10.0f);
	m_buildClock.buildTime = 10.0f;
	m_buildClock.timer = 0.0f;
}

std::wstring CommandBase::GetText()
{
	std::wstring str = L"Command Center";
	return str;
}

void CommandBase::Update(const float & dt)
{
	float deltaTime = dt;
	m_buildClock.Update(deltaTime);
	m_status.UpdateHealth(m_buildClock.timer);
	
	if (UpdateBuilds(deltaTime))
	{
		
		
	};
}
