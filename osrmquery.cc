#include "osrmquery.h"

// OSRM
OSRMQuery::OSRMQuery(std::string base)
{
	// config osrm server
	libosrm_config lib_config;

	lib_config.server_paths["base"] = base;
	lib_config.use_shared_memory = false;
	lib_config.max_locations_distance_table = 5000;
	
	// start osrm server
	this->osrm = make_unique<OSRM>(lib_config);
} 

// TABLE
std::string OSRMQuery::Table(coordinates coords)
{
	route_parameters_ptr params = make_unique<RouteParameters>();
	params->service = "table";

	// loop the coordinate pairs
	for(unsigned int i = 0; i < coords.size(); i++) 
	{
		params->coordinates.emplace_back(coords[i].first, coords[i].second);
	}

	// run the query
	osrm::json::Object result;
	this->osrm->RunQuery(*params, result);

	v8::Local<v8::Value> output;
	osrm::json::render(output, result);

	// turn into standard string
	v8::String::Utf8Value value(output);
	return std::string(*value);
}