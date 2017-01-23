#pragma once

enum _EntityType;
struct CreateUnitEvent
{
	_EntityType type;
	float buildTime;
	CreateUnitEvent(_EntityType type, float buildTime)
		:type(type), buildTime(buildTime)
	{}
};