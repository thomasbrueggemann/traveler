#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <string>
#include <vector>

#include "edge.h"

class Edge;
class Vertex
{
private:
	std::string name;
	std::vector<Edge> edges;
public:
	Vertex();
	Vertex(std::string name, std::vector<Edge> edges);
	std::string GetName();
};

#endif