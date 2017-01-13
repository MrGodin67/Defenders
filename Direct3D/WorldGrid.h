#pragma once

#include "AStar.h"
#include "Tile.h"
#include "Table.h"
#include "SpriteSheet.h"
#include "Camera.h"

class WorldGrid
{
	Table<Tile> m_cells;
	std::vector<Tile*> m_basePlacementTiles;
	float m_width, m_height;
	int m_rows, m_columns,m_cellWidth,m_cellHeight;
	std::unique_ptr<SpriteSheet> sprite;
	Camera& m_cam;
	AStar pathFinding;
private:
	void Create(std::vector<std::string>& map);
public:
	WorldGrid(Camera& cam);
	~WorldGrid();
	void LoadMap(const std::string& mapfile,const std::wstring& textureFile);
	void Draw(class Graphics& gfx,RectF& viewport);
	float Width() { return m_width; }
	float Height() { return m_height; }
	bool FindPath(Vec2i& startPt, Vec2i& endPt, std::vector<Vec2f>& newPath);
	Vec2i GetCellIndex(Vec2f& worldPoint);
	void SetBasePlacementTiles(const Vec2i& mousePos);
	bool SetBase( Vec2i pos,Tile& start_tile);
};
