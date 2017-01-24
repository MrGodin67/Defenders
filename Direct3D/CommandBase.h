#pragma once
#include "Bases.h"

class CommandBase : public Base
{
	const float constructTime = 20.0f;
public:
	CommandBase() {}
	CommandBase(Animation::RenderDesc& desc, std::vector<int> indices,std::string imageName,
		std::vector<Tile*>& buildingExitPoints);
	virtual std::wstring GetText()override;
	virtual void Update(const float& dt)override;
	
};