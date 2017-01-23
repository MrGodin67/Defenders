#pragma once

#include "Bases.h"

class RepairBase :
	public Base
{
	const float constructTime = 20.0f;
public:
	RepairBase();
	RepairBase(Animation::RenderDesc & desc, std::vector<int> indices, std::string imageName,
		std::vector<Tile*>& buildingExitPoints);
	virtual ~RepairBase();
	virtual std::wstring GetText()override;
	virtual void Update(const float& dt)override;
};

