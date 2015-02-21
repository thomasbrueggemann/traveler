#ifndef EDGE_H
#define EDGE_H

#include <iostream>
#include <string>
#include <memory>

#include "vertex.h"

class Vertex;
class Edge
{
private:
	Vertex *source;
	Vertex *destination;
	float weight;
public:
	Edge();
	Edge(float weight);
	void CreateConnection(const Vertex &source, const Vertex &destination);
	float GetWeight();
	Vertex GetSource();
	Vertex GetDestination();
};

#endif