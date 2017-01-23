#pragma once
#include "Bases.h"

class FactoryBase : public Base
{
	const float constructTime = 20.0f;
public:
	FactoryBase() {}
	FactoryBase(Animation::RenderDesc& desc, std::vector<int> indices, std::string imageName, std::vector<Tile*>& buildingExitPoints);
	virtual std::wstring GetText()override;
	virtual void Update(const float& dt)override;
};