#pragma once
#include "Bases.h"
class TechnologyBase :
	public Base
{
	const float constructTime = 20.0f;
public:
	TechnologyBase();
	TechnologyBase(Animation::RenderDesc & desc, std::vector<int> indices, std::string imageName,
		std::vector<Tile*>& buildingExitPoints);
	virtual ~TechnologyBase();
	virtual std::wstring GetText()override;
	virtual void Update(const float& dt)override;
};

