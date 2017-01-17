#include "MoveableObject.h"
#include "Utils.h"
#include "WorldGrid.h"
bool MoveableObject::CheckWaypointArrival(const float& dt)
{

	if (!m_pathFinished )
	{
		Tile* tileO = m_grid.GetTile(GetCenter());
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
		
		Vec2f pt = m_wayPoints[m_wayPointIndex] - GetCenter();
		if (pt.LenSq() < (m_speed * m_speed) * (dt*dt))
		{
			m_wayPointIndex++;
			if (m_wayPointIndex >= (int)m_wayPoints.size())
			{
				m_pathFinished = true;
				return false;
			}
			

			m_angle = Utils::GetAngleBetweenPoints(GetCenter(), m_wayPoints[m_wayPointIndex]);
			m_velocity = (m_wayPoints[m_wayPointIndex] - GetCenter()).Normalize();
			return true;
		}
	}
	return false;
}

MoveableObject::MoveableObject(WorldGrid& grid,SpriteSheet * image, int imageIndex, float width, float height, float& speed,Vec2f pos,_EntityType type)
	:Sprite(image,imageIndex,width,height,pos,type),
	m_speed(speed),
	m_position(pos),
	m_grid(grid)
{
	m_angle = 90.0f;
	m_wayPoints.push_back(m_position);
	m_wayPointIndex = 1;
	p_currentTile = m_grid.GetTile(m_position);
	m_grid.SetMapPassable(m_position, false);
}

void MoveableObject::Update(const float & dt)
{
	m_position += m_velocity * m_speed * dt;
	
	CheckWaypointArrival(dt);
	if (m_pathFinished)
	{
		m_velocity = Vec2f(0.0f, 0.0f);
		m_grid.SetMapPassable(GetCenter(), false);

	}
}

void MoveableObject::TransformToCamera(Vec2f & pos)
{
	m_drawRect.left = m_position.x + -pos.x;
	m_drawRect.top = m_position.y + -pos.y;
	m_drawRect.right = m_drawRect.left + m_width;
	m_drawRect.bottom = m_drawRect.top + m_height;

}

void MoveableObject::SetSpeed(float & s)
{
	m_speed = s;
}

Vec2f MoveableObject::GetCenter()
{
	return Vec2f(m_position.x +(m_width * 0.5f),m_position.y +(m_height * 0.5f));
}

void MoveableObject::SetWaypoints(std::vector<Vec2f>& wp)
{
	m_wayPoints.clear();
   m_wayPoints = std::move(wp);
   m_wayPointIndex = 1;
   m_pathFinished = false;
   m_velocity = (m_wayPoints[m_wayPointIndex] - GetCenter()).Normalize();
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
		m_angle = Utils::GetAngleBetweenPoints(GetCenter(), m_wayPoints[m_wayPointIndex]);
		m_velocity = (m_wayPoints[m_wayPointIndex] - GetCenter()).Normalize();

	};
}

bool MoveableObject::PathFinished()
{
	return m_pathFinished;
}
