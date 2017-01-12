#include "MoveableObject.h"

bool MoveableObject::CheckWaypointArrival()
{
	if (!m_pathFinished && m_wayPointIndex != -1)
	{
		

		Vec2f pt = m_wayPoints[m_wayPointIndex] - m_position;
		if (pt.Len() < m_speed*0.016f)
		{
			m_wayPointIndex++;
			if (m_wayPointIndex >= (int)m_wayPoints.size())
			{
				m_pathFinished = true;
				m_wayPointIndex = -1;
				return false;
			}
			m_velocity = (m_wayPoints[m_wayPointIndex] - m_position).Normalize();
			return true;
		}
	}
	return false;
}

MoveableObject::MoveableObject(SpriteSheet * image, int imageIndex, float width, float height, float& speed,Vec2f pos)
	:Sprite(image,imageIndex,width,height,pos),
	m_speed(speed),
	m_position(pos)
{

}

void MoveableObject::Update(const float & dt)
{
	m_position += m_velocity * m_speed * dt;
	
	CheckWaypointArrival();
	if (m_pathFinished)
		m_velocity = Vec2f(0.0f,0.0f);
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
   m_wayPoints = std::move(wp);
   m_wayPointIndex = 1;
   m_pathFinished = false;
   m_velocity = (m_wayPoints[m_wayPointIndex] - m_position).Normalize();
}

bool MoveableObject::PathFinished()
{
	return m_pathFinished;
}
