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

	struct sortstruct
	{
		// sortstruct needs to know its containing object
		TSPSolver* m;
		sortstruct(TSPSolver* p) : m(p) {};
 
		// this is our sort function, which makes use
		// of some non-static data (sortascending)
		bool operator() (Vertex a, Vertex &b)
		{
			Edge *eA = a.FindEdgeTo(m->currentNode);
			Edge *eB = b.FindEdgeTo(m->currentNode);

			return (eA->GetWeight() < eB->GetWeight());
		}
	};

public:
	TSPSolver(NetworkGraph network, int start_node);

	float CalculatePathCosts(Path s);
	void SetStartNode(int start_node);
	//void SetPartialProblem(Path path);
	Path GetUnvisitedNodes(Path s);
	void Solve(int max_steps);
	Path GetBestPath();
};

#endif