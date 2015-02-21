#ifndef TSPSOLVER_H
#define TSPSOLVER_H

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <boost/lexical_cast.hpp>

#include "edge.h"
#include "vertex.h"
#include "network.h"

#define DEBUG true

using namespace std::chrono;

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
	std::vector<std::vector<Vertex>> v;
	Path u;

public:
	TSPSolver(NetworkGraph network, int start_node);

	float CalculatePathCosts(Path s);
	void SetStartNode(int start_node);
	//void SetPartialProblem(Path path);
	Path GetUnvisitedNodes(Path s);
	static bool SortByMinPath(const Vertex a, const Vertex b);
	void Solve(int max_steps);
};

#endif