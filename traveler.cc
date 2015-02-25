//
// traveler.cc
// routing
//
// Created by tomaszbrue on 21/02/15.
// Copyright (c) 2015 Thomas Brüggemann. All rights reserved.
//
#include <iostream>
#include <vector>

#include "tsp.h"
#include "json.h"

#define EXIT_SUCCESS 0

using namespace std;
using json = nlohmann::json;

int main(int argc, const char *argv[])
{
	cout << "TRAVELER v1.0" << endl;
	cout << "=============" << endl;

	// TEST NETWORK
	// https://router.project-osrm.org/table?loc=50.858003798201786,7.089035511016845&loc=50.855877178964974,7.087082862854003&loc=50.85498315721184,7.091696262359619&loc=50.85155591505696,7.088091373443603&z=16
	// {"distance_table":[[0,329,477,861],[330,0,437,563],[478,437,0,665],[862,563,665,0]]}
	json table = json::parse("[[0,329,477,861],[330,0,437,563],[478,437,0,665],[862,563,665,0]]");
	DistanceTable table;

	for(int i = 0; i < table.size(); i++)
	{
		
	}

	/*table.push_back(0); table.push_back(329); table.push_back(477); table.push_back(861);
	table.push_back(330); table.push_back(0); table.push_back(437); table.push_back(563);
	table.push_back(478); table.push_back(437); table.push_back(0); table.push_back(665);
	table.push_back(862); table.push_back(563); table.push_back(665); table.push_back(0);*/

	TSP tsp(table);
	tsp.Anneal();



	return EXIT_SUCCESS;
}