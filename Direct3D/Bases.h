#pragma once
#include "Sprite2.h"
#include "SpriteSheet.h"
#include "Locator.h"
#include "Tile.h"
#include "StatusRect.h"

enum _BaseTypes
{
	baseCommand,
	baseFactory,
	baseTechnology,
	baseRepair,
	baseNumBases,
	baseInvalid
};
class Base :public Sprite
{
protected:
	_BaseTypes m_type;
	LifeRect m_status;
	bool m_selected = false;
	bool m_building = false;
	float m_buildIndex = 0.0f;
	class BuildingTypes
	{
	public:
		bool building = false;
		_EntityType type;
		float timer = 0.0f;
		float buildTime = 0.0f;
		BuildingTypes() {}
		BuildingTypes(_EntityType t, float buildTime)
			:type(t), buildTime(buildTime),timer(0.0f),building(true)
		{}
		bool Update(float& dt)
		{
			if ((timer += dt) > buildTime)
				building = false;

			return !building;
		}
	};
	std::vector<BuildingTypes> m_UnitsUnderConstruction;
	std::vector<_EntityType> m_Completedbuilds;
	std::vector<Tile*> m_buildingExitPoints;
	BuildingTypes m_buildClock;
	void UpdateMainBuild(float dt);
public:
	Base() {}
	Base(Animation::RenderDesc& desc, std::vector<int> indices, float interval,
		std::string imageName,float constructionTime, _BaseTypes type, std::vector<Tile*>& buildingExitPoints);
	_BaseTypes Type() { return m_type; }
	bool Active() { return !m_building; }
	bool UnitsReady() { return m_Completedbuilds.size() > 0; }
	int ActiveBuilds() { return (int)m_UnitsUnderConstruction.size(); }
	virtual void SetSelected(bool val) { m_selected = val; }
	virtual void Draw(class Camera& cam)override;
	virtual std::wstring GetText() { return std::wstring(); };
	virtual void ConstructNewUnit(_EntityType type, float buildTime);
	virtual bool UpdateBuilds(const float& dt);
	virtual std::vector<_EntityType> CompletedBuilds();
	virtual Vec2f GetNextAvaliableExitPosition();
};