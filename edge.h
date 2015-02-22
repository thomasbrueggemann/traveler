#ifndef EDGE_H
#define EDGE_H

#include <iostream>
#include <string>
#include <memory>

#include "vertex.h"

class Vertex;
typedef std::vector<Vertex> NetworkGraph;

class Edge
{
private:
	int source;
	int destination;
	float weight;
	
public:
	Edge();
	Edge(float weight);
	void CreateConnection(Vertex& source, Vertex& destination);
	float GetWeight();
	Vertex GetSource(NetworkGraph& graph);
	Vertex GetDestination(NetworkGraph& graph);
};

#endif