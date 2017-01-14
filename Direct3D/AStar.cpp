#include "AStar.h"
#include "Sprite.h"
void AStar::swap(int idx1, int idx2)
{
	pAStarNode tmp = openTable[idx1];
	openTable[idx1] = openTable[idx2];
	openTable[idx2] = tmp;
}


std::vector<Vec2i> AStar::getPossiblePlacements(Vec2i pos, int group_size)
{
	int offset = group_size / 2;
	if (group_size > 1 && offset == 0)
		offset = 1;
	int py = (int)(pos.x);
	int px = (int)(pos.y);

	std::vector<Vec2i>positions;
	// loop through a block of the grid. offset on either side / top / bottom
	// add non barrier cells to open list
	for (int y = py - offset; y <= py + offset; y++)
	{
		if (y < 0 || y >= ROW_SIZE)
			continue;
		for (int x = px - offset; x <= px + offset; x++)
		{
			if (x < 0 || x >= COL_SIZE)
				continue;
			if (maze(x, y).s_style != 0)
			{
				positions.push_back(Vec2i(maze(x, y).s_y, maze(x, y).s_x));
			}
		}

	}
	return positions;
}
void AStar::adjust_heap(int nIndex)
{
	int curr = nIndex;
	int child = curr * 2 + 1;
	int parent = (curr - 1) / 2;

	if (nIndex < 0 || nIndex >= open_node_count)
	{
		return;
	}
	while (child < open_node_count)
	{
		if (child + 1 < open_node_count && openTable[child]->s_g + openTable[child]->s_h > openTable[child + 1]->s_g + openTable[child + 1]->s_h)
		{
			++child;
		}

		if (openTable[curr]->s_g + openTable[curr]->s_h <= openTable[child]->s_g + openTable[child]->s_h)
		{
			break;
		}
		else
		{
			swap(child, curr);
			curr = child;
			child = curr * 2 + 1;
		}
	}

	if (curr != nIndex)
	{
		return;
	}

	while (curr != 0)
	{
		if (openTable[curr]->s_g + openTable[curr]->s_h >= openTable[parent]->s_g + openTable[parent]->s_h)
		{
			break;
		}
		else
		{
			swap(curr, parent);
			curr = parent;
			parent = (curr - 1) / 2;
		}
	}
}



void AStar::insert_to_opentable(int x, int y, pAStarNode curr_node, pAStarNode end_node, int w)
{
	int i;

	if (maze(x,y).s_style != 0 ) 
	{
		if (!maze(x, y).s_is_in_closetable)
		{
			if (maze(x, y).s_is_in_opentable)
			{
				if (maze(x, y).s_g > curr_node->s_g + w)
				{
					maze(x, y).s_g = curr_node->s_g + w;
					maze(x, y).s_parent = curr_node;

					for (i = 0; i < open_node_count; ++i)
					{
						if (openTable[i]->s_x == maze(x, y).s_x && openTable[i]->s_y == maze(x, y).s_y)
						{
							break;
						}
					}

					adjust_heap(i);
				}
			}
			else
			{
				maze(x, y).s_g = curr_node->s_g + w;
				maze(x, y).s_h = abs(end_node->s_x - x) + abs(end_node->s_y - y);
				maze(x, y).s_parent = curr_node;
				maze(x, y).s_is_in_opentable = 1;
				openTable[open_node_count++] = &(maze(x, y));
			}
		}
	}
}

void AStar::get_neighbors(pAStarNode curr_node, pAStarNode end_node)
{
	int x = curr_node->s_x;
	int y = curr_node->s_y;

	if ((x + 1) >= 0 && (x + 1) < ROW_SIZE && y >= 0 && y < COL_SIZE)
	{
		insert_to_opentable(x + 1, y, curr_node, end_node, 10);
	}

	if ((x - 1) >= 0 && (x - 1) < ROW_SIZE && y >= 0 && y < COL_SIZE)
	{
		insert_to_opentable(x - 1, y, curr_node, end_node, 10);
	}

	if (x >= 0 && x < ROW_SIZE && (y + 1) >= 0 && (y + 1) < COL_SIZE)
	{
		insert_to_opentable(x, y + 1, curr_node, end_node, 10);
	}

	if (x >= 0 && x < ROW_SIZE && (y - 1) >= 0 && (y - 1) < COL_SIZE)
	{
		insert_to_opentable(x, y - 1, curr_node, end_node, 10);
	}

	if ((x + 1) >= 0 && (x + 1) < ROW_SIZE && (y + 1) >= 0 && (y + 1) < COL_SIZE)
	{
		insert_to_opentable(x + 1, y + 1, curr_node, end_node, 14);
	}

	if ((x + 1) >= 0 && (x + 1) < ROW_SIZE && (y - 1) >= 0 && (y - 1) < COL_SIZE)
	{
		insert_to_opentable(x + 1, y - 1, curr_node, end_node, 14);
	}

	if ((x - 1) >= 0 && (x - 1) < ROW_SIZE && (y + 1) >= 0 && (y + 1) < COL_SIZE)
	{
		insert_to_opentable(x - 1, y + 1, curr_node, end_node, 14);
	}

	if ((x - 1) >= 0 && (x - 1) < ROW_SIZE && (y - 1) >= 0 && (y - 1) < COL_SIZE)
	{
		insert_to_opentable(x - 1, y - 1, curr_node, end_node, 14);
	}
}
void AStar::Reset()
{
	closedTable.clear();
	openTable.clear();
	pathStack.clear();
	open_node_count = close_node_count = 0;
	top = -1;
	pathPositions.resize(0);
	closedTable.resize(ROW_SIZE*COL_SIZE);
	openTable.resize(ROW_SIZE*COL_SIZE);
	pathStack.resize(ROW_SIZE*COL_SIZE);
	for (int i = 0; i < (int)ROW_SIZE - 1; i++)
	{
		for (int j = 0; j < (int)COL_SIZE - 1; j++)
		{
			
			maze(i, j).s_g = 0;
			maze(i, j).s_h = 0;
			maze(i, j).s_is_in_closetable = 0;
			maze(i, j).s_is_in_opentable = 0;
			maze(i, j).s_parent = NULL;
		}
	}
}
void AStar::Init(mapList& map,float cell_size)
{
	cellSize = cell_size;
	closedTable.clear();
	openTable.clear();
	pathStack.clear();
	open_node_count = close_node_count = 0;
	top = -1;
	pathPositions.resize(0);
	ROW_SIZE = (int)map.size();
	COL_SIZE = (int)map[0].size();
	closedTable.resize(ROW_SIZE*COL_SIZE);
	openTable.resize(ROW_SIZE*COL_SIZE);
	pathStack.resize(ROW_SIZE*COL_SIZE);
	maze.resize((int)map.size(), (int)map[0].size());
	for (int i = 0; i < (int)map.size(); i++)
	{
		for (int j = 0; j < (int)map[0].size(); j++)
		{
			maze(i, j).s_g = 0;
			maze(i, j).s_h = 0;
			maze(i, j).s_is_in_closetable = 0;
			maze(i, j).s_is_in_opentable = 0;
			maze(i, j).s_style = map[i][j];
			maze(i, j).s_objSpace = 0;
			maze(i, j).s_x = i;
			maze(i, j).s_y = j;
			maze(i, j).s_parent = nullptr;
		}
	}
}


std::vector<Vec2f> AStar::findPath(Vec2i start, Vec2i end)
{


	start_node = &(maze(start.y,start.x));
	end_node = &(maze(end.y,end.x));

	AStarNode *curr_node = nullptr;
	int       is_found;
	std::vector<Vec2f>tmp;
	tmp.resize(0);
	pathPositions.clear();

	openTable[open_node_count++] = start_node;

	start_node->s_is_in_opentable = 1;
	start_node->s_g = 0;
	start_node->s_h = abs(end_node->s_x - start_node->s_x) + abs(end_node->s_y - start_node->s_y);
	start_node->s_parent = NULL;

	if (start_node->s_x == end_node->s_x && start_node->s_y == end_node->s_y)
	{

		return tmp;
	}

	is_found = 0;

	while (1)
	{

		curr_node = openTable[0];
		openTable[0] = openTable[--open_node_count];
		adjust_heap(0);

		closedTable[close_node_count++] = curr_node;
		curr_node->s_is_in_closetable = 1;

		if (curr_node->s_x == end_node->s_x && curr_node->s_y == end_node->s_y)
		{
			is_found = 1;
			break;
		}

		get_neighbors(curr_node, end_node);

		if (open_node_count == 0)
		{
			is_found = 0;
			break;
		}
	}

	if (is_found == 1)
	{
		curr_node = end_node;

		while (curr_node)
		{
			pathStack[++top] = curr_node;
			if (curr_node)
			{
				float X = ((float)curr_node->s_x * cellSize) +(cellSize * 0.5f);
				float Y = ((float)curr_node->s_y * cellSize) +(cellSize * 0.5f);
				Vec2f p(Y, X);
				pathPositions.push_back(p);
			}
			curr_node = curr_node->s_parent;

		}
		if (pathPositions.size() > 0)
		{

			for (int i = (int)(pathPositions.size() - 1); i >= 0; i--)
			{
				tmp.push_back(pathPositions[i]);
			}

		}
	}

	return tmp;

}
