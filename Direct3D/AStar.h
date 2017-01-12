#pragma once
#include "includes.h"
#include <stdio.h>  
#include <stdlib.h>  
#include "Vec2.h"
#include "Table.h"



typedef struct _AStarNode
{
	int s_x;
	int s_y;
	int s_g;
	int s_h;
	int s_style;
	int s_objSpace = 0;
	struct _AStarNode * s_parent = nullptr;
	int s_is_in_closetable;
	int s_is_in_opentable;
	

}AStarNode, *pAStarNode;
typedef std::vector<int>nodeList;
typedef std::vector<nodeList>mapList;


class AStar
{
public:
	AStar() {};
	
private:
	void swap(int idx1, int idx2);
	void adjust_heap(int nIndex);
	void insert_to_opentable(int x, int y, pAStarNode curr_node, pAStarNode end_node, int w);
	void get_neighbors(pAStarNode curr_node, pAStarNode end_node);
public:
	void Init(mapList& map,float cell_size);
	void Reset();
	std::vector<Vec2f> findPath(Vec2i start, Vec2i end);
	std::vector<Vec2i> getPossiblePlacements(Vec2i pos, int group_size);
	pAStarNode getMapNode(int x, int y) { return &maze(y,x); }
	pAStarNode getNode(Vec2i pos) { return &maze(pos.y,pos.x); }
	
private:
	Table<AStarNode> maze;
	
	std::vector<pAStarNode> openTable;
	std::vector<pAStarNode> closedTable;
	int   open_node_count;
	int    close_node_count;
	std::vector<pAStarNode> pathStack;
	int        top = -1;
	pAStarNode start_node;
	pAStarNode end_node;
	std::vector<Vec2f> pathPositions;
	float cellSize;
	int COL_SIZE, ROW_SIZE;
};