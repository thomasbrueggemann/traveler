#include "tspsolver.h"

// CONSTRUCTOR
TSPSolver::TSPSolver(NetworkGraph network, int start_node)
{
	this->network = network;

	this->best_cost = INFINITY;
	this->cutting = true;
	this->min_heuristic = true;

	this->currentNode = this->network[start_node];
}

// CALCULATE PATH COSTS
float TSPSolver::CalculatePathCosts()
{
	return 0.0;
}