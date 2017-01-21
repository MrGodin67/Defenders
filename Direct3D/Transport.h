#pragma once

#include "MoveableObject.h"
#include "WorldGrid.h"
#include "Camera.h"
class ConstructionCrew
{
	WorldGrid& m_grid;
	Camera& m_cam;
	const size_t ship = 0;
	const size_t bulldozer = 1;
	const size_t framer = 2;
	const size_t numVehicals = 3;
	std::vector<MoveableObject> m_vehicals;
	std::vector<Vec2f> m_site;

public:
	ConstructionCrew(WorldGrid& grid,Camera& cam)
		:m_grid(grid),m_cam(cam)
	{
		m_vehicals.resize(numVehicals);
		m_vehicals[ship] = MoveableObject()
	}
};