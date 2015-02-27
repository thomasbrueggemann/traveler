#include "osrmquery.h"

// OSRM
OSRMQuery::OSRMQuery()
{
	ServerPaths paths;
	paths["base"] = "";
	this->osrm = std::make_shared<OSRM>(paths, false);
} 

// TABLE
std::string OSRMQuery::Table()
{
	return "";
}