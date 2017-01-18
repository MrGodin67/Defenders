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
	m_visibleMaxLenSq = ((float)Tile::Width() * 7.0f) * ((float)Tile::Width() * 7.0f);
	m_cells.resize(m_rows, m_columns);
	mapText.erase(mapText.begin());
	
	Create(mapText);
}

void WorldGrid::Draw(Graphics & gfx, RectF& viewport,Base* selectedBase )
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
	if (m_basePlacementTiles.size() <= 0)
		return;
	D2D1_COLOR_F color;
	m_basePlacementTiles.size() == 4 ? color = { 0.0f,1.0f,0.0f,0.25f } : color = { 1.0f,0.0f,0.0f,0.25f };
	if (selectedBase)
	{
		RectF rect = m_basePlacementTiles[0]->GetRect();
		rect.right = rect.left + 128.0f;
		rect.bottom = rect.top + 128.0f;
		gfx.DrawSprite(D2D1::Matrix3x2F::Identity(),
			rect.ToD2D(),
			Locator::ImageManager->GetImage("bases")->GetTexture(),
			&Locator::ImageManager->GetImage("bases")->GetClippedImage(selectedBase->ImageIndex()).ToD2D());
	}
	for (int d = 0; d < m_basePlacementTiles.size(); d++)
	{
		gfx.DrawFilledScreenRectangle(m_basePlacementTiles[d]->GetRect().ToD2D(), color);
	}
	

}

bool WorldGrid::FindPath(Vec2i& startPt,Vec2i& endPt,std::vector<Vec2f>& newPath)
{
	pathFinding.Reset();
	startPt.x /= m_cellWidth;
	startPt.y /= m_cellHeight;
	endPt.x /= m_cellWidth;
	endPt.y /= m_cellHeight;
	if (m_cells(endPt.y, endPt.x).Passable())
		newPath = pathFinding.findPath(startPt, endPt);
	else
		return false;
	
	if (newPath.size() <= 1)
		return false;

	return true;
}

Vec2i WorldGrid::GetCellIndex(Vec2f& worldPoint)
{
	return Vec2i((int)(worldPoint.x / (float)m_cellWidth), (int)(worldPoint.y / (float)m_cellHeight));
}

void WorldGrid::SetBasePlacementTiles(const Vec2i & mousePos)
{
	Vec2f mp = Vec2f(mousePos);
	mp +=  m_cam.GetPos();
	if (m_cam.PointInViewFrame(mp, Vec2f(0.0f, 0.0f)))
	{

		int row = mp.y / m_cellHeight;
		int col = mp.x / m_cellWidth;
		m_basePlacementTiles.clear();
		for (int r = row; r < row + 2; r++)
		{
			for (int c = col; c < col + 2; c++)
			{
				if (m_cells(r, c).Passable())
				{
					m_basePlacementTiles.push_back(&m_cells(r, c));
					
				}
			}
		}
	}
}

void WorldGrid::FlushPlacementTiles()
{
	m_basePlacementTiles.clear();
}

bool WorldGrid::SetBase(Vec2i pos, Tile& start_tile)
{
	if (m_basePlacementTiles.size() != 4)
		return false;
	int row = pos.y / m_cellHeight;
	int col = pos.x / m_cellWidth;
	start_tile = m_cells(row, col);
	m_basePlacementTiles.clear();
	for (int r = row; r < row + 2; r++)
	{
		for (int c = col; c < col + 2; c++)
		{
			m_cells(r, c).Passable(false);
			pathFinding.getNode(Vec2i(c, r))->s_style = 0;
		}
	}
	return true;
}

void WorldGrid::SetVisibility(Vec2i pos)
{
	int row = pos.y / m_cellHeight;
	int col = pos.x / m_cellWidth;
	int r1, c1;
	for (int r = 0; r < m_visibliltyArray.size(); r++)
	{
		r1 = row + m_visibliltyArray[r];
		if (r1 < 0)r1 = 0;
		if (r1 >= m_rows)r1 = m_rows -1;
		for (int c = 0; c < m_visibliltyArray.size(); c++)
		{
			c1 = col + m_visibliltyArray[c];
			if (c1 < 0)c1 = 0;
			if (c1 >= m_columns)c1 = m_columns -1;
			if (m_cells(r1, c1).GetVisibleColorAplha() != 0.0f)
			{
				float lenSq = (m_cells(r1, c1).GetWorldPosition() - pos).LenSq();
				float alpha = lenSq / m_visibleMaxLenSq;
				if (alpha < 0.1f)alpha = 0.0f;
				if (alpha > 1.0f)alpha = 1.0f;
				m_cells(r1, c1).SetVisibleColorAlpha(alpha);
			}
		}
	}
}

Tile * WorldGrid::GetTile(Vec2f pos)
{
	int row = (int)pos.y / m_cellHeight;
	int col = (int)pos.x / m_cellWidth;
	return &m_cells(row, col);
}

void WorldGrid::SetMapPassable(Vec2f pos, bool passable)
{
	int row = (int)pos.y / m_cellHeight;
	int col = (int)pos.x / m_cellWidth;
	int pass;
	m_cells(row, col).Passable(passable);
	passable ? pass = 1 : pass = 0;
	pathFinding.getNode(Vec2i(col, row))->s_style = pass;
}
