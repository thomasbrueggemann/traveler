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
DistanceTable OSRMQuery::Table(Coordinates coords)
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

	// the table to return eventually
	DistanceTable table;

	// fetch the distance table result
	osrm::json::Array distance_table = result.values["distance_table"].get<osrm::json::Array>();
	
	// loop distance table rows
	for(osrm::json::Value row : distance_table.values)
	{
		std::vector<double> innerRow;

		// loop this row into cells
		for(osrm::json::Value cell : row.get<osrm::json::Array>().values)
		{
			double cellValue = cell.get<osrm::json::Number>().value;
			innerRow.push_back(cellValue);
		}

		table.push_back(innerRow);
	}
	
	return table;
}