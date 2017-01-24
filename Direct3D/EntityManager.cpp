#include "EntityManager.h"
#include "MoveableObject.h"
#include "Locator.h"
#include "Rect.h"
#include "Graphics.h"
#include <algorithm>
#include <cmath>

void UnitManager::HandleInput( Mouse::Event& mouse)
{
	if (mouse.GetType() == Mouse::Event::LPress)
	{
		m_selectedMoveableEntity = nullptr;
		Vec2f mousePt = Vec2i(mouse.GetPosX(), mouse.GetPosY()) + m_cam.GetPos();
		for (size_t index = 0;index <  m_playerEntites.size();index++)
		{
		
			if (m_playerEntites[index]->GetRect().Contains(mousePt))
			{
				switch (m_playerEntites[index]->Type())
				{
				case radar:
				case fighter:
				case turret:
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
			Vec2f mp = Vec2f((float)mouse.GetPosX(), (float)mouse.GetPosY());
			mp = m_cam.ConvertToWorldSpace(mp);
			m_selectedMoveableEntity->SetWayPoints(mp);
		
		}
	
			
		
	}
	
}
UnitManager::UnitManager(InputManager& input, WorldGrid& world, Camera & cam, std::wstring imageFile)

	:m_cam(cam),
	m_grid(world),
	m_input(input)
{
	m_images = std::make_unique<SpriteSheet>(imageFile, 64.0f, 64.0f);
	assert(m_images);
	LifeRect::StatusRect::StatusRectDesc desc;
	desc.drawRect = { 0.0f,0.0f,48.0f,48.0f };
	desc.color = { 1.0f,1.0f,1.0f,1.0f };
	desc.alphaBlend = 1.0f;
	m_life.emplace_back(desc, 100.0f,8.0f);
}

MoveableObject* UnitManager::AddPlayerUnit(_EntityType type, Vec2i pos)
{
	Animation::RenderDesc rDesc;
	
	rDesc.drawRect.left = pos.x * 64.0f;
	rDesc.drawRect.top = pos.y * 64.0f;
	rDesc.drawRect.right = rDesc.drawRect.left + 48.0f;
	rDesc.drawRect.bottom = rDesc.drawRect.top + 48.0f;
	std::vector<int> indices;
	indices.clear();
	switch (type)
	{
	case drone:
		
		
		indices.push_back(0);
		m_playerEntites.push_back(std::make_unique<MoveableObject>(m_grid,rDesc, indices,0.25f,"player_units", speeds[3], drone));
		
		break;
	case fighter:
		indices.push_back(1);
		m_playerEntites.push_back(std::make_unique<MoveableObject>(m_grid, rDesc, indices, 0.25f, "player_units", speeds[2] , fighter));
		break;
	case artillary:
		indices.push_back(2);
		m_playerEntites.push_back(std::make_unique<MoveableObject>(m_grid, rDesc, indices, 0.25f, "player_units", speeds[1], artillary));
		break;
	case radar:
		indices.push_back(3);
		m_playerEntites.push_back(std::make_unique<MoveableObject>(m_grid, rDesc, indices, 0.25f, "player_units", speeds[0], radar));
		break;
	case turret:
		indices.push_back(4);
		m_playerEntites.push_back(std::make_unique<MoveableObject>(m_grid, rDesc, indices, 0.25f, "player_units", speeds[0], turret));
		break;
	case tech:
		indices.push_back(5);
		m_playerEntites.push_back(std::make_unique<MoveableObject>(m_grid, rDesc, indices, 0.25f, "player_units", 0.0f, tech));
		break;
	case _EntityType::data:
		indices.push_back(6);
		m_playerEntites.push_back(std::make_unique<MoveableObject>(m_grid, rDesc, indices, 0.25f, "player_units", 0.0f, _EntityType::data));
		break;
		default:
			return nullptr;
			break;
	}
	return m_playerEntites.back().get();
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
	case turret:
		break;
	}
}

void UnitManager::SelectUnit(Vec2f world)
{

}

void UnitManager::Update(const float & dt, Mouse::Event& mouse)
{
	static float health = 0.5f;
	m_life[0].UpdateHealth(health);
	health += 0.15f;
	HandleInput(mouse);
	
	for (size_t index = 0; index < m_playerEntites.size(); index++)
	{
		switch (m_playerEntites[index]->Type())
		{
		case radar:
		case fighter:
		case turret:
		case artillary:
		case drone:
		{
			MoveableObject* obj = (MoveableObject*)m_playerEntites[index].get();
			
			obj->Update(dt);
			m_grid.SetVisibility(obj->GetPosition());
			

		  
		}
		break;
		}
	}
}

void UnitManager::Draw(Graphics & gfx)
{
	for (auto& it : m_playerEntites)
	{
		it->Draw(m_cam);
	}
	//if (m_selectedMoveableEntity)
	//{
	//	m_selectedUnitRectAngle += 1.1f;
	//	if (m_selectedUnitRectAngle > 360.0f)m_selectedUnitRectAngle = 0.0f;
	//	RectF rect = m_selectedMoveableEntity->GetRect();
	//	Tile* tile = m_grid.GetTile(m_selectedMoveableEntity->GetPosition());
	//	float w = rect.right - rect.left;
	//	float h = rect.bottom - rect.top;
	//	h = h * 0.5f;// half it
	//	w = w * 0.5f;
	//	D2D1_POINT_2F center = { rect.left + w,rect.top + h };
	//	gfx.DrawRectangle(D2D1::Matrix3x2F::Rotation(m_selectedUnitRectAngle, center), rect.ToD2D(), D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f));
	//	gfx.DrawRectangle(D2D1::Matrix3x2F::Identity(),tile->GetRect().ToD2D(), D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f));

	//}
	if (m_selectedMoveableEntity)
	{
		m_life[0].SetPosition(Vec2f(m_selectedMoveableEntity->GetRect().left,
			m_selectedMoveableEntity->GetRect().top));
	}
	m_cam.Rasterize(m_life[0].GetDrawable());
}
