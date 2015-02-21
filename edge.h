#ifndef EDGE_H
#define EDGE_H

#include <iostream>
#include <string>

#include "vertex.h"

class Edge
{
private:
	Vertex between[2];
	float weight;
public:
	Edge(float weight);
	void CreateConnection(Vertex source, Vertex destination);
	float GetWeight();
	Vertex GetSource();
	Vertex GetDestination();
};

#endif