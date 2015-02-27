#ifndef OSRMQUERY_H
#define OSRMQUERY_H

#include <iostream>
#include <string>
#include <vector>

// OSRM
#include <osrm/OSRM.h>
#include <osrm/RouteParameters.h>
#include <osrm/Reply.h>
#include <osrm/ServerPaths.h>

class OSRMQuery
{
private:
	std::shared_ptr<OSRM> osrm;

public:
	OSRMQuery();
	std::string Table();
};

#endif