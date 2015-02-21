#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <string>
#include <vector>

#include "edge.h"
#include "vertex.h"

typedef std::vector<float> Graph;
typedef std::vector<Vertex> NetworkGraph;

class Network
{
private:

public:
	Network();
	NetworkGraph FromGraph(Graph graph);
};

#endif