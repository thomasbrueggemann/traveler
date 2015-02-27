#include "osrmquery.h"

// OSRM
OSRMQuery::OSRMQuery()
{
	ServerPaths paths;
	paths["base"] = "";
	OSRM o(paths, false);
	//this->osrm = std::make_shared<OSRM>(paths, false);
} 

// TABLE
std::string OSRMQuery::Table()
{
	return "";
}