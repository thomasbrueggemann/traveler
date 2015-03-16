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
std::string OSRMQuery::Table()
{
	//RouteParameters params();
	//params->service = "table";
	return "";
}