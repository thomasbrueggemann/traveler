//
// traveler.cc
// routing
//
// Created by tomaszbrue on 21/02/15.
// Copyright (c) 2015 Thomas Brüggemann. All rights reserved.
//
#include <iostream>
#include <vector>
#include <boost/lexical_cast.hpp>

#include "edge.h"
#include "vertex.h"
#include "network.h"
#include "tspsolver.h"

#define EXIT_SUCCESS 0

using namespace std;

int main(int argc, const char *argv[])
{
	cout << "TRAVELER v1.0" << endl;
	cout << "=============" << endl;

	// TEST NETWORK
	// https://router.project-osrm.org/table?loc=50.858003798201786,7.089035511016845&loc=50.855877178964974,7.087082862854003&loc=50.85498315721184,7.091696262359619&loc=50.85155591505696,7.088091373443603&z=16
	// {"distance_table":[[0,329,477,861],[330,0,437,563],[478,437,0,665],[862,563,665,0]]}
	Graph graph;
	graph.push_back(INFINITY); graph.push_back(329); graph.push_back(477); graph.push_back(861);
	graph.push_back(330); graph.push_back(INFINITY); graph.push_back(437); graph.push_back(563);
	graph.push_back(478); graph.push_back(437); graph.push_back(INFINITY); graph.push_back(665);
	graph.push_back(862); graph.push_back(563); graph.push_back(665); graph.push_back(INFINITY);

	Network net;
	NetworkGraph net_graph = net.FromGraph(graph);

	for(Vertex &v : net_graph)
	{
		v.Print();

		for(Edge &e : v.GetEdges())
		{
			e.Print();
		}
	}

	cout << "===========" << endl;

	Vertex vFirst = net_graph[0];
	cout << vFirst.GetName() << endl;
	cout << "net_graph size: ";
	cout << net_graph.size() << endl;

	TSPSolver tsp(net_graph, 0);
	tsp.Solve(net_graph.size());

	for(Vertex &node : tsp.GetBestPath())
	{
		cout << node.GetName() << endl;
	}

	return EXIT_SUCCESS;
}