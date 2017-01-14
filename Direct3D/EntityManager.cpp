#include "EntityManager.h"
#include "MoveableObject.h"
#include "Locator.h"
#include "Rect.h"
#include "Graphics.h"
void UnitManager::HandleInput(Entity * obj)
{
}
void UnitManager::HandleInput(MoveableObject * obj)
{
	if (m_input.MouseLeftClick())
	{
		m_selectedMoveableEntity = nullptr;
		for (size_t index = 0;index <  m_playerEntites.size();index++)
		{
		
			if (m_playerEntites[index]->GetAABB().Contains(m_input.GetMousePos()))
			{
				switch (m_playerEntites[index]->Type())
				{
				case radar:
				case fighter:
				case miner:
				case artillary:
				case drone:
					m_selectedMoveableEntity = (MoveableObject*)m_playerEntites[index].get();
					m_selectedUnitRectAngle = 0.0f;
					break;
				}// end switch
		
				break;// break loop;
			}
		}
	}
	if (m_input.MouseRightClick())
	{
		if (m_selectedMoveableEntity)
		{
			std::vector<Vec2f> pts;
			Vec2f mp = Vec2f((float)m_input.GetMousePos().x, (float)m_input.GetMousePos().y);
			mp = m_cam.ConvertToWorldSpace(mp);
			Vec2i s = m_grid.GetCellIndex(m_selectedMoveableEntity->GetCenter());
			Vec2i e = m_grid.GetCellIndex(mp);

			if (m_grid.FindPath(s, e, pts))
				m_selectedMoveableEntity->SetWaypoints(pts);
		}
	}
}
UnitManager::UnitManager(InputManager& input,WorldGrid& world,Camera & cam, std::wstring imageFile)

	:m_cam(cam),
	m_grid(world),
	m_input(input)
{
	m_images = std::make_unique<SpriteSheet>(imageFile, 64.0f, 64.0f);
	assert(m_images);
}

void UnitManager::AddPlayerUnit(_EntityType type, Vec2i pos)
{
	switch (type)
	{
	case drone:
		m_playerEntites.push_back(std::make_unique<MoveableObject>(m_images.get(), 0, 48.0f, 48.0f, speeds[3], Vec2f(pos.x*64.0f, pos.y* 64.0f), drone));
		break;
	case fighter:
		m_playerEntites.push_back(std::make_unique<MoveableObject>(m_images.get(), 1, 48.0f, 48.0f, speeds[2], Vec2f(pos.x*64.0f, pos.y* 64.0f), fighter));
		break;
	case artillary:
		m_playerEntites.push_back(std::make_unique<MoveableObject>(m_images.get(), 2, 48.0f, 48.0f, speeds[1], Vec2f(pos.x*64.0f, pos.y* 64.0f), artillary));
		break;
	case radar:
		m_playerEntites.push_back(std::make_unique<MoveableObject>(m_images.get(), 3, 48.0f, 48.0f, speeds[0], Vec2f(pos.x*64.0f, pos.y* 64.0f), radar));
		break;
	case miner:
		m_playerEntites.push_back(std::make_unique<MoveableObject>(m_images.get(), 4, 48.0f, 48.0f, speeds[0], Vec2f(pos.x*64.0f, pos.y* 64.0f), miner));
		break;
	}
}

void UnitManager::AddEnemyUnit(_EntityType type, Vec2i pos)
{
	switch (type)
	{
	case drone:
		break;
	case fighter:
		break;
	case artillary:
		break;
	case radar:
		break;
	case miner:
		break;
	}
}

void UnitManager::SelectUnit(Vec2f world)
{

}

void UnitManager::Update(const float & dt)
{
	for (size_t index = 0; index < m_playerEntites.size(); index++)
	{
		switch (m_playerEntites[index]->Type())
		{
		case radar:
		case fighter:
		case miner:
		case artillary:
		case drone:
		{
			MoveableObject* obj = (MoveableObject*)m_playerEntites[index].get();
			if (obj)
			{
				HandleInput(obj);
				obj->Update(dt);
				obj->TransformToCamera(m_cam.GetPos());
				if (!obj->PathFinished())
					m_grid.SetVisibility(obj->GetCenter());
			}
		}
		break;
		}
	}
}

void UnitManager::Draw(Graphics & gfx)
{
	for (auto& it : m_playerEntites)
	{
		it->Draw(gfx);
	}
	if (m_selectedMoveableEntity)
	{
		m_selectedUnitRectAngle += 1.1f;
		if (m_selectedUnitRectAngle > 360.0f)m_selectedUnitRectAngle = 0.0f;
		RectF rect = m_selectedMoveableEntity->GetAABB();
		float w = rect.right - rect.left;
		float h = rect.bottom - rect.top;
		h = h * 0.5f;// half it
		w = w * 0.5f;
		D2D1_POINT_2F center = { rect.left + w,rect.top + h };
		gfx.DrawRectangle(D2D1::Matrix3x2F::Rotation(m_selectedUnitRectAngle, center), rect.ToD2D(), D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f));
	}
}
