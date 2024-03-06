#pragma once
#include "Edge.h"

class Graph
{
private:
	int** adj_mat;
	int	vert_number;
	int edge_number;
	int maxWeight;

	int *source_vert;
	int *path_weight;

	int *adj_vert;

public:
	Graph(int v);
	~Graph();

	void InsertEdge(Edge e);
	void RemoveEdge(Edge e);

	void WriteADJ();
	void WriteMinCostPath();

	void Dijkstra(int s);
	void SortVert(int v);
	void RemoveVert(int v);
	bool IsAdjVert(int v);

	int PrevVert(int v);
	int PathWeight(int v);
};

