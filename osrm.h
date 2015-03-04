#ifndef OSRMQUERY_H
#define OSRMQUERY_H

#include <iostream>
#include <string>
#include <vector>

#include "happyhttp.h"

class OSRM
{
private:
	//std::shared_ptr<OSRM> osrm;

public:
	OSRM();
	std::string Table();
};

#endif