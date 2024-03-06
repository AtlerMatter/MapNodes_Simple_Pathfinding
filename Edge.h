#pragma once

class Edge {
private:
	int v;
	int w;
	int weight;

public:
	Edge();
	Edge (int vi, int vf, int wei);

	int Begin();
	int End();
	int Weight();
};

