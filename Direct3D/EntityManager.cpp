#include "EntityManager.h"
#include "MoveableObject.h"
#include "Locator.h"
#include "Rect.h"
#include "Graphics.h"
void UnitManager::HandleInput(Entity * obj)
{
}
void UnitManager::HandleInput( Mouse::Event& mouse, Keyboard::Event& kbd)
{
	if (mouse.GetType() == Mouse::Event::LPress)
	{
		m_selectedMoveableEntity = nullptr;
		for (size_t index = 0;index <  m_playerEntites.size();index++)
		{
		
			if (m_playerEntites[index]->GetAABB().Contains(Vec2i(mouse.GetPosX(),mouse.GetPosY())))
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
	if (mouse.GetType() == Mouse::Event::RPress)
	{
		if (m_selectedMoveableEntity)
		{
			if (!m_selectedMoveableEntity->PathFinished())
			{
				if (m_selectedMoveableEntity->GetWayPoints().size() > 0)
				{
					Tile* tile = m_grid.GetTile(m_selectedMoveableEntity->GetWayPoints().back());
					m_grid.SetMapPassable(tile->GetWorldPosition(), true);

					tile->Passable(true);
				}
				
			}

			std::vector<Vec2f> pts;
			Vec2f mp = Vec2f((float)mouse.GetPosX(), (float)mouse.GetPosY());
			mp = m_cam.ConvertToWorldSpace(mp);
			Vec2i s = m_grid.GetCellIndex(m_selectedMoveableEntity->GetCenter());
			Vec2i e = m_grid.GetCellIndex(mp);

			if (m_grid.FindPath(s, e, pts))
			{
				// set last tile in list to impassable
				// so can't select there with another obj
				Tile* tile = m_grid.GetTile(pts.back());
				tile->Passable(false);
				

				m_selectedMoveableEntity->SetWaypoints(pts);
			}
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

void UnitManager::Update(const float & dt, Mouse::Event& mouse, Keyboard::Event& kbd)
{
	HandleInput(mouse,kbd);
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
				
				Tile* tile = m_grid.GetTile(obj->GetCenter());
				
					// if a new tile
					if (obj->p_currentTile != tile)
					{
						// set old tile to passable
						if (obj->p_currentTile)
							m_grid.SetMapPassable(obj->p_currentTile->GetWorldPosition(), true);
						// new tile to impassable
						if (tile->Passable())
						{
							m_grid.SetMapPassable(tile->GetWorldPosition(), false);
							// set obj's new tile
							obj->p_currentTile = tile;
						}
				}
				obj->Update(dt);
				obj->TransformToCamera(m_cam.GetPos());
				if (!obj->PathFinished())
					m_grid.SetVisibility(obj->GetCenter());
				else
				{
					m_grid.SetMapPassable(obj->GetCenter(), true);
					
				}

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
		Tile* tile = m_grid.GetTile(m_selectedMoveableEntity->GetCenter());
		float w = rect.right - rect.left;
		float h = rect.bottom - rect.top;
		h = h * 0.5f;// half it
		w = w * 0.5f;
		D2D1_POINT_2F center = { rect.left + w,rect.top + h };
		gfx.DrawRectangle(D2D1::Matrix3x2F::Rotation(m_selectedUnitRectAngle, center), rect.ToD2D(), D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f));
		gfx.DrawRectangle(D2D1::Matrix3x2F::Identity(),tile->GetRect().ToD2D(), D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f));

	}
}
