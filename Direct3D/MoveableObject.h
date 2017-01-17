#pragma once
#include "Sprite.h"
#include "AStar.h"
#include "Tile.h"
class MoveableObject : public Sprite
{
protected:
	Vec2f m_position;
	Vec2f m_velocity;
	class WorldGrid& m_grid;
	float m_speed;
	std::vector<Vec2f> m_wayPoints;
	int m_wayPointIndex = 1;
	bool m_pathFinished = true;
	
private:
	bool CheckWaypointArrival(const float& dt);
public:
	
	MoveableObject(WorldGrid& grid,SpriteSheet* image, int imageIndex, float width, float height, float& speed,Vec2f pos,_EntityType type);
	virtual void Update(const float& dt)override;
	virtual void TransformToCamera(Vec2f& pos)override;
	virtual void SetSpeed(float& s);
	virtual Vec2f GetCenter() override;
	virtual void SetWaypoints(std::vector<Vec2f>& wp);
	virtual Vec2f GetPosition()override;

	virtual void SetWayPoints(Vec2i mouse);
public:
	bool PathFinished();
	Tile* p_currentTile = nullptr;
	std::vector<Vec2f>& GetWayPoints() { return m_wayPoints; }
	Vec2f GetCurrentWaypoint() 
	{ 
		int index = m_wayPointIndex - 1;
		if (index < 0)index = 0;
		return m_wayPoints[index]; 
	}
};
