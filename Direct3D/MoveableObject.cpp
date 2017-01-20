#include "MoveableObject.h"
#include "Utils.h"
#include "WorldGrid.h"
bool MoveableObject::CheckWaypointArrival(const float& dt)
{

	if (!m_pathFinished)
	{
		Tile* tileO = m_grid.GetTile(m_position);
		Tile* tile2 = m_grid.GetTile(m_wayPoints[m_wayPointIndex]);
		if (p_currentTile != tileO)
		{
			if (tile2 == tileO)
			{
				m_grid.SetMapPassable(p_currentTile->GetWorldPosition(), true);
				p_currentTile = tile2;

				m_grid.SetMapPassable(p_currentTile->GetWorldPosition(), false);

			}
		}

		Vec2f pt = m_wayPoints[m_wayPointIndex] - m_position;
		if (pt.LenSq() < (m_speed * m_speed) * (dt*dt))
		{
			m_wayPointIndex++;
			if (m_wayPointIndex >= (int)m_wayPoints.size())
			{
				m_pathFinished = true;
				return false;
			}


			m_rotAngles[0] = Utils::GetAngleBetweenPoints(m_position, m_wayPoints[m_wayPointIndex]);
			m_velocity = (m_wayPoints[m_wayPointIndex] - m_position).Normalize();
			return true;
		}
	}
	return false;
}

MoveableObject::MoveableObject(WorldGrid& grid, Animation::RenderDesc & desc, std::vector<int> indices, float interval, std::string imageName, float Speed, _EntityType type)
	:Sprite(desc, indices, interval, imageName, type),
	m_grid(grid),
	m_speed(Speed)
{
	m_wayPoints.push_back(m_position);
	m_wayPointIndex = 1;
	p_currentTile = m_grid.GetTile(m_position);
	m_grid.SetMapPassable(m_position, false);
}



void MoveableObject::Update(const float & dt)
{
	UpdatePosition(m_velocity * m_speed * dt);
	
	CheckWaypointArrival(dt);
	if (m_pathFinished)
	{
		m_velocity = Vec2f(0.0f, 0.0f);
		m_grid.SetMapPassable(m_position, false);

	}

	if (m_scale != Vec2f(1.0f, 1.0f))
	{
		m_scale.x > 1.0f ? m_scale.x -= dt * 0.5f: m_scale.x = 1.0f;
		m_scale.y > 1.0f ? m_scale.y -= dt * 0.5f : m_scale.y = 1.0f;
	}

}



void MoveableObject::SetSpeed(float & s)
{
	m_speed = s;
}



void MoveableObject::SetWaypoints(std::vector<Vec2f>& wp)
{
	m_wayPoints.clear();
   m_wayPoints = std::move(wp);
   m_wayPointIndex = 1;
   m_pathFinished = false;
   m_velocity = (m_wayPoints[m_wayPointIndex] - m_position).Normalize();
}

Vec2f MoveableObject::GetPosition()
{
	return m_position;
}



void MoveableObject::SetWayPoints(Vec2i mouse)
{
	std::vector<Vec2f> pts;
	if (m_grid.FindPath(Vec2i(m_position), mouse, pts))
	{
		m_wayPoints.clear();
		m_wayPoints = std::move(pts);
		m_wayPointIndex = 1;
		m_pathFinished = false;
		m_rotAngles[0]= Utils::GetAngleBetweenPoints(m_position, m_wayPoints[m_wayPointIndex]);
		m_velocity = (m_wayPoints[m_wayPointIndex] - m_position).Normalize();

	};
}

bool MoveableObject::PathFinished()
{
	return m_pathFinished;
}



Vec2f MoveableObject::GetCurrentWaypoint()

{
	int index = m_wayPointIndex - 1;
	if (index < 0)index = 0;
	return m_wayPoints[index];
}
