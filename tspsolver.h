#ifndef TSPSOLVER_H
#define TSPSOLVER_H

#include <iostream>
#include <string>
#include <vector>

#include "edge.h"
#include "vertex.h"
#include "network.h"

#define DEBUG false

typedef std::vector<Vertex> Path;

class TSPSolver
{
private:
	Path best_path;
	float best_cost; 
	
	NetworkGraph network;
	int start_node;

	bool cutting; // defines wether we want the best-cost cutting or not
	bool min_heuristic; // defines wether we want to use the min-heuristik or not

	Vertex currentNode; // represents the node where we are at right now
	Path s;
	Path v;
	Path u;

	float CalculatePathCosts();

public:
	TSPSolver(NetworkGraph network, int start_node);
};

#endif