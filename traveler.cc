//
// traveler.cc
// routing
//
// Created by tomaszbrue on 21/02/15.
// Copyright (c) 2015 Thomas Brüggemann. All rights reserved.
//
#include <iostream>
#include <string>
#include <fstream>
#include <utility>
#include <vector>

#include "tsp.h"
#include "json.h"
#include "http.h"

#include "osrmquery.h"

#define EXIT_SUCCESS 0
#define COORDINATE_PRECISION 1000000.0

using namespace std;
using namespace SimpleWeb;
using json = nlohmann::json;

int main(int argc, const char *argv[])
{
	cout << "TRAVELER v1.0" << endl;
	cout << "=============" << endl;

	OSRMQuery osrm("/home/thomas/Downloads/koeln-regbez-latest.osrm");

	// http-server at port 8080 using 4 threads
	Server<HTTP> server(8080, 1);
	cout << "HTTP Server listening on port 8080..." << endl;

	// TSP
	// [[50.950973, 6.915481],[50.927175, 6.937453],[50.932899, 6.955290]]
	server.resource["^/tsp$"]["POST"]=[&osrm](ostream& response, shared_ptr<Server<HTTP>::Request> request)
	{
		stringstream ss;
		request->content >> ss.rdbuf();
		string content = ss.str();

		// fetch parameters
		json loc = json::parse(content);
		Coordinates coords;

		for(unsigned int i = 0; i < loc.size(); i++) {
			int lat = loc[i][0].get<double>() * COORDINATE_PRECISION;
			int lon = loc[i][1].get<double>() * COORDINATE_PRECISION;
			pair<int, int> coord(lat, lon);
			coords.push_back(coord);
		} 
		
		// TEST NETWORK
		// https://router.project-osrm.org/table?loc=50.858003798201786,7.089035511016845&loc=50.855877178964974,7.087082862854003&loc=50.85498315721184,7.091696262359619&loc=50.85155591505696,7.088091373443603&z=16
		// {"distance_table":[[0,329,477,861],[330,0,437,563],[478,437,0,665],[862,563,665,0]]}
		//json table = json::parse("[[0,329,477,861],[330,0,437,563],[478,437,0,665],[862,563,665,0]]");
		
		// query osrm
		DistanceTable distancetable = osrm.Table(coords);

		// solve tsp
		TSP tsp(distancetable);
		tsp.Anneal();

		// print result
		double bestCost = tsp.GetShortestDistance();
		cout << bestCost << endl;

		std::string s = request->path;
		response << "HTTP/1.1 200 OK\r\nContent-Length: " << s.length() << "\r\n\r\n" << s;
	};

	thread server_thread([&server]()
	{
		// start server
		server.start();
	});
	
	// wait for server to start so that the client can connect
	this_thread::sleep_for(std::chrono::seconds(1));
	server_thread.join();

	return EXIT_SUCCESS;
}