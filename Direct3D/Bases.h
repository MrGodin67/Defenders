#pragma once
#include "Sprite2.h"
#include "SpriteSheet.h"
#include "Locator.h"

class Base :public Sprite
{
	
	bool m_active = false;
	bool m_buildingUnit = false;
	bool m_buildingComplete = false;
	bool m_underConstruction = false;
	_EntityType m_unitTypes[4];
	_EntityType  m_currentBuildType = none;
	int m_imageIndex;
	int m_numUnitTypes = 0;
	int m_cost = 600;
	float m_build_Timer = 0.0f;
	float m_buildTime = 0.0f;
	float m_constuction_Timer = 0.0f;
	float m_constuctionTime = 0.0f;
	float m_width;
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
public:
	Base() {}
	Base(Animation::RenderDesc& desc, std::vector<int> indices, float interval,
		std::string imageName, _EntityType type, float constructionTime);

	void SetPosition(Vec2f pos,float w,float h);
	void SetBuildTypes(_EntityType a, _EntityType b, _EntityType c, _EntityType d, int numTypes);
	_EntityType* UnitTypes();
	void Update(const float& dt);
	void Draw(class Graphics& gfx, class Camera&);
	void Draw(class Graphics& gfx);
	int NumUinitTypes() { return m_numUnitTypes; }
	std::wstring GetText();
	bool Active() { return m_active; }
	bool BuildingUnit() { return m_buildingUnit; }
	bool BuildingCompleted() { return m_buildingComplete; }
	bool UnderConstruction() { return m_underConstruction; }
	void BuildUnit(_EntityType type)
	{
		m_UnitsUnderConstruction.emplace_back(type, 30.0f);
	}
	_EntityType UpdateBuild(float& dt)
	{
		for (size_t i=0;i < m_UnitsUnderConstruction.size();i++)
		{
			if (m_UnitsUnderConstruction[i].Update(dt))
			{
				_EntityType result = m_UnitsUnderConstruction[i].type;
				m_UnitsUnderConstruction.erase(m_UnitsUnderConstruction.begin() + i);
				m_buildingUnit = m_UnitsUnderConstruction.size() > 0;
				return result;
			}
		}
		m_buildingUnit = m_UnitsUnderConstruction.size() > 0;
		return _EntityType::none;
	}
	size_t NumbUnitsUnderConstruction() { return m_UnitsUnderConstruction.size(); }
	int ImageIndex() { return m_seqIndices[0]; }
};