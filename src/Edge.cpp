#include "Edge.h"

Edge::Edge()
{
	v = 0;
	w = 0;
	weight = 0;
}

Edge::Edge(int vi, int vf, int wei)
{ 
	v = vi; 
	w = vf; 
	weight = wei; 
}

int Edge::Begin()
{
	return v;
}

int Edge::End()
{
	return w;
}

int Edge::Weight()
{
	return weight;
}
