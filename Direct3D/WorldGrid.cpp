#include "WorldGrid.h"
#include <fstream>
#include <Windows.h>
#include <string>
#include "Utils.h"
#include "Graphics.h"

WorldGrid::WorldGrid(Camera& cam)
	:m_cam(cam)
{
}

WorldGrid::~WorldGrid()
{
	
}
void WorldGrid::Create(std::vector<std::string>& map)
{
	mapList map_list;
	for (int r = 0; r < (int)map.size(); r++)
	{
		std::string str = map[r];
		nodeList list;
		for (int c = 0; c < (int)str.size(); c++)
		{
			Vec2f p((float)(c * this->m_cellWidth), (float)(r * this->m_cellHeight));
			switch (str[c])
			{
			case ' ':
				m_cells(r, c) = Tile(sprite.get(), 0, p, true);
				break;
			case '(':
				m_cells(r, c) = Tile(sprite.get(), 6, p, false);
				break;
			case ')':
				m_cells(r, c) = Tile(sprite.get(), 7, p, false);
				break;
			case '<':
				m_cells(r, c) = Tile(sprite.get(), 5, p, false);
				break;
			case '>':
				m_cells(r, c) = Tile(sprite.get(), 4, p, false);
				break;
			case '|':
				m_cells(r, c) = Tile(sprite.get(), 2, p, false);
				break;
			case '-':
				m_cells(r, c) = Tile(sprite.get(), 3, p, false);
				break;
			case '+':
				m_cells(r, c) = Tile(sprite.get(), 1, p, false);
				break;
			case 'T':
				m_cells(r, c) = Tile(sprite.get(), 9, p, false);
				break;
			case 'R':
				m_cells(r, c) = Tile(sprite.get(), 8, p, false);
				break;
			case 'W':
				m_cells(r, c) = Tile(sprite.get(), 10, p, false);
				break;
			case 'S':
				m_cells(r, c) = Tile(sprite.get(), 11, p,true);
				break;
			}
			
			m_cells(r, c).Passable() ? list.push_back(1) : list.push_back(0);

		}
		map_list.push_back(list);
	}
	pathFinding.Init(map_list, (float)m_cellWidth);
}
void WorldGrid::LoadMap(const std::string& mapfile, const std::wstring& textureFile)
{
	std::fstream txtfile(mapfile.c_str());
	sprite = std::make_unique<SpriteSheet>(textureFile, 64.0f, 64.0f);
	assert(sprite);
	assert(txtfile.good());
	std::vector<std::string> mapText;
	if (txtfile.good())
	{
		std::string str;
		while (std::getline(txtfile, str))
		{
			mapText.push_back(str);
		}
		txtfile.close();
	}
	std::string line = mapText[0];
	std::vector<std::string>tokens;
	Utils::Tokenize(&tokens, line, " ");
	m_width = (float)atof(tokens[0].c_str());
	m_height = (float)atof(tokens[1].c_str());
	m_rows = atoi(tokens[2].c_str());
	m_columns = atoi(tokens[3].c_str());
	m_cellWidth = atoi(tokens[4].c_str());
	m_cellHeight = atoi(tokens[5].c_str());
	Tile::SetWidthHeight((float)m_cellWidth, (float)m_cellHeight);
	m_cells.resize(m_rows, m_columns);
	mapText.erase(mapText.begin());
	
	Create(mapText);
}

void WorldGrid::Draw(Graphics & gfx, RectF& viewport)
{
	int startX = (int)viewport.left / m_cellWidth;
	int startY = (int)viewport.top / m_cellHeight;
	int endX = (int)viewport.right / m_cellWidth;
	int endY = (int)viewport.bottom / m_cellHeight;
	if (startX < 0)startX = 0;
	if (startY < 0)startX = 0;
	endX += 1;
	if (endX  > m_cells.numCols())endX = m_cells.numCols() ;
	endY += 1;
	if (endY > m_cells.numRows())endY = m_cells.numRows() ;
	for (int r = startY; r < endY; r++)
	{
		for (int c = startX; c < endX; c++)
		{
			m_cells(r, c).draw(gfx,m_cam);

		}
	}
}

bool WorldGrid::FindPath(Vec2f& startPt,Vec2f& endPt,std::vector<Vec2f>& newPath)
{
	pathFinding.Reset();
	if (m_cells((int)endPt.y, (int)endPt.x).Passable())
		newPath = pathFinding.findPath(startPt, endPt);
	else
		return false;
	
	return true;
}

Vec2f WorldGrid::GetCellIndex(Vec2f& worldPoint)
{
	return Vec2f(worldPoint.x / (float)m_cellWidth, worldPoint.y / (float)m_cellHeight);
}
