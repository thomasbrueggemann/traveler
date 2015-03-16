#ifndef OSRMQUERY_H
#define OSRMQUERY_H

#include <iostream>
#include <string>
#include <vector>

// OSRM
#include <osrm/json_container.hpp>
#include <osrm/libosrm_config.hpp>
#include <osrm/osrm.hpp>
#include <osrm/route_parameters.hpp>

typedef std::unique_ptr<OSRM> osrm_ptr;
typedef std::unique_ptr<RouteParameters> route_parameters_ptr;

namespace 
{
	template <class T, class... Types>
	std::unique_ptr<T> make_unique(Types &&... Args)
	{
		return (std::unique_ptr<T>(new T(std::forward<Types>(Args)...)));
	}
}

class OSRMQuery
{
private:
	osrm_ptr osrm;


public:
	OSRMQuery(std::string base);
	std::string Table();
};

#endif