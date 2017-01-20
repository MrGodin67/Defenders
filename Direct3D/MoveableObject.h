#pragma once
#include "Sprite2.h"
#include "AStar.h"
#include "Tile.h"
class MoveableObject : public Sprite
{
protected:
	
	Vec2f m_velocity;
	class WorldGrid& m_grid;
	float m_speed;
	std::vector<Vec2f> m_wayPoints;
	int m_wayPointIndex = 1;
	bool m_pathFinished = true;
	
private:
	bool CheckWaypointArrival(const float& dt);
public:
	MoveableObject(WorldGrid& grid, Animation::RenderDesc& desc, std::vector<int> indices, float interval,
		std::string imageName, float Speed, _EntityType type);
	
	virtual void Update(const float& dt)override;
	virtual void SetSpeed(float& s);
	virtual void SetWaypoints(std::vector<Vec2f>& wp);
	virtual Vec2f GetPosition()override;
	virtual void SetWayPoints(Vec2i mouse);
public:
	bool PathFinished();
	Tile* p_currentTile = nullptr;
	Vec2f GetCurrentWaypoint();
};
