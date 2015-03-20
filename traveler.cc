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

typedef std::vector<std::vector<float>> TSPResult;

int main(int argc, const char *argv[])
{
	cout << "TRAVELER v1.0" << endl;
	cout << "=============" << endl;

	cout << "Reading OSRM file ..." << endl;
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

		cout << request->path << endl;

		// fetch parameters
		json loc = json::parse(content);
		Coordinates coords;

		// prepare coordinate pairs for OSRM
		for(unsigned int i = 0; i < loc.size(); i++) {
			int lat = loc[i][0].get<double>() * COORDINATE_PRECISION;
			int lon = loc[i][1].get<double>() * COORDINATE_PRECISION;
			pair<int, int> coord(lat, lon);
			coords.push_back(coord);
		} 
		
		// query OSRM
		DistanceTable distancetable = osrm.Table(coords);

		// solve tsp
		TSP tsp(distancetable);
		tsp.Anneal();

		// prepare json result
		TSPResult resultCoordinates;
		Order resultOrder = tsp.GetCurrentOrder();
		for(int orderEntry : resultOrder)
		{
			pair<int, int> innerPair = coords[orderEntry];

			vector<float> inner;
			inner.push_back(innerPair.first / COORDINATE_PRECISION);
			inner.push_back(innerPair.second / COORDINATE_PRECISION);

			resultCoordinates.push_back(inner);
		}

		json jsonCoordinates(resultCoordinates);

		json jsonResult;
		jsonResult["cost"] = tsp.GetShortestDistance();
		jsonResult["coordinates"] = jsonCoordinates;

		string s = jsonResult.dump();
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