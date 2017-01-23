#pragma once
#include "EntityInterface.h"
#include "Camera.h"
#include "SpriteSheet.h"
#include "WorldGrid.h"
#include "InputManager.h"
#include "includes.h"
#include "MoveableObject.h"
#include "StatusRect.h"
class UnitManager
{
	Camera& m_cam;
	WorldGrid& m_grid;
	InputManager& m_input;
	std::unique_ptr<SpriteSheet> m_images;
	std::vector<std::unique_ptr<MoveableObject>> m_playerEntites;
	std::vector<std::unique_ptr<MoveableObject>> m_enemyEntites;
	MoveableObject* m_selectedMoveableEntity = nullptr;
	float speeds[4] = { 40.0f,60.0f,80.0f,100.0f };
	float m_selectedUnitRectAngle = 0.0f;
	std::vector<LifeRect> m_life;
	void HandleInput( Mouse::Event& mouse);
public:
	UnitManager(InputManager& input,WorldGrid& world,Camera& cam, std::wstring imageFile);
	~UnitManager() {}
	void AddPlayerUnit(_EntityType type, Vec2i pos);
	void AddEnemyUnit(_EntityType type, Vec2i pos);
	void SelectUnit(Vec2f world);
	void Update(const float& dt,Mouse::Event& mouse);
	void Draw(class Graphics& gfx);

};